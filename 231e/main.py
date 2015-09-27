import sys

txt = sys.stdin.read().strip()
for i in range(25):
    print(''.join([' x'[x != '0'] for x in txt]))
    r = '0{}0'.format(txt)
    txt = ''.join(['01'[int(r[n-1] != r[n+1])] for n in range(1, len(txt))])
