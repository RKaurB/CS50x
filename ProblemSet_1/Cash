// Cash:

// This program first asks the user how much change is owed and then prints the minimum number
// of coins with which that change can be made. 
// If the user provides a negative value, the program should re-prompt them for a valid amount again until compliance.

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Declare variables

    float dollars;

    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    // Prompt user for an amount of change, in dollars ('dollars')

    do
    {
        dollars = get_float("How much change is owed? Enter amount in $ (e.g. 0.41): ");
    }

    while (dollars < 0);    // If number entered is non-negative, keep prompting

    // Convert dollars (float) to cents (integer), and round to the nearest penny

    int cents = round(dollars * 100);

    // Define variable to hold minimum number of coins (coin counter) and set initial value to 0

    int min_coins = 0;

    // Compute coins, and keep track of coins used

    while (cents >= quarter)
    {
        cents = cents - quarter;
        min_coins++;
    }

    while (cents >= dime)
    {
        cents = cents - dime;
        min_coins++;
    }

    while (cents >= nickel)
    {
        cents = cents - nickel;
        min_coins++;
    }

    while (cents >= penny)
    {
        cents = cents - penny;
        min_coins++;
    }

    // Print minimum number of coins to return
    
    printf("%i \n", min_coins);

}
