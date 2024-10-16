///*
//  ==============================================================================
//
//    This file contains the basic framework code for a JUCE plugin editor.
//
//  ==============================================================================
//*/
//
//#include "PluginProcessor.h"
//#include "PluginEditor.h"
//
////==============================================================================
//A1StarterAudioProcessorEditor::A1StarterAudioProcessorEditor (A1StarterAudioProcessor& p)
//    : AudioProcessorEditor (&p), audioProcessor (p)
//{
//    // Make sure that before the constructor has finished, you've set the
//    // editor's size to whatever you need it to be.
//    setSize (400, 200);
//
//    // these define the parameters of our slider object
//    arpSlider.setSliderStyle (juce::Slider::LinearBarVertical);
//    arpSlider.setRange (0.0, 1.0, 0.05);
//    arpSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
//    arpSlider.setPopupDisplayEnabled (true, false, this);
//    arpSlider.setTextValueSuffix (" Speed");
//    arpSlider.setValue(0.5);
//
//
////    arpDirection.onChange = [this] { arpDirectionChanged(); };
////    arpDirection.setSelectedId (1);
// 
//    // this function adds the slider to the editor
//    addAndMakeVisible (&arpSlider);
//    arpSlider.addListener (this);
//    
//    addAndMakeVisible (&arpDirection);
//    arpDirection.addListener(this);
//    
//    //arpDirection
//    
//    arpDirection.addItem ("Ascending",  1);
//    arpDirection.addItem ("Descending",   2);
//    arpDirection.addItem ("temp blank holder",   3);
//    
//    
//    octaveInputBox.setInputRestrictions(0, "0123456789");
//    octaveInputBox.setText("1");
//    addAndMakeVisible(&octaveInputBox);
//    octaveInputBox.addListener(this); // i always forget to do this man
//    
//    
//    addAndMakeVisible (&otherPatterns);
//    otherPatterns.addListener(this);
//    otherPatterns.addItem ("Not strictly ascending or descending",  1);
//    otherPatterns.addItem ("Repeated notes",   2);
//    otherPatterns.addItem ("temp blank",   3);
//    
//    
//    addAndMakeVisible (&duration);
//    duration.addListener(this);
//    duration.addItem("half half none", 1);
//    duration.addItem("none half none", 2);
//    duration.addItem("half none half", 3);
//    duration.addItem("temp blank", 4);
//    
//}
//
//A1StarterAudioProcessorEditor::~A1StarterAudioProcessorEditor()
//{
//}
//
////==============================================================================
//void A1StarterAudioProcessorEditor::paint (juce::Graphics& g)
//{
//   // fill the whole window white
//    g.fillAll (juce::Colours::white);
// 
//    // set the current drawing colour to black
//    g.setColour (juce::Colours::black);
// 
//    // set the font size and draw text to the screen
//    g.setFont (15.0f);
// 
//    g.drawFittedText ("Arpeggiator", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
//}
//
//void A1StarterAudioProcessorEditor::resized()
//{
//    // This is generally where you'll want to lay out the positions of any
//    // subcomponents in your editor..
//    // sets the position and size of the slider with arguments (x, y, width, height)
//    arpSlider.setBounds (40, 30, 20, getHeight() - 60);
//    arpDirection.setBounds (120, 10, getWidth() - 130, 30); // I always need this to add the component
//    octaveInputBox.setBounds(120, 45, getWidth() - 300, 20);
//    otherPatterns.setBounds (120, 70, getWidth() - 130, 30); // I always need this to add the component
//    duration.setBounds (120, 100, getWidth() - 130, 30); // I always need this to add the component
//
//
//
//}
//
//void A1StarterAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
//{
//    audioProcessor.arpSpeed = arpSlider.getValue();
//}
//
//void A1StarterAudioProcessorEditor::comboBoxChanged (juce::ComboBox* box)
//{
//    audioProcessor.arpDirectionChoice = arpDirection.getSelectedId();
//    audioProcessor.otherPatternChoice = otherPatterns.getSelectedId();
//    audioProcessor.durationChoice = duration.getSelectedId();
//}
//
//void A1StarterAudioProcessorEditor::textEditorTextChanged (juce::TextEditor& text) // error: for this method i had to use & and not *
//{
//    audioProcessor.octaveValue = octaveInputBox.getText().getIntValue();
//}
//
// 
// ignore, this was for learning and troubleshooting
//

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A1StarterAudioProcessorEditor::A1StarterAudioProcessorEditor (A1StarterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Set the size of the editor window
    setSize (500, 300);

    // Set up arpSlider
    arpSlider.setSliderStyle (juce::Slider::LinearVertical);
    arpSlider.setRange (0.0, 1.0, 0.05);
    arpSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 20);
    arpSlider.setPopupDisplayEnabled (true, false, this);
    arpSlider.setTextValueSuffix (" Speed");
    arpSlider.setValue(0.5);
    addAndMakeVisible(arpSlider);
    arpSlider.addListener(this);

    // Set up arpDirection ComboBox
    arpDirection.addItem ("Ascending", 1);
    arpDirection.addItem ("Descending", 2);
    arpDirection.addItem ("NONE", 3);
    addAndMakeVisible (arpDirection);
    arpDirection.addListener(this);

    // Set up otherPatterns ComboBox
    otherPatterns.addItem ("Not strictly ascending or descending", 1);
    otherPatterns.addItem ("Repeated notes", 2);
    otherPatterns.addItem ("NONE", 3);
    addAndMakeVisible (otherPatterns);
    otherPatterns.addListener(this);

    // Set up duration ComboBox
    duration.addItem ("SHORT SHORT LONG", 1);
    duration.addItem ("SHORT MID LONG", 2);
    duration.addItem ("LONG SHORT MID", 3);
    duration.addItem ("NONE", 4);
    addAndMakeVisible (duration);
    duration.addListener(this);

    // Set up octaveInputBox
    octaveInputBox.setInputRestrictions(0, "0123456789");
    octaveInputBox.setText("1");
    addAndMakeVisible (octaveInputBox);
    octaveInputBox.addListener(this);

    // Add labels
    arpSliderLabel.setText("Arp Speed", juce::dontSendNotification);
    addAndMakeVisible(arpSliderLabel);

    arpDirectionLabel.setText("Arp Direction", juce::dontSendNotification);
    addAndMakeVisible(arpDirectionLabel);

    otherPatternsLabel.setText("Pattern", juce::dontSendNotification);
    addAndMakeVisible(otherPatternsLabel);

    durationLabel.setText("Duration", juce::dontSendNotification);
    addAndMakeVisible(durationLabel);

    octaveLabel.setText("Octave (>0)", juce::dontSendNotification);
    addAndMakeVisible(octaveLabel);
}

