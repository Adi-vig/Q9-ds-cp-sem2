#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[100];
    char division;
    int prn;
    float marks[3];
    int attendance;
    struct node *next;
};

struct node *head = NULL;

void insert(char *name, char division, int prn, float marks[3], int attendance)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    strcpy(new_node->name, name);
    // printf("here %s", name);

    new_node->division = division;

    new_node->prn = prn;

    for (int i = 0; i < 3; i++)
    {
        new_node->marks[i] = marks[i];
    }

    new_node->attendance = attendance;
    new_node->next = head;

    head = new_node;
}

char* sabji[3]={"Physics", "Maths", "Chemistry"};

void display_top_5()
{
    system("cls");
    struct node *current = head;

    int count = 0;

    while (current != NULL && count <= 5)
    {
        printf("Name: %s\n", current->name);
        printf("Division: %c\n", current->division);
        printf("PRN: %d\n", current->prn);
        for (int i = 0; i < 3; i++)
        {
            printf("Marks in %s: %.2f\n", sabji[i],current->marks[i]);
        }
        printf("Attendance: %d\n", current->attendance);
        printf("\n");
        current = current->next;
        count++;
    }
}

void calculate_percentile()
{
    struct node *current = head;
    float top_ranker_marks = current->marks[0];
    while (current != NULL)
    {
        for (int i = 0; i < 3; i++)
        {
            current->marks[i] = (current->marks[i] / top_ranker_marks) * 100;
        }
        current = current->next;
    }
}

void display_student_details(int prn)
{
    struct node *current = head;
    while (current != NULL)
    {
        if (current->prn == prn)
        {
            printf("Name: %s\n", current->name);
            printf("Division: %c\n", current->division);
            printf("PRN: %d\n", current->prn);
            for (int i = 0; i < 3; i++)
            {
                printf("Marks in %s: %.2f \n",  sabji[i]  ,current->marks[i]);
            }
            printf("Attendance: %d\n", current->attendance);
            printf("\n");
            break;
        }
        current = current->next;
    }
}








void addStud(){
    FILE *fp = fopen( "students.txt", "a" );
    char name[100];
    char div;
    int prn;
    float marks[3];
    int att;


    system("cls");
    printf("Enter student details\n");
    printf("Name : ");
    scanf(" %s",name);
    fflush(stdin);
    printf("Div : ");
    scanf(" %c", &div);
    printf("PRN : ");
    scanf("%d", &prn);
    
    for(int i=0; i<3; i++){
        printf("Marks in %s: ", sabji[i] );
        scanf("%f", &marks[i]);
    }

    printf("Attendance : ");
    scanf("%d", &att);

    insert(name, div, prn, marks, att);

    fprintf(fp, "\n\n%s \n%c\n%d\n%f\n%f\n%f\n%d", 
                    name, div, prn, marks[0], marks[1], marks[2], att );

    fclose(fp);
    



}









void search(){
    system("cls");
    int prn;
    printf("Enter the PRN of the student to display details: ");
    scanf("%d", &prn);
    display_student_details(prn);
}





void menu()
{
    // int n;

    int choice = 0;
    printf("\n\n**********Student DBMS*********\n\t1.Add Student \n\t2.Search \n\t3.Display Top 5 students\n\t4.Convert All marks to Percentile\n\t0.Exit\n\nEnter your choice :");

    scanf(" %d", &choice);
    // system("cls");
    if (choice == 0)
        exit(0);

    switch (choice)
    {
    case 1:
        addStud();
        break;

    case 2:
        search();
        break;

    case 3:
        display_top_5();
        break;
    
    case 4:
        calculate_percentile();
        break;

    default:
        printf("\nInvalid Choice.");
        break;
    }
}











int main()
{
    float marks[3];
    char name[100];
    char division;
    int prn;
    int attendance;

    FILE *fp;
    fp = fopen("students.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }

    while (fscanf(fp, "%s %c %d %f %f %f %d", name , &division, &prn, &marks[0] ,&marks[1], &marks[2], &attendance) != EOF)
    {
        insert(name, division, prn, marks, attendance);
    }

    fclose(fp);

    while(1)menu();

    return 0;
}