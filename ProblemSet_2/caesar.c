#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool iskeyvalid(string s);  // function prototype

int main(int argc, string argv[])
{
    // if there are not two command line arguments,
    // or if argv[1] (the key) is not valid (see iskeyvalid function)
    if (argc != 2 || !iskeyvalid(argv[1]))
    {
        // print error message
        printf("Usage: %s key\n", argv[0]);
        // return from main a value of 1 (signifies an error)
        return 1;
    }

    // convert from string to integer
    int key = atoi(argv[1]);

    // prompt user to enter plaintext
    string plaintext = get_string("Enter your plaintext: ");

    // output "ciphertext: ""
    printf("ciphertext: ");

    // iterate over plaintext
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char current_char = plaintext[i];
        // conditional on current character being alphabetical
        if (isalpha(current_char))
        {
            // checks whether current character is upper case, and preserves case accordingly
            if (isupper(current_char))
            {
                // shift according to equation and print new ciphertext character
                current_char = (current_char - 65 + key) % 26 + 65;
                printf("%c", current_char);
            }
            // checks whether current character is lower case, and preserves case accordingly
            if (islower(current_char))
            {
                // shift according to equation and print new ciphertext character
                current_char = (current_char - 97 + key) % 26 + 97;
                printf("%c", current_char);
            }
        }
        else
        {
            // preserves non-alphabetical characters
            printf("%c", current_char);
        }
    }
    // print new line
    printf("\n");
    // exit by returning 0 from main
    return 0;
}

// define iskeyvalid function
// iterates over the string and checks whether characters are digits
bool iskeyvalid(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
        if (!isdigit(s[i]))
        {
            return false;
        }
    return true;
}
