# as - almost something

`as` (short for _almost-something_) is an attempt at creating an easy to use header-only math library for prototype and hobby projects.

## Disclaimer

This library is really just a dumb experimental thing meant for my own personal amusement. If you're curious please do have a poke around but I would strongly advise not using it for anything serious.

Deficiencies include but are not limited to:

- The API is not stable (I'm still iterating on it)
- The test coverage is currently woefully inadequate (I'm working on improving this)
- I have used this in a few projects (see [vulkan-fruit](https://twitter.com/tom_h_h/status/957656446258307073)) and my fork of Aras Pranckevičius' \([aras_p's](https://twitter.com/aras_p)\) [ToyMeshPathTracer](https://github.com/pr0g/ToyMeshPathTracer), but nothing much else (yet..)
- There's bound to be bugs!
- The performance is likely not very good either (I'm working on improving this, for example creating template specializations for the common cases etc.)
- No SIMD (yet? we'll see... 🤔)
- I've probably made some horrible mistake somewhere which I'll be terribly embarassed about once brought to my attention.

## Origins

The inspriation for this project came from reading an excellent blog post by Nathan Reed ([@Reedbeta](https://twitter.com/Reedbeta)) about writing a vector math library. You can find the post titled 'On Vector Math Libraries' [here](http://www.reedbeta.com/blog/on-vector-math-libraries/) (it's well worth a read!).

The post has some interesting advice on how one might write a math library and goes into some detail about the pros and cons of various approaches.

I decided to follow the advice outlined (template heavy, parameterized on dimensions and type). This gives a high degree of flexibility at a cost of some performance and compile time.

I've tried something a bit different with the interface (which is a little unusual) but I've grown quite fond of it over time. I'll try and persuade you the approach I've taken is ~~a good idea~~ not completely stupid 🙃.

## Design

A lot of the design is informed by the article I mention in the [Origins](#origins) section (maybe read that first?) but there are some things I'd like to try and explain.

### Names and Namespaces

An aim I had early on for the API was to attempt to prioritize ease of use and 'discoverability' (apologies I know that's not technically a word but it captures the intent).

As all the types I'm creating are pretty simple I decided not to hide any internal state, so all members are public. This was a design choice to make writing expressions such as `v.x += value;` easier than `v.set_x(v.get_x() + value)`. This may well be a decision I regret and I know there are downsides to this (harder to know when a value changes, you lose a bit of abstraction) but for my use case this is a trade off I'm willing to make (I've slowly learnt everything in programming is a tradeoff and nothing is perfect 😖)

All functions are implemented as free functions. I wanted to avoid using static functions because you get into problems with circular dependencies, for example when static functions on one type need to include a type in another file and you'd like the API to be symmetrical.

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

The big problem with this is we get into a situation where `mat33.h` can't include `quat.h` and `quat.h` can't include `mat33.h` at the same time (we can get around this if we stick the implementation in a .cpp file and forward declare the type, but then we lose the ability to inline (forgetting LTO for the moment) and in doing so the ability to have a header-only library 😫).

So we're back to free functions. The lovely property about this is we can keep the `<type>.h` files quite light (we pretty much just have the special members and overloaded operators there) and all other functions can go into a separate file, which includes whatever types it likes. So we now have:

```c++
mat33 m1 = // ... build some rotation
quat q1 = to_quaternion(m1); // free
quat q2 = // ... build some rotation
mat33 m2 = to_mat33(q2); // free
```

When I first tried this, a big problem I ran into was how to logically group functions. One advantage to having static functions on a type is it's easy in most modern IDEs to type the name, hit the '`.`' operator, and see a list of available ~~methods~~ member/static functions. This advantage is really important and I wanted to try and find a way to do something similar.

I realized I could take advantage of `C++` namespaces to group functions by type. Irritatingly using the name `vec3` or `mat44` for the namespace means I lose the ability to use them as type names 😖 however a workaround I decided to borrow from `C` and `C++` was to add a `_t` postfix to indicate the type itself and use the unadorned name as the namespace (I know any name ending with `_t` is technically reserved, in `C` at least, but as I'm keeping everything inside my own namespace I think I should be safe - failing that I could use `_s` instead for struct but I'm sticking with `_t` for now).

With this approach I can now do this:

```c++
mat33_t m = // ... build some rotation
quat_t q = mat33::to_quaternion(m); // free
```

When you type `mat33::` in an IDE you'll get the list of all operations supported for `mat33_t`. Another idea (which is perhaps more contentious) is to put all common/generic matrix operations in the `mat` namespace, and specific operations (like `rotation_xyz`) in the `mat33` namespace. This might actually hinder discoverabilty in certain cases but I like the preciseness of the grouping so again this will remain until I've had a chance to start hating it 😉.

### Specializations

The core idea of the library is to create types that are (_pretty_) generic and write all functions in terms of those generic versions. This is so in theory you could have a `vec_t<int, 10>` and ~~all~~ most of the operations you get with a friendly `vec3_t` all still work.

The reality is 99.9% of the time people just want to use `vec3_t` and `mat33_t/mat44_t`. To make these common cases more ergonomic, I provide explicit (full) template specializations for the class templates `vec2/3/4_t` and `mat33/44_t`. The reason for doing this is purely for ease of use. I provide accessors for fields such as `x`, `y`, `z` and useful constructor overloads (I'll get on to function template specializations later which are done for performance reasons).

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

There are a few problems with this approach unfortunately. First, `C++` does not support anonymous `struct`s. There's a pretty good chance your compiler will support this but you might get a warning or it might not compile. The next problem with this approach is if you write to the field `data[1]` and then later read from `y`, you've _technically_ invoked undefined behaviour in `C++` (type punning like this is legal in `C` but not strictly in `C++`). I was totally not aware of this until relatively recently and I have Simon Brand \(aka [@TartanLlama](https://twitter.com/tartanllama)\) to thank for pointing [this](https://twitter.com/tom_h_h/status/961273239958892544) out to me. To play devil's advocate chances are everything will work fine but there's no guarantee - you might be able to avoid it by enabling `-fno-strict-aliasing` but perhaps you're in an environment where you (or your user) can't.

For the record the following approach can also technically lead to undefined behaviour:

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

This definitely looks more complicated than the previous snippets but it isn't as bad as it looks at first glance. Essentially what's happening is we introduce 3 new member variables (`x`, `y`, `z`) for this specialization which is where the actual data is stored per instance (no surprises there).

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

The last thing to mention is the function template specializations. These were made specifically for performance reasons. It's unfortunate but the reality is the hand crafted implementations of the various functions for `vec3_t` are considerably faster than their generic counterparts. This came to my attention when using my math library for the [ToyMeshPathTracer](https://github.com/pr0g/ToyMeshPathTracer). I dropped in the `as` library in place of the existing simple `float3` type and was disappointed to see my version taking a lot longer to render the scene 😔I spent a while trying to figure out why things were so much slower (thank you Nathan Reed for your ideas and suggestions) and in the end it all seemed to come down to the code the compiler would generate for the generic versions vs the handcrafted ones. I suppose this finding does slightly negate the point of writing a generic math library in the first place but I still think having a standard interface for all types is useful (you don't fall into the trap of having a slightly lacking Vector2 type which hasn't received as much love) and you can get up and running with the generic versions and write custom specializations later only if you need to for performance reasons.

### Row/Column Major

I wanted it to be possible to use the library with either row or column vectors and not get them accidentally mixed up. Different graphics APIs use different conventions (OpenGL uses column-major and DirectX uses row-major). Now the layout in memory (as far as `C++` is concerned) is always row-major (I recommend reading [this](http://seanmiddleditch.com/matrices-handedness-pre-and-post-multiplication-row-vs-column-major-and-notations/) article by Sean Middleditch \([@stmiddleditch](https://twitter.com/stmiddleditch)\) for a great treatment of this subject).

With row-major, when a vector is transformed by a matrix, the notation is to place the vector to the left of the matrix (so you multiply reading left to right) but with column-major the notation is to place the vector being transformed to the right of the matrix (in this case you multiply reading right to left). Now under the hood the multiplication is actually exactly the same, but I make sure to only enable the right overload for `operator *` when multiplying a vector and a matrix to make sure you can't get them the wrong way round (I do this by forcing you to pick the convention you want to use before you start using the library with a `#define` - you must define either `AS_COL_MAJOR` or `AS_ROW_MAJOR`).

In the case of multiplying two matrices the multiplication order is different to account for the left-to-right or right-to-left convention when combining matrices.

Also as a random aside [this](https://www.sebastiansylvan.com/post/matrix_naming_convention/) article by Sebastian Sylvan ([@ssylvan](https://twitter.com/ssylvan)) is pure genius and well worth a read to help simplify the naming of your transforms 😎

### real_t

I decided to also provide an abstraction over `float` and `double` for the common types (`vec3_t`, `mat44_t` etc.) so you can easily switch between precisions by either defining `AS_PRECISION_FLOAT` or `AS_PRECISION_DOUBLE`. I've wrapped all the base math functions with `r` versions (e.g. `fabsr` replaces either `fabsf` if floating point precision is used or `fabs` if double precision is used).

### Miscellaneous

#### Physical design

Even though this is a header-only library I still like the separation of interface and implementation when looking at the code. To achieve this all implementation code is in `.inl` files that are included at the bottom of all the `.h` files. You should never need to include these explicitly.

## Other Approaches

There are a million other math libraries out there that are more complete, more reliable, more efficient and likely more interesting. If this has in any way piqued your interest I suggest checking out these libraries and articles.

### Libraries

- [OpenGL Mathematics (glm)](https://glm.g-truc.net/0.9.9/index.html)
- [DirectXMath](https://docs.microsoft.com/en-us/windows/desktop/dxmath/directxmath-portal)
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)
- [Tuesday](https://github.com/Cincinesh/tue)
- [HandmadeMath](https://github.com/HandmadeMath/Handmade-Math)
- [RealTimeMath](https://github.com/nfrechette/rtm)

### Articles

- [How To Write A Maths Library In 2016](http://www.codersnotes.com/notes/maths-lib-2016/)
- [On Vector Math Libraries](http://www.reedbeta.com/blog/on-vector-math-libraries/)

## Related Links

- [GameDev.net - A slick trick in c](https://www.gamedev.net/forums/topic/261920-a-slick-trick-in-c/)
