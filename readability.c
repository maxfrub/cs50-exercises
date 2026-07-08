#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_grade(string text);
int calculate_letters(string text);
int calculate_words(string text);
int calculate_sentences(string text);
float calculate_average(int value, int words);

int main(void)
{
    string text = get_string("Text: ");
    int grade = calculate_grade(text);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int calculate_grade(string text)
{
    float L = calculate_letters(text);
    float S = calculate_sentences(text);
    int words = calculate_words(text);

    L = calculate_average(L, words);
    S = calculate_average(S, words);

    float grade = 0.0588 * L - 0.296 * S - 15.8;
    grade = round(grade);

    return (int) grade;
}

int calculate_letters(string text)
{
    int n = strlen(text);
    int L = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            L++;
        }
    }
    return L;
}

int calculate_words(string text)
{
    int n = strlen(text);
    int words = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    words++;
    return words;
}

int calculate_sentences(string text)
{
    int n = strlen(text);
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s++;
        }
    }
    return s;
}

float calculate_average(int value, int words)
{
    float v = (float) value;
    float w = (float) words;

    v /= w;
    v *= 100;
    return v;
}
