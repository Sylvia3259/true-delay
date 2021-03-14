#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

template <class Rep, class Period>
void delay(const std::chrono::duration<Rep, Period>& delay_duration) {
	bool use_sleep = true;
	const auto start = std::chrono::high_resolution_clock::now();
	for (;;) {
		const auto time_elapsed = std::chrono::high_resolution_clock::now() - start;
		if (delay_duration <= time_elapsed) {
			return;
		}
		if (use_sleep == true) {
			const auto time_remaining = delay_duration - time_elapsed;
			if (time_remaining < 100ms) {
				use_sleep = false;
			}
			else {
				std::this_thread::sleep_for(time_remaining / 2);
			}
		}
	}
}

int main() {
	auto start = chrono::high_resolution_clock::now();

	delay(1s);

	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration<double, milli>(end - start).count();

	cout << fixed << elapsed << "ms" << endl;

	return 0;
}