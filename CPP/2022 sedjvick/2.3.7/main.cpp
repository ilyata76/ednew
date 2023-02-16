#include <iostream>
#include <stdlib.h>
#include <string.h>

int compare(const void* i, const void* j) {
    return std::strcmp(*(char**)i, *(char**)j); // ?
}

void string_sort() {
    const int Nmax = 1000;
    const int Mmax = 10000;
    char* a[Nmax]; int N = 0;
    char buf[Mmax]; int M = 0;

    for (N = 0; N < Nmax; N++) {
        a[N] = &buf[M];
        if (!(std::cin >> a[N]))
            break;

        M += std::strlen(a[N]) + 1;
    }
    
    qsort(a, N, sizeof(char*), compare);
    
    for (int i = 0; i < N; i++)
        std::cout << a[i] << std::endl;

}

// матрица смежности для графа (1 - есть связь, 0 - нет)
void graph() {
    static const int V = 5;
    int i, j, adj[V][V];

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            adj[i][j] = 0;

    for (i = 0; i < V; i++) 
        adj[i][i] = 1;

    while (std::cin >> i >> j) {
        adj[i][j] = 1;
        adj[j][i] = 1;
    }    

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++)
            std::cout << adj[i][j] << " ";
        std::cout << std::endl;   
    } 

}

struct node {
    int v;
    node* next;

    node(int x, node* t) {
        v = x; next = t;
    }

};

typedef node* link;

// массив и списков смежности => граф
void graph_by_lists() {
    static const int V = 5;
    int i, j;
    link adj[V];

    for (i = 0; i < V; i++) 
        adj[i] = 0;

    while (std::cin >> i >> j) {
        adj[j] = new node{i, adj[j]};
        adj[i] = new node{j, adj[i]};
    }
}


int main(int argc, char** argv) {

    // string_sort();
    // graph();
    

    return 0;
}