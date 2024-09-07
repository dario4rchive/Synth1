/*
  ==============================================================================

    PluginEditor.h
    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"
#include "FilterComponent.h"

//==============================================================================
// LookAndFeel Klasse für benutzerdefinierte Farben und Stile
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        // Setze benutzerdefinierte Farben für Slider und andere Elemente
        setColour(juce::Slider::thumbColourId, juce::Colour(0xFF656D4A));
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFFC2C5AA));
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF333D29));
        // Farben für ComboBoxen
        setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xFF414833));
        setColour(juce::ComboBox::textColourId, juce::Colour(0xFFFFFFFF));
        setColour(juce::ComboBox::arrowColourId, juce::Colour(0xFFFFFFFF));
        setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFFFFFFFF));
        setColour(juce::PopupMenu::backgroundColourId, juce::Colour(0xFF414833));
        setColour(juce::PopupMenu::textColourId, juce::Colour(0xFFFFFFFF));
        setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour(0xFFFFFFFF));
        setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour(0xFF333D29));
    }
};

//==============================================================================
// TapSynthAudioProcessorEditor Klasse
class TapSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    TapSynthAudioProcessorEditor(TapSynthAudioProcessor&);
    ~TapSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    TapSynthAudioProcessor& audioProcessor;

    // Erstelle Instanzen der Komponenten
    OscComponent osc;
    AdsrComponent adsr;
    AdsrComponent filterAdsr;
    FilterComponent filter;

    // Midi-Keyboard-Komponente
    juce::MidiKeyboardComponent keyboardComponent;

    // LookAndFeel-Instanz für benutzerdefinierte Stile
    CustomLookAndFeel customLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TapSynthAudioProcessorEditor)
};
