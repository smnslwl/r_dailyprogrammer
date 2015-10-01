#Vampire Numbers

Challenge #234 Easy

2015-09-28

https://www.reddit.com/r/dailyprogrammer/comments/3moxid/20150928_challenge_234_easy_vampire_numbers/

##Description

Some notes:

- If 2 or more fangs have zero as their last digit, the number is not considered a vampire number.

##Usage

    ./main.out <NUMBER_OF_DIGITS> <NUMBER_OF_FANGS>

Both arguments are optional, with defaults set to 2. Passing strings instead of numbers that `atoi` cannot parse will result in bad things (floating point exception most likely) happening.

##Results and Times

Here's some results and the times taken for each of them. Times shown are in seconds, from the real times from the bash `time` command.

Digits | Fangs each | Vampires found | Time
-------|------------|----------------|------
4|2|7|0.005s
6|3|17|0.035s
6|2|149|0.104s
8|4|34|0.271s
8|2|3243|5.043s
9|3|2664|12.175s
10|5|69|2.640s
10|2|108626|9m47.543s
12|6|59|33.910s
12|4|71590|36m53.227s
