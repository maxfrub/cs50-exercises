#include <stdio.h>
#include <cs50.h>

int calculate_changue(int c);
int calculate_coins(int type, int cha);
int check_changue_left(int money_valor, int total_c, int t_coins);


int main(void)
{
    int changue;
    do
    {
        changue = get_int("Changue owed: ");

        if (changue >= 0)
        {
            int result = calculate_changue(changue);
            printf("%i\n", result);
        }
        else
        {
            printf("Please select a valid number.\n");
        }

    }
    while (changue < 0);
}


int calculate_changue(int c)
{
    int total_coins = 0;
    int temp_c = c;
    int temp_coins = 0;
    temp_coins = calculate_coins(25, temp_c);
    total_coins += temp_coins;
    temp_c = check_changue_left(25, temp_c, temp_coins);
    temp_coins = calculate_coins(10, temp_c);
    total_coins += temp_coins;
    temp_c = check_changue_left(10, temp_c, temp_coins);
    temp_coins = calculate_coins(5, temp_c);
    total_coins += temp_coins;
    temp_c = check_changue_left(5, temp_c, temp_coins);
    total_coins += calculate_coins(1, temp_c);
    return total_coins;
}

int calculate_coins(int type, int cha)
{
    int coins = 0;
    while (cha > 0)
    {
        cha -= type;
        coins++;
        if (cha >= 0 && cha < type)
        {
            break;
        }
        else if (cha < 0)
        {
            cha += type;
            coins--;
            break;
        }
    }
    return coins;
}


int check_changue_left(int money_valor, int total_c, int t_coins)
{
    if (t_coins > 0)
    {
        total_c -= t_coins * money_valor;
    }
    return total_c;
}
