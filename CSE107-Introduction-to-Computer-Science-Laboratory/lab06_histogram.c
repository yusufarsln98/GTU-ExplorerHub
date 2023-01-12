# include <stdio.h>

void print_line(char c, int num_of_chars);
void print_histogram(char c, int vals []);
int len(int arr []) ;


int main () {
	
	int values [100], val = 1, count = 0;
	
	printf ("Enter pozitif integer(s) to print histogram and negative integer to stop.\n");
	do
	{		
		printf ("Enter a value :");	
		scanf ("%d", & val);
		
		values[count] = val;
		count ++;
	} 
	while (val > 0);
	
	print_histogram('*', values);
	return 0;
}

void print_histogram(char c, int vals [])
{
	int length, i=0;
	length = len(vals);
	
	do
	{
		print_line(c, vals[i]);
		i++;
	}
	while(i < length);
	
}

void print_line(char c, int num_of_chars)
{
	int i;
	
	for(i = 0; i < num_of_chars; i++)
	{
		printf("%c",c);
	}
	printf("\n");
}

int len(int arr[])
{
	int length=0;
	
    do
    {
    	length++;
	}
	while(arr[length] > 0);
    
    
	return length;
}
