#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/* strlen & sizeof */
/* strcpy & strncpy */
/* strcat & strncat */
/* strcmp & strncmp */

#define STR_SIZE 32

int main( )
{
    char str[32]        = "hello\0abc";
    char str1[STR_SIZE] = "hello";
    char str2[STR_SIZE] = "world";

    printf("%d\n", strcmp(str1, str2));
    // out:-15



    // strcat(str1, " ");
    // strcat(str1, "world");
    // // out:hello world

    // strncat(str, " ", STR_SIZE);
    // strncat(str, "world", STR_SIZE);
    // // out:hello world



    // strcpy(str, "abcde");
    // puts(str);
    // // out: abcde

    // strncpy(str, "abcde", STR_SIZE);
    // puts(str);
    // // out: abcde





    // printf("%d\n", strlen(str));
    // // out: 5
    // printf("%d\n", sizeof(str));
    // // out: 6



    exit(0);
}