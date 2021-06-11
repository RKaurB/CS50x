// Mario (less comfortable):

// This task is to re-create the pyramid from Mario game using hashes on the screen.
// The user chooses how tall or short they want the pyramid to be.
// The user can input any height between one and eight inclusive, and the programme will display the pyramid on the screen, to the
// appropriate height.
// If the user enters a height outside of the values 1-8, the program re-prompts the user to type in another height.

#include <cs50.h>
#include <stdio.h>

int main(void)                              //equivalent of 'when green flag clicked'
{
    int h;                                  //define variable h (height) as integer
    do
    {
        h = get_int("Pyramid height: ");    //prompt user for desired height of pyramid, to be stored in h variable
    }
    while (h < 1 || h > 8);

    for (int r = 0; r < h; r++)             //row loop
    {
        for (int s = 0; s < h - 1 - r; s++) //space loop
        {
            printf(" ");                    //prints space
        }
        for (int c = 0; c <= r; c++)        //column loop
        {
            printf("#");                    //prints hash (#)
        }
        printf("\n");                       //new line
    }
}
