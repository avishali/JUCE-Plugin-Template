#include "Parameters.h"

//==============================================================================
Parameters::Parameters()
    : gain (1.0f)
{
}

float Parameters::getGain() const noexcept
{
    return gain.load();
}

void Parameters::setGain (float newGain) noexcept
{
    // Canonical parameter boundary:
    // All incoming values (UI, hardware, automation, modulation)
    // are clamped here and nowhere else.
    gain.store (juce::jlimit (0.0f, 2.0f, newGain));
}

void Parameters::getState (juce::ValueTree& state) const
{
    state.setProperty ("gain", getGain(), nullptr);
}

void Parameters::setState (const juce::ValueTree& state)
{
    setGain (static_cast<float> (state.getProperty ("gain", 1.0)));
}
