#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);
string check_win(int score1, int score2);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    printf("%s\n", check_win(score1, score2));
}

int compute_score(string word)
{
    int score[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int s = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            int c = toupper(word[i]);
            c -= 65;
            s += score[c];
        }
    }
    return s;
}

string check_win(int score1, int score2)
{
    if (score1 > score2)
    {
        return "Player 1 wins!";
    }
    else if (score2 > score1)
    {
        return "Player 2 wins!";
    }
    else
    {
        return "Tie!";
    }
}

