// Problem Set 3: Runoff

// This program implements a ranked-choice voting ('instant runoff') system, where
// voters can vote for more than one candidate - ranking them in order of preference.
// By considering ranked preferences, a voting system may be able to choose a winner
// that more accurately reflects the preference of the voters.

// In the 'instant runoff' system, voters can rank as many candidates as they wish.
// If any candidate has a majority (>50%) of the first preference votes, that candidate
// is declared the winner.
// If no candidate has >50% of the vote, then an 'instant runoff' occurs.
// The candidate who received fewest number of votes is eliminated from the election,
// and anyone who originally chose that candidate as their 1st preference now has their
// 2nd pref considered (simulating what would have happened if least popular candidate
// had not been in election to begin with).
// The process repeats: if no candidate has a majority of the votes, the last place
// candidate is eliminated, and anyone who voted for them will instead vote for their
// next preference (who hasn't themlselves already been eliminated).
// Once a candidate has a majority, that candidate is declared the winner.

// Header files
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Defines two constants: Max voters and candidates
// Max number of voters in the election
#define MAX_VOTERS 100
// Maximum number of candidates in the election
#define MAX_CANDIDATES 9

// A two-dimensional array, preferences:
// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Defining a new struct, candidate:
// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;        // candidate's name
    int votes;          // number of votes they currently have
    bool eliminated;    // bool value that indicates if eliminated from election
}
candidate;

// Array of candidates: keeps track of all of the candidates in the election
candidate candidates[MAX_CANDIDATES];

// Global variables: numbers of voters (voter_count) and candidates (candidate_count)
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
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Loop over all voters
    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // As the voter enters their preferences, the vote function is called to keep
        // track of all of the preferences. If at any point, the ballot is deemed to be
        // invalid, the program exits
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Once all of the votes are in, another loop begins. This one loops through the
    // runoff process of checking for a winner and elminatin gthe last place candidate
    // until there is a winner.
    // Keep holding runoffs until winner exists:
    while (true)
    {
        // Calls the tabulate function, which looks at all of the voters' preferences
        // and computes the current vote totals, by looking at each voter's top choice
        // candidate who hasn't yet been eliminated.
        // Calculate votes given remaining candidates:
        tabulate();

        // Next, the print_winner function prints out the winner if there is one.
        // If there is, the program is over.
        // Check if election has been won:
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Otherwise, call the find_min function, to determine the fewest number of
        // votes anyone still in the election received.
        // Eliminate last-place candidates:
        int min = find_min();
        bool tie = is_tie(min);

        // Call the is_tie function.
        // If tie, everyone wins:
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

        // Otherwise, call the eliminate function, and the last-place candidate(s)
        // is/are eliminated from election.
        // Eliminate anyone with minimum number of votes:
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// 1) COMPLETE THE VOTE FUNCTION:
// The function takes arguments voter, rank and name. If name is a match for the name
// of a valid candidate, then update the global preferences array to indicate that
// the voter has that candidate as their rank preference (where 0 is the 1st pref,
// 1 is the 2nd pref, etc).
// If the preference is successfully recorded, the function should return true; the
// function should return false otherwise (if, for instance, name is not the name of
// one of the candidates).

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate/loop through candidates array (of size equal to candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        // Check whether name provided is equal to existing name in the candidates array
        if (strcmp(name, candidates[i].name) == 0)    // if equal (==0)
        {
            // If name is a candidate, add vote/update preferences array, and return true
            // Recall that preferences[i][j] stores the index of the candidate who is the
            // jth ranked preference for the ith voter
            preferences[voter][rank] = i;
            return true;
        }
    }
    // Else, if name is not a candidate, return false
    return false;
}

// 2) COMPLETE THE TABULATE FUNCTION:
// The function should update the number of votes each candidate has at this stage
// in the runoff.
// Recall that at each stage in the runnoff, every voter effectively votes for their
// top-preferred candidate who has not already been eliminated.

// Tabulate votes for non-eliminated candidates
// Keep tabs on which candidates are still in array, and which have been eliminated
void tabulate(void)
{
    // Iterate/loop through candidates array
    // Recall that, for voter i, their top choice candidate is represented by
    // preferences[i][0], their second choice candidate by preferences[i][1], etc...

    // First (outer) loop iterates over first part of 2D array (i.e. voter)
    // Recall that voter_count stores the number of voters in the election
    for (int i = 0; i < voter_count; i++)
    {
        // Second (inner) loop iterates over second part of 2D array (i.e. rank)
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate not eliminated, update their vote
            // Recall that candidate struct has a field called eliminated - which will
            // be true if the candidate has been eliminated from the election
            if (candidates[preferences[i][j]].eliminated == false)
            {
                // Recall that candidate struct has a field called votes
                // Update this field for each voter's prefered candidate
                candidates[preferences[i][j]].votes++;
                // Break out of inner for loop, and back to outer for loop
                break;
            }
        }
    }
    return;
}

// 3. COMPETE THE PRINT_WINNER FUNCTION:
// If any candidate has more than half of the vote, their name should be printed to
// stdout and the function should return true.
// If nobody has won the election yet, the function should return false.

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Recall that voter_count stores the number of voters in the election.
    // So, in order to express number of votes needed to win election, we can simply
    // divide the voter_count by 2 - then, if a candidate's number of votes are greater
    // than half, they have a majority and win the election.

    int halfVotes = voter_count / 2;

    // Iterate/loop through candidates array (of size equal to candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate's number of votes are greater than half of the total vote...
        if (candidates[i].votes > halfVotes)
        {
            // Print candidate name as winner, and return true.
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // If no winner, return false.
    return false;
}

// 4. COMPLETE THE FIND_MIN FUNCTION:
// The function should return the minimum vote total for any candidate who is still
// in the election.
// Loop through the candidates to find the one who is both still in the election,
// and has the fewest number (minimum) votes.

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Recall that MAX_VOTERS stores the maximum amount of voters
    int min = MAX_VOTERS;

    // Iterate/loop through candidates array (of size equal to candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate has not been eliminated and their vote is less than the min vote...
        if (candidates[i].eliminated == false && candidates[i].votes < min)
        {
            // then reassign the min vote
            min = candidates[i].votes;
        }
    }

    return min;
}

// 5.  COMPLETE THE IS_TIE FUNCTION:
// The function takes an argument min, which will be the minimum number of votes that
// anyone in the election currently has.
// The function should return true if every candidate remaining in the election has
// the same number of votes, and should return false otherwise.

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate/loop through candidates array (of size equal to candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        // If any (non-eliminated) candidate does not have the minimum number of votes...
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            // no tie, so return false
            return false;
        }
    }

    // Otherwise, there is a tie, so return true
    return true;
}

// 6. COMPLETE THE ELIMINATE FUNCTION:
// The function takes an argument min, which will be the minimum number of votes that
// anyone in the election currently has.
// The function should eliminate the candidate(s) who have min number of votes.

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate/loop through candidates array (of size equal to candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate has the minimum number of votes...
        if (candidates[i].votes == min)
        {
            // set eliminated to true
            candidates[i].eliminated = true;
        }
    }
    return;
}
