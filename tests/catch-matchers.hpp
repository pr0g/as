#include "catch2/catch.hpp"

#include <sstream>

#include "gsl/span"

template<typename T>
class ElementsAreSpan
    : public Catch::MatcherBase<gsl::span<const T>>
{
    gsl::span<const T> m_span;
public:
    ElementsAreSpan(const T* const t, gsl::index size)
        : m_span(t, size) {}
    explicit ElementsAreSpan(gsl::span<const T> span)
        : m_span(span) {}
    explicit ElementsAreSpan(gsl::span<T> span)
        : m_span(span) {}

    bool match(const gsl::span<const T>& span) const override {
        return m_span == span;
    }

    std::string describe() const override {
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
    gsl::index m_len;
    float m_epsilon = std::numeric_limits<float>::epsilon();
    float m_margin = 0.0f;
    Sub m_subscriptable;
public:
    ElementsAreSubscript(
        const Sub& subscriptable, const gsl::index len)
            : m_len(len), m_subscriptable(subscriptable) {}

    ElementsAreSubscript& epsilon(const float epsilon) {
        m_epsilon = epsilon;
        return *this;
    }

    ElementsAreSubscript& margin(const float margin) {
        m_margin = margin;
        return *this;
    }

    bool match(const gsl::span<const typename Sub::value_type>& span) const override {
        for (gsl::index i = 0; i < span.size(); ++i) {
            const auto approxElem {
                Approx(span[i])
                    .epsilon(m_epsilon)
                    .margin(m_margin)
            };

            if (m_subscriptable[i] != approxElem) {
                return false;
            }
        }
        return true;
    }

    std::string describe() const override {
        std::ostringstream ss;
        ss << "was expected, actual: { ";
        for (gsl::index i = 0; i < m_len; ++i) {
            ss << std::fixed << m_subscriptable[i] << ", ";
        }
        ss << "}";
        return ss.str();
    }
};

template<typename Sub>
ElementsAreSubscript<Sub> make_elements_sub(
    const Sub& subscriptable, const gsl::index len)
{
    return ElementsAreSubscript<Sub>(subscriptable, len);
}

template<typename T>
gsl::span<T> make_span(const T* pointer, const gsl::index count)
{
    return gsl::span<T>(pointer, count);
}
