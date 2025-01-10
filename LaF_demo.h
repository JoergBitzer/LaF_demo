#pragma once

#include <vector>
#include <juce_audio_processors/juce_audio_processors.h>

#include "tools/SynchronBlockProcessor.h"
#include "PluginSettings.h"
#include "myLaF.h"

class LaF_demoAudioProcessor;

// This is how we define our parameter as globals to use it in the audio processor as well as in the editor
const struct
{
	const std::string ID = "ExampleID";
	const std::string name = "Example";
	const std::string unitName = "xyz";
	const float minValue = 1.f;
	const float maxValue = 2.f;
	const float defaultValue = 1.2f;
}g_paramExample;


class LaF_demoAudio : public SynchronBlockProcessor
{
public:
    LaF_demoAudio(LaF_demoAudioProcessor* processor);
    void prepareToPlay(double sampleRate, int max_samplesPerBlock, int max_channels);
    virtual int processSynchronBlock(juce::AudioBuffer<float>&, juce::MidiBuffer& midiMessages, int NrOfBlocksSinceLastProcessBlock);

    // parameter handling
  	void addParameter(std::vector < std::unique_ptr<juce::RangedAudioParameter>>& paramVector);
    void prepareParameter(std::unique_ptr<juce::AudioProcessorValueTreeState>&  vts);
    
    // some necessary info for the host
    int getLatency(){return m_Latency;};

private:
	LaF_demoAudioProcessor* m_processor;
    int m_Latency = 0;
};

class LaF_demoGUI : public juce::Component
{
public:
	LaF_demoGUI(LaF_demoAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts);
	~LaF_demoGUI(){setLookAndFeel(nullptr);};
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	LaF1 m_laf1;
	LaF2 m_laf2;
	LaF_demoAudioProcessor& m_processor;
    juce::AudioProcessorValueTreeState& m_apvts; 

	juce::Slider m_slider;

};
