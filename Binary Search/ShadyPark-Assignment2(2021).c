// Marvin Orozco
// 9/23/2022
// COP 3502
// Assignment 2: Shady Park

#include <stdio.h>
#include <math.h>

int main() {
    // initializing variables
    int N, L, P, x, h, i = 0, j = 0;
    double percentage, target, mid, low, high, error, currentCoverage;

    error = 0.0000001; // 1e-7
    scanf("%d %d %d", &N, &L, &P); // user input that is then stored in arrays
    int distance [N], height [N];
    double doubleHeight[N], coverage[N];
    percentage = (double)P/100; // calculating the desired coverage
    target = L * percentage;

    for (i = 0; i < N; i++) { // using the amount of user inputted amount of towers, give each tower a height
        scanf("%d %d", &x, &h); // and distance from origin by storing them in arrays
        distance[i] = x;
        height[i] = h;
        doubleHeight[i] = height[i];
    }

    high = 90; // upper and lower limit for when the sun is on the east side
    low = 0;

    for (i = 0; i < 60; i++) {
        if (low == high) {
            break;
        }

        mid = (low + high) / 2; // sets mid equal to the midpoint between the two angles
        double midRadians = mid * (M_PI / 180); // converts mid to value in radians
        midRadians = tan(midRadians); // finds the tangent of mid using the value in radians

        for (j = 1; j < N; j++) { // set each towers coverage by using tan() = opposite / adjacent
            coverage[j] = doubleHeight[j] / midRadians; // tan() = opposite / adjacent
            // adjacent = opposite / tan()
        }

        for (j = 1; j < N; j++) {
            // If else statements that check for overlap
            // if the coverage of the current tower reaches the next tower:
            if (coverage [j] > distance[j] - distance[j - 1]) {
                // if the length of coverage tower[j] is greater than or equal to
                // the next tower then the coverage of the next tower (tower[j+1])
                // will not be included
                if (distance[j] - coverage [j] <= distance [j-1] - coverage[j - 1]) {
                    coverage[j - 1] = 0;
                } else { // otherwise, the coverage is set to the distance between the two towers
                    coverage[j] = distance[j] - distance[j - 1];
                }
            }
        }

        currentCoverage = 0; // reset the value of currentCoverage so the correct currentCoverage
        // can be used in the binary search.
        // adding the total currentCoverage by adding each coverage value
        
        for (j = 1; j < N; j++) {
            currentCoverage += coverage[j];
        }
        // Binary Search over the (currentCoverage - target) in regards to the error value
        if (currentCoverage - target <= error) {
            high = mid; // if the difference is less than or equal to the error value, high is set equal to mid
        }
        else if (currentCoverage - target >= error) {
            low = mid; // else, low is set equal to the current mid value
        }
    }

    printf("%.5lf ", mid); //prints and rounds the value of the angle found
    high = 180; // upper limit for when sun is on the west side
    low = 90; // lower limit

    for (i = 0; i < 60; i++) {

        if (low == high) {
            break;
        }

        mid = (low + high) / 2;
        double midRadians = mid * (M_PI / 180);
        midRadians = tan(midRadians);

        for (j = 0; j < N-1; j++) {
            coverage[j] = doubleHeight[j] / midRadians;
            coverage[j] = fabs(coverage[j]); // the value of tan() within the range of 180 - 90
            // is negative, in order to compare, they must be positive
        }

        for (j = 0; j < N-1; j++) {
            // If else statements that check for overlap
            // if the coverage of the current tower reaches the next tower:
            if (coverage[j] > distance[j+1] - distance[j]) {
                // if the length of coverage tower[j] is greater than or equal to
                // the next tower then the coverage of the next tower (tower[j+1])
                // will not be included
                if (distance[j] - coverage[j] >= distance[j+1] - coverage[j+1]) {
                    coverage[j+1] = 0;
                } else { // otherwise, the coverage is set to the distance between the two towers
                    coverage[j] = distance[j+1] - distance[j];
                }
            }
        }

        currentCoverage = 0; // reset the value of currentCoverage so the correct currentCoverage
        // can be used in the binary search.
        // adding the total currentCoverage by adding each coverage value

        for (j = 0; j < N-1; j++) {
            currentCoverage += coverage[j];
        }
        // Binary Search over the (currentCoverage - target) and the error value
        if (currentCoverage - target >= error) {
            high = mid; // if the difference is greater than the error value, then high is set equal to mid
        }
        else if (currentCoverage - target <= error) {
            low = mid; // else, the low value is set to mid
        }
    }
    printf("%.5lf", mid); // prints second angle rounded to 5 decimal places
    return 0;
}