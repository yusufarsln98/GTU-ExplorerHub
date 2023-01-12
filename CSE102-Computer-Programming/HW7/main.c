#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDLENGTH 40   

/* Header Functions. */
void fix_spelling_error(char *dictionfile, char *sourcefile);
void find_best_correction(FILE *dictionary, char *buffer);

/* Bonus Header Function */
void fix_spelling_error2(char *dictionfile, char *sourcefile);


/* Helper Functions. */
void make_lowercase(char *lower);
int arrange_word(const char *str);
int find_different_char(const char *temp, const char *buffer, int *index);
int separate_word(char *partial, const char *str);

/* 
Uyarı!

1-) -tırnak ve kesme işareti hariç- 
Noktalama işareti içeren kelimeler işaretten öncesi ve (eğer varsa) sonrası ayrı birer string olarak ele alındı, 
kelimeler sözlükte kontrol edilip gerekli değişiklikler yapıldı.

örneğin:
--> part1/part2  part1.part2 part1-part2 ... Şeklindeki stringler ikiye bölündüler
kontrol edildiler ve tekrar birleştirildiler.

!!
--> Sözlükte part1 ve part2'lerin ayrı ayrı bulunduğundan emin olunuz.

2-) Tırnak veya kesme işareti ile ayrılan kelimeler önce noktalama işaretinden temizlenip daha kontrollerden
sonra eski haline getirildi.

--> version's + album's gibi kelimelerin kontrolü için sözlükte 
!! 
versions ve albums 
şeklindeki stringlerinin varlığından emin olunuz.

3-) Ampresand ile birleştirilen kelimeler tek bir kelimeymiş gibi düşünüldü.

--> part1&part2  şeklindeki stringlerin kontrolu için sözlüğe part1&part2 şeklinde
eklendiğinden emin olun.

4-) Sözlükte büyük harfli stringlerin olması hiçbir şey ifade etmeyecektir.

*/

