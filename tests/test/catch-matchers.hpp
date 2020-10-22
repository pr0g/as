#include "catch2/catch.hpp"

#include <sstream>

#include "gsl/span"
#include "gsl/span_ext"

template<typename Sub1, typename Sub2>
class ElementsAreSubscript : public Catch::MatcherBase<Sub2>
{
  using value_t = typename Sub1::value_type;
  value_t m_epsilon = value_t(std::numeric_limits<float>::epsilon());
  value_t m_margin = value_t(0.0);
  Sub1 m_subscriptable;

public:
  ElementsAreSubscript(const Sub1& subscriptable)
    : m_subscriptable(subscriptable)
  {
  }

  ElementsAreSubscript& epsilon(const value_t epsilon)
  {
    m_epsilon = epsilon;
    return *this;
  }

  ElementsAreSubscript& margin(const value_t margin)
  {
    m_margin = margin;
    return *this;
  }

  bool match(const Sub2& sub2) const override
  {
    using std::size;
    for (int64_t i = 0; i < size(m_subscriptable); ++i) {
      const auto approx_elem{
        Approx(sub2[i]).epsilon(m_epsilon).margin(m_margin)};

      auto subscript = gsl::narrow_cast<ptrdiff_t>(i);
      if (m_subscriptable[subscript] != approx_elem) {
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
    for (int64_t i = 0; i < size(m_subscriptable); ++i) {
      auto subscript = gsl::narrow_cast<ptrdiff_t>(i);
      ss << std::fixed << m_subscriptable[subscript] << ", ";
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
