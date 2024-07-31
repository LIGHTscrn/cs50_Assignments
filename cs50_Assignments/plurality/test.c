#include<stdio.h>
#include<cs50.h>
#include<string.h>

typedef struct
{
    string names;
    string number;
}
person;

int main(void)
{
    person people[3];
    people[0].names = "Pranav";
    people[0].number = "+91 9995285076";

    people[1].names = "Seema";
    people[1].number = "+91 9961482852";

    people[2].names = "john";
    people[2].number = "+91 6592584652";

    string name = get_string("Name: ");
    for(int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].names,name) == 0)
        {
            printf("found\n%s \n%s\n",people[i].names, people[i].number);
            return 0;
        }
    }

}
