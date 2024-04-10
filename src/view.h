#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "deck.h"
#include "linkedlist.h"

void generateEmptyView(char lastCommand[], char message[]);

void showDeck(Linked_list *deck_list, char command[], char statusMessage[]);

void generatePlayView(Linked_list *C_ptr[7], Linked_list *F_ptr[4], char lastCommand[], char message[]);

int calculateMaxNumOfRows(Linked_list *columns[]);

void generateColumns();

void clearView();

void printCommandConsole(char lastCommand[], char message[]);

#endif