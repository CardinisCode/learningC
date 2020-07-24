// The Readability challenge:
// Design and implement a program, readability, that computes the Coleman-Liau index of the text.

// Rules: 
// # Your program must prompt the user for a string of text (using get_string).
// # Your program should count the number of letters, words, and sentences in the text. 
//      You may assume that:
//      -   a letter is any lowercase character from a to z or any uppercase character from A to Z, 
//      -   any sequence of characters separated by spaces should count as a word, 
//      -   and that any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.
// # Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
//      Like: "Grade 5"
//      # If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), 
//          your program should output "Grade 16+" instead of giving the exact index number. 
//      # If the index number is less than 1, 
//          your program should output "Before Grade 1".

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// I want to have my main function first, for easy access, so I'll
// just reference my 3 other functions here so main function sees them.
float calculate_letters(string quote_line, int quote_length);
float calculate_words(string quote_line, int quote_length);
float calculate_sentences(string quote_line, int quote_length);

int main(void)
{
    // Let's start by getting the user to give us a paragraph to check:
    string quote_line = get_string("Text: \n");
    int quote_length = strlen(quote_line);

    // Now to calculate the letter, word and sentence count:
    float letter_count = calculate_letters(quote_line, quote_length);
    float word_count = calculate_words(quote_line, quote_length);
    float sentence_count = calculate_sentences(quote_line, quote_length);

    // Now we need to calculate our L & S values according to the Coleman-Liau index:
    // L = the average number of letters per 100 words
    float L = letter_count / word_count * 100;
    // S = the average number of sentences per 100 words
    float S = sentence_count / word_count * 100;
    // Now the Coleman-Liau index calculation:
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // We know we need the resulted value to be rounded:
    int grade_level = round(index);

    // To end this, let's print the grade level for the provided paragraph:

    if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
    return 0;
}

float calculate_letters(string quote_line, int quote_length)
{
    // I'll first get the overall letter count using Int:
    int letter_count = 0;
    for (int i = 0, len = quote_length; i < len; i++)
    {
        char current_letter = quote_line[i];
        if ((current_letter >= 65 && current_letter <= 90) || (current_letter >= 97 && current_letter <= 122))
        {
            letter_count ++;
        }
    }
    // Now to convert the letter_count to float as needed:
    float letters = (float) letter_count;
    return letters;
}

float calculate_words(string quote_line, int quote_length)
{
    // I'll first get the overall word count (using Int) by counting the spaces:
    // (Counting from 1 as there will always be 1+ more word than spaces in a sentence!)
    int space_count = 1;
    for (int i = 0, len = quote_length; i < len; i++)
    {
        char current_letter = quote_line[i];
        if (current_letter == ' ')
        {
            space_count ++;
        }
    }
    // Now to convert the letter_count to float as needed:
    float words = (float) space_count;
    return words;
}

float calculate_sentences(string quote_line, int quote_length)
{
    // Let's start by first getting the overall sentence count (using Int):
    int punctuation_count = 0;
    for (int i = 0, len = quote_length; i < len; i++)
    {
        char current_letter = quote_line[i];
        int ascii_value = (int) current_letter;

        // We'll be counting every '!', '?' & '.' as valid endings for a sentence
        // So for every occurrence ('!', '?' & '.') we'll add +1 to our punctuation_count:
        if (ascii_value == 33 || ascii_value == 46 || ascii_value == 63)
        {
            punctuation_count ++;
        }
    }
    // Now to convert the punctuation_count to float as needed:
    float sentences = (float) punctuation_count;
    return sentences;
}

