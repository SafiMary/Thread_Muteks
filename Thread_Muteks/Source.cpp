
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <optional>

class Logger {
public:

	//thread safety 
	void log(const std::string& message) {
		std::lock_guard<std::recursive_mutex> lock(_rmutex); // мутекс для класса. только один мутекс блокирует
		//std::scoped_lock s_lock (_mutex,_mutex2);//подсчитывает сколько мутекс заблокировал
		std::cout << "[" << _messageCounter << "]" << message << "\n";
		//race condition - состояние гонки
		successMessage();
	}

	void successMessage() {
		std::lock_guard lock(_rmutex);
		std::cout << "message" << std::endl;
	}
private:
	std::mutex _mutex; // объявление мьютекс
	int _messageCounter = 0;
	std::recursive_mutex _rmutex;// не дает доступа к дргуим
};


//main thread -главный поток, его нельзя блокировать
int main() {

	/*Logger logger;
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

	t1.join(), t2.join();
*/

	//std::optional<int> val;
	std::optional<int> val = std::nullopt;
	val = 5;
	if (val.has_value()) {
		std::cout << "val  has value" << std::endl;
	}
	else {
		std::cout << "no " << std::endl;
	}
	//std::cout << val.value() << std::endl;




	return 0;
}