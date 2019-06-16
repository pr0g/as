# as - almost something

`as` (short for _almost-something_) is an attempt at creating an easy to use header-only math library for prototype and hobby projects.

## Disclaimer

This library is really just a dumb experimental thing meant for my own personal amusement. If you're curious please do have a poke around but I would strongly advise not using it for anything serious.

Deficiencies include but are not limited to:

- The API is not stable (I'm still iterating on it)
- The test coverage is currently woefully inadequate (I'm working on improving this)
- I have used this in a few Vulkan demo projects (see [vulkan-fruit](https://twitter.com/tom_h_h/status/957656446258307073) if you're interested) and my fork of [aras_p's](https://twitter.com/aras_p) [ToyMeshPathTracer](https://github.com/pr0g/ToyMeshPathTracer) but nothing much else (yet..)
- There's bound to be bugs!
- The performance is likely not very good either (I'm working on improving this, for example creating template specializations for the common cases etc.)
- No SIMD (yet?)

## Origins

The inspriation for this project came from reading an excellent blog post by Nathan Reed ([@Reedbeta](https://twitter.com/Reedbeta)) about writing a vector math library. You can find the post titled 'On Vector Math Libraries' [here](http://www.reedbeta.com/blog/on-vector-math-libraries/) (it's well worth a read!).

The post has some interesting advice on how one might write a math library and goes into some detail about the pros and cons of various approaches.

I decided to follow the advice outlined (template heavy, parameterized on dimensions and type). This gives a high degree of flexibility at a cost of some performance and compile times.

I've tried something a bit different with the interface (which is a little unusual) but I've grown quite fond of it over time. I'll try and persuade you the approach I've taken is ~~a good idea~~ not complete stupid 🙃.

## Design

A lot of the design is informed by the article I mention in the [Origins](#origins) section but there are some things I'd like to try and explain.

### Names and Namespaces

An aim I had early on for the API was to attempt to prioritize ease of use and 'discoverability' (apologies I know that's not technically a word but it captures the intent).

As all the types I'm creating are pretty simple I decided not to hide any internal state, so all members are public. This was a design choice to make writing expressions such as `v.x += value;` easier than `v.set_x(v.get_x() + value)`. This may well be a decision I regret and I know there are downsides to this (harder to know when a value changes, you lose a bit of abstraction) but for my use case this is a trade off I'm willing to make (I've slowly learnt everything in programming is a tradeoff and nothing is perfect 😖)

All functions are implemented as free functions. I wanted to avoid using static functions because you get into problems with circular includes when static functions on oe type need a type in another file, and you'd like the API to be symmetrical.

For example if we want to be able to create a quaternion from a 3 by 3 matrix and vice versa, the api might look like this:

```c++
mat33 m = // ... build some rotation
quat q = m.to_quaternion(); // member
// or
quat q = mat33::to_quaternion(m); // static

...

quat q = // ... build some rotation
mat33 m = q.to_mat33(); // member
// or
mat33 m = quat::to_mat33(q); // static
```

The big problem with this is we get into a situation where `mat33.h` can't include `quat.h` and `quat.h` include `mat33.h` at the same time (we can get around this if we stick the implementation in the .cpp file and forward declare the type, but then we lose the ability to inline (forgetting LTO for the moment) and in doing so the ability to have a header-only library 😫).

So we're back to free functions. The lovely property about this is we can keep the `<type>.h` files pretty light (we pretty much just have the special members and overloaded operators) and all other functions can go into a separate file, which includes whatever types it likes. So we now have:

```c++
mat33 m = // ... build some rotation
quat q = to_quaternion(m); // free
```

When I first tried this, a big problem I ran into was how to logically group functions. One advantage of having static functions on a type is it's easy in most modern IDEs to type the name, hit the '`.`' operator, and see a list of available ~~methods~~ member/static functions. This advantage is really important and I wanted to try and find a way to do something similar.

I realized I could take advantage of `C++` namespaces to group functions by type. Irritatingly using the name `vec3` or `mat44` for the namespace means I lose the ability to use them as type names 😖however a workaround I decided to borrow from `C` and `C++` was to add an `_t` postfix to indicate the type itself and use the unadorned name as the namespace (I know any name ending with `_t` is technically reserved, in `C` at least, but as I'm keeping everything inside my own namespace I think I should be safe - failing that I could use `_s` instead for struct but I'm sticking with `_t` for now).

With this approach I can now do this:

```c++
mat33_t m = // ... build some rotation
quat_t q = mat33::to_quaternion(m); // free
```

When you type `mat33::` in an IDE you'll get the list of all operations supported for `mat33_t`. Another idea (which is perhaps more contentious) is to put all common/generic matrix operations in the `mat` namespace, and specific operations (like `rotation_xyz`) in the `mat33` namespace. This might actually hinder discoverabilty in certain cases but I like the preciseness of the grouping so again this will remain until I've had a chance to start hating it 😉

### Specializations

The core idea of the library is to create types that are (_pretty_) generic and write all functions in terms of those generic versions. This is so in theory you could have a `vec_t<int, 10>` and ~~all~~ most of the operations you get with a friendly `vec3_t` all still work.

The reality is 99.9% of the time people just want to use `vec3_t` and `mat33_t/mat44_t`. To make these common cases more ergonomic I provide explicit (full) template specializations for the class templates `vec2/3/4_t` and `mat33/44_t`. The reason for doing this is purely for ease of use. I provide accessors for fields such as `x`, `y`, `z` and useful constructor overloads (I'll get on to function template specializations later which are done for performance reasons).

This is most commonly done by using a `union` in `C/C++`.

```c++
template<typename T> struct Vec<T, 3>
{
    union
    {
        T data[3];
        struct { T x; T y; T z; };
        Vec<T, 2> xy;
    };

    T& operator[](int i) { return data[i]; }
}
```

There are a few problems with this approach unfortunately. First is `C++` does not support an anonymous `struct`. There's a pretty good chance your compiler will support this but you might get a warning or it might not compile. The next problem with this approach is if you write to the field `data[1]` and then later read from `y`, you've `technically` invoked undefined behaviour in `C++` (type punning like this is legal in `C` but not strictly in `C++`). I was totally not aware of this until relatively recently and I have Simon Brand \(aka [@TartanLlama](https://twitter.com/tartanllama)\) to thank for pointing [this](https://twitter.com/tom_h_h/status/961273239958892544) out to me. To play devil's advocate chances are everything will work fine but there's no guarantee - you might be able to avoid it by enabling `-fno-strict-aliasing` but perhaps you're in an environment where you (or your user) can't change that.

For the record this is also technically undefined behaviour:

```c++
template<typename T>struct Vec<T, 3>
{
    T x; T y; T z;
    T& operator[](int i) { return ((&x)[i]); }
};
```

I spent a while digging into possible alternatives and eventually came across a post on [gamedev.net](https://www.gamedev.net/forums/topic/328530-c-union-question/) about this very topic. In it there's what I believe to be quite an elegant solution to the problem which is standard compliant! 😄

```c++
template<typename T> struct Vec<T, 3>
{
    T x, y, z;
    T& operator[](size_t i) { return this->*elem[i]; }
    const T& operator[](size_t i) const { return this->*elem[i]; }

private:
    static T Vec::*elem[3];
};

using vec3_t = Vec<float, 3>;

template<typename T>
T vec3_t<T>::*vec3_t<T>::elem[3] = { &vec3_t<T>::x, &vec3_t<T>::y, &vec3_t<T>::z }; // .cpp file
```

This definitely looks more complicated than the previous snippets but it isn't as bad as it looks at first glance. Essentially what's happening is we introduce 3 new member variables (`x`, `y`, `z`) for this specialization which is where the actual data is stored per instance (no surprises there!).

The first unusual bit of code to examine is the declaration of the static member `float Vec::*elem[3];`. The syntax may be unfamiliar but this is declaring an array of _member pointers_ (not just regular pointers) indicated by the `Vec::` prefix before `*elem[3]`. Because it's static we need to initialize it in the .cpp file. Here were setup each member pointer to point to the address of the member variables of the class (so `elem[0]` corresponds to the address/offset of `x` in `vec3_t`).

The last line of interest is `return this->*elem[i];` used in the `operator[]` overloads. Remember that in a normal member function there's always an implicit `this` pointer:

```c++
struct vec
{
    float x, y, z;
    float get_x()
    {
        return x; // actually return this->x;
    }
};
```

So our expression `return this->*elem[i];` is really syntactic sugar for `return this->*this->elem[i];` In this case the first `this` is the instance/object we're calling the `[]` operator on, and then we dereference the pointer to the data member for that instance. It's easier to think about if we think how we'd do this outside the class.

```c++
struct Person
{
    int age_;
};

void Example()
{
    int Person::*age_ptr = &Person::age_; // declare a member pointer to age
    Person person;
    person.*age_ptr = 30; // dereference the member pointer on an instance of Person
    printf("%d\n", person.*age_ptr);
}
```

We're doing the exact same thing but just using `this` as the object instead of a named instance like in the `Person` example.

One drawback to this approach is if you provide a full template specialization you have to put the static definitions in the .cpp file, which sort of throws a spanner in the works with creating a header-only library 😫. The good news is if you only partially specialize the class template you can put the definition of the static variables in the header and the linker won't complain 🙂This is because the definition of the static data member is itself a template. 🥳

The final approach I went for was this but hiding the `elem` magic stuff in a base class so anyone using the type `vec3_t` won't see `elem` popup in their IDE intellisense (hopefully!) 😬

```c++
template<typename T>
struct vec3_base_t
{
    T x, y, z;
    T& operator[](size_t i) { return this->*elem[i]; }
    const T& operator[](size_t i) const { return this->*elem[i]; }

private:
    static T vec3_base_t::*elem[3];
};

template<typename T>
T vec3_base_t<T>::*vec3_base_t<T>::elem[3] =
{
    &vec3_base_t<T>::x, &vec3_base_t<T>::y, &vec3_base_t<T>::z
};

template<typename T>
struct vec_t<T, 3> : internal::vec3_base_t<T>
{
    ... // constructors etc..
};

using vec3_t = vec_t<float, 3>;
```

### Row/Column Major

- todo

### Miscellaneous

- Physical design - separation of .hpp and .inl files
- Variadic templates for constructors taking arbitrary number of arguments

## Other Approaches

- [How To Write A Maths Library In 2016](http://www.codersnotes.com/notes/maths-lib-2016/)