A1StarterAudioProcessorEditor::~A1StarterAudioProcessorEditor() {}

//==============================================================================
void A1StarterAudioProcessorEditor::paint (juce::Graphics& g)
{
    
   g.fillAll (juce::Colours::blueviolet);

    g.setColour (juce::Colours::orange);
    g.setFont (20.0f);
    g.drawFittedText ("Mehtab's Arpeggiator Plugin", getLocalBounds(), juce::Justification::centredTop, 1);
    g.drawFittedText ("Octave Input: Please Enter a Positive Integer", getLocalBounds(), juce::Justification::centredBottom, 1);

    g.setColour (juce::Colours::darkgrey);
    g.drawRect (getLocalBounds(), 2);
}

void A1StarterAudioProcessorEditor::resized()
{
    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::column;
    flexBox.alignContent = juce::FlexBox::AlignContent::center;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::center;

    
// sets the position and size of the slider with arguments (x, y, width, height)

    arpSlider.setBounds (50, 50, 60, 180);
    arpSliderLabel.setBounds (50, 230, 60, 20);

    arpDirection.setBounds (150, 70, 200, 30);
    arpDirectionLabel.setBounds (150, 40, 200, 30);

    otherPatterns.setBounds (150, 130, 200, 30);
    otherPatternsLabel.setBounds (150, 100, 200, 30);

    duration.setBounds (150, 190, 200, 30);
    durationLabel.setBounds (150, 160, 200, 30);

    octaveInputBox.setBounds (370, 70, 50, 30);
    octaveLabel.setBounds (370, 40, 100, 30);
}

void A1StarterAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &arpSlider)
        audioProcessor.arpSpeed = arpSlider.getValue();
}

void A1StarterAudioProcessorEditor::comboBoxChanged (juce::ComboBox* box)
{
    if (box == &arpDirection)
    {
        audioProcessor.arpDirectionChoice = arpDirection.getSelectedId();
    }
    else if (box == &otherPatterns)
    {
        audioProcessor.otherPatternChoice = otherPatterns.getSelectedId();
    }
    else if (box == &duration)
    {
        audioProcessor.durationChoice = duration.getSelectedId();
    }
    
//            audioProcessor.arpDirectionChoice = arpDirection.getSelectedId();
//            audioProcessor.otherPatternChoice = otherPatterns.getSelectedId();
//            audioProcessor.durationChoice = duration.getSelectedId();

}

void A1StarterAudioProcessorEditor::textEditorTextChanged (juce::TextEditor& text)
{
    audioProcessor.octaveValue = octaveInputBox.getText().getIntValue();
}

