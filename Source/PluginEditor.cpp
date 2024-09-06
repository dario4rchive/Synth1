/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//=== LookAndFeel-Klasse (ehemals GUI)
class LookAndFeel : public juce::LookAndFeel_V4
{
public:
    LookAndFeel()
    {
        // Farben für ComboBoxen mit Hex-Codes setzen
        setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xB6AD90)); // Dunkelgrauer Hintergrund
        setColour(juce::ComboBox::textColourId, juce::Colour(0xFFFFFFFF)); // Weißer Text
        setColour(juce::ComboBox::arrowColourId, juce::Colour(0x582F0E)); // Oranger Pfeil
        setColour(juce::ComboBox::outlineColourId, juce::Colour(0xC2C5AA)); // Schwarzer Umriss
        setColour(juce::PopupMenu::backgroundColourId, juce::Colour(0x414833)); // Dunkelgrau für das Dropdown-Menü
        setColour(juce::PopupMenu::textColourId, juce::Colour(0xFFFFFFFF)); // Weißer Text im Dropdown-Menü
        setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour(0xFFFFA500)); // Orange für hervorgehobenen Eintrag
        setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour(0xFF000000)); // Schwarzer Text für hervorgehobenen Eintrag
    }

    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override
    {
        auto cornerSize = 5.0f;
        auto boxBounds = juce::Rectangle<float>(buttonX, buttonY, width, height).reduced(0.5f, 0.5f);

        g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
        g.fillRoundedRectangle(boxBounds, cornerSize);

        g.setColour(box.findColour(juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle(boxBounds, cornerSize, 1.0f);

        juce::Rectangle<int> arrowZone(width - 30, 0, 20, height);
        juce::Path path;
        path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
        path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
        path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

        g.setColour(box.findColour(juce::ComboBox::arrowColourId));
        g.strokePath(path, juce::PathStrokeType(2.0f));
    }
};

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor(TapSynthAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
    , osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
    , adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filterAdsr("Mod Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
    , filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
    , keyboardComponent(audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    setSize(900, 600); // Fenstergröße

    // LookAndFeel anwenden
    static LookAndFeel lookAndFeel;
    osc.setLookAndFeel(&lookAndFeel);
    adsr.setLookAndFeel(&lookAndFeel);
    filter.setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(keyboardComponent); // Keyboard wird sichtbar gemacht
}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
    // LookAndFeel-Zuordnung zurücksetzen, bevor die Klasse zerstört wird
    osc.setLookAndFeel(nullptr);
    adsr.setLookAndFeel(nullptr);
    filter.setLookAndFeel(nullptr);
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::bisque); // Hintergrundfarbe
}

//==============================================================================
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
