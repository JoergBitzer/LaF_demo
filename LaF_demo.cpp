#include <math.h>
#include "LaF_demo.h"

#include "PluginProcessor.h"

LaF_demoAudio::LaF_demoAudio(LaF_demoAudioProcessor* processor)
:SynchronBlockProcessor(), m_processor(processor)
{
}

void LaF_demoAudio::prepareToPlay(double sampleRate, int max_samplesPerBlock, int max_channels)
{
    juce::ignoreUnused(max_samplesPerBlock,max_channels);
    int synchronblocksize;
    synchronblocksize = static_cast<int>(round(g_desired_blocksize_ms * sampleRate * 0.001)); // 0.001 to transform ms to seconds;
    if (g_forcePowerOf2)
    {
        int nextpowerof2 = int(log2(synchronblocksize))+1;
        synchronblocksize = int(pow(2,nextpowerof2));
    }
    prepareSynchronProcessing(max_channels,synchronblocksize);
    m_Latency += synchronblocksize;
    // here your code

}

int LaF_demoAudio::processSynchronBlock(juce::AudioBuffer<float> & buffer, juce::MidiBuffer &midiMessages, int NrOfBlocksSinceLastProcessBlock)
{
    juce::ignoreUnused(buffer, midiMessages, NrOfBlocksSinceLastProcessBlock);
    return 0;
}

void LaF_demoAudio::addParameter(std::vector<std::unique_ptr<juce::RangedAudioParameter>> &paramVector)
{
    // this is just a placeholder (necessary for compiling/testing the template)
    paramVector.push_back(std::make_unique<AudioParameterFloat>(g_paramExample.ID,
        g_paramExample.name,
        NormalisableRange<float>(g_paramExample.minValue, g_paramExample.maxValue),
        g_paramExample.defaultValue,
        AudioParameterFloatAttributes().withLabel (g_paramExample.unitName)
                                        .withCategory (juce::AudioProcessorParameter::genericParameter)
                                        // or two additional lines with lambdas to convert data for display
                                        // .withStringFromValueFunction (std::move ([](float value, int MaxLen) { value = int(exp(value) * 10) * 0.1f;  return (String(value, MaxLen) + " Hz"); }))
                                        // .withValueFromStringFunction (std::move ([](const String& text) {return text.getFloatValue(); }))
                        ));

}

void LaF_demoAudio::prepareParameter(std::unique_ptr<juce::AudioProcessorValueTreeState> &vts)
{
    juce::ignoreUnused(vts);
}


LaF_demoGUI::LaF_demoGUI(LaF_demoAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
:m_processor(p) ,m_apvts(apvts)
{
    setLookAndFeel(&m_laf1);

    m_slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(m_slider);
    m_slider.setLookAndFeel(&m_laf2);
    
}

void LaF_demoGUI::paint(juce::Graphics &g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (12.0f);
    
    juce::String text2display = "LaF_demo V " + juce::String(PLUGIN_VERSION_MAJOR) + "." + juce::String(PLUGIN_VERSION_MINOR) + "." + juce::String(PLUGIN_VERSION_PATCH);
    g.drawFittedText (text2display, getLocalBounds(), juce::Justification::bottomLeft, 1);

}

void LaF_demoGUI::resized()
{
	auto r = getLocalBounds();
    
    // if you have to place several components, use scaleFactor
    //int width = r.getWidth();
	//float scaleFactor = float(width)/g_minGuiSize_x;

    // use the given canvas in r
    m_slider.setBounds(10,10,80,80);
}
