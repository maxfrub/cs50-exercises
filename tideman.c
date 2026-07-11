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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int locked_pair_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void swap(pair one, pair two, int i);
int search_cycle(int winner, int i);

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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count - 1; j++)
        {
            int n = j + 1;
            preferences[ranks[i]][ranks[n]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                j++;
            }
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int times = 1;
    for (int k = 0; k < pair_count; k++)
    {
        for (int i = 0; i < pair_count - times; i++)
        {
            int j = i + 1;
            if (preferences[pairs[i].winner][pairs[i].loser] -
                    preferences[pairs[i].loser][pairs[i].winner] <
                preferences[pairs[j].winner][pairs[j].loser] -
                    preferences[pairs[j].loser][pairs[j].winner])
            {
                swap(pairs[i], pairs[j], i);
            }
        }
        times++;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (search_cycle(pairs[i].winner, i) != 2)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            locked_pair_count++;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    bool not;
    for (int i = 0; i < candidate_count; i++)
    {
        not= false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                not= true;
                break;
            }
        }
        if (not== false)
            printf("%s\n", candidates[i]);
    }
    return;
}

void swap(pair one, pair two, int i)
{
    pairs[i] = two;
    pairs[i + 1] = one;
}

int search_cycle(int winner, int i)
{
    printf("Estoy en %d\n", winner);
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[j][winner] == true)
        {
            for (int k = 0; k < i; k++)
            {
                if (pairs[k].winner == j)
                {
                    printf("Voy de %d a %d\n", j, i);
                    if (search_cycle(j, i) == 1)
                    {
                        return 2;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
