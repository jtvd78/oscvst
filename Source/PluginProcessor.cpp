/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <string>

//==============================================================================
Waveform2AudioProcessor::Waveform2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif

{
	fifos[0] = new BasicFifo(BUFFER_SIZE);
	fifos[1] = new BasicFifo(BUFFER_SIZE);
}

Waveform2AudioProcessor::~Waveform2AudioProcessor() {
	delete fifos[0];
	delete fifos[1];
}

//==============================================================================
const String Waveform2AudioProcessor::getName() const {
	return JucePlugin_Name;
}

bool Waveform2AudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool Waveform2AudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool Waveform2AudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double Waveform2AudioProcessor::getTailLengthSeconds() const {
	return 0.0;
}

int Waveform2AudioProcessor::getNumPrograms() {
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int Waveform2AudioProcessor::getCurrentProgram() {
	return 0;
}

void Waveform2AudioProcessor::setCurrentProgram(int index) {
}

const String Waveform2AudioProcessor::getProgramName(int index) {
	return {};
}

void Waveform2AudioProcessor::changeProgramName(int index, const String& newName) {
}

//==============================================================================
void Waveform2AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void Waveform2AudioProcessor::releaseResources() {
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Waveform2AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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


void Waveform2AudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// Write audio data to buffer. 
	fifos[0]->write(buffer, 0);
	fifos[1]->write(buffer, 1);
}

bool Waveform2AudioProcessor::hasEditor() const {
	return true;
}

AudioProcessorEditor* Waveform2AudioProcessor::createEditor() {
	return new Waveform2AudioProcessorEditor(*this);
}

//==============================================================================
void Waveform2AudioProcessor::getStateInformation(MemoryBlock& destData) {
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void Waveform2AudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

// "Main" function. Create a new instance of the plugin. 
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
	return new Waveform2AudioProcessor();
}