int main()
{
    /* Copy the file names into the strings and pass them to fix_spelling error function. */
    char sourcefile[20], dictionfile[20];
    strcpy(sourcefile, "text.txt");         
    strcpy(dictionfile, "dictionary.txt");
    fix_spelling_error(dictionfile, sourcefile);
    /* BONUS PART */
    /*
    fix_spelling_error2(dictionfile, sourcefile);
    */
   
    return 0;
}
void fix_spelling_error(char *dictionfile, char *sourcefile)
{
    char str[WORDLENGTH],               /* Original string taken in file. */
         temp[WORDLENGTH],              /* Keeps the lowercase version of the string. */
         buffer[WORDLENGTH],            /* Keeps the fixed word. */
         partial_word[WORDLENGTH];      /* Keeps the partial fixed words. ie: run-time (run and time). */

    int i,              /* Counter */ 
        length,         /* Keeps the length of "cleaned" string */
        flag,           /* Which type of string. (Clean or with puntiations) */
        index,          /* Keeps where the string cutted. (ie: black" --> 5) */
        temp_index,     /* Keeps the index temporarily for 2-case strings (menager/producer) */
        difference;     /* Keeps the difference of char which should be change. */

    char ch;            /* Keeps a " or ' temporarily to fix the words like version's... */
    
    /* File operations. */
    FILE *source, *dictionary;          

    source = fopen(sourcefile, "r+");
    dictionary = fopen(dictionfile, "r");
    if(source == NULL || dictionary == NULL)
    {
        printf("Could not open text file!\n");
        exit(1);
    }
    /* Primary loop. Reads word from sourcefile then fix the words. */
    i = 0;
    while(fscanf(source, "%s", str) == 1)
    {
        difference = 0;                 /* Initial the variables and clean them in all iteration. */
        strcpy(temp, "\0");             /* Initial the variables and clean them in all iteration. */
        strcpy(partial_word, "\0");     /* Initial the variables and clean them in all iteration. */
        strcpy(buffer, "\0");           /* Initial the variables and clean them in all iteration. */
        
        strcpy(temp, str);          /* Copy the original string to temp */
        make_lowercase(temp);       /* Then change the chars with lowercases */
        flag = arrange_word(temp);  /* Arrange the word. "paint or run-time or aftermath... */
        switch (flag)
        {
        case 0:     /* Case for the clean words, part1&part2 shaped */
            strcpy(buffer, temp);                                       /* Copies the temp into the buffer to find fixed word. */
            find_best_correction(dictionary, temp);                     /* Finds fixed word. */

            /* Compares temp and buffer to find which char was different (index) and what is the difference between chars (difference). 
            ie: aftermmth --> aftermath : index is 7 and difference is ('m' - 'a') */
            difference = find_different_char(temp, buffer, &index);     
            if (difference != 0)                                        /* If there is difference... */
            {
                str[index] -= (difference);                             /* Add difference to the char to fix wrong char. */
            }
            break;

        case 1:     /* Case for words contain punctiations. */
            length = separate_word(partial_word, temp);     /* Seperate the word and keep the length of seperated word. */

            /* If there is another word after the first word (ie: run-time) Do this: */
            if ((temp[length + 1] >= 'a' && temp[length + 1] <= 'z') || (temp[length + 1] >= '0' && temp[length + 1] <= '9'))
            {   
                /* Same process with case 1 for the first part of the word. (ie: run) */
                strcpy(buffer, partial_word);                               
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index] -= (difference);
                }
                /* Keep the other string (ie: time) and find the best correction then replace the faults. */
                temp_index = length + 1;
                strcpy(partial_word, "\0");
                strcpy(buffer, "\0");
                length = separate_word(partial_word, (temp + length + 1));
                strcpy(buffer, partial_word);
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                
                if (difference != 0)
                {
                    str[temp_index + index] -= (difference);
                }
            }
            /* Else if there is not any word after the first word (influences,) Do this: */
            else
            {
                /* Same process with case 1 for the first part of the word. (only difference keep the partial(ie: influences))*/
                strcpy(buffer, partial_word);
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index] -= (difference);
                }
            }
            break; 
        case 2:     /* Case for words contain " or ' */
            /* 
            We assume that there is not any word after the first word. 
            ie: xx part1"part2 xx  but, there can be a char after the marks. ie: version's
            for this case we going to think this word as versions and find best match then
            bring it its original shape back.
            */   
            length = separate_word(partial_word, temp);
            /* If there is a char after the mark then replace it into word's --> words' */
            if ((temp[length + 1] >= 'a' && temp[length + 1] <= 'z') || (temp[length + 1] >= '0' && temp[length + 1] <= '9'))
            {
                ch = temp[length];
                temp[length] = temp[length + 1];
                temp[length + 1] = ch; 
            }
            /* Then same process with the first part. */
            length = separate_word(partial_word, temp);
            strcpy(buffer, partial_word);
            find_best_correction(dictionary, partial_word);
            difference = find_different_char(partial_word, buffer, &index);
            /* If the letter after ' is broken then increase the index */
            if(index == (length - 1))
            {
                index++;
            }
            if (difference != 0)
            {
                str[index] -= (difference);
            }
            break;
        case 3:     /* Case for words start a punctiation (ie: "paint) and single punctiations. (ie: -) */
            /* If it is not a single punctiations then shift the word ones time. */            
            if ((temp[1] >= 'a' && temp[1] <= 'z') || (temp[1] >= '0' && temp[1] <= '9'))
            {
                /* Then the same process with first part. */
                length = separate_word(partial_word, (temp + 1));
                strcpy(buffer, partial_word);
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);

                if (difference != 0)
                {
                    str[index + 1] -= (difference);
                }
            }
            break;
        }
        /* Go where the last string starts and replace it with fixed word. */   
        fseek(source, -1 * strlen(str), SEEK_CUR);
        fprintf(source, "%s ", str);
        i++;
    }
    fclose(source);
    fclose(dictionary);
}
    
/* If there is a punctiation to clean, finds it and return the length of the cleaned word. */
int separate_word(char *partial, const char *str)
{
    int i;
    i = 0;
    while((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9'))
    {
        partial[i] = str[i];
        i++;
    }
    partial[i] = '\0';
    return i;
}
/* Find the different char and return the value between chars. Also pass the (index) as which char is different */
int find_different_char(const char *temp, const char *buffer, int *index)
{
    int i;
    for (i = 0; temp[i] != '\0'; i++)
    {
        if (temp[i] != buffer[i])
        {
            *index = i;
            return (strcmp(buffer, temp));  /* Returns mathematical difference of the different char. Such as 'a' - 'c' = 2 */
        }
    }
    return 0;
}

/* Looks the string and arange it according to the type of it. (ie: clean or has punctiation or starts with punctiation) */
int arrange_word(const char *str)
{
    int i;

    /* If it does not start with a letter or number, return 3*/
    if(!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= '0' && str[0] <= '9')))
    {
        return 3;
    }

    /* Other arrangment. */
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '&')
        {
            return 0;
        }
        else if (str[i] == '-' || str[i] == '/' || str[i] == '.' || str[i] == ',' || str[i] == '?' || str[i] == '!' || str[i] == ':')
        {
            return 1;
        }
        else if (str[i] == '\'' || str[i] == '\"')
        {
            return 2;
        }
    }
    return 0;   
}

