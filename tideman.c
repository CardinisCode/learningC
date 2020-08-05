#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
                printf("Your vote function didnt work as expected\n");
                //printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    // lock_pairs();
    // print_winner();
    return 0;
}

// Update ranks given a new vote
// ranks[i] is voter's ith preference so:
//  -   ranks[0] = voter's 1st preference
//  -   ranks[1] = voter's 2nd preference
//  -   ranks[2] = voter's 3rd preference

// Vote works!
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        string current_candidate = candidates[candidate];
        if (strcmp(current_candidate, name) == 0)
        {
            ranks[rank] = candidate;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int preferred = 0; preferred < candidate_count - 1; preferred++)
    {
        int prefererred_candidate = ranks[preferred];
        for (int over = preferred + 1; over < candidate_count; over++)
        {
            int over_candidate = ranks[over];
            preferences[prefererred_candidate][over_candidate] += 1;
        }
    }

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
    // TODO
    for (int candidate_i = 0 ; candidate_i < candidate_count; candidate_i++)
    {
        for (int candidate_j = 0; candidate_j < candidate_count; candidate_j++)
        {
            if (preferences[candidate_i][candidate_j] > preferences[candidate_j][candidate_i])
            {
                pairs[pair_count].winner = candidate_i;
                pairs[pair_count].loser = candidate_j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int current = 0; current < pair_count - 1; current++)
    {
        int current_winner = preferences[pairs[current].winner][pairs[current].loser];
        int current_loser = preferences[pairs[current].loser][pairs[current].winner];
        int current_strength_of_victory = current_winner - current_loser; 

        int winning_index = current; 

        for (int comparison = current + 1; comparison < pair_count; comparison++)
        {
            int comparison_winner = preferences[pairs[comparison].winner][pairs[comparison].loser];
            int comparison_loser = preferences[pairs[comparison].loser][pairs[comparison].winner];
            int comparison_strength_of_victory = comparison_winner - comparison_loser;

            if (comparison_strength_of_victory > current_strength_of_victory)
            {
                winning_index = comparison; 
            }
        }

        pair temp = pairs[current];
        pairs[current] = pairs[winning_index]; 
        pairs[winning_index] = temp;
    }

    // for (int pair = 0; pair < candidate_count; pair++)
    // {
    //     int winner_votes = preferences[pairs[pair].winner][pairs[pair].loser];
    //     int loser_votes = preferences[pairs[pair].loser][pairs[pair].winner];
    //     int difference = winner_votes - loser_votes;

    //     printf("At Index %i: Winner %i with %i votes & Loser: %i with %i votes\n & a difference: %i\n", pair, pairs[pair].winner, winner_votes, pairs[pair].loser, loser_votes, difference);
    //     // printf("At index %i: winner: %i loser: %i %i\n", pair, pairs[pair].winner, pairs[pair].loser);
    // }
    return;
}

// // Lock pairs into the candidate graph in order, without creating cycles
// void lock_pairs(void)
// {
//     // TODO
//     return;
// }

// // Print the winner of the election
// void print_winner(void)
// {
//     // TODO
//     return;
// }

