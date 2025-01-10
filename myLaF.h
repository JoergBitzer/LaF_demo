#pragma once

// define your own colors
#include <juce_gui_basics/juce_gui_basics.h>

const auto JadeWhite(juce::Colour::fromFloatRGBA(0.95, 0.95, 0.95, 1.0));
const auto JadeRed(juce::Colour::fromFloatRGBA(0.890196078431373, 0.023529411764706, 0.074509803921569, 1.0));

class LaF1 : public juce::LookAndFeel_V4
{
public:
    LaF1()
    {
        setColour(juce::ResizableWindow::backgroundColourId, JadeWhite);
        setColour(juce::Slider::backgroundColourId, JadeWhite.darker(0.5));
        //setDefaultLookAndFeel(this);
    }
};

class LaF2 : public juce::LookAndFeel_V4
{
public:
    LaF2()
    {
        setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::darkgrey);
        setColour(juce::Slider::backgroundColourId, juce::Colours::darkgrey.brighter(0.5));
        
        //setDefaultLookAndFeel(this);
    }
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, 
    float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
    {
        g.fillAll(findColour(juce::Slider::backgroundColourId));
        juce::ignoreUnused(slider);
        auto radius = juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = 2.0f * radius;
        auto angle = rotaryStartAngle + (rotaryEndAngle - rotaryStartAngle) * sliderPos;

        // fill
        g.setColour(juce::Colours::goldenrod);
        g.fillEllipse(rx, ry, rw, rw);

        // Point
        int PointSize = juce::jmax(width / 6, 10);
        juce::Path p;
        p.addEllipse(-PointSize / 2, -0.95 * radius, PointSize, PointSize);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        g.setColour(juce::Colours::darkmagenta);
        g.fillPath(p);
        
    }
    
};
