#Word Compactification

Challenge #230 Intermediate

2015-09-01

https://www.reddit.com/r/dailyprogrammer/comments/3jd72z/20150901_challenge_230_intermediate_word/

#Description

###Input Specification

You'll be given a set of words on one line, separated by commas. Your solution should be case insensitive, and treat hyphens and apostrophes as normal letters - you should handle the alphabet, ' and - in words. 

###Output Description

Output the the compactified set of words, along with the number of crossings (ie. the number of letters you saved). Words may be touching, as long as all of the words present in the input are present in the output (the words may travel in any direction, such as bottom-to-top - the company's logo is /r/CrappyDesign material).

#Usage

The program reads data from stdin and prints a sorted list of all words.

    $ python main.py < input2.txt

