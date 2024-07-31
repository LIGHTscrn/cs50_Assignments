#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    long cardnumber = 0;
    int z = 0;
    int l = 0;
    do
    {
        cardnumber = get_long("Input your credit card number : ");
    }
    while (cardnumber < 0);
    int i = 0;
    long number = cardnumber;
    do
    {
        cardnumber = (cardnumber / 10);
        i++;
    }
    while (cardnumber > 0);
    for (int j = 0; j < i; j++)
    {

        if (j % 2 == 0)
        {
            long e = pow(10, j);
            int x = (number / (10 * e)) % 10;
            int y = (number / e) % 10;
            if (2 * x > 9)
            {
                z = z + (((2 * x) / 10) + ((2 * x) % 10));
            }
            else
            {
                z = z + 2 * x;
            }
            l = l + y;
        }
    }
    int credit = z + l;
    long d = pow(10, (i - 1));
    long f = pow(10, (i - 2));
    long g = pow(10, (i - 4));
    if (credit % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (number / d == 4 && (i == 13 || i == 16))
    {
        printf("VISA\n");
    }
    else if ((number / f > 50 && number / f < 56 && i == 16) || (number / g > 2220 && number / g < 2721&& i == 16))
    {
        printf("MASTERCARD\n");
    }
    else if ((number / f == 34 || number / f == 37) && i == 15)
    {
        printf("AMEX\n");
    }
    else
    {
      printf("INVALID\n");
    }
}
