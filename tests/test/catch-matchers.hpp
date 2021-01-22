#include "catch2/catch_all.hpp"

#include <sstream>

#include "gsl/span"
#include "gsl/span_ext"

template<typename Sub1, typename Sub2>
class ElementsAreSubscript : public Catch::Matchers::MatcherBase<Sub2>
{
  using value_t = typename Sub1::value_type;
  value_t epsilon_ = value_t(std::numeric_limits<float>::epsilon());
  value_t margin_ = value_t(0.0);
  Sub1 subscriptable1_;

public:
  ElementsAreSubscript(const Sub1& subscriptable)
    : subscriptable1_(subscriptable)
  {
  }

  ElementsAreSubscript& epsilon(const value_t epsilon)
  {
    epsilon_ = epsilon;
    return *this;
  }

  ElementsAreSubscript& margin(const value_t margin)
  {
    margin_ = margin;
    return *this;
  }

  bool match(const Sub2& subscriptable2) const override
  {
    using std::size;
    for (decltype(size(subscriptable2)) i = 0; i < size(subscriptable2); ++i) {
      const auto approx_elem{
        Catch::Approx(subscriptable2[i]).epsilon(epsilon_).margin(margin_)};
      auto subscript = gsl::narrow_cast<decltype(size(subscriptable1_))>(i);
      if (subscriptable1_[subscript] != approx_elem) {
        return false;
      }
    }

    return true;
  }

  [[nodiscard]] std::string describe() const override
  {
    std::ostringstream ss;
    ss << "was expected, actual: { ";

    using std::size;
    for (int64_t i = 0; i < size(subscriptable1_); ++i) {
      auto subscript = gsl::narrow_cast<ptrdiff_t>(i);
      ss << std::fixed << subscriptable1_[subscript] << ", ";
    }

    ss << "}";
    return ss.str();
  }
};

template<typename Sub>
ElementsAreSubscript<Sub, Sub> elements_are(const Sub& subscriptable)
{
  return ElementsAreSubscript<Sub, Sub>(subscriptable);
}

template<typename Sub>
ElementsAreSubscript<Sub, std::array<typename Sub::value_type, Sub::size()>>
elements_are_array(const Sub& subscriptable)
{
  return ElementsAreSubscript<
    Sub, std::array<typename Sub::value_type, Sub::size()>>(subscriptable);
}

template<typename Sub>
ElementsAreSubscript<Sub, gsl::span<const typename Sub::value_type>>
elements_are_span(const Sub& subscriptable)
{
  return ElementsAreSubscript<Sub, gsl::span<const typename Sub::value_type>>(
    subscriptable);
}
