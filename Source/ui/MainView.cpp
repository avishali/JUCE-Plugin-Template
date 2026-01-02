#include "MainView.h"

static constexpr ui_core::ControlId kGainControlId = 1001;

//==============================================================================
MainView::MainView (PluginTemplateAudioProcessor& p)
    : audioProcessor (p)
{
    setWantsKeyboardFocus (true);

    // Gain Label
    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, false);
    gainLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (gainLabel);

    // Gain Slider
    gainSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider.setRange (0.0, 2.0, 0.01);
    gainSlider.setValue (audioProcessor.getParameters().getGain());
    gainSlider.onValueChange = [this] { gainSliderChanged(); };
    gainSlider.onDragStart = [this] { focusManager.setFocusedControl (kGainControlId); };
    addAndMakeVisible (gainSlider);

    // Setup focus adapter
    gainFocusAdapter.flag = &gainFocused;
    gainFocusAdapter.repaintTarget = this;
    focusManager.registerWidget (kGainControlId, &gainFocusAdapter);

    // Add binding to registry
    bindingRegistry.add (ui_core::makeBinding (
        kGainControlId,
        [this]() { return audioProcessor.getParameters().getGain(); },
        [this](float v)
        {
            audioProcessor.getParameters().setGain (v);
            // keep UI in sync without recursion
            gainSlider.setValue (v, juce::dontSendNotification);
        }));

    setSize (400, 300);
}

MainView::~MainView()
{
    focusManager.unregisterWidget (kGainControlId, &gainFocusAdapter);
}

void MainView::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    if (gainFocused)
    {
        auto focusBounds = gainSlider.getBounds().expanded (4);
        g.setColour (juce::Colours::white.withAlpha (0.25f));
        g.drawRoundedRectangle (focusBounds.toFloat(), 12.0f, 2.0f);
    }
}

void MainView::resized()
{
    auto area = getLocalBounds().reduced (20);
    gainSlider.setBounds (area.removeFromTop (200).withSizeKeepingCentre (150, 150));
}

void MainView::gainSliderChanged()
{
    audioProcessor.getParameters().setGain (static_cast<float> (gainSlider.getValue()));
}

bool MainView::keyPressed (const juce::KeyPress& key)
{
    auto ch = key.getTextCharacter();
    if (ch == 'h' || ch == 'H')
    {
        if (auto* b = bindingRegistry.find (kGainControlId))
        {
            b->set (0.75f);
            DBG ("Gain set via binding registry");
        }
        return true;
    }
    return false;
}
