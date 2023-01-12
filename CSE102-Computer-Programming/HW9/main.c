#include <stdio.h>
#include <string.h>

/* Max costumer number and max costumer name length */
#define MAXCOSTUMER 50
#define WORDSIZE 100

#define MAXEMP 5        /* Max employee in a row */
#define MAXRETSTU 3     /* Max retired and student in a row */
#define MAXUNPOTH 2     /* Max unemployed and other costumers in a row */

#define TRUE 1
#define FALSE -1

/* Label enumerate type */
typedef enum label {employee, retired, student, unemployed, other} label_t;

/* Costumer struct type */
typedef struct costumer
{
    char name[WORDSIZE];
    int age;
    unsigned int label;
}
costumer_t;

/* Number of costumers in each iteration. (Prevent to obligation of carrying counter in each iteration and in each function moduls.) */
int costumer_counter;

void discharge_labels(costumer_t *costumers, int MAX);                  /* Since there is garbage values in array, it fills the array with -1 */
void expand_sequence(costumer_t *costumers, costumer_t new_costumer);   /* Expands the line when someone comes to line */
void shrink_sequence(costumer_t *costumers);                            /* Shrinks the line when someone proceed */
int find_index(costumer_t *costumers, unsigned int label);              /* Finds index of array which people has priority in the line */
int fill_set(costumer_t *costumers, unsigned int label);                /* Fill the very first set */
int fill_gaps(costumer_t *costumers, unsigned int label);               /* Fill the gaps */
int priority(costumer_t *costumers, unsigned int label);                /* Finds priority of in extreme situations */
int if_label(costumer_t *costumers, unsigned int label);                /* If the label already exist in the line or not */
int number_of_costumers(costumer_t *costumers, unsigned int label);     /* Number of labeled costumers in the "row" */
int find_label(costumer_t *costumers, unsigned int label);              /* Find location of current requested */  
int line_number(costumer_t *costumers, unsigned int label);             /* Finds the number of requested label in the line */
void print_line(costumer_t *costumers);                                 /* Prints current line */

/* 
=========================
FIRST PART: MAIN FUNCTION
=========================

 */
int main(void)
{
    int operator;                               /* Operator for shrink or expand */
    costumer_t costumers[MAXCOSTUMER];          /* Costumer struct type array */
    costumer_t new_costumer;                    /* Costumer struct type new costumer */
    
    discharge_labels(costumers, MAXCOSTUMER);   /* Turns garbages to -1 */


    /* Begining of iteration. (-1 for break the loop)*/
    do
    {
        printf("\n==================================");
        printf("\n--------- BANKING SYSTEM ---------");
        printf("\n==================================\n\n");

        /* Print the current sequence. */
        printf("\nCURRENT SEQUENCE:  ");
        print_line(costumers);     

        /* Getting the operation from user. */                                 
        printf("\n\nPick the operation you want to do:  \n");
        printf("1- Add Costumer \n2- Process Costumer \n(To leave: -1)\n\n");
        scanf("%d", &operator);

        /* If number of costumers is MAX then ask proceeding or exit */
        while (costumer_counter == MAXCOSTUMER && operator == 1)
        {
            printf("\n\nWARNING!\nYou have completed the user limit. \nPlease enter 2 for process consumer or 0 for exit!\n");
            scanf("%d", &operator);
            printf("\n");
        }
        /* If number of costumers is 0 then ask to add new costumer or exit */
        while (costumer_counter == 0 && operator == 2)
        {
            printf("\n\nWARNING!\nThere is no one in the line. \nPlease enter 1 for add consumer or 0 for exit!\n");
            scanf("%d", &operator);
            printf("\n");
        }

        /* If operator is ADD */
        if (operator == 1)
        {
            /* Get the information of new costumer from console */
            printf("\n----- COSTUMER INFORMATIONS -----\n\n");
            printf("Name:  ");
            scanf("%s", new_costumer.name);
            printf("Age: ");
            scanf("%d", &new_costumer.age);
            printf("Label:\n  Employee   --> 0\n  Retired    --> 1\n  Student    --> 2\n  Unemployed --> 3\n  Other      --> 4\n  ");
            scanf("%u", &new_costumer.label);
            printf("\n");
            /* Increase counter one by one in each ADD operation */
            costumer_counter++;
            /* Call the expand function */
            expand_sequence(costumers, new_costumer);
        }
        /* If operator is PROCEED */
        else if (operator == 2)
        {
            /* Decrease costumer number one by one in each PROCEED operation */
            costumer_counter--;
            /* Print name of costumer and SHRINK the line */
            printf("\n-- Proceed Costumer is %s (%d) --\n\n", costumers[0].name, costumers[0].age);
            shrink_sequence(costumers);
        }

    } while (operator != -1);
    
    return 0;
}

