#pragma once

#include <julia/julia.h>
#include <stdexcept>

namespace impl
{

template<typename RetT>
RetT unbox(jl_value_t* arg_)
{
    if (jl_typeis(arg_, jl_float32_type))
        return jl_unbox_float32(arg_);
    else if (jl_typeis(arg_, jl_float64_type))
        return jl_unbox_float64(arg_);
    else if (jl_typeis(arg_, jl_int32_type))
        return jl_unbox_int32(arg_);
    else if (jl_typeis(arg_, jl_int64_type))
        return jl_unbox_int64(arg_);
    else if (jl_typeis(arg_, jl_bool_type))
        return jl_unbox_bool(arg_);

    throw std::runtime_error{
        "jl - Unexpected result type. Supported types: "
        "Float32, Float64, Int32, Int64, Bool"};
}

template<typename ArgT>
jl_value_t* box(ArgT arg_)
{
    if constexpr (std::is_same<ArgT, bool>())
        return jl_box_bool(arg_);
    else if constexpr (std::is_floating_point_v<ArgT>)
        return jl_box_float64(arg_);
    else if constexpr (std::is_integral_v<ArgT> && std::is_signed_v<ArgT>)
        return jl_box_int64(arg_);
    else if constexpr (std::is_integral_v<ArgT> && !std::is_signed_v<ArgT>)
        return jl_box_uint64(arg_);
}

} // namespace impl
