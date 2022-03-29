#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <time.h>
#include <ctype.h>

typedef struct all
{
    int score;
    char* name;

} all;

// Display Menu
int menu(struct all *start);
void display();
void display_choices();
// Help
void help_menu(int in);
// Start playing
void name_display(struct all *start);
void difficult(struct all *start);
void display_diff();
int playing(int diff, struct all *start);
// easy
void easy_start(int diff, char* word, struct all *start);
// show score
void score(struct all *start); // used with the files

#define BUFF 1000

int main(int argc, char **argv)
{
    all start;
    FILE *writting;

    start.score = 0;

    start.name = (char *)malloc(256 * sizeof(char));

    if(access("user_score.txt", F_OK) != -1)
    {
        // system("clear");
        menu(&start);
    }
    else
    {
        writting = fopen("user_score.txt", "w+");
        fprintf(writting, "\t\tName\t\tScore\n");
        fprintf(writting, "\t\t---------------------\n");
        fclose(writting);
        menu(&start);
    }

    return 0;
}

int menu(struct all *start)
{
    char c[2];
    int ch;
    int in = 0;

    display();

    fprintf(stdout, "--- Menu ---\n");
    while (!in)
    {
        display_choices();

        fprintf(stdout, "Your choice: ");
        scanf("%s", c);

        if(atoi(c) != 1 && atoi(c) != 2 && atoi(c) != 3 && atoi(c) != 4)
        {
            system("clear");
            fprintf(stderr, "Choose a valid option! \n");
        }
        else
        {
            ch = atoi(c);
            switch(ch)
            {
                case 1:
                    system("clear");
                    start->score = 0;
                    name_display( start);
                    difficult(start);
                    break;
                case 2:
                    system("clear");
                    help_menu(in);
                    break;
                case 3:
                    system("clear");
                    score(start);
                    break;
                case 4:
                    fprintf(stdout, "Exiting!\n\n");
                    in = 1;
                    system("clear");
                    exit(0);
                    break;
                default:
                    perror("Function has a problem");
                    exit(0);
                    break;
            }
        }
    }
}

void score(struct all *start)
{
    FILE *open;
    char num[BUFF];
    char *score;

    int lines_number = 0;

    open = fopen("user_score.txt", "r");

    if(open == NULL)
    {
        fprintf(stdout, "Your file has a problem");
        exit(0);
    }

    while(fgets(num, BUFF, open))
    {
        printf("%s",num);
        lines_number++;

        if(num[strlen(num) - 1] != '\n')
        {
            printf("\n");
        }
    }

    fclose(open);
    fprintf(stdout,"\n\n1. Back\n");
    fprintf(stdout, "Enter an option:");
    scanf("%s", score);

    int a = atoi(score);

    if(a != 1)
    {
        system("clear");
        fprintf(stdout,"Please add the options below");
    }
    else
    {
        system("clear");
        menu(start);
    }
}

void name_display(struct all *start)
{
    fprintf(stdout, "Enter your character name: ");
    scanf("%s", start->name); //start->name

    if(strlen(start->name) < 4)
    {
        fprintf(stderr,"Do not leave me less than 3 letter!\n");
        fprintf(stderr,"Express yourself more!\n");
        return name_display(start);
    }

    printf("Your name is: %s\n\n", start->name);
}

void display()
{
    for(int i = 0; i < 20; i++)
    {
        fprintf(stdout, "-");
    }
    fprintf(stdout, "Welcome at Hangman!");
    for(int i = 0; i < 20; i++)
    {
        fprintf(stdout, "-");
    }
    fprintf(stdout, "\n\n");
}

void display_choices()
{
    fprintf(stdout, "1. Play\n");
    fprintf(stdout, "2. How to play\n");
    fprintf(stdout, "3. Show score\n");
    fprintf(stdout, "4. Exit\n\n");
}

void help_menu(int in)
{
    char c[2];
    int ch;

    fprintf(stdout, "--- Help Menu ---\n");
    fprintf(stdout, "Hangman is a children game were the player receive underscores (i.e. empty letters)\n");
    fprintf(stdout, "from the computer were he must guess the letters. The number of wrong guess are alowed before\n");
    fprintf(stdout, "the game ends is 5: head, body, right hand, left hand, right leg, and then left leg respictevely.\n");
    fprintf(stdout, "The game will be divided into 3 sections each containing number of points.\n\n");
    fprintf(stdout, "The sections are:\n  1. Easy - 10 points\n  2. Medium - 30 points\n  3. Hrad - 50 points\n\n");
    fprintf(stdout, "If the player wins the section, he can choose either to continue or to exit. If he continues\n");
    fprintf(stdout, "his old score will be added with the new score but if he exits then his own score will be saved.\n");
    fprintf(stdout, "If the players fails guessing the word. He will have 2 options in front of him. The first option\n");
    fprintf(stdout, "is an exit function and the a reset function were his score will be reset to 0.\n\n");
    fprintf(stdout,"1. Back\n");

    while (!in)
    {
        
        fprintf(stdout, "Option:");
        scanf("%s", c);

        if(atoi(c) != 1)
        {
            system("clear");
            fprintf(stderr, "Choose a valid option!\n");
            fprintf(stdout, "1. back\n");
        }
        else
        {
            ch = atoi(c);
            switch(ch)
            {
                case 1:
                    system("clear");
                    fprintf(stdout, "--- Menu ---\n");
                    in = 1;
                    break;
                default:
                    perror("Function has a problem");
                    exit(0);
                    break;
            }
        }
    }
}

