#include <iostream>
#include <thread>
#include <chrono>


void doWork(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	std::cout << "======dowork======\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	std::cout << "a + b = " << a + b << "\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	std::cout << "======dowork END======\n";
}

int main() {

	std::thread th(doWork, 1, 6);

	for (size_t i = 0; true; ++i) {
		std::cout << "main\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	th.join();
	return 0;
}
// result:
//main
//main
//main
//main
//main
//main
//======dowork======
//main
//main
//main
//main
//main
//main
//main
//main
//main
//main
//a + b = 7
//main
//main
//main
//main
//main
//main
//======dowork END======
//main
//main
//main
//main
//main
//main
//main