
#include <iostream>
#include <thread>
#include <string>
#include <mutex>

class Logger {
public:

	//thread safety 
	void log(const std::string& message) {
		std::lock_guard<std::mutex> lock(_mutex); // мюьтекс дл€ класса
		std::cout << "[" << _messageCounter << "]" << message << "\n";
		_messageCounter++;

		//race condition - состо€ние гонки
	}


private:
	std::mutex _mutex; // объ€вление мьютекс
	int _messageCounter = 0;

};






int main() {

	Logger logger;
	logger.log("Hello");
	logger.log("info message");

	std::thread t1 = std::thread([&logger]() {
		std::string threadName = "t1";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + "doing" + std::to_string(i) + "iteration of work. \n");
		}
	});

	std::thread t2 = std::thread([&logger]() {
		std::string threadName = "t2";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + "doing" + std::to_string(i) + "iteration of work. \n");
		}
});





	return 0;
}