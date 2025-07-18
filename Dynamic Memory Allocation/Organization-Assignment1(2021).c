// Marvin Orozco
// Travis Meade
// 9/12/2022
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Zoo Zoo;
typedef struct Section Section;
typedef struct Cage Cage;
struct Cage
{
    char *name;
};
struct Section
{
    Cage *cages;
    int cageCount;
};
struct Zoo
{
    Section *sections;
    int sectionCount;
};
// Function to change the size of a particular section.
// When sizing up you will want to initialize the newly created cages.
// When sizing down you will want to free the removed animals (prior to
// resize)
void resizeSection(Zoo *myZoo, int section, int newCageCount);
// Function Prototypes
// Add an animal (with some given name) to the zoo at some section/cage #
void addAnimal(Zoo *myZoo, int section, int cage, char *name);
// Function to print the animal in the zoo at the given section/cage #
void printsAnimal(Zoo *myZoo, int section, int cage);
int main()
{
    int comm = 0;
    int y, sectionCnt, S, C, i;
    int sections[20], cageamnt[20];
    char animalname[20];
    scanf("%d", &sectionCnt);
    // sectionCnt = 5;
    if (sectionCnt < 1 || sectionCnt > 100000)
    {
        while (y < 1 || y > 100000)
        {
            // printf("Pick a number between 1 and 100,000\n");
            scanf("%d", &sectionCnt);
        }
    }
    Zoo *zoo = (Zoo *)malloc(sizeof(Zoo));
    zoo->sectionCount = sectionCnt;
    zoo->sections = (Section *)malloc(sectionCnt * sizeof(Section));
    for (i = 0; i < sectionCnt; i++)
    {
        zoo->sections[i].cageCount = -1;
    }
    while (comm != 4)
    {
        int i = 0, j = 0, S = 0, C = 0;
        scanf("%d", &comm);
        if (comm == 1)
        {
            scanf("%d", &S);
            scanf("%d", &C);
            resizeSection(zoo, S, C);
        }
        else if (comm == 2)
        {
            scanf("%d", &S);
            scanf("%d", &C);
            scanf("%s", animalname);
            addAnimal(zoo, S, C, animalname);
        }
        else if (comm == 3)
        {
            scanf("%d", &S);
            scanf("%d", &C);
            printsAnimal(zoo, S, C);
        }
    }
    return 0;
}
void resizeSection(Zoo *myZoo, int section, int newCageCount)
{
    if (myZoo->sections[section - 1].cageCount != -1)
    {
        int oldCageCount = myZoo->sections[section - 1].cageCount;
        myZoo->sections[section - 1].cageCount = newCageCount - 1;
        if (newCageCount - 1 > oldCageCount)
        {
            Cage *newCageArray = (Cage *)realloc(myZoo->sections[section - 1].cages,
                                                 newCageCount * sizeof(Cage));
            myZoo->sections->cages = newCageArray;
            for (int i = 0; i < newCageCount; i++)
            {
                myZoo->sections[section - 1].cages[i].name = NULL;
            }
        }
        else
        {
            for (int i = oldCageCount + 1; i < newCageCount - 1; i++)
            {
                free(myZoo->sections[section - 1].cages[i].name);
            }
        }
    }
    else
    {
        myZoo->sections[section - 1].cages =
            (Cage *)malloc(newCageCount * sizeof(Cage));
        myZoo->sections[section - 1].cageCount = newCageCount;
        for (int i = 0; i < newCageCount; i++)
        {
            myZoo->sections[section - 1].cages[i].name = NULL;
        }
    }
}
void addAnimal(Zoo *myZoo, int section, int cage, char *name)
{
    Section currSection = myZoo->sections[section - 1];
    if (currSection.cageCount != -1)
    {
        if (currSection.cages[cage - 1].name == NULL)
        {
            myZoo->sections[section - 1].cages[cage - 1].name =
                (char *)malloc((strlen(name) + 1) * sizeof(char));
            strcpy((myZoo->sections[section - 1].cages[cage - 1].name), name);
        }
    }
}
void printsAnimal(Zoo *myZoo, int section, int cage)
{
    if (myZoo->sections[section - 1].cageCount != -1 && myZoo->sections[section -
                                                                        1]
                                                                .cageCount >= cage)
    {
        if (myZoo->sections[section - 1].cages[cage - 1].name == NULL)
        {
            printf("No animal found.\n");
        }
        else
        {
            printf("%s\n", myZoo->sections[section - 1].cages[cage - 1].name);
        }
    }
    else
    {
        printf("No animal found.\n");
    }
}