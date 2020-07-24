// To get a sense of how to play with an array of strings in C

#include <string.h>
#include <stdio.h>
#include <cs50.h>

int main() {
    string names[4];
    names[0] = "EMMA";
    names[1] = "RODRIGO";
    names[2] = "BRIAN";
    names[3] = "DAVID";

    printf("First name: %s\n", names[0]);
    printf("%c%c%c%c\n", names[0][0], names[0][1], names[0][2], names[0][3]);

    return 0;
} 