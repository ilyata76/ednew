#include <iostream>
#include <thread>
#include <chrono>


int doWork(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	std::cout << "======dowork======\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	std::cout << "a + b = " << a + b << "\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	std::cout << "======dowork END======\n";

	return a + b;
}

void doWorkRef(int& a, int& b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	std::cout << "======doworkref======\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	std::cout << "a + b = " << (a = a + b) << "\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	std::cout << "======doworkref END======\n";
}

int main() {
	int result = 0; int x = 10; int y = 20;
	std::thread th1([&result]() {result = doWork(1, 6); });
	std::thread th2(doWorkRef, std::ref(x), std::ref(y));

	for (size_t i = 0; i <= 10; ++i) {
		std::cout << "main\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	th1.join(); // сначала додждаться выполнения!!!
	th2.join();

	std::cout << result;
	std::cout << x;

	return 0;
}
	// result
// 
	//main
	//main
	//main
	//main
	//main
	//main
	//======dowork======
	//======doworkref======
	//main
	//main
	//main
	//main
	//main
	//a + b = 7
	//a + b = 30
	//======dowork END======
	//======doworkref END======
	//730