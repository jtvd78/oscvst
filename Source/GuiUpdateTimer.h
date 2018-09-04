#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TimerCallback {

public:
	virtual void on_timer_fired() = 0;
};

class GuiUpdateTimer : public HighResolutionTimer {

public:
	GuiUpdateTimer(TimerCallback* callback) : callback(callback) {}

private:
	TimerCallback* callback;

	void hiResTimerCallback() override {
		callback->on_timer_fired();
	}
};
