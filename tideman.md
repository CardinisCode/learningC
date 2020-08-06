The Tideman challenge: 

The main() function asks the user to provide the candidates each voter elected in ranked order. 
It's our job to write code that finds the winner of the election.

*** Desired outcome: 
- The code we write 
    -   for functions: 
        -   vote
        -   record_preferences
        -   add_pairs
        -   sort_pairs
        -   lock_pairs
        -   print_winner

    Should enable their main() function to find the source candidate (the winner) in the election 
    -   using the tideman algorithm/process 
    -   & print the winner's name at the end. 

Below you'll find:          Line:
-   Challenge background    26
-   Code Breakdown          50
-   Our challenge           111


***Background:

Put more formally, the Tideman voting method consists of three parts:

-   Tally: 
    -   Once all of the voters have indicated all of their preferences,
        determine, for each pair of candidates, 
        ->  who the preferred candidate is
        ->  by what margin they are preferred.

-   Sort: 
    -   Sort the pairs of candidates in decreasing order of strength
        of victory
        ->   where strength of victory is defined to be the number of voters who prefer the preferred candidate.

-   Lock: 
    -   Starting with the strongest pair, 
        ->  go through the pairs of candidates in order
        ->  “lock in” each pair to the candidate graph
            -   so long as locking in that pair does not create
                a cycle in the graph.

Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!

Code Breakdown:

#1: There are 2x two-dimensional arrays 
    *1: preferences. 
    -   The integer preferences[i][j] will represent the number of voters
        -> who prefer candidate i over candidate j.

    *2: Locked:     
    -   will represent the candidate graph. 
    -   is a boolean array, 
        -   so locked[i][j] being true: represents the existence of an edge pointing from candidate i to candidate j; 
        -   false means there is no edge. 
        (If curious, this representation of a graph is known as an “adjacency matrix”).

#2: Next up is a struct called pair
    ->  used to represent a pair of candidates where each pair includes:
        -   the winner’s candidate index
        -   the loser’s candidate index.

* The candidates themselves are stored in the array candidates, 
-   which is an array of strings representing the names of each of the candidates. 

* There’s also an array of pairs, 
-   which will represent all of the pairs of candidates 
    (for which one is preferred over the other) in the election.

* The program also has two global variables: 
-   pair_count
-   candidate_count
->  representing the number of pairs and number of candidates in the arrays pairs and candidates, respectively.

#3: Now onto main(). 
-   *1: It determines the number of candidates

-   *2: It loops through the locked graph &
        initially sets all of the values to false, 
        ->  which means our initial graph will have no edges in it.

-   *3: The program loops over all of the voters & 
        collects their preferences in an array called ranks 
        (via a call to vote)
        ->  where ranks[i] is the index of the candidate
            who is the ith preference for the voter.

-   *4: These ranks are passed into the record_preference function
        ->  whose job it is to:
            -   take those ranks
            -   update the global preferences variable.

Once all of the votes are in the pairs of candidates:
-   *5: are added to the pairs array
        ->  via a called to add_pairs
-   *6: sorted
        ->  via a call to sort_pairs
-   *7: locked into the graph
        ->  via a call to lock_pairs

Finally:
- *8:   print the name of the election’s winner
        ->  via a call to print_winner

** Our challenge:

Further down in the file, you’ll see that there are 6 functions left blank:
-   vote, record_preference, add_pairs,sort_pairs, lock_pairs, and print_winner
->  That’s up to you!

* 1: vote()
-   The function takes arguments
    -   rank
    -   name
    -   ranks. 

-   If name is a match for the name of a valid candidate (ie a candidate actually in the election), 
    -   then you should update the ranks array
        -   to indicate that the voter has that candidate
            as their rank preference 
            (where 0 is the first preference, 1 is the second preference, etc.)
    so if voter 0 votes A, B, C
    then the ranks will be: 
        0: A  1: B  2: C

-   ranks[i] here represents the user’s ith preference.

-   if the rank was successfully recorded
    -   The function should return true
-   Otherwise 
    (if, for instance, name is not the name of one of the candidates)
    -   return false  
-   You may assume that no two candidates will have the same name.

* 2: record_preferences
-   The function is called once for each voter, 
-   takes (as argument) the ranks array, 
    (recall that ranks[i] is the voter’s ith preference, where ranks[0] is the first preference).
-   The function should update the global preferences array
    -   to add the current voter’s preferences. 
        (Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j.)
-   You may assume that every voter will rank each of the candidates.

- So if voter 0 votes A, B, C
->  Then voter 0 
    -   prefers A over B & C
        -   preferences[A][B] +=1
        -   preferences[A][C] +=1
    -   prefers B over C
        -   preferences[B][C] +=1

* 3: add_pairs
-   The function should add a pair (to the pairs array) if
    -   one candidate is preferred over another 
    -   both candidates are not in a tie (ie both candidates have the same number of overall votes)
-   It should then update the global variable pair count to reflect the number of pairs that have been added to the pairs array.
    -   The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive.

-   So in pair A & B, if A has 5 votes and B has 3 votes, 
    it would be a valid pair 
    -   It gets added to the pair array
    -   We add +1 to the pairs count 

    But if A & B both have 4 votes, 
    -   We don't add this pair to the pairs array

* 4: sort_pairs
-   The function should sort the pairs array in decreasing order of strength of victory, 
    -   where strength of victory is defined to be the number of voters who prefer the preferred candidate. 
    -   If multiple pairs have the same strength of victory, you may assume that the order does not matter.
Hint: Consider the difference in the votes between the winner and the loser of every pair and sort according to this difference
- We basically want to sort the pairs so they're in order 
    from:   the strongest victory
        (the pair with the greatest difference between the winner and the loser)
    To:     the weakest victory
        (the pair with the least difference between the winner and the loser)
    -> Where pairs with the same difference can be in any order between themselves

So we have the following pairs                      Sorted version:
1)  B = 5 votes C = 4 votes -> Difference = 1       A = 7votes B = 2 votes -> difference = 5             
2)  A = 3 votes C = 6 Votes -> Difference = 3       A = 3 votes C = 6 Votes -> Difference = 3 
3)  A = 7votes B = 2 votes -> difference = 5        B = 5 votes C = 4 votes -> Difference = 1 
 
* 5: lock_pairs 
-   The function should create the locked graph, 
    -   adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.

-   Here's where you're actually adding the edges/arrows from winner to loser, 
    -   whilst ensuring that adding the arrow doesn't create a cycle 

Using the previous stats, in sorted order from strongest to weakest:
    0: A - B
    1: C - A
    2: B - C

If we added all these arrows, we'd definitely get a cycle (C -> A -> B -> C)
So we're told to ignore any pair that would create this cycle: 
    C -> A -> B
Now C doesn't have any arrows pointing to it! 

** Note this may work out to be the hardest function in this challenge. Don't give up! 
-> Feel free to create more than 1 function to solve this problem

* 6: print_winner
-   The function should print out the name of the candidate who is the source of the graph. 
    -> Basically the only candidate that has no arrows pointing to it.
-   You may assume there will not be more than one source.


    


