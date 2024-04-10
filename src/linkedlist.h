#ifndef YUKON_LINKEDLIST_H
#define YUKON_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Structs start here */
struct ListCard {
    char suit;
    char value;
    bool faceDown;
    bool existsInGame;
    struct ListCard *next;
    struct ListCard *prev;
};

typedef struct {
    struct ListCard *head;
    struct ListCard *tail;
    int size;
} Linked_list;

/** Methods start here */
Linked_list *createLinkedList();

void appendCard(Linked_list *list, struct ListCard card);

void prependCard(Linked_list *list, struct ListCard card);

void insertNode(Linked_list *list, struct ListCard *nodeToInsert, struct ListCard *previousNode, bool insertBefore);

void removeNode(Linked_list *list);

void deleteLinkedList(Linked_list *list);

void LinkedListToString(Linked_list *list);

struct ListCard *findNodeFromCard(Linked_list *list, char value, char suit);

bool moveCardFromOneLinkedListToAnother(Linked_list *from, struct ListCard *cardFrom, Linked_list *to);

#endif //YUKON_LINKEDLIST_H
