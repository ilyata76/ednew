#include <iostream>
#include <stdlib.h>

static const int N = 1000;

// решето Эратосфена - нахождение простых чисел
void Eratosthenes() {
    int i, a[N];

    for (i = 2; i < N; i++)
        a[i] = 1; // сначала все числа (индексы массива) 
                  // - простые (предположение)

    for (i = 2; i < N; ++i) {
        if (a[i]) // если наше число простое
            for (int j = i; i * j < N; ++j)
                a[i * j] = 0; // и оно является множителем другого в массиве, то другое - не простое
    }

    for (i = 2; i < N; ++i) {
        if (a[i])
            std::cout << " " << i;
    } std::cout << std::endl;

}

//  2 3 5 7 11 13 17 19 23 29 
//  31 37 41 43 47 53 59 61 67 
//  71 73 79 83 89 97 101 103 107 
//  109 113 127 131 137 139 149 151 
//  157 163 167 173 179 181 191 193 197 
//  199 211 223 227 229 233 239 241 251 257 
//  263 269 271 277 281 283 293 307 311 313 
//  317 331 337 347 349 353 359 367 373 379 
//  383 389 397 401 409 419 421 431 433 439 
//  443 449 457 461 463 467 479 487 491 499 
//  503 509 521 523 541 547 557 563 569 571 577 
//  587 593 599 601 607 613 617 619 631 641 643 
//  647 653 659 661 673 677 683 691 701 709 
//  719 727 733 739 743 751 757 761 769 773 787 797 
//  809 811 821 823 827 829 839 853 857 859 863 877
//   881 883 887 907 911 919 929 937 941 947 953 
//   967 971 977 983 991 997


void Eratosthenes(int count) {
    long long int i;
    long long int* a = new long long int[count];

    if (a == 0) {
        std::cout << "out of memory" << std::endl; 
        return;
    }

    for (i = 2; i < count; ++i)
        a[i] = 1;                 

    for (i = 2; i < count; ++i) {
        if (a[i]) 
            for (long long int j = i; i * j < count; ++j)
                a[i * j] = 0; // 46k * 46k does not fit in an INT
    }

    for (i = 2; i < count; ++i) {
        if (a[i])
            std::cout << " " << i;
    } std::cout << std::endl;

}


int heads() {
    return rand() < RAND_MAX / 2;
}

void headsOrTails(int argc, char** argv) {
    int i, j, cnt = 0; 

    int N = std::atoi(argv[1]), 
        M = std::atoi(argv[2]);

    int *f = new int[N+1];

    for (j = 0; j <= N; ++j) {
        f[j] = 0; // индексируем всё нулями
    }

    for (i = 0; i < M; i++, f[cnt]++ /*f[cnt] - это количество раз, сколько выпало cnt из M экспериментов*/) {
        // i < M про количество экспериментов подбрасывания по N раз

        // std::cout << cnt << " " << f[cnt] << "\n";
        // 0 0
        // 18 1
        // 15 1
        // 16 1
        // 16 2
        // 14 1
        // 19 1
        // 17 1
        // 10 1
        // 17 2
        // 15 2
        // 16 3
        // 15 3
        // 20 1
        // 13 1
        // 17 3
        // 16 4
        // 17 4
        // 17 5
        // 17 6

        for (cnt = 0, j = 0; j <= N; j++) {

            // j про количество подбрасываний N 

            if (heads()) // если выпадает
                cnt++; // то ++ количество выпавших. cnt < N всегда. cnt станет индексом, а после сделается f[cnt]++
        }
    }
        std::cout << '\n';
    // и вывод

    for (j = 0; j <= N; j++) {
        if (f[j] == 0) std::cout << ".";

        for (i = 0; i < f[j]; i+= 10) 
            std::cout << "*";

        std::cout << std::endl;
    }

}

int main(int argc, char** argv) {

    // Eratosthenes();
    // Eratosthenes(std::atoi(argv[1]));

    headsOrTails(argc, argv);

    return 0;
}