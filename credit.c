#include <cs50.h>
#include <stdio.h>

int check_number_checksum(long cn, int wich);
int get_last_n(long number);
string check_brand(long credit_number);

int main(void)
{
    long credit_number = get_long("Number: ");
    string final_type;

    int final_checksum = check_number_checksum(credit_number, 1);
    final_checksum += check_number_checksum(credit_number, 0);
    if (final_checksum % 10 == 0)
    {
        final_type = check_brand(credit_number);
        printf("%s\n", final_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

int check_number_checksum(long cn, int wich)
{
    long temp_cn = cn;
    long n = 100;
    if (wich == 1)
    {
        temp_cn /= 10;
    }
    int checksum = 0;
    while (temp_cn > 1)
    {
        int temp_digit = 0;
        temp_digit = get_last_n(temp_cn);
        if (wich == 1)
        {
            temp_digit *= 2;
        }
        if (temp_digit < 10)
        {
            checksum += temp_digit;
        }
        else
        {
            checksum += get_last_n(temp_digit);
            temp_digit /= 10;
            checksum += temp_digit;
        }
        temp_cn /= n;
    }
    return checksum;
}

string check_brand(long credit_number)
{
    long temp_credit_number = credit_number;
    string type = "INVALID";
    int index = 0;
    while (temp_credit_number > 100)
    {
        temp_credit_number /= 10;
        index++;
    }
    if (temp_credit_number >= 51 && temp_credit_number <= 55)
    {
        if (index == 14)
        {
            type = "MASTERCARD";
        }
    }
    else if (temp_credit_number == 34 || temp_credit_number == 37)
    {
        if (index == 13)
        {
            type = "AMEX";
        }
    }
    else
    {
        temp_credit_number /= 10;
        index++;
        if (temp_credit_number == 4)
        {
            if (index == 12 || index == 15)
            {
                type = "VISA";
            }
        }
    }
    return type;
}

int get_last_n(long number)
{
    number %= 10;
    return number;
}
