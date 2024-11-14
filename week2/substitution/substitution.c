#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2) // Validate that key exists
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int i = 0, length = strlen(key); i < length; i++) // validate that key is not repetative
    {
        for (int j = i + 1; j < length; j++)
        {
            if (key[i] == key[j])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    if (strlen(key) != 26) // checks for key length
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, length = strlen(key); i < length; i++) // checks for non alphabetical key
    {
        if (isalpha(key[i]))
        {
        }
        else
        {
            printf("Key should be alphabetic.\n");
            return 1;
        }
    }

    // code..................................................................................
    string plaintext = get_string("plaintext:  ");
    int lenplaintext = strlen(plaintext);
    printf("ciphertext: ");
    string key2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < lenplaintext; i++)
    {
        if (islower(plaintext[i]))
        {
            char k = toupper(plaintext[i]);
            for (int j = 0; j < 26; j++)
            {
                if (k == key2[j])
                {
                    printf("%c", tolower(key[j]));
                }
            }
        }
        else if (isupper(plaintext[i]))
        {
            char z = plaintext[i];
            for (int j = 0; j < 26; j++)
            {
                if (z == key2[j])
                {
                    printf("%c", toupper(key[j]));
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
