// The Caesar Challenge:

// The aim of this program: 
// #1: For the user to run this program from the command line & provides the key as their 2nd argument. 
// #2: Request input from the user when the program starts up: the message they want to have encrypted
// #3: The program will then encrypt the message according to the key the user provided
//      Eg: Where if the user provides a key of 2, every letter in the message will "roll over" by 2 characters
//      whilst still maintaining the same case. 
// #4: Once done the program will print the encrypted message and return 0

// Rules: 
// #1: The program should only allow the user to input the filename & 1 key (where the key contains digits only)
// if not, 
//      you must print a message (of your choosing) to the user
//      return 1.
// #2: The user must provide a message to encrypt
// if no message provided you must: 
//      print: "Usage: ./caesar key\n"
//      return 1;     
// #3: For every letter in the message, the character's ascii value should modified according to the value of the key:
// EG: If key = 2 && message == "Hello" -> our output would become "Jgnnq"
// #4: The case of the letter must be honoured so a lowercase letter is always changed to a lowercase letter
// and likewise a capital letter should always be changed to an uppercase letter. 
// #4: All non-letters should remain unchanged (so spaces, special characters & digits)

// Note: When you receive the user's key, it will initially be a string
//  -> you'll have to validate it and then convert it to digits before you can use it. 


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int validateKeyandConvertToInt(string user_key, int *keyValidity, int *key);

int main(int argc, char *argv[])
{
    // #1: Let's make sure the user provided the correct / expected number of arguments when calling './caesar':
    if (argc != 2)
    {
        // printf("Usage: ./caesar key\n");
        printf("Invalid arguments! When calling this file, please provide your output filename followed by your key.\n");
        return 1;
    }

    // #2: Let's validate our key to make sure it only contains digits.
    //  If so, we should convert key to an int so we can use it in our program:
    string user_key = argv[1];
    int keyValidity = 0, key = 0;
    validateKeyandConvertToInt(user_key, &keyValidity, &key);

    if (keyValidity == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // #3: Let's take the user's input (our message to encrypt):
    string plaintext = get_string("plaintext: ");
    int message_length = strlen(plaintext);
    char encrypted_message[30] = "";

    // #4: Let's encrypt our message:
    for (int i = 0, len = message_length; i < len; i++)
    {
        char current_character = plaintext[i];
        // Now we need to take the (ascii value of) current letter + key.
        // However if current_character is a capital it should be replaced only by another capital letter
        // So no lowercase characters or basically any non-capital letter.
        // Likewise if current_character is a lowercase letter, it should only be replaced with another lowercase letter:

        // Upper case letters:
        if ((current_character >= 65 && current_character <= 90))
        {
            // printf("Current letter: %c\n", current_character);
            int ascii_value = (int) current_character;
            int replacement_value = ((ascii_value - 65 + key) % 26 + 65);
            char updated_letter = replacement_value;
            strncat(encrypted_message, &updated_letter, 1);
        }

        // Lower case letters:
        else if (current_character >= 97 && current_character <= 122)
        {
            int ascii_value = (int) current_character;
            int replacement_value = ((ascii_value - 97 + key) % 26 + 97);
            char updated_letter = replacement_value;
            strncat(encrypted_message, &updated_letter, 1);
        }

        // If it's not a letter at all, it doesn't get changed at all, and gets added to the encrypted_message
        // in it's original form:
        else
        {
            strncat(encrypted_message, &current_character, 1);
        }
    }
    // #5: Let's finish this off by printing our encrypted message and return 0
    // (To show our message has been successfully encrypted)
    printf("ciphertext: %s\n", encrypted_message);
    return 0;
}

// Let's check our key only contains digits, and then convert key's value to int.
// Note I want to return more than 1 input here, so I'll be adding a star * before keyValidity & key
// to note/highlight the variables I want to export outside of this function:
int validateKeyandConvertToInt(string user_key, int *keyValidity, int *key)
{
    // Let's start by assuming our string is valid: containing only digits.
    // (By adding a star before this variable, I can return this variable's output for external access.)
    *keyValidity = 0;

    // Now to iterate over every character in user_key, looking for any invalid (non-digit) characters:
    for (int i = 0, len = strlen(user_key); i < len; i++)
    {
        char current_char = user_key[i];
        // If current_char is any character other than a 0, 1, 2, 3, 4, 5, 6, 7, 8, 9:
        //      then our key is not longer valid! Thus our keyValidity changes to 1.
        if (current_char <= 47 || current_char >= 58)
        {
            *keyValidity = 1;
        }
    }

    // By this point, we know our key is in fact only digits,
    // so we can convert it to type int without encountering any errors / bugs:
    int key_int = atoi(user_key);
    *key = key_int;
    // We know our function has valid input so we end this off by returning 0:
    return 0;
}