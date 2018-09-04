#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class BasicFifo {

public:
	BasicFifo(int size) : size(size), fifo(size) {
		data = new float[size];
	}

	~BasicFifo() {
		delete data;
	}

	void write(AudioBuffer<float>& buffer, int channel) {

		int start1, size1, start2, size2;
		auto samples_to_process = buffer.getNumSamples();
		fifo.prepareToWrite(samples_to_process, start1, size1, start2, size2);

		auto space_to_write = size1 + size2;
		if (space_to_write < samples_to_process) {
			DBG("Buffer Full!");
			return;
		}

		const float* read_pointer = buffer.getReadPointer(channel);
		std::memcpy(data + start1, read_pointer, size1 * sizeof(float));
		std::memcpy(data + start2, read_pointer + size1, size2 * sizeof(float));
		fifo.finishedWrite(size1 + size2);
	}

	int numSamples() {
		return fifo.getNumReady();
	}

	float* data;
	AbstractFifo fifo;

private:

	int size;
};