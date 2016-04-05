#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//ASCII×Ö·û±í
//ºìÌÒ3 ·½Æ¬4 Ã·»¨5 ºÚÌÒ6

char CardValue[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
int ReallValue[13] = {12, 13, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

typedef struct
{
    char type;
    int number;
}Card;

typedef struct
{
    Card cards[54];
    int length;
}CardList;

void InitList(CardList *cards)
{
    cards->length = 0;
}

int CardCompare(Card a, Card b)
{
    if (ReallValue[a.number] > ReallValue[b.number])
    {
        return 1;
    }
    else if (ReallValue[a.number] == ReallValue[b.number])
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void InsertList(CardList *list, int pos, Card card)
{
    if (pos < 1 || pos > list->length + 1)
    {
        return;
    }

    for (int i = list->length; i >= pos; --i)
    {
        list->cards[i] = list->cards[i - 1];
    }

    list->cards[pos - 1] = card;
    list->length++;
    return;
}

void RemoveList(CardList *list, int pos)
{
    if (pos < 1 || pos > list->length)
    {
        return;
    }

    for (int i = pos - 1; i < list->length - 1; ++i)
    {
        list->cards[i] = list->cards[i + 1];
    }

    list->length--;
    return;
}

void PrintList(CardList *list)
{
    for (int i = 0; i < list->length; ++i)
    {
        printf("%c%s", list->cards[i].type, CardValue[list->cards[i].number]);
    }
    printf("\n");
}

void SortList(CardList *list)
{
    for (int i = 0; i < list->length; ++i)
    {
        for (int j = 0; j < list->length - 1; ++j)
        {
            if (CardCompare(list->cards[j], list->cards[j + 1]) < 0)
            {
                Card temp = list->cards[j];
                list->cards[j] = list->cards[j + 1];
                list->cards[j + 1] = temp;
            }
        }
    }
}

int main()
{
    CardList deck;
    CardList playerA;
    CardList playerB;

    InitList(&deck);
    InitList(&playerA);
    InitList(&playerB);

    srand(time(NULL));

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            Card card;
            card.type = 3 + i;
            card.number = j;
            InsertList(&deck, deck.length + 1, card);
        }
    }

    for (int i = 0; i < 15; ++i)
    {
        int rpos = rand() % deck.length;
        InsertList(&playerA, playerA.length + 1, deck.cards[rpos]);
        RemoveList(&deck, rpos + 1);
        rpos = rand() % deck.length;
        InsertList(&playerB, playerB.length + 1, deck.cards[rpos]);
        RemoveList(&deck, rpos + 1);
    }

    SortList(&playerA);
    PrintList(&playerA);
    SortList(&playerB);
    PrintList(&playerB);
    return 0;
}
