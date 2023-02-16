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

// задача Иосифа:
// встают в круг (связный цикличный список), и постепенно
// удаляется каждый M-ный участник до тех пор, пока не останется один
void JosephProblem(int argc, char** argv) {
    int i, N = std::atoi(argv[1]), M = atoi(argv[2]);
    link t = new node(1, 0); t->next = t; // создаём первого
    link x = t;
    link temp = nullptr;

    for (i = 2; i <= N; ++i) {
        x = (x->next = new node{i, t});
    }

    while(x != x->next) {
        for (i = 1; i < M; ++i)
            x = x->next;
        
        std::cout << x->next->item << " ";

        temp = x->next->next;
        delete x->next;
        x->next = temp;
    }

    std::cout << std::endl << x->item << std::endl;
    delete x;
}
//2 4 6 8 10 3 7 1 9
//5 остался

int main(int argc, char** argv) {

    JosephProblem(argc, argv);

    return 0;
}