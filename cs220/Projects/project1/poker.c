#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "poker.h"

/* Global instances of the two players */
struct player P1, P2;

/* Parse card from a 2 char input */
struct card parse(const char *card)
{
    /* TASK 14: parse input and store in card data structure. */
    struct card c;
    /* Hint: You could use switch statements here */
    switch (*card){
        case '2': c.val = TWO; break;
        case '3': c.val = THREE; break;
        case '4': c.val = FOUR; break;
        case '5': c.val = FIVE; break;
        case '6': c.val = SIX; break;
        case '7': c.val = SEVEN; break;
        case '8': c.val = EIGHT; break;
        case '9': c.val = NINE; break;
        case 'T': c.val = TEN; break;
        case 'J': c.val = J; break;
        case 'Q': c.val = Q; break;
        case 'K': c.val = K; break;
        case 'A': c.val = A; break;
    }
    card++;
    switch (*card) {
        case 'H':
            c.suit = HEARTS;
            break;
        case 'S':
            c.suit = SPADES;
            break;
        case 'C':
            c.suit = CLUBS;
            break;
        case 'D':
            c.suit = DIAMONDS;
            break;
    }
    return c;
}

/* Count the number of occurrences of each card 2 through Ace */
void count_cards(struct player *p)
{
    /* TASK 13:
     * Iterate through the cards and increment the counter for each card
     */
    int i;
    for(i = 0; i < 5; i++){
        p->card_count[p->cards[i].val]++;
    }
}

int is_full_house(struct player *p)
{
    int i, threeOfAKind = 0, pair = 0;
    /* TASK 12b:
     * Hand is full house if there is a pair and 3 of a kind
     */
    for (i = 0; i < 13; i++) {
        if(p->card_count[i] == 3) threeOfAKind++;
        else if(p->card_count[i] == 2) pair++;
    }
    
    return pair && threeOfAKind; /*Return 1 if full house*/
}

int is_flush(struct player *p)
{
    /* TASK 12:
     * Hand is flush if suit of all the cards is the same
     */
    if (p->cards[0].val == p->cards[1].val &&
        p->cards[1].val == p->cards[2].val &&
        p->cards[2].val == p->cards[3].val &&
        p->cards[3].val == p->cards[4].val &&
        p->cards[4].val == p->cards[5].val){
        return 1;
    }
    return 0; /* Return 1 if flush */
}

int is_straight(struct player *p)
{
    /* NOTE: By this stage, the vector must be constructed.
     *
     * The hand is a straight, if the cards are sequential.
     * A2345 as well as TJQKA are both valid straights, and Ace
     * assumes the value of 1 or 13, but not both.
     */
    
    /* TASK 11: Check for regular straights
     * Hint: If this is a straight, player's card_count for i, i+1, i+2, i+3 and i+4 should be 1. */
    int i;
    for(i=0; i < 9; i++){
        if(p->card_count[i] == 1
           && p->card_count[i+1] == 1
           && p->card_count[i+2] == 1
           && p->card_count[i+3] == 1
           && p->card_count[i+4] == 1) return 1;
    }
    
    /* Check for A2345
     * TASK 10: If the hand is A2345, reset the bit for highcard Ace in the player's vector to appropriately reflect that the value of A is not 13.
     * Hint: 1 << position will generate a bit mask for the position of Ace. Xoring it with the vector will reset the bit.
     */
    int countForStraight = 0;
    if (p->card_count[12] == 1) countForStraight++;
    for(i = 0; i < 4; i++){
        if(p->card_count[i]) countForStraight++;
    }
    if (countForStraight == 5) {
        p->vector -= pow(2.0, 12.0);
        return 1;
    }
    
    return 0; /* Return 1 if straight */
}

int is_straight_flush(struct player *p)
{
    /* TASK 9: Detect straight flush. A straight flush is nothing but a straight and a flush */
    return is_flush(p) && is_straight(p); /* Return 1 if straight flush */
}

/* This is the main function that converts the player's hand into weighted unsigned long number.
 It is a 56bit vector as shown below (2 is the LSB and StraightFlush is the MSB) */
/* 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A, 22, 33, 44, 55, 66, 77, 88, 99, TT, JJ, QQ, KK, AA,
 222, 333, 444, 555, 666, 777, 888, 999, TTT, JJJ, QQQ, KKK, AAA, Straight, Flush, FullHouse, 2222, 3333,
 4444, 5555, 6666, 7777, 8888, 9999, TTTT, JJJJ, QQQQ, KKKK, AAAA, StraightFlush */
/* The number of occurrences of each number in the hand is first calculated in count_cards.
 Then, depending on the numeber of occurrences, the corresponding bit in the bit-vector is set.
 In order to find the winner, a simple comparison of the bit vectors (i.e., unsigned long integers) will suffice! */
void eval_strength(struct player *p)
{
    unsigned int straight_or_flush_possible;
    unsigned int i;
    straight_or_flush_possible = 1;
    
    /*
     * TASK 6: Invoke the function to count the occurrences of each card
     */
    
    count_cards(p);
    
    /*
     * TASK 7: Iterate through the card_count array, and set the appropriate bit in the bit vector.
     * For example, if the hand is JH JS 3C AH 4H, set the 23rd bit to indicate a pair of jacks, and 2nd, 3rd and 13th bit to indicate 3, 4 and A respectively. */
    
    for(i = 0; i < 13; i++){
        if(p->card_count[i] == 1){
            p->vector += pow(2.0, (double)i);
        }
        else if(p->card_count[i] == 2){
            p->vector += pow(2.0,(double)i+13);
        }
        else if(p->card_count[i] == 3){
            p->vector += pow(2.0,(double)i+26);
        }
        else if(p->card_count[i] == 4){
            p->vector += pow(2.0,(double)i+43);
        }
    }
    
    /* TASK 8:
     * Check if this is a straight, flush, full house, or a straight flush, and set the appropriate bit in the vector.
     */
    if (is_straight(p)) p->vector += pow(2.0, (double) 40);
    if (is_flush(p)) p->vector += pow(2.0, (double) 41);
    if (is_full_house(p)) p ->vector += pow(2.0, (double) 42);
    if (is_straight_flush(p)) p->vector += pow(2.0, (double) 55);
}

/* Parse each hand in the input file, evaluate the strengths of hands and identify a winner by comparing the weighted vectors */
void compare_hands(FILE *fp)
{
    char p1[5][3];
    char p2[5][3];
    int i;
    
    while(fscanf(fp, "%s %s %s %s %s %s %s %s %s %s",
                 &p1[0][0], &p1[1][0], &p1[2][0], &p1[3][0], &p1[4][0],
                 &p2[0][0], &p2[1][0], &p2[2][0], &p2[3][0], &p2[4][0]) == 10) {
        memset(&P1, 0, sizeof(struct player));
        memset(&P2, 0, sizeof(struct player));
        for(i = 0; i < 5; i++) {
            P1.cards[i] = parse(&p1[i][0]);
            P2.cards[i] = parse(&p2[i][0]);
        }
        
        /* TASK 4: Invoke eval_strength for each player */
        eval_strength(&P1);
        eval_strength(&P2);
        /* TASK 5: Report the winner (e.g., "Player 1 wins") depending on whoever has the higher vector */
        if (P1.vector > P2.vector) puts("Player 1 wins");
        else puts("Player 2 wins");
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    
    /* TASK 2: Validate command line arguments and try to open the file. Exit on failure. */
        fp = fopen(argv[1], "r");
        if(!fp){
            exit(0);
    }
    /* TASK 3: Invoke the compare hands function */
    compare_hands(fp);
    return 0;
}