/* Finds the best match. */
void find_best_correction(FILE *dictionary, char *buffer)
{
    char dic_word[WORDLENGTH],  /* Keeps the words from dictionary. */
         temp_word[WORDLENGTH]; /* Keeps the possible correct word. */
    int i, j,                   /* Counters. */
        flag, temp_flag,        /* Keeps the number of matched chars. */
        count_vowels,           /* Keeps the number of vowels for the strings. */
        temp_vowels;            /* Keeps the number of vowels temporarily to compare the previous string. */

    /* Initial values. */
    temp_vowels = 1;
    count_vowels = 0;
    flag = 0;
    temp_flag = 0;

    
    fseek(dictionary, 0, SEEK_SET);     /* Brings the dictionary file to the start position in all call */

    /* For reading strings and compare the parameter. */
    for (i = 0, j = 0; !feof(dictionary); i++)
    {
        fscanf(dictionary, "%s", dic_word);
        /* For the first word. To keep temporarily a string */
        if (i == 0 && (strlen(dic_word) == strlen(buffer)))   
        {
            /* Count the number of matched chars. */
            while (buffer[j] != '\0')
            {
                if (dic_word[j] == buffer[j])
                {
                    temp_flag++;
                }
                j++;
            }
            strcpy(temp_word, dic_word);
        }
        /* For the other words to compare buffer with dictionary */
        else
        {
            j = 0;
            flag = 0;
            if (strlen(dic_word) == strlen(buffer))
            {
                while (buffer[j] != '\0')
                {
                    if (dic_word[j] == buffer[j])   /* If there is same char with buffer and word from dictionary. */
                    {
                        flag++;                     /* Count number of chars. */
                    }
                    j++;
                }
                if (flag > temp_flag)   /* If the last word has more similarity then the previous word */
                {
                    strcpy(temp_word, dic_word);    /* Then replace it. */
                    temp_flag = flag;
                }
            }
            /* Vowel letter priority */
            if (flag == temp_flag && strlen(dic_word) > 3 && strlen(dic_word) == strlen(buffer))
            {
                /* Count the vowels. */
                for (j = 0; dic_word[j] != '\0'; j++)
                {
                    if (dic_word[j] == 'a' || dic_word[j] == 'e' || dic_word[j] == 'i' || dic_word[j] == 'o' || dic_word[j] == 'u')
                    {
                        count_vowels++;
                    }
                }
                /* If the last word has more vowels then the other option previous option, then replace it. */
                if (count_vowels > temp_vowels)
                {
                    temp_flag = flag;
                    strcpy(temp_word, dic_word);
                }
            }
        }
    }
    strcpy(buffer, temp_word);
}

/* Turns the string with its lowercase version. */
void make_lowercase(char *lower)
{
    int i;
    for (i = 0; lower[i] != '\0'; i++)
    {
        if (lower[i] >= 'A' && lower[i] <= 'Z')
        {
            lower[i] += 'a' - 'A';
        }
    }
}



/* ****************************************************** */

/*
**B                                                      B**
        
**O                                                      O**    

**N                                                      N**    
        
**U                                                      U**    

**S                                                      S**    

*/

/* ****************************************************** */

