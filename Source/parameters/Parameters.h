// This class defines the canonical parameter pattern for all plugins using this template.

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <atomic>

//==============================================================================
/**
    Simple parameter container without APVTS.
    Owns plugin parameters with thread-safe access.
*/
class Parameters
{
public:
    Parameters();
    ~Parameters() = default;

    //==============================================================================
    float getGain() const noexcept;
    void setGain (float newGain) noexcept;

    //==============================================================================
    void getState (juce::ValueTree& state) const;
    void setState (const juce::ValueTree& state);

private:
    std::atomic<float> gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Parameters)
};
