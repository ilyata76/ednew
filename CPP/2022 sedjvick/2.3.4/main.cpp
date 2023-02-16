#include <iostream>
#include <stdlib.h>

struct node {
    int item;
    node* next;

    node(int x, node* t) {
        item = x; next = t;
    }
};

typedef node* link;

void visit(int value) {
    std::cout << value << '\n';
}

// обход
void traverse(link x) {
    for (link t = x; t != 0; t = t->next)
        visit(t->item);
}

// обратить назад
link reverse(link x) {
    link t, y = x, r = 0; // делим список на обработанный и необработанный + временная переменная
    while (y != 0) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }
    return r;
}

void simple(int argc, char** argv) {
    int N = std::atoi(argv[1]);
    link t = new node(1, 0); t->next = nullptr; 
    // создаём первого. и конец будет указывать на "ничего"
    link x = t;

    for (int i = 2; i <= N; ++i) {
        x = (x->next = new node{i, t});
        x->next = nullptr;
    }

    //traverse(t);
    traverse(reverse(t));

    // while delete

}

void insertionSort(int argc, char** argv) {
    int N = std::atoi(argv[1]);
    node heada(0, 0); /**/
    node headb(0, 0); /*это фиктивные узлы, которые будут началом списка*/

    std::srand(std::time(0));

    link a = &heada;
    link b = &headb;

    link t = a; link u, x;

    for (int i = 0; i < N; ++i)
        t = (t->next = new node( rand() % 1000, 0));

    traverse(&heada);
    std::cout << std::endl;
    
    traverse(&headb);
    std::cout << std::endl;

    for (t = a->next; t != 0; t = u) {
        u = t->next;

        for (x = &headb; x->next != 0; x = x->next)
            if (x->next->item > t->item)
                break;
        auto temp = x->next; 
        x->next = new node{t->item, temp};
        

    }

    traverse(&heada);
        std::cout << std::endl;
    traverse(&headb);

    // while delete

}

int main(int argc, char** argv) {
    insertionSort(argc, argv);
}