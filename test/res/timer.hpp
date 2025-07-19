#ifndef TIMER_
#define TIMER_
#include <chrono>
#include <iostream>

class Timer {
public:
	using clock = std::chrono::steady_clock;

	Timer(bool autostart = false) {
		if (autostart) { start(); }
	}

	void start() {
		StartTime = clock::now();
		inProgress = true;
	}
	void stop() {
		if (inProgress) {
			EndTime = clock::now();
			inProgress = false;
		}
	}

	long long milliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(end() - StartTime).count();
	}
	long long microseconds() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(end() - StartTime).count();
	}
	long long nanoseconds() const {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end() - StartTime).count();
	}


private:
	clock::time_point StartTime;
	clock::time_point EndTime;

	bool inProgress;

	clock::time_point end() const {
		return inProgress ? clock::now() : EndTime;
	}

};

#endif

