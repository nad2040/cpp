#include <iostream>
#include <string>
#include <chrono>

class Timer {
public:
	using timing = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<double>;
	
	Timer(const std::string& blockName) : blockName_(blockName) {
		time_ = timing::now();
		std::cout << "enter " << blockName_ << std::endl;
	}
	~Timer() {
		auto t2 = timing::now();
		duration time_span = std::chrono::duration_cast<duration>(t2 - time_);
		std::cout << "leave " << blockName_ << " time taken " << time_span.count() << " secs" << std::endl;
	}
private:
	std::string blockName_;
	timing::time_point time_;
};
