#ifndef YUKON_COMMANDS_H
#define YUKON_COMMANDS_H

#include "linkedlist.h"
#include "deck.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

Linked_list *LD(char arg[], int numOfInputs);

void SD(Linked_list *list, char arg[]);

Linked_list *SI(Linked_list *, int split);

Linked_list *SR(Linked_list *unshuffledPile);

Linked_list **P(Linked_list *);

bool moveValidation(struct ListCard *from, struct ListCard *to, bool toFoundation);

int convertCardValue(char value);

bool gameMoves(char buf[], Linked_list **column_lists, Linked_list **foundation_lists);

#endif //YUKON_COMMANDS_H
