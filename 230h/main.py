import sys
from itertools import chain

wordlist = {x for x in open('words.txt').read().splitlines()}
lines = sys.stdin.read().splitlines()

nr = int(lines[0])
rows = lines[1:nr + 1]
nc = len(rows[0])
cols = (''.join([rows[j][i] for j in range(nr)]) for i in range(nc))
rows_and_cols = (x.strip().lower() for x in chain(rows, cols) if x.strip())

words = []
for text in rows_and_cols:
    n = len(text)
    combs = (text[i:j] for i in range(n) for j in range(n, i, -1))
    for comb in sorted(combs, key=len, reverse=True):
        if comb in wordlist:
            words.append(comb)
            break
        if comb[::-1] in wordlist:
            words.append(comb[::-1])
            break

for word in sorted(words):
    print(word)
