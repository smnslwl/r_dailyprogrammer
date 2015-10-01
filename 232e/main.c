#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#define BUFFER_SIZE 4096

int is_palindrome(const char *);
void palindrome_or_not(int);
void check_for_palindromes(FILE *, int, int, int, int);
void display_help(const char *);

/**
 * Main: Get options and arguments
*/
int
main(int argc, char* argv[])
{
    int opt;
    int o_f = 0;
    int o_l = 0;
    int o_n = 0;
    int o_t = 0;
    
    while ((opt = getopt(argc, argv, "hflnt")) != -1)
        switch (opt) {
            case 'h':
                display_help(argv[0]);
                exit(EXIT_SUCCESS);

            case 'f':
                o_f = 1;
                break;

            case 'l':
                o_l = 1;
                break;

            case 'n':
                o_n = 1;
                break;

            case 't':
                o_t = 1;
                break;

            default:
                printf("Try '%s -h' for more information.\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    
        
    if (argc > optind) {
        FILE* fp;
        if ((fp = fopen(argv[optind], "r")) != NULL) {
            check_for_palindromes(fp, o_l, o_f, o_n, o_t);
            fclose(fp);
        }
        else
            error(EXIT_FAILURE, 0, "Could not open %s", argv[optind]);
    }

    else {
        check_for_palindromes(stdin, o_l, o_f, o_n, o_t);
    }

    exit(EXIT_SUCCESS);
}

/**
 * Returns 1 if str is a palindrome, 0 if not
*/
int
is_palindrome(const char *str)
{
    int n = strlen(str);
    for (int i=0; i < n; ++i)
        if (str[i] != str[n-1-i])
            return 0;
    return 1;
}

/**
 * Displays message depending on if str is a palindrome
*/
void
palindrome_or_not(int is_palindrome)
{
    char* msg = (is_palindrome) ? "Palindrome" : "Not a palindrome";
    printf("%s\n", msg);
}

/**
 * Checks for palindromes in the stream, with specifed options
*/
void
check_for_palindromes(FILE *stream, int each_line, 
    int first_line, int no_msg, int show_totals)
{
    char c;
    char *ptr;
    char text[BUFFER_SIZE];
    int n_lines = 0;
    int n_palindromes = 0;
    int lines_to_read = 0;
    
    if (first_line) {
        ptr = text;
        while ((c = fgetc(stream)) != '\n')
            *ptr++ = c;
        lines_to_read = atoi(text);
    }
        
    ptr = text;
    while ((c = fgetc(stream)) != EOF) {
        if (first_line && n_lines == lines_to_read)
            break;

        if isalnum(c)
            *ptr++ = tolower(c);


        if (c == '\n' && each_line) {
            n_lines++;
            *ptr = '\0';

            if (is_palindrome(text)) {
                n_palindromes++;
                if (!no_msg) palindrome_or_not(1);
            }
            else {
                if (!no_msg) palindrome_or_not(0);
            }
            
            ptr = text;
        }
    }

    *ptr = '\0';
    if (!each_line) {
        n_lines = 1;
        n_palindromes = is_palindrome(text);
        if (!no_msg) palindrome_or_not(n_palindromes);
    }
    
    if (show_totals)
        printf("%i palindromes out of %i\n", n_palindromes, n_lines);
}

/**
 * Display help and exit
*/
void
display_help(const char* cmd)
{
    const char* help;
    
    help =  "Usage: [OPTIONS] FILE\n"
            "Check text(s) in FILE for palindromes\n"
            "\n"
            "   -h     display this help and exit\n"
            "   -f     read N lines at most, N specified by the first line\n"
            "   -l     check each line of text separately\n"
            "   -n     supress 'Palindrome/Not a palindrome' messages\n"
            "   -t     show total number of palindromes found\n"
            "\n"
            "With no FILE, read standard input\n";
    
    printf(help, cmd);
}
