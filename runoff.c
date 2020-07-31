#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc < 2){
        // printf("You have not provided any arguments. Please 1+ arguments when calling this program.\n");
        return 1;
    }
    // To find the number of candidates provided, take the total no. of arguments - 1
    // (As the first argument by default is the filename to run)
    candidate_count = argc - 1;

    // If there are more candidates than the preset max number of candidates:
    if (candidate_count > MAX_CANDIDATES)
    {
        // printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    
    // Let's add the candidate's name and set the candidate's variables 'votes' to 0 and 'eliminated' to false
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    
    // To get the number of voters, we'll ask the user:
    voter_count = get_int("Number of voters: ");
    // Now to check that the user hasn't provided a higher vote count than the max number of voters. 
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
    // For the current voter
    for (int i = 0; i < voter_count; i++)
    {
        // The ranking will be from 0 to the number of candidates:
        for (int j = 0; j < candidate_count; j++)
        {
            // Here we ask the user to provide the candidate's name for the current voter at the current rank:
            string name = get_string("Rank %i: ", j + 1); 

            // Record vote, unless it's invalid
            // by calling the function vote with i (current iteration through voters), j (current rank) & name (candidate's name provided by user for current rank)
            if (!vote(i, j, name))
            {
                // printf("Invalid vote.\n");
                return 4;
            }
        }
            printf("\n");
    }

    //Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        printf("The min vote value is: %i\n", min);

        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// This is a function we created (not part of their code and not added to my code submission)
// Outputs Internal datastructures to make debugging easier.
void outputPreferences(void) 
{
    printf("\n");
    printf("Preferences\n");
    printf("         ");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%i    ", i + 1);
    }
    printf("\n");
    for (int voter = 0; voter < voter_count; voter++) 
    {
        printf("Voter %i: ", voter);
        for (int preference = 0; preference < candidate_count; preference++) 
        {
            printf("%s    ", candidates[preferences[voter][preference]].name);
        }
        printf("\n");
    }

    printf("\n");
    printf("Candidates:\n");
    printf("index | name | vote | eliminated\n");
    for (int i = 0; i < candidate_count; i++) 
    {
        printf("  %i   |   %s  |   %i  |     %d     \n", i, candidates[i].name, candidates[i].votes, candidates[i].eliminated);
    }
    printf("\n");
    return;
}


// Function #1: vote()
// Iterates through candidates array, and 
// [X] #1: if the current candidate (in iteration) matches (in name) to the string 'name'
// [X] #2: Update the preferences array -  to indicate that the voter voter has that candidate as their rank preference (from 0, 1, 2 etc)
// [X] #3: If the preference is successfully recorded, 
//      the function should return true
// [X] #4: (else)  (if, for instance, name is not the name of one of the candidates).
//      return false

//AIM:
// Preferences
//          1    2    3    
// Voter 0: a    b    c    
// Voter 1: c    b    a    

bool vote(int voter, int rank, string name)
{
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (strcmp(candidates[candidate].name, name) == 0)
        {
            preferences[voter][rank] = candidate;
            return true;
        }
    }
    return false;
}

// Function #2: tabulate
// It takes no input and returns no input. 
// It's purpose: 
//  - to update the number of votes each candidate has at this stage in the runoff.
//  Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.
// So we're looking for every voter's top candidate: the first candidate that has not been eliminated
// and when we find the top candidate we add +1 to the candidate's votes
 
void tabulate(void) 
{
    for (int voter_index = 0; voter_index < voter_count; voter_index++)
    {
        for (int preference = 0; preference < candidate_count; preference++)
        {
            int candidate_index = preferences[voter_index][preference];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }

    outputPreferences();

    return;
}


// Function #3: print_winner
// If any candidate has more than half of the vote, 
//      print their name to stdout
//      return true.
// If nobody has won the election yet, 
//      return false.
// Note: Every voter has only 1 vote that counts: 
//      their vote goes to their top candidate
//      so the number of valid votes = number of voters (voter_count)

bool print_winner(void)
{
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        float candidate_votes = candidates[candidate_index].votes;
        float percentage = candidate_votes / voter_count * 100;
        
        if (percentage > 50.00)
        {
            printf("%s\n", candidates[candidate_index].name);
            return true;
        }
    }
    return false;
}

// Function #4: find_min()
// The function should return the minimum vote total for any candidate who is still in the election.
// Hints
//  You’ll likely want to loop through the candidates to find the one who is both
//  -   still in the election
//  -   has the fewest number of votes. 
//  Q: What information should you keep track of as you loop through the candidates?

// It takes no input and should return an int (the minimal vote total)

int find_min(void)
{
    printf("\n");
  
    // int lowest_vote_count;

    int lowest_index = -1;
    int lowest_votes = 0;

    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (!candidates[candidate].eliminated)
        {
            int current_votes = candidates[candidate].votes;
            if (lowest_index == -1)
            {
                lowest_votes = current_votes;
                lowest_index = candidate;
            }
            if (current_votes < lowest_votes)
            {
                lowest_votes = current_votes;
                lowest_index = candidate;                
            }
        }
    }

    printf("Lowest is: %i\n", lowest_votes);
    return lowest_votes;
}

// Function #5: is_tie()
// takes an argument min, 
//      - will be the minimum number of votes that anyone in the election currently has.
// if every candidate remaining in the election has the same number of votes:
//      The function should return true , 
//  else 
//      return false otherwise.

bool is_tie(int min)
{
    printf("\n");
    
    printf("Our min value: %i\n", min);

    int total_valid_votes = 0;
    int candidates_with_min_vote = 0;
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (!candidates[candidate_index].eliminated)
        {
            total_valid_votes++;
            if (candidates[candidate_index].votes == min)
            {
                candidates_with_min_vote ++;
            }
        }
    }
    
    bool multiple_candidates_with_min_votes = candidates_with_min_vote > 1;
    bool no_candidates_with_more_than_min = candidates_with_min_vote == total_valid_votes;

    if (multiple_candidates_with_min_votes && no_candidates_with_more_than_min)
    {
        printf("Tie!\n");
        return true;
    }
    return false;
}




// Function #6: eliminate()
// As Input, the function takes an argument min, 
//  -   which will be the minimum number of votes that anyone in the election currently has.
//  The function should eliminate the candidate (or candidates) who have min number of votes.
void eliminate(int min)
{
    printf("\n");

    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (candidates[candidate_index].votes == min)
        {
            candidates[candidate_index].eliminated = true;
            printf("elimiated %s\n", candidates[candidate_index].name);
        }
    }
    return;
}
