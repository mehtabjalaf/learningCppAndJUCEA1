/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A1StarterAudioProcessor::A1StarterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

A1StarterAudioProcessor::~A1StarterAudioProcessor()
{
}

//==============================================================================
const juce::String A1StarterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool A1StarterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool A1StarterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool A1StarterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double A1StarterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int A1StarterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int A1StarterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void A1StarterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String A1StarterAudioProcessor::getProgramName (int index)
{
    return {};
}

void A1StarterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void A1StarterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    notes.clear();                          // [1] clearning every set of nodes before processing
    currentNote = 0;                        // [2]
    lastNoteValue = -1;                     // [3]
    time = 0;                               // [4]
    rate = static_cast<float> (sampleRate); // [5] we need to get the sample rate to be able to modify it
    arpSpeed = 0.5; // this is the default speed tht is on the slider gui
    arpDescSpeed = 0.5; // try to use the same variable
    std::cout << arpSpeed; /* shift left operator in c++, similar to doing *2 but double check
                             also in our case since this is being used as standard output its
                             constructor gets overloaded everytime - becomes an extractor
                            
                            
                            this is us taking the slider value
                            */
    octaveValue = 1;
}

void A1StarterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A1StarterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void A1StarterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
 
    // We use the audio buffer to get timing information
    auto numSamples = buffer.getNumSamples();                                                   // [7]

    // get note duration
    auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (arpSpeed)))));   // [8] arpSpeed is the slider value
                        /* the static_cast<int> is just like doing (int) infront of something in java
                         in this case it is going to take that int from std::ceil and cast it to an int defined as 
                         noteDuration
                         
                         what is the auto keyword???
                         
                         it deducts the type from the RHS of = sign and assigns it to noteDuration
                         
                         so in our case noteDuration becomes an int
                         
                         
                                                    (rate * 0.25f * (0.1f + (1.0f - (arpSpeed))
                         
                         
                         he said there are "magic numbers" here and hes right i have no idea what they do
                         but one thing i did understand is that this varibale is what is telling us
                         
                         " every so time periods you should be creating a midi event "
                         
                         
                         notes:
                         
                            - we are using the noteDuration to comare current time and return another time value
                                for now I am going to assume this is for the MIDI
                            -
                         
                         */
    
    /*
     
     std::ceil?????
     
     ok but what is " :: " ?
     
     ok first of all we use the :: to access a member from a namespace OR class
     it is called the "scope resolution operator"
     
     you can kind of compare it to dot notation but dont get it confused, dot notation we use to
     access members of an object (think back to java, this DOT, this DOT, the things (var, func, methd, etc.,)
     the dots linked too a part of code within an object.
     
     here in c++ we can just have name spaces and have things like this:
     
     nameSpace::x
     
     where we are accessing it like this:
     
                                 namespace nameSpace {
                                    int x = 1;
                                 }
                                 
                                 int main () {
                                    cout << nameSpace::x // this is how u System.out.print() in c++
                                 }
                                 
     
     ... so back to std::ceil
     
     ceil is a FUNCTION NOT A METHOD
     
     method can access private variables vs function needs to use getter to get variables, different incapsulation
     
     ceil is just ceiling and when given a decimal (double, float, ...)  it just rounds it up to the nearest BIGGEST int
     
     once understanding the :: operator this was obvious lol
     
     
     */
    
    
    
    // tells us how many time periods to be creating midi event

    for (const auto metadata : midi) 
    /* the midi is defined in the params of the process block, it is the midibuffer taken from a juce function and using & we can access this midi vars using the midi reference the : is the loop so the metadata var is looping tru midi
     */    // [9]
    {
        const auto msg = metadata.getMessage(); 
        /* the metadata.Message is the element that we get looping through the midi container
         and we store it in an auto constant called message (what ever type getMessage returns,
         msg will be of that type.
         */

        if      (msg.isNoteOn())  notes.add (msg.getNoteNumber()); // using a function we check the keystroke and assign that key to the msg constant
        else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber()); // remove from the msg constant when let go
    }

    
    
    /*
     I think from // [10] to // [15] i will have to store in one block of code as "assending apprigiator"
     then create my descending one and that will be another block of code.
     
     then i can have some sort of condition where if the checkbox is checked for asscending or descending then
     based on that value I can select what code to run.
     */
    
    
    midi.clear();                                                                                   // [10]

    if ((time /* time is a variable we created in the PluginProcessor . h file */ + numSamples) >= noteDuration)  // [11]
    { /* recall that numSamples we get from a function and it just tells us the current # of samples, noteDuration you already know (derived from slider value)*/
        auto offset = juce::jmax (0, juce::jmin ((int) (noteDuration - time), numSamples - 1));     // [12]
        /* jmax is a function that returns the larger of 2 ints
           so in this case we are comparing (0 , and...
         
                jmin (smaller of two ints) which are:
                    " (int) (noteDuration - time) // i think the (int) is for strong casting
                    and numSamples - 1 "
        */
        if (lastNoteValue > 0)                                                                      // [13]
        {
            midi.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue /* we created this in PluginProcessor.h */), offset);
            
            /*
             
             addEvent takes 2 params: the midimsg buffer (the &midi we stored) and the sample number
                                      the sample number here is (offset) which we created above
                                      and the midibuffer we are passing uses noteOff to send it
                                      noteOff takes channel (1) and note number, which is (lastNoteValue)
             
    
             the noteOff is so when we are using the approgiator, we need to turn off the previous note before starting the next note, so this is how we do it if lastNoteValue is 0 meaning that no note is pressed
             */
            
            
            
            lastNoteValue = -1; // sets this value to -1 meaning no notes left to approgiate
        }
        
        /*
         ^
         ^
         ^
                THESE TWO IF STATEMENTS ARE WHERE WERE ARE CREATING MIDI EVENTS!!!!!
         v
         v
         v
         */
        

        if (notes.size() > 0) /* this is the code that is doing the apprigiation */  // [14]
        {
            int totalNumberOfNotes = notes.size() * octaveValue; // Handling multiple octaves

                // Determine the current note index based on direction and pattern choice
                if (arpDirectionChoice == 1)  // Ascending
                {
                    currentNote = (currentNote + 1) % totalNumberOfNotes;
                }else if (arpDirectionChoice == 2)  // Descending
                {
                    currentNote = (currentNote - 1 + totalNumberOfNotes) % totalNumberOfNotes;
                }

                if (otherPatternChoice == 1)  // Custom pattern:
                {
                    std::vector<int> customPattern = {0, 2, 1};
                    patternIndex = currentNote % customPattern.size();
                    baseNoteIndex = customPattern[patternIndex]; // Custom note index based on pattern
                } else if (otherPatternChoice == 2)  // Repeated pattern
                {
                    std::vector<int> repeatPattern = {0, 1, 0, 2};
                    patternIndex = currentNote % repeatPattern.size();
                    baseNoteIndex = repeatPattern[patternIndex]; // Repeated note index
                } else // Default case, no pattern choice
                {
                    baseNoteIndex = currentNote % notes.size();
                }

                // Calculate octave shift based on the number of completed octaves
                octaveShift = currentNote / notes.size();
                lastNoteValue = notes[baseNoteIndex] + (octaveShift * 12);
                // Clamp the note value to ensure it's a valid MIDI note
            
                if (lastNoteValue < 0 || lastNoteValue >= 128)
                {
                    lastNoteValue = juce::jlimit(0, 127, lastNoteValue);
                }

                std::vector<double> noteDurations;
                if (durationChoice == 1)
                {
                    noteDurations = {0.6, 0.6, 10.0}; // short short long
                } else if (durationChoice == 2)
                {
                    noteDurations = {0.6, 4.0, 10.0}; // short mid long
                } else if (durationChoice == 3)
                {
                    noteDurations = {10.0, 0.6, 4.0}; // long short mid
                }

                if (!noteDurations.empty())
                {
                    baseNoteIndex = baseNoteIndex % noteDurations.size();
                    durationFactor = noteDurations[baseNoteIndex % noteDurations.size()];
                    noteDurationInSamples = static_cast<int>(noteDuration * durationFactor);

                    std::cout << "Base Note Index: " << baseNoteIndex << " Octave Shift: " << octaveShift << " Last Note Value: " << lastNoteValue << " Duration: " << durationFactor << std::endl;
                    
                    
                    time = (time + numSamples) % noteDurationInSamples;
                } else {
                    durationFactor = 1.0f;
                }
                
                lastNoteValue = juce::jlimit(0, 127, lastNoteValue);
                midi.addEvent(juce::MidiMessage::noteOn(1, lastNoteValue, (juce::uint8)127), offset);
        }
    }
    
    
    time = (time + numSamples) % noteDuration; /* here we are adjusting at what time we add the buffer becuase we can change it via the slider */                                                     // [15]
    }


//==============================================================================
bool A1StarterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* A1StarterAudioProcessor::createEditor()
{
    return new A1StarterAudioProcessorEditor (*this);
}

//==============================================================================
void A1StarterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void A1StarterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A1StarterAudioProcessor();
}
