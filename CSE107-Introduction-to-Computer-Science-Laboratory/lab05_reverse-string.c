#include <stdio.h>
#include <string.h>

void reverse_string(char str []);


int main() {
	
	char str_arr[100];
	printf("Enter a string: ");
 	scanf("%s", str_arr);
 	
 	
 	reverse_string(str_arr);
 	printf ("Reversed string is: %s\n", str_arr);
	
	
	return 0;
}

void reverse_string (char str []){
	int length = strlen(str);
	int i, j;
	  
	char reverseStr[100];
	  
	for(i = 0; i < length; i++)
	{  
		reverseStr[i] = str[i];
	}
	  
	for(i = 0, j = (length-1); i < length; i++, j--)
	{ 
	    str[i]=reverseStr[j];
	}
}