/* For the fixing 2 char differences. */
void fix_spelling_error2(char *dictionfile, char *sourcefile)
{
    char str[WORDLENGTH],               /* Original string taken in file. */
         temp[WORDLENGTH],              /* Keeps the lowercase version of the string. */
         buffer[WORDLENGTH],            /* Keeps the fixed word. */
         partial_word[WORDLENGTH];      /* Keeps the partial fixed words. ie: run-time (run and time). */

    int i,              /* Counter */ 
        length,         /* Keeps the length of "cleaned" string */
        flag,           /* Which type of string. (Clean or with puntiations) */
        index,          /* Keeps where the string cutted. (ie: black" --> 5) */
        temp_index,     /* Keeps the index temporarily for 2-case strings (menager/producer) */
        difference;     /* Keeps the difference of char which should be change. */

    char ch;            /* Keeps a " or ' temporarily to fix the words like version's... */
    
    /* File operations. */
    FILE *source, *dictionary;          

    source = fopen(sourcefile, "r+");
    dictionary = fopen(dictionfile, "r");
    if(source == NULL || dictionary == NULL)
    {
        printf("Could not open text file!\n");
        exit(1);
    }
    /* Primary loop. Reads word from sourcefile then fix the words. */
    i = 0;
    while(fscanf(source, "%s", str) == 1)
    {
        difference = 0;                 /* Initial the variables and clean them in all iteration. */
        strcpy(temp, "\0");             /* Initial the variables and clean them in all iteration. */
        strcpy(partial_word, "\0");     /* Initial the variables and clean them in all iteration. */
        strcpy(buffer, "\0");           /* Initial the variables and clean them in all iteration. */
        
        strcpy(temp, str);          /* Copy the original string to temp */
        make_lowercase(temp);       /* Then change the chars with lowercases */
        flag = arrange_word(temp);  /* Arrange the word. "paint or run-time or aftermath... */

        /* *********** */
        /* 
        Only difference from the 1st version: 
        First (if (difference != 0))s for the first char and second one is for the 2nd char. 
        */
        /* *********** */
        switch (flag)
        {
        case 0:     /* Case for the clean words, part1&part2 shaped */
            strcpy(buffer, temp);                                       /* Copies the temp into the buffer to find fixed word. */
            find_best_correction(dictionary, temp);                     /* Finds fixed word. */

            /* Compares temp and buffer to find which char was different (index) and what is the difference between chars (difference). 
            ie: aftermmth --> aftermath : index is 7 and difference is ('m' - 'a') */
            difference = find_different_char(temp, buffer, &index);     
            if (difference != 0)                                        /* If there is difference... */
            {
                str[index] -= (difference);                             /* Add difference to the char to fix wrong char. */
            }
            /* Same process for the 2nd char. */
            strcpy(temp, str);          
            strcpy(buffer, temp);                                       
            find_best_correction(dictionary, temp);                     
            difference = find_different_char(temp, buffer, &index);
            if (difference != 0)              
            {
                str[index] -= (difference);   
            }
            break;

        case 1:     /* Case for words contain punctiations. */
            length = separate_word(partial_word, temp);     /* Seperate the word and keep the length of seperated word. */

            /* If there is another word after the first word (ie: run-time) Do this: */
            if ((temp[length + 1] >= 'a' && temp[length + 1] <= 'z') || (temp[length + 1] >= '0' && temp[length + 1] <= '9'))
            {   
                /* Same process with case 1 for the first part of the word. (ie: run) */
                strcpy(buffer, partial_word);                               
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index] -= (difference);
                }
                /* Keep the other string (ie: time) and find the best correction then replace the faults. */
                buffer[index] = str[index];
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index] -= (difference);
                }

                temp_index = length + 1;
                strcpy(partial_word, "\0");
                strcpy(buffer, "\0");
                length = separate_word(partial_word, (temp + length + 1));
                strcpy(buffer, partial_word);
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[temp_index + index] -= (difference);
                }

                buffer[index] = str[temp_index + index];
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[temp_index + index] -= (difference);
                }
            }
            /* Else if there is not any word after the first word (influences,) Do this: */
            else
            {
                /* Same process with case 1 for the first part of the word. (only difference keep the partial(ie: influences))*/
                strcpy(buffer, partial_word);
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index] -= (difference);
                }
                buffer[index] = str[index];
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index] -= (difference);
                }
            }
            break; 
        case 2:     /* Case for words contain " or ' */
            /* 
            We assume that there is not any word after the first word. 
            ie: xx part1"part2 xx  but, there can be a char after the marks. ie: version's
            for this case we going to think this word as versions and find best match then
            bring it its original shape back.
            */   
            length = separate_word(partial_word, temp);
            /* If there is a char after the mark then replace it into word's --> words' */
            if ((temp[length + 1] >= 'a' && temp[length + 1] <= 'z') || (temp[length + 1] >= '0' && temp[length + 1] <= '9'))
            {
                ch = temp[length];
                temp[length] = temp[length + 1];
                temp[length + 1] = ch; 
            }
            /* Then same process with the first part. */
            length = separate_word(partial_word, temp);
            strcpy(buffer, partial_word);
            find_best_correction(dictionary, partial_word);
            difference = find_different_char(partial_word, buffer, &index);
            if (index == (length - 1))
            {
                index++;
            }
            if (difference != 0)
            {
                str[index] -= (difference);
            }
            buffer[index] = str[index];
            difference = find_different_char(partial_word, buffer, &index);
            if (index == (length - 1))
            {
                index++;
            }
            if (difference != 0)
            {
                str[index] -= (difference);
            }
            break;
        case 3:     /* Case for words start a punctiation (ie: "paint) and single punctiations. (ie: -) */
            /* If it is not a single punctiations then shift the word ones time. */            
            if ((temp[1] >= 'a' && temp[1] <= 'z') || (temp[1] >= '0' && temp[1] <= '9'))
            {
                /* Then the same process with first part. */
                length = separate_word(partial_word, (temp + 1));
                strcpy(buffer, partial_word);
                find_best_correction(dictionary, partial_word);
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index + 1] -= (difference);
                }
                buffer[index] = str[index + 1];
                difference = find_different_char(partial_word, buffer, &index);
                if (difference != 0)
                {
                    str[index + 1] -= (difference);
                }
            }
            break;
        }
        /* Go where the last string starts and replace it with fixed word. */   
        fseek(source, -1 * strlen(str), SEEK_CUR);
        fprintf(source, "%s ", str);
        i++;
    }
    fclose(source);
    fclose(dictionary);
}