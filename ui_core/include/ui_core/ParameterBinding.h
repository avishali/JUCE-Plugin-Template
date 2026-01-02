#pragma once

#include "ControlId.h"
#include <functional>

namespace ui_core
{

struct ParameterBinding
{
    ControlId controlId{};
    std::function<void(float)> setNormalized;
    std::function<float()> getNormalized;

    void set (float v)
    {
        if (setNormalized)
            setNormalized (v);
    }

    float get() const
    {
        return getNormalized ? getNormalized() : 0.0f;
    }
};

inline ParameterBinding makeBinding (ControlId id,
                                     std::function<float()> getter,
                                     std::function<void(float)> setter)
{
    ParameterBinding binding;
    binding.controlId = id;
    binding.getNormalized = std::move (getter);
    binding.setNormalized = std::move (setter);
    return binding;
}

}
