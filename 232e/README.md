#Palindromes

Challenge #232 Easy

2015-09-14

https://www.reddit.com/r/dailyprogrammer/comments/3kx6oh/20150914_challenge_232_easy_palindromes/

## Examples

I symlinked `palindromes` to `main.out` from a folder included in $PATH, for better readability.

    $ palindromes -h
    Usage: [OPTIONS] FILE
    Check text(s) in FILE for palindromes

       -h     display this help and exit
       -f     read N lines at most, N specified by the first line
       -l     check each line of text separately
       -m     show whether each text is a palindrome or not
       -t     show total number of palindromes found

    With no FILE, read standard input

Checking input files where the first line specifies how many lines to read.
    
    $ palindromes -f input1.txt
    Not a palindrome
    $ palindromes -f input2.txt
    Palindrome
    
Checking the number of palindromes in the [https://code.google.com/p/dotnetperls-controls/downloads/detail?name=enable1.txt&can=2&q=] (enable1.txt) wordlist. If the 'check each line of text separately' option is not specified here, the program will break as the file is too large to be read all at once. The -n option is used to supress the 'Palindrome/Not a palindrome' messages that would get displayed for each word.

    $ time palindromes -lnt ../enable1.txt
    103 palindromes out of 172819

    real	0m0.032s
    user	0m0.028s
    sys	0m0.000s

Reading from stdin. '> ' is not actually typed, just used to denote input. ^D stands for the EOF character, i.e. `Ctrl+D`.

    $ palindromes
    > Was it a car
    > or a cat I saw?
    ^D
    Palindrome
    
Reading palindromes from stdin, line-by-line.

    $ palindromes -l
    > hello
    Not a palindrome
    > Hannah@han.nah
    Palindrome
