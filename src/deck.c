#include "deck.h"
#include "view.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

/**
 * @authors s215797 Mikael Fangel (45%), s215812 Silja Ye-Chi Sandersen (45%), s215805 Mads Sørensen (10%)
 */
void fillSuits() {
    char suits[4] = {'C', 'D', 'H', 'S'};

    for (int i = 0; i < 4; i++) {
        deck[i][0].value = 'A';
        deck[i][0].suit = suits[i];
        deck[i][0].existsInGame = false;

        for (int j = 1; j < 10; ++j) {
            deck[i][j].value = (j + 1) + '0';
            deck[i][j].suit = suits[i];
            deck[i][j].existsInGame = false;
        }

        deck[i][9].value = 'T';
        deck[i][9].suit = suits[i];
        deck[i][9].existsInGame = false;
        deck[i][10].value = 'J';
        deck[i][10].suit = suits[i];
        deck[i][10].existsInGame = false;
        deck[i][11].value = 'Q';
        deck[i][11].suit = suits[i];
        deck[i][11].existsInGame = false;
        deck[i][12].value = 'K';
        deck[i][12].suit = suits[i];
        deck[i][12].existsInGame = false;
    }
}

/**
 * @authors s215805 Mads Sørensen (60%), s215812 Silja Ye-Chi Sandersen (40%)
 * @param deck_card
 * @return if duplicate card returns 1. If invalid card returns 2. If existing card returns 0
 */
int checkCard(struct ListCard *deck_card) {
    int suit;
    switch (deck_card->suit) {
        case 'C' :
            suit = 0;
            break;
        case 'D' :
            suit = 1;
            break;
        case 'H' :
            suit = 2;
            break;
        case 'S' :
            suit = 3;
            break;
        default:
            return 2;
    }

    int value = convertCardASCIItoDecimal(deck_card->value);
    if (value == -1) return 2;

    if (!deck[suit][value].existsInGame) {
        deck[suit][value].existsInGame = true;
        deck_card->existsInGame = true;
        return 0;
    }
    else return 1;
}

/**
 * @authors s215805 Mads Sørensen (45%), s215812 Silja Ye-Chi Sandersen (40%), s215797 Mikael Fangel (25%)
 * @param cardValue the ascii value from the card to be converted to a decimal number
 * @return the 0 index decimal corresponding to the card in the deck (2D array)
 */
int convertCardASCIItoDecimal(char cardValue) {
    int value;
    // 65 = A and 97 = a
    if (cardValue == 65 || cardValue == 97) {
        value = 0;
    }
        // If between 1 and 10
    else if (cardValue > 49 && cardValue < 58) {
        value = cardValue - 49;
    }
    else {
        switch (cardValue) {
            case 'T':
                value = 9;
                break;
            case 'J':
                value = 10;
                break;
            case 'Q':
                value = 11;
                break;
            case 'K':
                value = 12;
                break;
            default:
                return -1;
        }
    }

    return value;
}

/**
 * Load a deck from a file. File must be a list of cards represented with 2 characters
 * eg. Ace of Hearts - "AH" with newline after each card. Returns the deck in a linked list
 * Used in LD command
 * @authors s215805 Mads Sørensen (65%), s215812 Silja Ye-Chi Sandersen (25%), s215797 Mikael Fangel (10%)
 * @param fptr pointer to the file from which should be read
 * @return NULL if errors occur. A deck of cards, where all cards are valid and there is no duplicates
 */
Linked_list *loadDeck(FILE *fptr) {
    fillSuits();
    char line[4];
    Linked_list *cardDeck = createLinkedList();

    // While file not empty, read a line, create a card, and add it to linked list.
    int lineNum = 1;
    while (fgets(line, sizeof(line), fptr) != NULL) {
        struct ListCard newCard;
        newCard.value = line[0];
        newCard.suit = line[1];

        char buffer[40];
        char *num;

        int check = checkCard(&newCard);

        if (check != 0 && asprintf(&num, "%d", lineNum) != -1) {
            if (check == 1)
                strcat(strcpy(buffer, "ERROR! Duplicate card found on line "), num);
            else {
                strcat(strcpy(buffer, "ERROR! Invalid card found on line "), num);
            }
            generateEmptyView("LD", buffer);
            deleteLinkedList(cardDeck);
            return NULL;
        }
        else {
            appendCard(cardDeck, newCard);
            ++lineNum;
        }
    }

    if(cardDeck->size != 4 *SUIT_SIZE) {
        generateEmptyView("LD", "ERROR! CardDeck doesn't match the deck size of 52");
        deleteLinkedList(cardDeck);
        return NULL;
    }

    return cardDeck;
}

/**
 * Save deck to a file
 * Used in SD command
 * @author s215805 Mads Sørensen
 * @param list
 */
void saveDeck(Linked_list *list, FILE *fptr) {
    char line[3];
    line[2] = '\n';
    struct ListCard *node = list->head;
    // While linked list not null, write a card to the file.
    while (node != NULL) {
        struct ListCard *card = node;
        line[0] = card->value;
        line[1] = card->suit;
        fwrite(line, 1, sizeof line, fptr);
        node = node->next;
    }
}