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
