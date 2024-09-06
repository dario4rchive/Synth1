/*
  ==============================================================================

    SynthSound.h
    Created: 2 Sep 2024 11:39:19pm
    Author:  Dario

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};