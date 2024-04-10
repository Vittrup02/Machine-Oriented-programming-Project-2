#ifndef DECK_H
#define DECK_H
// defined because of asprintf on line 124 in deck.c
#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"

#define SUIT_SIZE 13
typedef struct {
    char suit;
    char value;
    bool faceDown;
    bool existsInGame;
} Card;

extern Card clubs[SUIT_SIZE];
extern Card diamonds[SUIT_SIZE];
extern Card hearts[SUIT_SIZE];
extern Card spades[SUIT_SIZE];

extern Card *deck[4];

void fillSuits();

Linked_list *loadDeck(FILE *);

void saveDeck(Linked_list *list, FILE *fptr);

int checkCard(struct ListCard *deck_card);

int convertCardASCIItoDecimal(char cardValue);

#endif