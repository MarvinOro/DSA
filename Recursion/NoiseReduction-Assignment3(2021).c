#include <stdio.h>
#include <stdlib.h>
int lowestSum = 2147483647;
void permute(int SIZE, int loops, int *curRow, int *used, int *target, int x[SIZE][SIZE])
{
    int i = 0, j = 0, Max, Min;
    if (loops == 0)
    {
        // loops 0 is a lie
        // Check that the row matches the target
        int good = 1;
        for (i = 0; i < SIZE; i++)
            if (target[i] != 0 && curRow[i] != target[i])
                good = 0;
        // IF good then add sum of noises
        if (good)
        {
            int curSum = 0;
            for (i = 0; i < SIZE; i++)
            {
                if (SIZE - 1 <= i + 2)
                { // sets boundaries for addition for loop on
                    line 33 Max = SIZE - 1;
                }
                else
                {
                    Max = i + 2;
                }
                if (0 <= (i - 2))
                {
                    Min = i - 2;
                }
                else
                {
                    Min = 0;
                }
                for (j = Min; j <= Max; j++)
                {
                    curSum += x[curRow[i] - 1][curRow[j] - 1]; // adds each valid noise
                    element
                }
            }
            if (lowestSum > curSum) // if current sum is less than lowestSum update
                lowestSum to equal curSum
                    lowestSum = curSum;
        }
        return;
    }
    // Try all values for the current position
    int position = SIZE - loops;
    for (i = 0; i < SIZE; i++)
    {
        // Check if the value was already used
        if (used[i])
            continue;
        // Make the value used
        used[i] = 1;
        curRow[position] = i + 1;
        // Do recursion
        permute(SIZE, loops - 1, curRow, used, target, x);
        // Unmake value used
        used[i] = 0;
        curRow[position] = 0;
    }
}
int main()
{
    int i = 0, j = 0, n;
    scanf("%d", &n);
    int loops = n;
    int curRow[n], used[n], target[n];
    for (i = 0; i < n; i++)
    {
        curRow[i] = 0; // empty row to begin with
        used[i] = 0;   // use nothing to begin with
        target[i] = 0;
    }
    int noises[n][n]; // creating a static 2D array that holds n amount of noises
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &noises[i][j]); // set's the value for each noise
        }
    }
    permute(n, loops, curRow, used, target, noises); // calls the permutation
    function
        printf("%d", lowestSum); // permute() updates the global variable lowestSum and
    this prints it return 0;
}