/*
============================
SECOND PART: BASIC FUNCTIONS
============================
*/

/* Expand the line and put the new costumer in appropriate place */
void expand_sequence(costumer_t *costumers, costumer_t new_costumer)
{
    int index,  /* Array indexs */
        i;      /* Loop initiliazer */

    /* Find index going to return appropriate index for new costumer. */
    index = find_index(costumers, new_costumer.label);

    /* Loop going to make place for new costumer */
    for (i = costumer_counter - 1; i > index; i--)
    {
        costumers[i] = costumers[i - 1];
    }
    /* Puts the new costumer in its new place */
    strcpy(costumers[index].name, new_costumer.name);
    costumers[index].age = new_costumer.age;
    costumers[index].label = new_costumer.label;
    
}

/* Shrink sequence when someone was proceed. */
void shrink_sequence(costumer_t *costumers)
{
    int i;
    for (i = 0; i < costumer_counter; i++)
    {
        costumers[i] = costumers[i + 1];
    }
    costumers[costumer_counter].label = -1;
}

/* Arrange the function which returns indexes and return final index to upper function */
int find_index(costumer_t *costumers, unsigned int label)
{
    int i, j,
        fill;
    
    /*
        1. fill_set() --> It returns the index if there is not any costumer in the line.
        2. fill_gaps() --> It returns the index if there is same labeled costumer in the line 
        but not in the extreme case (ie: 00000 is an extreme case but 22 is not) So it will return for 2's return FALSE for 0's
    */
    fill = fill_set(costumers, label);
    if (fill != FALSE)
    {
        return fill;
    }
    else
    {
        fill = fill_gaps(costumers, label);
        if (fill != FALSE)
        {
            return fill;
        }
    }
    /*
    3. priority() --> If there is costumers in the line and they are in the extreme cases. So it will find the appropirate place for each.
                      ie: 2-2-2-3-3-1-1-4-4  if new costumers is would be "2" then it will put it right side of 1 --> 2-2-2-3-3-1-1-"2"-4-4
                                                                                                                                     ^
    */
    fill = priority(costumers, label);
    return fill;
}


