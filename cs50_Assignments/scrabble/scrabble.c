#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string word1 = get_string("PLAYER 1: ");
    string word2 = get_string("PLAYER 2: ");

    int z = 0;
    for (int i = 0, length = strlen(word1); i < length; i++)
    {
        char k = toupper(word1[i]);
        if (k == 'A' || k == 'E' || k == 'I' || k == 'L' || k == 'N' || k == 'O' || k == 'R' || k == 'S' || k == 'T' || k == 'U')
        {
            z = z + 1;
        }
        else if (k == 'D' || k == 'G')
        {
            z = z + 2;
        }
        else if (k == 'B' || k == 'C' || k == 'M' || k == 'P')
        {
            z = z + 3;
        }
        else if (k == 'F' || k == 'H' || k == 'W' || k == 'V' || k == 'Y')
        {
            z = z + 4;
        }
        else if (k == 'K')
        {
            z = z + 5;
        }
        else if (k == 'J' || k == 'X')
        {
            z = z + 8;
        }
        else if (k == 'Q' || k == 'Z')
        {
            z = z + 10;
        }
    }

    int y = 0;
    for (int j = 0, length = strlen(word2); j < length; j++)
    {
        char P = toupper(word2[j]);
        if (P == 'A' || P == 'E' || P == 'I' || P == 'L' || P == 'N' || P == 'O' || P == 'R' || P == 'S' || P == 'T' || P == 'U')
        {
            y = y + 1;
        }
        else if (P == 'D' || P == 'G')
        {
            y = y + 2;
        }
        else if (P == 'B' || P == 'C' || P == 'M' || P == 'P')
        {
            y = y + 3;
        }
        else if (P == 'F' || P == 'H' || P == 'W' || P == 'V' || P == 'Y')
        {
            y = y + 4;
        }
        else if (P == 'K')
        {
            y = y + 5;
        }
        else if (P == 'J' || P == 'X')
        {
            y = y + 8;
        }
        else if (P == 'Q' || P == 'Z')
        {
            y = y + 10;
        }
    }
    if (z > y)
    {
        printf("Player 1 wins!\n");
    }
    else if (z < y)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
