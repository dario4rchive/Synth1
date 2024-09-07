/*
  ==============================================================================

    PluginEditor.cpp
    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// Konstruktor für den Plugin-Editor
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor(TapSynthAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
    , adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filterAdsr("Mod Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
    , filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
    , keyboardComponent(audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // Setze die Fenstergröße
    setSize(900, 600); // Fenstergröße

    // Setze das benutzerdefinierte LookAndFeel
    setLookAndFeel(&customLookAndFeel);
    osc.setLookAndFeel(&customLookAndFeel);
    adsr.setLookAndFeel(&customLookAndFeel);
    filter.setLookAndFeel(&customLookAndFeel);

    // Komponenten hinzufügen
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(keyboardComponent); // Keyboard sichtbar machen
}

//==============================================================================
// Destruktor für den Plugin-Editor
TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
    // LookAndFeel-Zuordnung zurücksetzen, bevor die Klasse zerstört wird
    setLookAndFeel(nullptr);
    osc.setLookAndFeel(nullptr);
    adsr.setLookAndFeel(nullptr);
    filter.setLookAndFeel(nullptr);
}

//==============================================================================
// Paint-Methode zum Zeichnen des Hintergrunds und der anderen GUI-Komponenten
void TapSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Fülle den Hintergrund mit einer Farbe, die du anpassen möchtest
    g.fillAll(juce::Colour(0xFFfff0d6)); // Beispiel: Hintergrundfarbe "bisque"
}

//==============================================================================
// Methode zum Anordnen und Größenanpassen der GUI-Komponenten
void TapSynthAudioProcessorEditor::resized()
{
    const int componentWidth = 300;  // Breite der Komponente
    const int componentHeight = 200; // Höhe der Komponente

    // Komponenten mittig platzieren
    const int oscX = (getWidth() / 2) - componentWidth - 10; // Linke Seite des Fensters
    const int oscY = 35;
    osc.setBounds(oscX, oscY, componentWidth, componentHeight);

    const int adsrX = (getWidth() / 2) + 10; // Rechte Seite des Fensters
    const int adsrY = oscY;
    adsr.setBounds(adsrX, adsrY, componentWidth, componentHeight);

    const int filterAdsrX = (getWidth() / 2) - componentWidth - 10; // Linke Seite des Fensters
    const int filterAdsrY = oscY + componentHeight + 10;
    filterAdsr.setBounds(filterAdsrX, filterAdsrY, componentWidth, componentHeight);

    const int filterX = (getWidth() / 2) + 10; // Rechte Seite des Fensters
    const int filterY = filterAdsrY;
    filter.setBounds(filterX, filterY, componentWidth, componentHeight);

    //=== Hier wird das Keyboard positioniert
    keyboardComponent.setBounds(10, filterY + componentHeight + 20, getWidth() - 20, 100);
}
