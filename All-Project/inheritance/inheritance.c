// Simulate genetic inheritance of blood type

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GENERATIONS 3
#define INDENT_LENGTH 4

// Define the blood types for alleles
typedef enum { A = 0, B = 1, O = 2 } allele_t;

// Structure to represent a person
typedef struct person {
    struct person *parents[2]; // Two parents
    allele_t alleles[2];       // Two alleles
} person;

// Function declarations
person* create_family(int generations);
void print_family(const person *p, int generation);
void free_family(person *p);
allele_t random_allele(void);
char allele_to_char(allele_t allele);

// Main function
int main(void) {
    srand(time(0));  // Seed the random number generator

    // Create a new family
    person *family_tree = create_family(GENERATIONS);

    // Print the family tree
    print_family(family_tree, 0);

    // Free the allocated memory
    free_family(family_tree);

    return 0;
}

// Function to create a family recursively
person* create_family(int generations) {
    person *new_person = malloc(sizeof(person));
    if (!new_person) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    // If there are generations left to create
    if (generations > 1) {
        new_person->parents[0] = create_family(generations - 1);
        new_person->parents[1] = create_family(generations - 1);

        // Assign alleles based on the parent's alleles
        new_person->alleles[0] = new_person->parents[0]->alleles[rand() % 2];
        new_person->alleles[1] = new_person->parents[1]->alleles[rand() % 2];
    } else {
        // If no generations left, assign random alleles
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    return new_person;
}

// Function to print the family tree
void print_family(const person *p, int generation) {
    if (p == NULL) return;

    // Print indentation based on the generation
    for (int i = 0; i < generation * INDENT_LENGTH; i++) {
        printf(" ");
    }

    // Print the person's blood type
    if (generation == 0) {
        printf("Child (Generation %d): blood type %c%c\n", generation, allele_to_char(p->alleles[0]), allele_to_char(p->alleles[1]));
    } else {
        const char *relation = generation == 1 ? "Parent" : (generation == 2 ? "Grandparent" : "Ancestor");
        printf("%s (Generation %d): blood type %c%c\n", relation, generation, allele_to_char(p->alleles[0]), allele_to_char(p->alleles[1]));
    }

    // Recursively print the parents of the current person
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Function to free the allocated memory for the family
void free_family(person *p) {
    if (p == NULL) return;

    free_family(p->parents[0]);
    free_family(p->parents[1]);
    free(p);
}

// Function to randomly select a blood type allele
allele_t random_allele(void) {
    return rand() % 3;  // Randomly return A, B, or O
}

// Function to convert allele_t to character
char allele_to_char(allele_t allele) {
    switch (allele) {
        case A: return 'A';
        case B: return 'B';
        case O: return 'O';
        default: return '?';  // This should never happen
    }
}
