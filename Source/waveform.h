#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "BasicFifo.h"
#include <string>


class WaveformComponent : public Component {

public:

	WaveformComponent(BasicFifo* fifo) : fifo(fifo) {
		setOpaque(false);
	}

	void paint(Graphics&) override;
	void resized() override;

	void setWaveformColor(Colour color) {
		this->color = color;
	}

private:
	int previousPx = 0;
	Colour color = Colours::white;
	BasicFifo* fifo;
};