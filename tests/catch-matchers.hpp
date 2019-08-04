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
    : public Catch::MatcherBase<gsl::span<const typename Sub::type>>
{
    Sub m_subscriptable;
    gsl::index m_len;
public:
    ElementsAreSubscript(const Sub& subscriptable, const gsl::index len)
        : m_subscriptable(subscriptable), m_len(len) {}

    bool match(const gsl::span<const typename Sub::type>& span) const override {
        for (gsl::index i = 0; i < span.size(); ++i) {
            if (m_subscriptable[i] != span[i]) {
                return false;
            }
        }
        return true;
    }

    std::string describe() const override {
        std::ostringstream ss;
        ss << "actual, expected: { ";
        for (gsl::index i = 0; i < m_len; ++i) {
            ss << m_subscriptable[i] << ", ";
        }
        ss << "}";
        return ss.str();
    }
};