int fill_set(costumer_t *costumers, unsigned int label)
{
    /* 
    This function basicly checks for the IF THERE IS NOT ANY PAIR OF NEW COSTUMER LABEL IN THE LINE 
    There is 6 basic case for this function:
    */

    /* 1- If there is not any 0 (employee) in the line,
       Put it in the very firt of the line. */
    if (label == employee && if_label(costumers, employee) == FALSE)
    {
        return 0;
    }
    /* 2- If there is not any 1 (retired) in the line,
       If there is 0, then put it the right side of 0
       Else put it the very first of the line. */
    else if (label == retired && if_label(costumers, retired) == FALSE)
    {
        if (number_of_costumers(costumers, employee) >= 5)
        {
            return 5;
        }
        return number_of_costumers(costumers, employee);
    }
    /* 3- If there is not any 2 (student) in the line,
       Check if there is 1 in the line then put it the right side of 1
       else  if there is 0 in the line then put it the right side of 0 */
    else if (label == student && if_label(costumers, student) == FALSE)
    {
        if (if_label(costumers, employee) == FALSE && if_label(costumers, retired) == FALSE)       
        {
            return 0;
        }
        if (if_label(costumers, retired) == TRUE)
        {
            if (number_of_costumers(costumers, retired) >= 3)
            {
                return find_label(costumers, retired) + 3;
            }
            return find_label(costumers, retired) + number_of_costumers(costumers, retired);
        }
        if (if_label(costumers, employee) == TRUE)
        {
            if (number_of_costumers(costumers, employee) >= 5)
            {
                return find_label(costumers, employee) + 5;
            }
            return find_label(costumers, employee) + number_of_costumers(costumers, employee);
        }
    }
    /* 4- If there is not any 3 (retired) in the line,
       Check if there is 2 in the line then put it the right side of 2
       else  if there is 1 in the line then put it the right side of 1
       else  if there is 0 in the line then put it the right side of 0 */
    else if (label == unemployed && if_label(costumers, unemployed) == FALSE)
    {
        if (if_label(costumers, employee) == FALSE && if_label(costumers, retired) == FALSE && if_label(costumers, student) == FALSE)       
        {
            return 0;
        }
        if (if_label(costumers, student) == TRUE)
        {
            if (number_of_costumers(costumers, student) >= 3)
            {
                return find_label(costumers, student) + 3;
            }
            return find_label(costumers, student) + number_of_costumers(costumers, student);
        }
        if (if_label(costumers, retired) == TRUE)
        {
            if (number_of_costumers(costumers, retired) >= 3)
            {
                return find_label(costumers, retired) + 3;
            }
            return find_label(costumers, retired) + number_of_costumers(costumers, retired);
        }
        if (if_label(costumers, employee) == TRUE)
        {
            if (number_of_costumers(costumers, employee) >= 5)
            {
                return find_label(costumers, employee) + 5;
            }
            return find_label(costumers, employee) + number_of_costumers(costumers, employee);
        }
    }

    /* 5- If there is not any 4 (retired) in the line,

       Check if there is 3 in the line then put it the right side of 3
       else  if there is 2 in the line then put it the right side of 2 
       else  if there is 1 in the line then put it the right side of 1
       else  if there is 0 in the line then put it the right side of 0 */
    else if (label == other && if_label(costumers, other) == FALSE)
    {
        if (if_label(costumers, employee) == FALSE && if_label(costumers, retired) == FALSE 
         && if_label(costumers, student) == FALSE && if_label(costumers, unemployed) == FALSE)       
        {
            return 0;
        }
        if (if_label(costumers, unemployed) == TRUE)
        {
            if (number_of_costumers(costumers, unemployed) >= 2)
            {
                return find_label(costumers, unemployed) + 2;
            }
            return find_label(costumers, unemployed) + number_of_costumers(costumers, unemployed);
        }   
        if (if_label(costumers, student) == TRUE)
        {
            if (number_of_costumers(costumers, student) >= 3)
            {
                return find_label(costumers, student) + 3;
            }
            return find_label(costumers, student) + number_of_costumers(costumers, student);
        }
        if (if_label(costumers, retired) == TRUE)
        {
            if (number_of_costumers(costumers, retired) >= 3)
            {
                return find_label(costumers, retired) + 3;
            }
            return find_label(costumers, retired) + number_of_costumers(costumers, retired);
        }
        if (if_label(costumers, employee) == TRUE)
        {
            if (number_of_costumers(costumers, employee) >= 5)
            {
                return find_label(costumers, employee) + 5;
            }
            return find_label(costumers, employee) + number_of_costumers(costumers, employee);
        }
    }

    /* 6- If there is any pair of label in the sequence then return FALSE */
    return FALSE;
}
int fill_gaps(costumer_t *costumers, unsigned int label)
{
    /* 
    This function has a basic mentality:

    We know that the current label is exist in the sequence,
    (if it wouldn't, upper function would do its job and will find appropriate place for it)
    It checks the line from beginning to end, then if there is gap, which mean:
    If there is less then 5 employee, or less then 3 retired and student or less then 2 unemployed and other
    it will find the place for new label. (It will return the very right side of current labels in the line)
    Else -If there is not any gap, extreme cases- it would not find place and return FALSE
    */
    int i, j, counter;

    counter = 0;

    for (i = 0; i < costumer_counter; i++)
    {  
        if (label == employee)
        {
            for (j = i; j < i + MAXEMP; j++)
            {
                if (costumers[j].label == employee)
                {
                    counter++;
                }
                else
                {
                    i += counter;
                    break;
                }
            }
            if (counter < MAXEMP && counter != 0)
            {
                return i;
            }
            if (counter == MAXEMP)
            {
                i = i + counter - 1;
                counter = 0;
            }
        }
        else if (label == retired)
        {
            for (j = i; j < i + MAXRETSTU; j++)
            {
                if (costumers[j].label == retired)
                {
                    counter++;
                }
                else
                {
                    i += counter;
                    break;
                }
            }
            if (counter < MAXRETSTU && counter != 0)
            {
                return i;
            }
            if (counter == MAXRETSTU)
            {
                i = i + counter - 1;
                counter = 0;
            }
        }
        else if (label == student)
        {
            for (j = i; j < i + MAXRETSTU; j++)
            {
                if (costumers[j].label == student)
                {
                    counter++;
                }
                else
                {
                    i += counter;
                    break;
                }
            }
            if (counter < MAXRETSTU && counter != 0)
            {
                return i;
            }
            if (counter == MAXRETSTU)
            {
                i = i + counter - 1;
                counter = 0;
            }
        }
        else if (label == unemployed)
        {
            for (j = i; j < i + MAXUNPOTH; j++)
            {
                if (costumers[j].label == unemployed)
                {
                    counter++;
                }
                else
                {
                    i += counter;
                    break;
                }
            }
            if (counter < MAXUNPOTH && counter != 0)
            {
                return i;
            }
            if (counter == MAXUNPOTH)
            {
                i = i + counter - 1;
                counter = 0;
            }
        }
        else if (label == other)
        {
            for (j = i; j < i + MAXUNPOTH; j++)
            {
                if (costumers[j].label == other)
                {
                    counter++;
                }
                else
                {
                    i += counter;
                    break;
                }
            }
            if (counter < MAXUNPOTH && counter != 0)
            {
                return i;
            }
            if (counter == MAXUNPOTH)
            {
                i = i + counter - 1;
                counter = 0;
            }
        }
    }
    return FALSE;
}