void difficult(struct all *start)
{
    FILE *writting;

    char c[2];
    int ch;
    int in = 0;

    fprintf(stdout, "--- Difficulty ---\n");

    while(!in)
    {
        display_diff();
        fprintf(stdout, "Choose your difficulty: ");
        scanf("%s", c);

        if(atoi(c) != 1 && atoi(c) != 2 && atoi(c) != 3 && atoi(c) != 4)
        {
            system("clear");
            fprintf(stderr, "Choose a valid option! \n");
        }
        else
        {
            ch = atoi(c);
            switch(ch)
            { 
                case 1:
                    system("clear");
                    playing(1, start);
                    break;
                case 2:
                    system("clear");;
                    playing(2, start);
                    break;
                case 3:
                    system("clear");
                    playing(3, start);
                    break;
                case 4:
                    in = 1;
                    system("clear");
                    if(start->score > 0)
                    {
                        writting = fopen("user_score.txt", "a+");
                        if(strlen(start->name) > 7)
                            {fprintf(writting, "\t\t%s\t%d\n",start->name, start->score);}
                        if(strlen(start->name) <= 7)
                            {fprintf(writting, "\t\t%s\t\t%d\n",start->name, start->score);}
                        fclose(writting);
                    }
                    menu(start);
                    break;
                default:
                    perror("Function has a problem");
                    exit(0);
                    break;
            }
        }
    }
}

void display_diff()
{
    fprintf(stdout, "1. Easy\n");
    fprintf(stdout, "2. Medium\n");
    fprintf(stdout, "3. Hard\n");
    fprintf(stdout, "4. Back\n\n");
}

int playing(int diff, struct all *start)
{
    FILE *file;
    char *size;

    int in = 0;
    int line_number = 0;
    int easy_count = 0, medium_count = 0, hard_count = 0, empty_count = 0;

    char* arr[BUFF];
    char* easy[BUFF];
    char* medium[BUFF];
    char* hard[BUFF];
    char* word;

    file = fopen("all_words.txt", "r");
    size = (char *) malloc(BUFF*sizeof(char));

    while(fgets(size, BUFF, file) != NULL)
    {
        arr[line_number] = (char *) malloc(sizeof(char) * BUFF);
        strcpy(arr[line_number], size);
        line_number++; 
    }

    for(int i = 0; i < BUFF; i++)
    {
        if(strlen(arr[i]) <= 5 && arr[i] != NULL)
        {
            easy[easy_count] = (char *) malloc(sizeof(char) * BUFF);
            strcpy(easy[easy_count], arr[i]);
            easy_count++;
        }
        if(strlen(arr[i]) > 5 && strlen(arr[i]) < 10 && arr[i] != NULL)
        {
            medium[medium_count] = (char *) malloc(sizeof(char) * BUFF);
            strcpy(medium[medium_count], arr[i]);
            medium_count++;
        }
        if(strlen(arr[i]) > 10 && arr[i] != NULL)
        {
            hard[hard_count] = (char *) malloc(sizeof(char) * BUFF);
            strcpy(hard[hard_count], arr[i]);
            hard_count++;

        }
    }

    time_t t;
    if(diff == 1)
    {
        printf("%s entered as an easy mode\n",start->name);
        srand((unsigned)time(&t));
        word = easy[rand() % easy_count];
    }
    if(diff == 2)
    {
        printf("%s entered as an Medium mode\n",start->name);
        srand((unsigned)time(&t));
        word = medium[rand() % medium_count];
    }
    if(diff == 3)
    {
        printf("%s entered as an Hard mode\n",start->name);
        srand((unsigned)time(&t));
        word = hard[rand() % hard_count];
    }

    for(int i = 0; i < strlen(word); i++)
    {
        word[i] = tolower(word[i]);
    }

    if(diff == 1)
    {
        easy_start(diff, word, start);
    }

    if(diff == 2)
    {
        easy_start(diff, word, start);
    }
    
    if(diff == 3)
    {
        easy_start(diff, word, start);
    }

    return 1;
}

