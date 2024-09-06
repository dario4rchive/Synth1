/*
  ==============================================================================

    AdsrData.h
    Created: 2 Sep 2024 11:40:29pm
    Author:  Dario

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void update(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};