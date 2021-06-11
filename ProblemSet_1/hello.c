#include<cs50.h>
#include <stdio.h>

int main(void)

{
    string name = get_string("What is your name?\n");       //prompts user to enter their name
    printf("Hello, %s!\n", name);                           //Responds with Hello [name]!
}
