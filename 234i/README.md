#Red Squiggles

Challenge #234 Intermediate

2015-09-30

https://www.reddit.com/r/dailyprogrammer/comments/3n55f3/20150930_challenge_234_intermediate_red_squiggles/

##Description

Many of us are familiar with real-time spell checkers in our text editors. Two of the more popular editors Microsoft Word or Google Docs will insert a red squiggly line under a word as it's typed incorrectly to indicate you have a problem. (Back in my day you had to run spell check after the fact, and that was an extra feature you paid for. Real time was just a dream.) The lookup in a dictionary is dynamic. At some point, the error occurs and the number of possible words that it could be goes to zero.

For example, take the word foobar. Up until foo it could be words like foot, fool, food, etc. But once I type the b it's appearant that no words could possibly match, and Word throws a red squiggly line.

Your challenge today is to implement a real time spell checker and indicate where you would throw the red squiggle. For your dictionary use /usr/share/dict/words or the always useful enable1.txt.

###Input Description

You'll be given words, one per line. Examples:

    foobar
    garbgae

###Output Description

Your program should emit an indicator for where you would flag the word as mispelled. Examples:

    foob<ar
    garbg<ae

Here the < indicates "This is the start of the mispelling". If the word is spelled correctly, indicate so.

