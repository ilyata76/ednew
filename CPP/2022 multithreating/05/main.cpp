#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx1;
std::mutex mtx2;

void print1() {
	mtx2.lock();
	mtx1.lock();
	for (int i = 0; i < 5; ++i) {
		for (int i = 0; i < 10; ++i) {
			std::cout << '@';
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	mtx1.unlock();
	mtx2.unlock();
}

void print2() {
	mtx1.lock();

	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	mtx2.lock();

	for (int i = 0; i < 5; ++i) {
		for (int i = 0; i < 10; ++i) {
			std::cout << '*';
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	mtx2.unlock();

	mtx1.unlock();
}



int main() {

	std::thread t1(print1);
	std::thread t2(print2);

	t1.join();
	t2.join();

	// DEADLOCK

	// исправляется тем, что блокировка и разблокировка мьютексов в обоих потоках
	// должна проходить в одном и том же порядке

	return 0;
}