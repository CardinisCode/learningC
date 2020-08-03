The Tideman challenge: 

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

***Understanding:

Let’s open up tideman.c to take a look at what’s already there.

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

#3: Now onto main. 
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

Further down in the file, you’ll see that the functions vote, record_preference, add_pairs,sort_pairs, lock_pairs, and print_winner are left blank. That’s up to you!

The functions: 
* 1: vote()
-   The function takes arguments
    -   rank
    -   name
    -   ranks. 

-   If name is a match for the name of a valid candidate, 
    -   then you should update the ranks array
        -   to indicate that the voter has the candidate
            as their rank preference 
            (where 0 is the first preference, 1 is the second preference, etc.)

-   ranks[i] here represents the user’s ith preference.

-   if the rank was successfully recorded
    -   The function should return true
-   Otherwise 
    (if, for instance, name is not the name of one of the candidates)
    -   return false  
-   You may assume that no two candidates will have the same name.

