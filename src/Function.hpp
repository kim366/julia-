#pragma once

#include "GenericString.hpp"

#include <julia.h>
#include <string>

namespace jl
{
class module
{

public:
    module(generic_string name_)
        : _module{reinterpret_cast<jl_module_t*>(
              jl_get_global(jl_main_module, jl_symbol(name_)))}
    {
    }

    module(module& parent_module_, generic_string name_)
        : _module{reinterpret_cast<jl_module_t*>(
              jl_get_global(parent_module_, jl_symbol(name_)))}
    {
    }

    operator jl_module_t*() { return _module; }

private:
    jl_module_t* _module;
};

class function
{
};

} // namespace jl
