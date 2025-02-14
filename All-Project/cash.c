#include <stdio.h>
#include <cs50.h>

int calculate_quarters(int cents);

int main(void){
    int cents;
    do{
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);

    int dimes = cents / 10;
    cents = cents - (dimes * 10);

    int nickels = cents / 5;
    cents = cents - (nickels * 5);

    int pennies = cents;

    int total_coins = quarters + dimes + nickels + pennies;

    printf("%d\n",total_coins);
}

int calculate_quarters(int cents){
    int quarters = 0;
    while (cents >= 25){
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}