int priority(costumer_t *costumers, unsigned int label)
{
    /*  
    Final control:
    If label is already exist and labels are in the extreme cases. 
    for example: if current line is: 
    0-0-0-0-0-1-1-1-2-2-2-3-3-1-1-1-2-2  and new label is NEWLABEL 
    It will check the all line and find the last NEWLABEL 
    Then treat the last NEWLABEL place as the beginning of the new row,
    then it will do the exactly same with fill_set() function. 
    
    0-0-0-0-0-1-1-1-2-2-2- 3- 3- 1- 1- 1- 2- 2
    ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^  ^  ^  ^  ^  ^  ^  ^
    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17

    Lets assume that NEWLABEL is 3

    Loop checks the last 3's place which is 12 now,
    then treat array[13] is a new row,

    checks other labels in the row and according to instructions,
    finds best place for the NEWLABEL which is 18 in this case.

   */

    int i, j, index, counter;       /* Initiliazers. */

    counter = 0;                    /* Counter for counting the labels in the row */

    /* Since there is 5 label and each of them has different priority, each case handled one by one */
    if (label == employee)
    {
        for (i = 0; i < costumer_counter; i++)
        {
            if (costumers[i].label == employee)
            {
                counter = 0;
                i += (MAXEMP - 1);
            }
            if (costumers[i].label == -1)
            {
                for (j = (i - counter); j < costumer_counter; j++)
                {
                    if (costumers[j].label < costumers[j - 1].label)
                    {  
                        return j;
                    }
                    if (costumers[j].label == retired && line_number(&costumers[j], retired) > MAXRETSTU)
                    {
                        return j + MAXRETSTU;
                    }
                    if (costumers[j].label == student && line_number(&costumers[j], student) > MAXRETSTU)
                    {
                        return j + MAXRETSTU;
                    }
                    if (costumers[j].label == unemployed && line_number(&costumers[j], unemployed) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                    if (costumers[j].label == other && line_number(&costumers[j], other) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                }
            }
            counter++;
        }
    }
    if (label == retired)
    {
        for (i = 0; i < costumer_counter; i++)
        {
            if (costumers[i].label == retired)
            {
                counter = 0;
                i += (line_number(&costumers[i], retired) - 1);
            }
            if (costumers[i].label == -1)
            {
                for (j = (i - counter); j < costumer_counter; j++)
                {
                    if (costumers[j].label == employee)
                    {
                        if (line_number(&costumers[j], employee) >= MAXEMP)
                        {
                            return j + MAXEMP;
                        }
                        return j + line_number(&costumers[j], employee);
                    }
                    if (costumers[j].label < costumers[j - 1].label)
                    {  
                        return j;
                    }
                    if (costumers[j].label == student && line_number(&costumers[j], student) > MAXRETSTU)
                    {
                        return j + MAXRETSTU;
                    }
                    if (costumers[j].label == unemployed && line_number(&costumers[j], unemployed) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                    if (costumers[j].label == other && line_number(&costumers[j], other) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                }
            }
            counter++;
        }
    }
    if (label == student)
    {
        for (i = 0; i < costumer_counter; i++)
        {
            if (costumers[i].label == student)
            {
                counter = 0;
                i += (MAXRETSTU - 1);
            }
            if (costumers[i].label == -1)
            {
                for (j = (i - counter); j < costumer_counter; j++)
                {
                    if (costumers[j].label == employee)
                    {
                        if (costumers[j + line_number(&costumers[j], employee)].label != employee)
                        {
                            if (costumers[j + line_number(&costumers[j], employee)].label != retired)
                            {
                                return j + line_number(&costumers[j], employee);
                            }
                            else
                            {
                                j += line_number(&costumers[j], employee);
                            }
                        }
                        else
                        {
                            j += (line_number(&costumers[j], employee) - 1);
                        }
                    }
                    if (costumers[j].label == retired)
                    {
                        if (line_number(&costumers[j], retired) >= MAXRETSTU)
                        {
                            return j + MAXRETSTU;
                        }
                        return j + line_number(&costumers[j], retired);
                    }
                    if (costumers[j].label < costumers[j - 1].label)
                    { 
                        return j;
                    }
                    if (costumers[j].label == unemployed && line_number(&costumers[j], unemployed) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                    if (costumers[j].label == other && line_number(&costumers[j], other) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                }
            }
            counter++;
        }
    }
    if (label == unemployed)
    {
        for (i = 0; i < costumer_counter; i++)
        {
            if (costumers[i].label == unemployed)
            {
                counter = 0;
                i += (MAXUNPOTH - 1);
            }
            if (costumers[i].label == -1)
            {
                for (j = (i - counter); j < costumer_counter; j++)
                {
                    if (costumers[j].label == employee)
                    {
                        if (line_number(&costumers[j], employee) >= MAXEMP)
                        {
                            if (line_number(&costumers[j], employee) == MAXEMP)
                            {
                                if (costumers[j + MAXEMP].label == other || costumers[j + MAXEMP].label == -1)
                                {
                                    return j + MAXEMP;
                                }
                                else
                                {
                                    j += MAXEMP;
                                }
                            }
                            else
                            {
                                return j + MAXEMP;
                            }
                        }
                        else
                        {
                            j += line_number(&costumers[j], employee);
                        }
                    }
                    if (costumers[j].label == retired)
                    {
                        if (line_number(&costumers[j], retired) >= MAXRETSTU)
                        {
                            if (line_number(&costumers[j], retired) == MAXRETSTU)
                            {
                                if (costumers[j + MAXRETSTU].label == other || costumers[j + MAXRETSTU].label == -1)
                                {
                                    return j + MAXRETSTU;
                                }
                                else
                                {
                                    j += MAXRETSTU;
                                }
                            }
                            else
                            {
                                return j + MAXRETSTU;
                            }
                        }
                        else
                        {
                            j += line_number(&costumers[j], retired);
                        }
                    }
                    if (costumers[j].label == student)
                    {
                        if (line_number(&costumers[j], student) >= MAXRETSTU)
                        {
                            return j + MAXRETSTU;
                        }
                        return j + line_number(&costumers[j], retired);
                    }
                    if (costumers[j].label < costumers[j - 1].label)
                    { 
                        return j;
                    }
                    if (costumers[j].label == other && line_number(&costumers[j], other) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                }
            }
            counter++;
        }
    }
    if (label == other)
    {
        for (i = 0; i < costumer_counter; i++)
        {
            if (costumers[i].label == other)
            {
                counter = 0;
                i += (MAXUNPOTH - 1);
            }
            if (costumers[i].label == -1)
            {
                for (j = (i - counter); j < costumer_counter; j++)
                {
                    if (costumers[j].label == employee && line_number(&costumers[j], employee) > MAXEMP)
                    {
                        return j + MAXEMP;
                    }
                    if (costumers[j].label == retired && line_number(&costumers[j], retired) > MAXRETSTU)
                    {
                        return j + MAXRETSTU;
                    }
                    if (costumers[j].label == student && line_number(&costumers[j], student) > MAXRETSTU)
                    {
                        return j + MAXRETSTU;
                    }
                    if (costumers[j].label == unemployed && line_number(&costumers[j], unemployed) > MAXUNPOTH)
                    {
                        return j + MAXUNPOTH;
                    }
                }
            }
            counter++;
        }
    }
    return costumer_counter - 1;
}

/* 
===========================
LAST PART: HELPER FUNCTIONS
===========================
*/

/* This function takes the array[N] and find the how many costumer (same label) in the line */
int line_number(costumer_t *costumers, unsigned int label)
{
    int i, 
        counter;
    
    counter = 0;
    if (label == employee)
    {    
        for (i = 0; i <= MAXEMP; i++)
        {
            if (costumers[i].label == label)
            {
                counter++;
            }
            if (costumers[i].label != label)
            {
                break;
            }
        }
        return counter;
    }
    if (label == retired || label == student)
    {    
        for (i = 0; i <= MAXRETSTU; i++)
        {
            if (costumers[i].label == label)
            {
                counter++;
            }
            if (costumers[i].label != label)
            {
                break;
            }
        }
        return counter;
    }
    if (label == unemployed || label == other)
    {    
        for (i = 0; i <= MAXEMP; i++)
        {
            if (costumers[i].label == label)
            {
                counter++;
            }
            if (costumers[i].label != label)
            {
                break;
            }
        }
        return counter;
    }
}

/* Finds the where the costumer exactly in the line */
int find_label(costumer_t *costumers, unsigned int label)
{
    int i;
    for (i = 0; i < costumer_counter; i++)
    {
        if (costumers[i].label == label)
        {
            return i;
        }
    }
    return 0;
}
/* Returns TRUE if there label is exist, or FALSE if does not */
int if_label(costumer_t *costumers, unsigned int label)
{
    int i;
    for (i = 0; i < costumer_counter; i++)
    {
        if (costumers[i].label == label)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/* Number of costumers in the line. */
int number_of_costumers(costumer_t *costumers, unsigned int label)
{
    int i,
        flag,
        counter;
    
    for (i = 0, flag = 0, counter = 0; i < costumer_counter; i++)
    {
        if (costumers[i].label == label)
        {
            flag = 1;
        }
        if (flag == 1 && costumers[i].label == label)
        {
            counter++;
        }
        if (flag == 1 && (costumers[i].label != label || i == costumer_counter - 1))
        {
            return counter;  
        }
    }
    return 0;
}

/* Prints current line if someone is in the line, if not, prints "There is nobody in the line!" */
void print_line(costumer_t *costumers)
{
    int i;

    printf("\n\n ¯¯/|\n");
    printf("¯¯| |");
    if (costumer_counter == 0)
    {
        printf("    There is nobody in the line!");
        printf("\n  |_|________________");
        printf("\n__|_________________\n\n");
        return;
    }
    for (i = 0; i < costumer_counter; i++)
    {
        printf(" %d |", costumers[i].label);
    }
    printf("\n  |_|________________");
    printf("\n__|_________________\n\n");
}

/* Discharges labels from garbages to -1. */
void discharge_labels(costumer_t *costumers, int MAX)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        costumers[i].label = -1;
    }
}