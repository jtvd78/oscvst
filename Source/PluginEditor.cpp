/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <string>

//==============================================================================
Waveform2AudioProcessorEditor::Waveform2AudioProcessorEditor(Waveform2AudioProcessor& p) :
	AudioProcessorEditor(&p),
	processor(p),
	timer(this),
	waveform_l(processor.fifos[0]),
	waveform_r(processor.fifos[1]) {

	setOpaque(true);


	waveform_l.setWaveformColor(Colours::red);
	waveform_r.setWaveformColor(Colours::blue);


	slider.setRange(1, 5, 1);
	slider.addListener(this);

	addAndMakeVisible(slider);

	addAndMakeVisible(waveform_l);
	//	addAndMakeVisible(waveform_r);




		// Must be called before setSize
	setResizable(true, true);
	setResizeLimits(100, 100, 4000, 600);

	setSize(400, 300);

	// Begin repaint loop. 
	timer.startTimer(17);
}

Waveform2AudioProcessorEditor::~Waveform2AudioProcessorEditor() {}

void Waveform2AudioProcessorEditor::on_timer_fired() {
	const MessageManagerLock mmLock;
	waveform_l.repaint();
	waveform_r.repaint();
}

void Waveform2AudioProcessorEditor::sliderValueChanged(Slider * slider) {
	mult = (int)slider->getValue();
}

//==============================================================================
void Waveform2AudioProcessorEditor::paint(Graphics& g) {

	double current_time = Time::getMillisecondCounterHiRes();

	// (Our component is opaque, so we must completely fill the background with a solid colour)

	g.setColour(Colours::black);
	g.fillRect(0, 0, getWidth(), getHeight());

	DBG("Fill Time: " + std::to_string(Time::getMillisecondCounterHiRes() - current_time));
}

void Waveform2AudioProcessorEditor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	slider.setBounds(0, 0, getWidth(), 100);
	waveform_l.setBounds(0, 0, getWidth(), getHeight());
	waveform_r.setBounds(0, 0, getWidth(), getHeight());
}
