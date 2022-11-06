// current < c++20


// если потоков не будет физически, то они будут выполняться поочерёдно
// => нет производительности
// но если задача тяжёлая, то в этом будет смысл

#include <iostream>
#include <thread> // работа с потоками
#include <chrono> // время

void doWork() {
	for (size_t i = 0; i < 10; ++i) { // будем эмулировать сложную долгую задачу этим циклом
		std::cout << "ID" << std::this_thread::get_id() << " \t dowork " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
	}
}


int main() {
	setlocale(LC_ALL, "ru");

	//std::cout << std::this_thread::get_id() << std::endl; // идентификатор потока
	//std::cout << "start\n";
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));  // приостанавливает действие потока на 3 секунды
	//std::cout << "endl\n";

	/*
					doWork(); // ОН БУДЕТ ВЫПОЛНЯТЬСЯ ВО ОДНОМ ПОТОКЕ
	*/

	//	ID7204   dowork 0
	//	ID7204   dowork 1
	//	ID7204   dowork 2
	//	ID7204   dowork 3
	//	ID7204   dowork 4
	//	ID7204   dowork 5
	//	ID7204   dowork 6
	//	ID7204   dowork 7
	//	ID7204   dowork 8
	//	ID7204   dowork 9
	//	ID7204   main 0
	//	ID7204   main 1
	//	ID7204   main 2
	//	ID7204   main 3
	//	ID7204   main 4
	//	ID7204   main 5
	//	ID7204   main 6
	//	ID7204   main 7
	//	ID7204   main 8
	//	ID7204   main 9

	// давайте заставим программу выполнять dowork отдельным потоком

	std::thread th(doWork); // передали указатель на функцию в отдельный поток
							// но вылетит runtime ошибка
							// а первая строчка сольётся из двух
	/*	
		ID20112          main ID7848     dowork 00

		ID20112          main 1
		ID7848   dowork 1
		ID20112          main 2
		ID20112          main 3
		ID7848   dowork 2
		ID20112          main 4
		ID7848   dowork 3
		ID20112          main 5
		ID20112          main 6
		ID7848   dowork 4
		ID20112          main 7
		ID20112          main 8
		ID7848   dowork 5
		ID20112          main 9
		ID7848   dowork 6
		ID7848   dowork 7
		ID7848   dowork 8
		ID7848   dowork 9
	*/

	// чтобы избежать ошибки нужно определить поведение объекта thread
	// detach разорвёт связь
	
	
			// th.detach();
	

	// то поток прервётся когда закончится main
	/*	ID16360          main ID12224    dowork 0
		0
		ID16360          main 1
		ID12224          dowork 1
		ID16360          main 2
		ID16360          main 3
		ID12224          dowork 2
		ID16360          main 4
		ID12224          dowork 3
		ID16360          main 5
		ID16360          main 6
		ID12224          dowork 4
		ID16360          main 7
		ID12224          dowork 5
		ID16360          main 8
		ID16360          main 9
		ID12224          dowork 6
	*/
	///th.join();
	// -> th.join(); дожидаться - выполнение будет будто синхронное
		//ID3676   dowork 0
		//ID3676   dowork 1
		//ID3676   dowork 2
		//ID3676   dowork 3
		//ID3676   dowork 4
		//ID3676   dowork 5
		//ID3676   dowork 6
		//ID3676   dowork 7
		//ID3676   dowork 8
		//ID3676   dowork 9
		//ID20908          main 0
		//ID20908          main 1
		//ID20908          main 2
		//ID20908          main 3
		//ID20908          main 4
		//ID20908          main 5
		//ID20908          main 6
		//ID20908          main 7
		//ID20908          main 8
		//ID20908          main 9




	for (size_t i = 0; i < 10; ++i) { // будем эмулировать сложную долгую задачу этим циклом
		std::cout << "ID" << std::this_thread::get_id() << " \t main " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}


	th.join(); // теперь норм

	//ID6364   main ID14100    dowork 00
	//	ID6364   main 1
	//	ID14100          dowork 1
	//	ID6364   main 2
	//	ID6364   main 3
	//	ID14100          dowork 2
	//	ID6364   main 4
	//	ID14100          dowork 3
	//	ID6364   main 5
	//	ID6364   main 6
	//	ID14100          dowork 4
	//	ID6364   main 7
	//	ID14100          dowork 5
	//	ID6364   main 8
	//	ID6364   main 9
	//	ID14100          dowork 6
	//	ID14100          dowork 7
	//	ID14100          dowork 8
	//	ID14100          dowork 9

	return 0;
}