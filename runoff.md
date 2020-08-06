Our Runoff challenge:

Their main() function will take each voter's elected candidates in ranked order. 
It's our job to write to determine which candidate has the majority of the votes (%50 or higher). 

If there is no majority, 
    -   we run an instant runoff
        -   where the weakest candidate gets eliminated 
        -   then from the remaining candidates -> we (once again) check which candidate has the majority. 
->  We keep repeating this process until we have either:
-   1 candidate with the majority of the votes
    OR 
-   A tie between between all the candidates

Desired outcome: 
-   The code we write 
    - For functions 
        -   vote(), tabulate(), print_winner(), find_min(), is_tie(), eliminate()

    Enables main() to print the name/s of:
        -   the candidate with the majority win
        OR
        -   all the candidates (in the case of a tie)

    
Below you'll find:                          Line:
-   Code Breakdown                          35
    -   Preferences array                   45
    -   Struct: candidate                   56
    -   Global Variables
        -   voter_count                     66
        -   candidate_count                 67
    -   Main()                              69
-   Our Challenge                           104
-   Notes for future self                   202

** Code Breakdown:

* We’re defining two constants: 
-   MAX_CANDIDATES
    -   for the maximum number of candidates in the election
-   MAX_VOTERS
    -   for the maximum number of voters in the election.


* There is a two-dimensional array: 
-   preferences. 
    -   The array preferences[i] will represent all of the preferences for voter number i
    -   The integer preferences[i][j] here will store the index of the candidate who is the jth preference for voter i.

    -   Preference Array format: 
        ->  They're wanting you to store your preferences array in this format: 
        -   preferences[voter_index][preference_index] = candidate_index 
        So you'll want to create:
        -   an (outer) loop through voters (from 0 to voter_count)
        -   an (inner) loop through preferences (from 0 to candidate count)

* There is a Struct:
-   candidate
    -   Every candidate has:
        -   a string field for their name, 
        -   int representing the number of votes they currently have,
        -   a bool value called eliminated
            ->  indicates whether the candidate has been eliminated from the election. 
    ->  The array candidates will keep track of all of the candidates in the election.

The program also has two global variables: 
-   voter_count
-   candidate_count.

* Now onto main():
-   Notice that after determining the number of candidates and the number of voters, 
    ->  the main voting loop begins, 
    -   giving every voter a chance to vote. 
    -   As the voter enters their preferences, 
        ->  the vote function is called to keep track of all of the preferences. 
        -   If at any point, the ballot is deemed to be invalid, the program exits.

-   Once all of the votes are in, 
    ->  another loop begins: 
        -   this one’s going to keep looping through the runoff process of
            -   checking for a winner
            -   & eliminating the last place candidate until there is a winner.

-   The first call here is to a function called tabulate,
    -   which should:
        -   look at all of the voters’ preferences
        -   compute the current vote totals, 
            ->  by looking at each voter’s top choice candidate who hasn’t yet been eliminated. 

-   the print_winner function:
    -   if there is a winner: 
        -   it should print out the winner's name
        -   it should end the program
    -   Otherwise:
        -   the program needs to determine the fewest number of votes anyone still in the election received (via a call to find_min)
        -   If it turns out that everyone in the election is tied with the same number of votes 
            (as determined by the is_tie function)
            -   the election is declared a tie
        -   otherwise:
            -   the last-place candidate (or candidates) is eliminated from the election 
                via a call to the eliminate function.

*** NB: They created the main function with explicit instruction not to add any code to main()

** Our Challenge:

- We have 6 functions we need to "write" code for: 

                            Line:
#1: vote()                  116
#2: tabulate()              134
#3: print_winner()          153
#4: find_min()              164
#5: is_tie()                173
#6: eliminate()             193

* Function #1: Vote()
-   The function takes arguments:
    -   voter, rank, and name. 

-   Iterate through the candidates (from 0 to candidate count)
    -   If 'name' is a match for the name of a valid candidate, 
        -   (then) you should update the global preferences array 
        -   thankfully for this function, we can use the 'voter' & 'rank' variables provided in the arguments:
            -   preferences[voter][rank] = candidate_index

-   If the preference is successfully recorded, 
    -   the function should return true; 
    Otherwise (if, for instance, name is not the name of one of the candidates):
    -   the function should return false

-   You may assume that no two candidates will have the same name.


* Function #2: Tabulate()
-   The function should update the number of votes each candidate has at this stage in the runoff.
-   Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.

-   Hints (Recall): 
    -   voter_count stores the number of voters in the election.
    -   for a voter i, (so iterate through the voters)
        -   their top choice candidate is represented by preferences[i][0],
                preferences[voter i][preference 0] -> Voter's #1st preference candidate
        -   their second choice candidate by preferences[i][1]
            -   preferences[voter i][preference 1] -> Voter's #2nd preference candidate
        -   etc....

    -   the candidate struct has a field called eliminated -> 
        -   which will be true if the candidate has been eliminated from the election.
    -   the candidate struct has a field called votes, 
        -   which you’ll likely want to update for each voter’s preferred candidate.


* Function #3: Print winner
-   If any candidate has more than half of the vote, 
    -   their name should be printed to stdout
    -   the function should return true.
-   (else) If nobody has won the election yet, 
    -   the function should return false.
-   Hint: 
    -   voter_count stores the number of voters in the election. 
    Q: How would you express the number of votes needed to win the election?


* Function #4: find_min()
-   The function should return the minimum vote total for any candidate who is still in the election.
-   Hints: 
    -   You’ll likely want to loop through the candidates to find the one who is:
        -   still in the election
        -   has the fewest number of votes. 
    Q: What information should you keep track of as you loop through the candidates?


* Function #5: is_tie()
-   The function takes an argument min, 
    -   which will be the minimum number of votes that anyone 
        in the election currently has.
-   if every candidate remaining in the election has the same 
    number of votes
    ->   The function should return true

-   Otherwise: 
    ->   return false.
    
-   Hints: 
    -   a tie happens if every candidate still in the election 
        has the same number of votes.
    -   the is_tie function takes an argument min, 
        -   which is the smallest number of votes 
            any candidate currently has. 
    Q: How might you use that information to determine if the election is a tie (or, conversely, not a tie)?


* Function #6: Eliminate()
-   The function takes an argument min, 
    -   which will be the minimum number of votes that anyone
        in the election currently has.
-   The function should eliminate the candidate (or candidates) 
    who have min number of votes.
    

**** NB ******
** Notes for future self:
-   Always watch the videos provided with the challenge 
    (sometimes they give more detail/info in their video than in their written text)
-   Write 1 function at a time, 
    -   run 'check50' constantly to compare my code with their expectations
    -   ONLY once all requirements for the current function have been met, 
        ->  then move forward to the next function! 
-   If there are 2D arrays, 
    -   create a function for your own testing that outputs the data you're working on
        so you can compare the data you're creating to their/your expectations. 


