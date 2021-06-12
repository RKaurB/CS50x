// Problem Set 3: Plurality

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Defines a struct type called candidate
// Candidates have name and vote count
typedef struct
{
    // Each candidate has two fields
    string name;
    int votes;
}
candidate;

// Defines a global array of candidates (of type 'candidate', above) which holds up to a max of 9 candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

// Main program
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// 1. Complete the vote function, below:
// (i) vote should take a single argument, a string called name,
// representing the name of the candidate who was voted for.
// (ii) If name matches one of the names of the candidates in the
// election, then update that candidate's vote total to account
// for the new vote.  The vote function in this case should return
// true to indicate a successful ballot.
// (iii) If name does not match the name of any of the candidates in
// the election, no vote totals should change, and the vote function
// should return false to indicate an invalid ballot.
// (iv) You may assume that no two candidates will have the same name.

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop through candidate's array (of size equal to candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        // Check whether name provided is equal to a name in the candidates array
        if (strcmp(name, candidates[i].name) == 0)    // if equal (==0)
        {
            // If they match, increment that candidate's vote total
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// 2. Complete the print_winner function, below:
// (i) The function should print out the name of the candidate who
// received the most votes in the election, and then print a newline.
// (ii) It is possible that the election could end in a tie if
// multiple candidates each have the maximum number of votes. In that
// case, you should output the names of each of the winning
// candidates, each on a separate line.

// Print the winner (or winners) of the election
void print_winner(void)
{
    int most_votes = -1;
    string winning_candidate;
    // Find candidate(s) with most votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= most_votes)
        {
            most_votes = candidates[i].votes;
            winning_candidate = candidates[i].name;
            // Print name of candidate(s) with most votes, i.e. winning candidate(s)
            printf("%s\n", winning_candidate);
        }
    }
    return;
}
