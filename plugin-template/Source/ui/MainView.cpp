#include "MainView.h"

//==============================================================================
MainView::MainView (PluginTemplateAudioProcessor& p)
    : audioProcessor (p)
{
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
    addAndMakeVisible (gainSlider);

    setSize (400, 300);
}

void MainView::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
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
