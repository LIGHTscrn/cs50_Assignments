#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int l = 0;
    int w = 1;
    int s = 0;
    string text = get_string("Text :");
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (text[i] != ' ' && text[i] != '!' && text[i] != '.' && text[i] != '?' && text[i] != ',' && text[i] != '\'')
        {
            l = l + 1;
        }
        else if (text[i] == ' ')
        {
            w = w + 1;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            s = s + 1;
        }
    }
    float index1 = (0.0588 * (100 * l / (float) w)) - (0.296 * (100 * s / (float) w)) - 15.8;
    int index2 = (0.0588 * (100 * l / (float) w)) - (0.296 * (100 * s / (float) w)) - 15.8;
    float index = index1 - (float) index2;
    if (index >= 0.5)
    {
        index2++;
    }
    if (index2 < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index2 > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index2);
    }
}
