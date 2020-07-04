#include "catch2/catch.hpp"

#include <sstream>

#include "gsl/span"
#include "gsl/span_ext"

template<typename T>
class ElementsAreSpan : public Catch::MatcherBase<gsl::span<const T>>
{
    gsl::span<const T> m_span;

public:
    ElementsAreSpan(const T* const t, size_t size) : m_span(t, size) {}
    explicit ElementsAreSpan(gsl::span<const T> span) : m_span(span) {}
    explicit ElementsAreSpan(gsl::span<T> span) : m_span(span) {}

    bool match(const gsl::span<const T>& span) const override
    {
        return m_span == span;
    }

    [[nodiscard]] std::string describe() const override
    {
        std::ostringstream ss;
        ss << "actual, expected: { ";

        for (const auto& element : m_span) {
            ss << element << ", ";
        }

        ss << "}";
        return ss.str();
    }
};

template<typename Sub>
class ElementsAreSubscript
    : public Catch::MatcherBase<gsl::span<const typename Sub::value_type>>
{
    using value_t = typename Sub::value_type;
    size_t m_len;
    value_t m_epsilon = value_t(std::numeric_limits<float>::epsilon());
    value_t m_margin = value_t(0.0);
    Sub m_subscriptable;

public:
    ElementsAreSubscript(const Sub& subscriptable, const size_t len)
        : m_len(len), m_subscriptable(subscriptable)
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

    bool match(
        const gsl::span<const typename Sub::value_type>& span) const override
    {
        for (size_t i = 0; i < span.size(); ++i) {
            const auto approx_elem{
                Approx(span[i]).epsilon(m_epsilon).margin(m_margin)};

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

        for (size_t i = 0; i < m_len; ++i) {
            auto subscript = gsl::narrow_cast<ptrdiff_t>(i);
            ss << std::fixed << m_subscriptable[subscript] << ", ";
        }

        ss << "}";
        return ss.str();
    }
};

template<typename Sub>
ElementsAreSubscript<Sub> make_elements_sub(
    const Sub& subscriptable, const size_t len)
{
    return ElementsAreSubscript<Sub>(subscriptable, len);
}
