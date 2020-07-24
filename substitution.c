// The Substitution Challenge:
// Design and implement a program, substitution, that encrypts messages using a substitution cipher.

// Rules: 
// # Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive 
//      (so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.)
// # If your program is executed without any command-line arguments or with more than one command-line argument, 
//      your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
// # If the key is invalid 
//  (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), 
//      your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
// # Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
// # Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, 
//  with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; 
//  # *Note:* non-alphabetical characters should be outputted unchanged.
// # Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
// # After outputting ciphertext, you should print a newline. 
// # Your program should then exit by returning 0 from main.

// When running this file via command line, type:
//         gcc substitution.c -o substitution -lcs50

// My code to solve this challenge:
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validateKey(string keyStr, int keyLength);
int checkForLetterDuplication(string keyStr, int keyLength);
// string encryptUserInput(string userInput, string keyStr);
int charIndexInAlphabet(char currentCharInInput);

int main(int argc, char *argv[])
{
    // Step #1: Check our user provides the correct number of arguments: Filename key
    if (argc != 2)
    {
        printf("Invalid arguments! Make sure to use the format: filename key.\n");
        return 1;
    }

    // Step #2: Check our user's key meets the requirements:
    string keyStr = argv[1];
    int keyLength = strlen(keyStr);
    int keyIsValid = validateKey(keyStr, keyLength);
    if (keyIsValid == 1)
    {
        printf("Your key doesn't meet the requirements, please try again.\n");
        return 1;
    }

    // Step #3: Ask the user for their plaintext message to encrypt:
    string userInput = get_string("plaintext: ");

    // Step #4: Let's encrypt the message according to the key:
    // (Going to do this by:
    // #1: Find the current character in user's input: currentCharInInput
    // #2: Finding the currentCharInInput's index in the alphabet: from 0-25
    // & save it in intAlphaIndex)
    // #3: Go to the intAlphaIndex in our key, find the character that sits at the index: replacementChar
    // #4: Replace currentCharInInput with replacementChar
    // #5 If currentCharInInput is a upper case, ensure that replacementChar is uppercase
    // & likewise if currentCharInInput is a lowercase, ensure that replacementChar is lowercase:
    // )
    int userInputLength = strlen(userInput);
    // We have no idea how long the user's message is going to be. We'll make the assumption it won't exceed 50 characters.
    char encryptedMessage[50] = "";
    for (int i = 0; i < userInputLength; i++)
    {
        // Let's grab the current character in user's input and current character in the key:
        char currentCharInInput = userInput[i];
        char currentCharInKey = keyStr[i];

        // If the current character in user's input is a capital:
        if (currentCharInInput >= 65 && currentCharInInput <= 90)
        {
            char lowerCharInInput = tolower(currentCharInInput);
            int intAlphaIndex = charIndexInAlphabet(lowerCharInInput);
            char replacementChar = keyStr[intAlphaIndex];
            char upperChar = toupper(replacementChar);
            strncat(encryptedMessage, &upperChar, 1);
        }
        // If the current character in user's input is lowercase:
        else if (currentCharInInput >= 97 && currentCharInInput <= 122)
        {
            char lowerCharInInput = tolower(currentCharInInput);
            int intAlphaIndex = charIndexInAlphabet(lowerCharInInput);
            char replacementChar = keyStr[intAlphaIndex];
            char lowerChar = tolower(replacementChar);
            strncat(encryptedMessage, &lowerChar, 1);
        }
        // If the current character in user's input is not a letter at all,
        // it gets added to our encrypted message without modification:
        else
        {
            strncat(encryptedMessage, &currentCharInInput, 1);
        }
    }
    // Step #5: print our encrypted message and return 0 to confirm our user's message
    // has been successfully encrypted:
    printf("ciphertext: %s\n", encryptedMessage);
    return 0;
}

int validateKey(string keyStr, int keyLength)
{
    char validCharacters[30];

     // Step 1: check that the key is in fact 26 characters & if not: end the function:
    if (keyLength != 26)
    {
        printf("Invalid message: You have not provided 26 characters.\n");
        return 1;
    }

    // Step 2: Check that all the characters in our key are in fact letters & if it finds a non-alphabetic char: end the function;
    for (int i = 0; i < keyLength; i++)
    {
        char current_char = keyStr[i];
        if (current_char < 65 || current_char > 122)
        {
            return 1;
        }
        else if (current_char > 90 && current_char < 97)
        {
            return 1;
        }
    }

    // Step 3: Let's check to see if there are any letters duplicated within our key!
    // For this, we shall use our checkForLetterDuplication function.
    int letterDuplicated = checkForLetterDuplication(keyStr, keyLength);
    return letterDuplicated;
}

int checkForLetterDuplication(string keyStr, int keyLength)
{
    // Let's iterate through every letter in the key (keyStr)
    // & if any letter is duplicated, our function will return 1 and return to main() -> where it will end the program.
    for (int i = 0; i < keyLength; i++)
    {
        int duplicates = 0;
        char current_char = keyStr[i];
        for (int j = 0; j < keyLength; j++)
        {
            char comparison_char = keyStr[j];
            if (comparison_char == current_char)
            {
                duplicates++;
            }
        }
        if (duplicates > 1)
        {
            printf("You have duplicated letters in your key! Please try again.\n");
            return 1;
        }
    }
    return 0;
}

int charIndexInAlphabet(char currentCharInInput)
{
    // Let's iterate over every letter in the alphabet and when we come across our search character (currentCharInInput)
    // we'll grab the index where that specific character is found in the alphabet and store it in charAlphaIndex
    // & then return that index at the end of the function.

    int charAlphaIndex = 0;
    char lettersOfAlphabet[30] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0, len = strlen(lettersOfAlphabet); i < len; i++)
    {
        char currentLetterInAlpha = lettersOfAlphabet[i];
        if (currentLetterInAlpha == currentCharInInput)
        {
            // printf("The current char: %c is found at index %i of the alphabet.\n", currentLetterInAlpha, i);
            charAlphaIndex = i;
        }
    }
    return charAlphaIndex;
}
