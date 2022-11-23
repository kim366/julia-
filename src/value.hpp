#pragma once

#include "boxing.hpp"
#include "init.hpp"

#include <julia/julia.h>
#include <utility>

namespace jl
{

class value;

template<typename T>
T value_cast(value&& val);

template<typename T>
T value_cast(const value& val);

class value
{
private:
    jl_value_t* raw_;

public:
    template<typename T>
    value(const T& val);

    value(const value& other);
    value& operator=(const value& other);

    value(value&& other);
    value& operator=(value&& other) noexcept;

    ~value();

    jl_value_t *raw() const;
    static value from_raw(jl_value_t* val);

private:
    explicit value(jl_value_t* raw);
};

template<typename T>
T value_cast(value&& val)
{
    return value_cast<T>(val);
}

template<typename T>
T value_cast(const value& val)
{
    return jl::impl::unbox<T>(val.raw());
}

value::value(jl_value_t* raw)
    : raw_{raw}
{
    impl::root_value(raw_);
}

template<typename T>
value::value(const T& val)
    : value{impl::box(val)}
{
}

value::value(const value& other)
    : value{other.raw_}
{
}

value& value::operator=(const value& other)
{
    auto tmp = other;
    std::swap(tmp.raw_, raw_);
    return *this;
}

value::value(value&& other)
    : raw_{nullptr}
{
    std::swap(other.raw_, raw_);
}

value& value::operator=(value&& other) noexcept
{
    std::swap(other.raw_, raw_);
    return *this;
}

value::~value()
{
    if (raw_)
        impl::release_value(raw_);
}

value value::from_raw(jl_value_t* val)
{
    return value{val};
}

jl_value_t* value::raw() const
{
    return raw_;
}

} // namespace jl