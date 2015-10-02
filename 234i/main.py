with open('../enable1.txt') as f:
    wordlist = f.read().splitlines()
    
with open('input1.txt') as f:
    input_words = f.read().splitlines()
    
for word in input_words:
    for i in range(2, len(word)):
        for w in wordlist:
            if w.startswith(word[:i]):
                break
        else:
            print(word[:i] + '<' + word[i:])
            break
