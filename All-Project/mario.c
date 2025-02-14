#include <stdio.h>
#include <cs50.h> // Include this if you're using the CS50 library for `get_int`

// Function prototype
void print_row(int spaces, int bricks);

int main(void)
{
    // Input of the height of the pyramid's
    int n;
    do{
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); // Restrict height to 1-8 for a typical pyramid

    // Print each row of the pyramid
    for (int i = 1; i <= n; i++) // Loop from 1 to n for rows
    {
        int spaces = n - i; // Calculate spaces
        int bricks = i;     // Calculate bricks
        print_row(spaces, bricks); // Print the current row
    }
}

void print_row(int space, int bricks){

    //Space
    for (int i = 0; i < space; i++){
        printf(" ");
    }

    for (int i = 0; i < bricks; i++){
        printf("#");
    }
    printf("\n");
}
