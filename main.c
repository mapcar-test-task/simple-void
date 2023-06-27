#include <stdio.h>
#include <stdlib.h>

struct Node {
    void* data;
    struct Node* next;
};

struct Node* mapcar(struct Node* head, void* (func)(void*)) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* new_head = (struct Node*) malloc(sizeof(struct Node));
    new_head->data = func(head->data);
    new_head->next = mapcar(head->next, func);
    return new_head;
}

// Вспомогательные функции для создания и печати списка
struct Node* create_node(void* data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%p ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Функция, которую будем применять к каждому элементу списка
void* functor(void* ptr) {
    return ptr;
}

int main() {
    int intNumber = 1;
    float floatNumber = 2.0f;
    double doubleNumber = 3.0;
    char charSymbol = 'D';

    struct Node* list = create_node(&intNumber);
    list->next = create_node(&floatNumber);
    list->next->next = create_node(&doubleNumber);
    list->next->next->next = create_node(&charSymbol);

    printf("Original list: ");
    print_list(list);

    struct Node* new_list = mapcar(list, functor);
    printf("New list: ");
    print_list(new_list);

    // Освобождение памяти для каждого узла списка
    struct Node* current = list;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // Освобождение памяти для нового списка
    current = new_list;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
