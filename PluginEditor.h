#pragma once

#include "PluginProcessor.h"
// #include "JadeLookAndFeel.h"
#include "tools/PresetHandler.h"
#include "tools/MidiModPitchState.h"


#include "LaF_demo.h"

//==============================================================================
class LaF_demoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    explicit LaF_demoAudioProcessorEditor (LaF_demoAudioProcessor&);
    ~LaF_demoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // JadeLookAndFeel m_jadeLAF;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LaF_demoAudioProcessor& m_processorRef;
    PresetComponent m_presetGUI;
#if WITH_MIDIKEYBOARD    
    MidiKeyboardComponent m_keyboard;
    MidiModPitchBendStateComponent m_wheels;    
#endif
    // plugin specific components
    LaF_demoGUI m_editor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LaF_demoAudioProcessorEditor)
};
