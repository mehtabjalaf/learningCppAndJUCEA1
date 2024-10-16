/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
 
 https://forum.juce.com/t/how-to-set-a-sliders-text-box-to-display-midi-note-numbers/43950

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class A1StarterAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener, private juce::ComboBox::Listener, private juce::TextEditor::Listener
{
public:
    A1StarterAudioProcessorEditor (A1StarterAudioProcessor&);
    ~A1StarterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox*) override; //the arpDirectionChanged was already defined
    void textEditorTextChanged(juce::TextEditor&) override;
    /* recall that these override functions need to be the same name as api */
        
private:
    void sliderValueChanged (juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A1StarterAudioProcessor& audioProcessor;

    juce::Slider arpSlider; // [1]
    juce::ComboBox arpDirection; // asscending or descending
    juce::TextEditor octaveInputBox;
    juce::ComboBox otherPatterns;
    juce::ComboBox duration;
    
    juce::Label arpSliderLabel;
    juce::Label arpDirectionLabel;
    juce::Label otherPatternsLabel;
    juce::Label durationLabel;
    juce::Label octaveLabel; // needed all these for the lables

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A1StarterAudioProcessorEditor)
};
