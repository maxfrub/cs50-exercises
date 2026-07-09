#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int check_key(string key);
void encrypt(string key, string plaintext);

const int letters_in_alphabet = 26;

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (check_key(argv[1]) == 1)
        {
            return 1;
        }
    }
    else
    {
        printf("Usage: ./subtitution KEY\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    encrypt(argv[1], plaintext);
}

void encrypt(string key, string plaintext)
{
    printf("ciphertext: ");
    char alphabet_upper[26];
    char alphabet_lower[26];
    for (int i = 0; i < letters_in_alphabet; i++)
    {
        alphabet_upper[i] = 'A' + i;
        alphabet_lower[i] = 'a' + i;
    }
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            for (int j = 0; j < letters_in_alphabet; j++)
            {
                if (isupper(plaintext[i]))
                {
                    if (alphabet_upper[j] == plaintext[i])
                    {
                        printf("%c", toupper(key[j]));
                    }
                }
                else
                {
                    if (alphabet_lower[j] == plaintext[i])
                    {
                        printf("%c", tolower(key[j]));
                    }
                }
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

int check_key(string key)
{
    if (strlen(key) != letters_in_alphabet)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < letters_in_alphabet; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }
    char letters[letters_in_alphabet];
    for (int i = 0; i < letters_in_alphabet; i++)
    {
        letters[i] = key[i];
        for (int j = 0; j < i; j++)
        {
            if (toupper(key[i]) == toupper(letters[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    return 0;
}