void body(int bo)
{
    switch(bo)
    {
        case 6:
            printf("\t\t   _____ \n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t ( )    |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t      __|__\n");
            break;
        case 5:
            printf("\t\t   _____ \n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t ( )    |\n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t      __|__\n");
            break;
        case 4:
            printf("\t\t   _____ \n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t ( )    |\n");
            printf("\t\t  |\\    |\n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t      __|__\n");
            break;
        case 3:
            printf("\t\t   _____ \n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t ( )    |\n");
            printf("\t\t /|\\    |\n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t        |\n");
            printf("\t\t        |\n");
            printf("\t\t      __|__\n");
            break;
        case 2:
            printf("\t\t   _____ \n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t ( )    |\n");
            printf("\t\t /|\\    |\n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t   \\    |\n");
            printf("\t\t        |\n");
            printf("\t\t      __|__\n");
            break;
        case 1:
            printf("\t\t   _____ \n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t ( )    |\n");
            printf("\t\t /|\\    |\n");
            printf("\t\t  |     |\n");
            printf("\t\t  |     |\n");
            printf("\t\t / \\    |\n");
            printf("\t\t        |\n");
            printf("\t\t      __|__\n");
            break;
        default:
            break;
    }
}

void easy_start(int diff, char* word, struct all *start)
{
    char let;
    char *pchar;

    int tries = 0, tries_next = 6, in = 0, k,count = 0;
    char choice[1];

    FILE *writting;

    int size = strlen(word) - 1; // 4 for food
    char temp[size]; // empty array

    pchar = (char *) malloc(32);

    fprintf(stdout, "Score: %d\n",start->score);

    for (int i=0; i < size; ++i) {
        temp[i] = 0;
    }

    while(!tries) // 6 tries
    {
        for(int i = 0; i < strlen(pchar); i++)
        {
            printf("%c ",pchar[i]);
        }

        printf("\n");

        for(int j=0; j < size; j++) {
            if (temp[j]) {
                printf("%c", word[j]);
            }
            else {
                printf("_");
            }
        }

        printf("\n");

        fprintf(stdout, "Enter the letter: ");
        scanf(" %c", &let);

        fprintf(stdout, "Letters used: \n");

        for(int i = 0;i < 32; i++)
        {
            if(!strchr(pchar, let))
            {
                pchar[count] = let;
                count++;
            }
            else
                tries = 0;
                break;
        }

        for(int k = 0; k < size; k++)
        {
            if(word[k] == let)
            {
                temp[k] = 1;
            }
        }

        tries = 1;
        for(int i = 0; i < size; i++)
        {
            if(strchr(word, let))
            {
                if(!temp[i])
                {
                    system("clear");
                    tries = 0;
                    break;  
                }
            }
            else{
                system("clear");
                body(tries_next);

                if(tries_next == 1)
                {
                    tries = 1;
                    printf("You lost the game!\n");
                    printf("Your score is %d\n",start->score);
                    printf("Would you like to:\n");
                    while(!in)
                    {
                        printf("1. Restart\n");
                        printf("2. Exit\n\n");
                        printf("Your choice: ");
                        scanf("%s", choice);

                        k = atoi(choice);
                        if(k != 1 || k != 2)
                        {
                            system("clear");
                            fprintf(stdout, "Provide a valid option!\n");
                        }
                        switch (k)
                        {
                            case 1:
                                system("clear");
                                start->score = 0;
                                fprintf(stdout, "Difficult\n");
                                difficult(start);
                                break;
                            
                            case 2:
                                if(start->score > 0)
                                {
                                    writting = fopen("user_score.txt", "a+");
                                    if(strlen(start->name) > 7)
                                        {fprintf(writting, "\t\t%s\t%d\n",start->name, start->score);}
                                    if(strlen(start->name) <= 7)
                                        {fprintf(writting, "\t\t%s\t\t%d\n",start->name, start->score);}
                                    fclose(writting);
                                }
                                system("clear");
                                memset(start->name, 0, strlen(start->name));
                                menu(start);
                                break;
                            default:
                                break;
                        }
                        in = 1;
                    }
                }
                printf("Try: %d\n", tries_next--);
                tries = 0;
                break;
            }
        }
    }
    system("clear");
    fprintf(stdout,"Congrats %s you won!\n", start->name);
    fprintf(stdout, "The word was %s\n", word);
    switch(diff)
    {
        case 1: start->score += 10; break;
        case 2: start->score += 30; break;
        case 3: start->score += 50; break;
        default: break;
    }
    fprintf(stdout,"Your score is %d\n", start->score);
    if(writting == NULL)
    {
        fprintf(stdout, "Your file has problems");
        exit(0);
    }

    while (!in)
    {
        fprintf(stdout, "1. Continue\n");
        fprintf(stdout, "2. Exit\n");
        fprintf(stdout, "Option:");
        
        scanf("%s", choice);
        k = atoi(choice);

        if(k != 1 || k != 2)
        {
            system("clear");
            fprintf(stderr, "Choose a valid option!\n");
        }
        switch(k)
        {
            case 1:
                system("clear");
                fprintf(stdout, "Difficult\n");
                difficult(start);
                break;
            case 2:
                writting = fopen("user_score.txt", "a+");
                if(strlen(start->name) > 7)
                    {fprintf(writting, "\t\t%s\t%d\n",start->name, start->score);}
                if(strlen(start->name) <= 7)
                    {fprintf(writting, "\t\t%s\t\t%d\n",start->name, start->score);}
                fclose(writting);
                system("clear");
                memset(start->name, 0, strlen(start->name));
                menu(start);
                break;
            default:
                break;
        }
    }
}