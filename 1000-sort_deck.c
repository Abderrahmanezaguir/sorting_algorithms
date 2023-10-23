#include <stdlib.h>
#include "deck.h"

/* Function to compare two cards */
int compare_cards(const void *card1, const void *card2)
{
    const card_t *c1 = *(const card_t **)card1;
    const card_t *c2 = *(const card_t **)card2;

    /* First, compare the kind */
    if (c1->kind != c2->kind)
        return c1->kind - c2->kind;

    /* If the kind is the same, compare the values */
    const char *values[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    int i;
    for (i = 0; i < 13; i++) {
        if (values[i] == c1->value)
            break;
    }
    int j;
    for (j = 0; j < 13; j++) {
        if (values[j] == c2->value)
            break;
    }
    return i - j;
}

/* Function to sort a deck of cards */
void sort_deck(deck_node_t **deck)
{
    /* Create an array to hold the pointers to each card */
    const int deck_size = 52;
    const card_t **cards = malloc(deck_size * sizeof(*cards));
    if (!cards)
        return;

    /* Populate the array with the cards from the deck */
    deck_node_t *current = *deck;
    int i = 0;
    while (current) {
        cards[i++] = current->card;
        current = current->next;
    }

    /* Sort the array of cards using qsort */
    qsort(cards, deck_size, sizeof(*cards), compare_cards);

    /* Reconstruct the sorted deck using the sorted array */
    current = *deck;
    i = 0;
    while (current) {
        current->card = cards[i++];
        current = current->next;
    }

    /* Free the temporary array */
    free(cards);
}
