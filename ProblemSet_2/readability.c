// Problem set 2 - Readability


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Prompt user for a string of text (using get_string).

    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text.
    // Assume that a letter is any lowercase or uppercase character
    // from a to z / A to Z.
    // Any sequence of characters separated by spaces count as a word.
    // And any period, exclamation point, or Q mark, indicate sentence end.

    float letters = 0, words = 1, sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Print out number of letters, words, and sentences.

    // printf("This text contains %.0f letter(s), %.0f word(s), and %.0f sentence(s)\n", letters, words, sentences);

    // Calculate grade.
    // Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
    // Here, L is the average number of letters per 100 words in the text,
    // and S is the average number of sentences per 100 words in the text.

    float L = letters / words * 100, S = sentences / words * 100;
    float cl_index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(cl_index);

    // Print as output "Grade X", rounded to the nearest integer.
    // If grade is 16 or higher, output "Grade 16+", and if less than 1,
    // then output "Before Grade 1".

    if (grade > 0 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }

}
