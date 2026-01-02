#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginTemplateAudioProcessorEditor::PluginTemplateAudioProcessorEditor (PluginTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mainView (p)
{
    addAndMakeVisible (mainView);
    setSize (400, 300);
}

PluginTemplateAudioProcessorEditor::~PluginTemplateAudioProcessorEditor()
{
}

//==============================================================================
void PluginTemplateAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PluginTemplateAudioProcessorEditor::resized()
{
    mainView.setBounds (getLocalBounds());
}
