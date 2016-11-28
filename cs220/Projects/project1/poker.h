#ifndef _POKER_H
#define _POKER_H

/* TASK 1: 
 * Define the Value and Suit enumerators
 */

enum Suit{
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
};

enum Value{
    TWO = 0,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,J,Q,K,A
};

struct card {
	enum Value val;
	enum Suit suit;
};

struct player {
	struct card cards[5]; /* 5 cards for each player */
	unsigned int card_count[13]; /* counters for each of the 13 cards */
	unsigned long vector; /* A bit vector that represents the hand. Bit vector represented by higher hand is larger than bit vector represented by lower hand. */
};

/* TASK 15:
 * Insert declarations for functions in poker.c here.
 */
struct card parse(const char *card);
void count_cards(struct player *p);
int is_full_house(struct player *p);
int is_flush(struct player *p);
int is_straight(struct player *p);
int is_straight_flush(struct player *p);
void eval_strength(struct player *p);
void compare_hands(FILE *fp);

#endif
