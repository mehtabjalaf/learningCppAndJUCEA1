/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.
 
    there is where we declare all variables and functions

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class A1StarterAudioProcessor  : public juce::AudioProcessor
{
public:
    float arpSpeed;
    float arpDescSpeed;
    int arpDirectionChoice;
    int otherPatternChoice;
    int durationChoice;
    int noteDurationInSamples;
    std::vector<double> noteDurations;
    float durationFactor;
    double currentNoteDuration;
    int octaveValue;
    //==============================================================================
    A1StarterAudioProcessor();
    ~A1StarterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private: // these are all the variables I am going to be using
    //==============================================================================
    int currentNote, lastNoteValue;
    int baseNoteIndex, octaveShift;
    int time;
    int patternIndex;
    float rate;
    juce::SortedSet<int> notes; // this is a certain set of integers called notes becuase we have to keep track of the notes pressed
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A1StarterAudioProcessor)
};
