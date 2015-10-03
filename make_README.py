import os
import re

README      =   """
# Solutions to /r/dailyprogrammer challenges

https://www.reddit.com/r/dailyprogrammer/


## Solutions

 Challenge # | Date | Title | Solutions 
-------------|------|-------|-----------
{solution_list}

## Licence

Pretty simple, see [LICENCE.txt](LICENCE.txt) for details.

"""

SOLUTION    =   '{challenge_id} | {date} | [{title}]({url}) | {solutions}\n'

IS_DIR      =   re.compile(r'[0-9]+[eihw]')

BASE_DIR    =   ''

LEVELS      =   { 
                    'e'     : 'Easy',
                    'i'     : 'Intermediate',
                    'h'     : 'Hard',
                    'w'     : 'Weekly',
                }
    
NAMES       =   [
                    'main',
                    'Main',
                    'bonus',
                ]

LANGS       =   {
                    '.py'    : 'Python',
                    '.c'     : 'C',
                    '.cpp'   : 'C++',
                    '.hs'    : 'Haskell',
                    '.rb'    : 'Ruby',
                }


dirs = [x for x in os.listdir() if os.path.isdir(x) and IS_DIR.fullmatch(x)]

solution_list = ''

for challenge in sorted(dirs):
    path = os.path.join(BASE_DIR, challenge)

    with open(os.path.join(path, 'README.md')) as f:
        lines = [x for x in f.read().splitlines() if x][:4]
    title, date, url = lines[0][1:], lines[2], lines[3]
    challenge_id = '{} {}'.format(challenge[:-1], LEVELS[challenge[-1]])
    
    
    files = [x for x in os.listdir(path) 
                if os.path.isfile(os.path.join(path, x))]

    solutions = []
    for filename in files:
        root, ext = os.path.splitext(filename)
        if root in NAMES and ext in LANGS:
            solutions.append('[{}]({})'.format(
                                LANGS[ext], (os.path.join(path, filename))
                            ))
    
    if solutions:
        all_solutions = ', '.join(solutions)
    else:
        all_solutions = 'Incomplete'

    solution_list += SOLUTION.format(
                        challenge_id=challenge_id, date=date, url=url, 
                        title=title, solutions=all_solutions
                     )


with open('README.md', 'w') as f:
    f.write(README.format(solution_list=solution_list))
