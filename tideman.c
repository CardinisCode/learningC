#include <cs50.h>
#include <stdio.h>
#include <string.h>

// All the below is their code defining the various variables and structs that will be needed.

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool is_cycle(pair past, int loser, int pair_index);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        printf("\n");

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// The below functions are for me to write to ensure the main() function works as expected. 

// Update ranks given a new vote
// ranks[i] is voter's ith preference so:
//  -   ranks[0] = voter's 1st preference
//  -   ranks[1] = voter's 2nd preference
//  -   ranks[2] = voter's 3rd preference

// This function makes sure that the voter's current candidate (in iteration) is in fact in the election.
bool vote(int rank, string name, int ranks[])
{
    // We'll iterate over the candidates to see if there's any candidate that matches the name provided by the current voter:
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        // We'll grab the name of the current candidate (the candidate sitting at index 'candidate' in the candidates array)
        string current_candidate = candidates[candidate];
        // If the name of the current candidate matches the 'name' (provided by the voter)
        if (strcmp(current_candidate, name) == 0)
        {
            // Then we'll update the ranks array to reflect that at this 'rank', we'll find the index 'candidate' for the current candidate
            ranks[rank] = candidate;
            // Now that we've found a match, this function can true & exit. The function has served it's purpose. 
            return true;
        }
    }
    // If it gets to the point, it means no matches were found 
    //  -> this means voter voted for a candidate not in the election.
    return false;
}

// Update preferences for current voter given the voter's candidates in ranked order
void record_preferences(int ranks[])
{
    // We'll first iterate over the candidate array from the beginning to the end-1
    // Eg: 0, 1, 2, 3 (not including 4)
    for (int preferred = 0; preferred < candidate_count - 1; preferred++)
    {
        // It will find the candidate found at the 'preferred' index in the ranks array and this candidate will be our preferred candidate
        // It will start from the most preferred candidate and descend down to the least preferred candidate
        int prefererred_candidate = ranks[preferred];

        // Now to look over our candidates array from the current preferred candidate's index + 1 to the end of the candidate array
        // Eg 1, 2, 3, 4
        // So the candidate at index 0 is compared to the candidate at index 1 & so forth. 
        for (int over = preferred + 1; over < candidate_count; over++)
        {
            // It will find the candidate found at the 'over' index in our ranks array and this candidate will be our over_candidate
            int over_candidate = ranks[over];

            // Now we update our preference array to reflect that the 'preferred' candidate has +1 vote against the 'over' candidate
            preferences[prefererred_candidate][over_candidate] += 1;
        }
    }
    // This is to allow me see the output of the preferences array in printed form
    // to follow the progress as each voter's preferences are added in.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // We'll compare the candidates against each other
    for (int candidate_i = 0 ; candidate_i < candidate_count; candidate_i++)
    {
        for (int candidate_j = 0; candidate_j < candidate_count; candidate_j++)
        {
            // Then we check to see in the current pair, which candidate has the higher votes (our winner)
            if (preferences[candidate_i][candidate_j] > preferences[candidate_j][candidate_i])
            {
                // We can now update the current pair's winner (who has the higher votes) and loser
                pairs[pair_count].winner = candidate_i;
                pairs[pair_count].loser = candidate_j;
                // And update the pair count to reflect that we've found a valid pair.
                pair_count += 1;
            }
            // If the 2 candidates in the pair are in a draw, we don't do anything and move onto the next pair
            // If preferences[candidate_j][candidate_i] > preferences[candidate_i][candidate_j], 
            //  it will be picked up when candidate i's index reaches that index value. 
        }
    }
    // Now our pairs have been added to the pairs array with each pair having their allocated winner and loser.
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // For every (current) pair:
    for (int current = 0; current < pair_count - 1; current++)
    {
        // We'll get the winner, loser and calculate the strength of victory for this current pair:
        int current_winner = preferences[pairs[current].winner][pairs[current].loser];
        int current_loser = preferences[pairs[current].loser][pairs[current].winner];
        int current_strength_of_victory = current_winner - current_loser; 

        // We want to create a winning index variable whose's value will default to the current index in iteration. 
        int winning_index = current; 

        // Now to compare the current pair to every other pair in the pairs array:
        for (int comparison = current + 1; comparison < pair_count; comparison++)
        {
            // We'll get the comparison pair's winner, loser & calculate the comparison's strength of victory
            int comparison_winner = preferences[pairs[comparison].winner][pairs[comparison].loser];
            int comparison_loser = preferences[pairs[comparison].loser][pairs[comparison].winner];
            int comparison_strength_of_victory = comparison_winner - comparison_loser;

            // If any of the comparison pairs have a higher strength of victory compared to the current's strength of victory
            if (comparison_strength_of_victory > current_strength_of_victory)
            {
                // Then we want to update the winning index to reflect the index where that comparison pair was found
                // in the pair array:
                winning_index = comparison; 
            }
        }
        
        // For every current pair, we'll need to switch the pairs[current] with the pair[winning_index] 
        pair temp = pairs[current];
        pairs[current] = pairs[winning_index]; 
        pairs[winning_index] = temp;
    }
    return;
}

