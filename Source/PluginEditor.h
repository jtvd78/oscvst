/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once



#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"
#include "GuiUpdateTimer.h"
#include "waveform.h"

//==============================================================================
/**
*/
class Waveform2AudioProcessorEditor : public AudioProcessorEditor, TimerCallback, Slider::Listener {
public:
	Waveform2AudioProcessorEditor(Waveform2AudioProcessor&);
	~Waveform2AudioProcessorEditor();

	// Component Overrides
	void resized() override;
	void paint(Graphics&) override;

	void on_timer_fired() override;
	void sliderValueChanged(Slider* slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	Waveform2AudioProcessor& processor;

	int mult = 1;

	Slider slider;
	GuiUpdateTimer timer;
	WaveformComponent waveform_l;
	WaveformComponent waveform_r;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Waveform2AudioProcessorEditor)
};

