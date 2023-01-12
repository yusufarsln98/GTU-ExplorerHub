#include <stdio.h>
#include <stdlib.h>
#define N 15
#define filename "TASK.txt"


struct student{
	
	char name[50];
	char surname[50];
	float gpa;
	int id;
};

void read (struct student student[])
{
	FILE *fptr;
	fptr = fopen(filename, "r");
	
	if (fptr == NULL)
	{
	    printf("Couldn't open text file.\n");
	    exit(1);
	}
	
	int i = 0;
    student[N];
    
    while(!feof(fptr))
	{
    	fscanf(fptr, "%s %s %d %f", student[i].name, student[i].surname, &student[i].id, &student[i].gpa);
    	i++;
    }
	fclose(fptr);  
}

int main(){
	
	int i, max_gpa, min_gpa;
	
	struct student student[N];
	read(student);
	
	float max = student[0].gpa, min = student[0].gpa; 
	
	for(i = 0 ; i < N; i++)
	{

	    if(max < student[i].gpa)
		{
			max = student[i].gpa;
	        max_gpa = i;
	    }
	    
    	if(min > student[i].gpa)
		{
			min = student[i].gpa;
	        min_gpa = i;
	    }
 	}
 	
	printf("The student with the greatest GPA\nname: %-12s surname: %-12s id: %-5d gpa: %.1f\n", student[max_gpa].name, student[max_gpa].surname, student[max_gpa].id, student[max_gpa].gpa);
  	printf("The student with the lowest GPA\nname: %-12s surname: %-12s id: %-5d gpa: %.1f\n", student[min_gpa].name, student[min_gpa].surname, student[min_gpa].id, student[min_gpa].gpa);
  	
	return 0;
}


