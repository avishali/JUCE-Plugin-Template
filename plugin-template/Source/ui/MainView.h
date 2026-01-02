#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../PluginProcessor.h"

//==============================================================================
/**
    Main UI view component.
    Contains the plugin's user interface elements.
*/
class MainView : public juce::Component
{
public:
    explicit MainView (PluginTemplateAudioProcessor& p);
    ~MainView() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PluginTemplateAudioProcessor& audioProcessor;

    juce::Label gainLabel;
    juce::Slider gainSlider;

    void gainSliderChanged();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};
