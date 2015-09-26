# Stable Marriage Problem

choices = {x[0] : x.split(', ')[1:] 
            for x in open("input1.txt").read().splitlines()}

free_men = [x for x in choices if x.isupper()]
free_women = [x for x in choices if x.islower()]
engaged = {}

while free_men:
    man = free_men[0]
    woman = choices[man].pop(0)
    if woman in free_women:
        engaged[woman] = man
        free_men.remove(man)
        free_women.remove(woman)
    else:
        rival = engaged[woman]
        if choices[woman].index(man) < choices[woman].index(rival):
            free_men.append(rival)
            free_men.remove(man)
            engaged[woman] = man

for wife, husband in sorted(engaged.items(), key=lambda x: x[1]):
    print('({} ,{})'.format(husband, wife))

"""Algorithm (from Wikipedia)

function stableMatching {
    Initialize all m ∈ M and w ∈ W to free
    while ∃ free man m who still has a woman w to propose to {
       w = highest ranked woman to whom m has not yet proposed
       if w is free
         (m, w) become engaged
       else some pair (m', w) already exists
         if w prefers m to m'
           (m, w) become engaged
           m' becomes free
         else
           (m', w) remain engaged
    }
}

"""
