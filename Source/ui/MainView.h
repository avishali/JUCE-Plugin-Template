#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../PluginProcessor.h"
#include <ui_core/UiCore.h>
#include "hardware/PluginHardwareAdapter.h"
#include <memory>

//==============================================================================
/**
    Main UI view component.
    Contains the plugin's user interface elements.
*/
class MainView : public juce::Component
{
public:
    explicit MainView (PluginTemplateAudioProcessor& p);
    ~MainView() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool keyPressed (const juce::KeyPress& key) override;

private:
    PluginTemplateAudioProcessor& audioProcessor;

    juce::Label gainLabel;
    juce::Slider gainSlider;

    ui_core::FocusManager focusManager;
    ui_core::BindingRegistry bindingRegistry;
    std::unique_ptr<PluginHardwareAdapter> hardwareAdapter;

    // Focus state for this view (only for verification now)
    bool gainFocused = false;

    // Adapter object that FocusManager can call
    struct FocusFlagAdapter : ui_core::Focusable
    {
        bool* flag = nullptr;
        juce::Component* repaintTarget = nullptr;
        void setFocused (bool focused) override
        {
            if (flag)
                *flag = focused;
            if (repaintTarget)
                repaintTarget->repaint();
        }
    };

    FocusFlagAdapter gainFocusAdapter;

    void gainSliderChanged();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};
