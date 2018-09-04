#include "waveform.h"

juce::Path* make_path(std::vector<juce::Path*>& paths) {
	juce::Path* newPath = new juce::Path();
	paths.push_back(newPath);
	return newPath;
}

void WaveformComponent::paint(Graphics& g) {

	double current_time = Time::getMillisecondCounterHiRes();

	g.setColour(color);


	int num_samples = fifo->numSamples();
	int start1, size1, start2, size2;
	fifo->fifo.prepareToRead(num_samples, start1, size1, start2, size2);

	//Path

	std::vector<juce::Path*> paths;
	juce::Path* path = make_path(paths);

	int pxCtr = previousPx;
	int half_height = getHeight() / 2;

	bool current_path_empty = true;

	for (int i = 0; i < size1; i += 1) {
		float sample = fifo->data[start1 + i];

		if (current_path_empty) {
			path->startNewSubPath(pxCtr, sample * half_height + half_height);
			current_path_empty = false;
		} else {
			path->lineTo(pxCtr, sample * half_height + half_height);
		}

		pxCtr++;

		if (pxCtr >= getWidth()) {
			pxCtr = 0;
			path = make_path(paths);
			current_path_empty = true;
		}
	}

	g.drawLine(pxCtr, 0, pxCtr, getHeight(), 1);

	for (int i = 0; i < size2; i += 1) {
		float sample = fifo->data[start2 + i];

		if (current_path_empty) {
			path->startNewSubPath(pxCtr, sample * half_height + half_height);
			current_path_empty = false;
		} else {
			path->lineTo(pxCtr, sample * half_height + half_height);
		}

		pxCtr++;

		if (pxCtr >= getWidth()) {
			pxCtr = 0;
			path = make_path(paths);
			current_path_empty = true;
		}
	}

	g.drawLine(pxCtr, 0, pxCtr, getHeight(), 1);

	fifo->fifo.finishedRead(num_samples);

	juce::PathStrokeType stroke_type(2.0f);
	for (int i = 0; i < paths.size(); i++) {
		g.strokePath(*paths[i], stroke_type);
		delete paths[i];
	}

	previousPx = pxCtr;

	DBG("Repaint Time: " + std::to_string(Time::getMillisecondCounterHiRes() - current_time));
}

void WaveformComponent::resized() {

}