// This function is designed to be called by lock_pairs()
//  It will take the current loser from lock_pairs and iterate through all the pairs 
//  from the past pair index (from lock_pairs) -1 -> the pair at index 0
//  And if at any point, the current loser matches any of the pairs' winner's, then it has found a cycle
// So it will return true. 

bool is_cycle(pair past, int loser, int pair_index)
{
    // Let's iterate over the pairs in reverse order from pair_index-1 back to 0. 
    for (int i = pair_index - 1; i >= 0; i--)
    {
        pair current = pairs[i]; 
        if (past.winner == current.loser)
        {
            // There's a link
            printf("There's a link: %i\n", past.winner);
            if (locked[current.winner][current.loser] == true && loser == current.winner)
            {
                // There's a cycle!
                return true;
            }
            // else -> call the function recursively with the current pair, the original loser and the current index
            return is_cycle(current, loser, i);
        }
    }
    // No cycle found by this point so it returns false and exits.
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // It will iterate over every pair in the pairs array:
    for (int pair_index = 0; pair_index < pair_count; pair_index++)
    {
        // It will grab the winner and loser from that pair
        int winner = pairs[pair_index].winner; 
        int loser = pairs[pair_index].loser;

        // Then it will run is_cycle with the pair 'pairs[pair_index]', the current loser, & current pair index
        // If is_cycle resolves to false:
        if (!is_cycle(pairs[pair_index], loser, pair_index))
        {
            // Then we can update the locked array so there's now an arrow pointing from the winner to the loser
            locked[winner][loser] = true;
        }
        // If the is_cycle resolves to true, we do nothing and move onto the next pair.
    }
    return;
}


// // Print the winner of the election (the source of the graph)
void print_winner(void)
{
    // For every candidate:
    for (int current = 0; current < candidate_count; current++)
    {
        // We'll set the candidateIsSource to a defaul false value
        bool candidateIsSource = false;

        // Before comparing current candidate to every other candidate in the array:
        for (int comparison = 0; comparison < candidate_count; comparison++)
        {
            // If candidate[comparison] is pointing at candidate[current]:
            if (locked[comparison][current] == true)
            {
                // Then candidate[current] is not the source.  
                // Update candidate's candidateIsSource to true to reflect they have an arrow pointing to them.
                candidateIsSource = true;
                // Move onto the next candidate.
                break;
            }
        }
        // After we've compared the current candidate to all their peers
        //  we can check if their candidateIsSource still remains as false 
        //  -> to indicate no arrows were found to be pointing to the current candidate

        if (candidateIsSource == false)
        {
            // We can print the candidate's name and break to make sure it doesn't move onto the next candidate
            // in our outer loop (current)
            printf("%s\n", candidates[current]);
            break;
        }
    }
    return;
}

