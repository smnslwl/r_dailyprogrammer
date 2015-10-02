#include <iostream>
#include <fstream>

class Trie
{

public:

Trie(std::string filename) : root(new Node)
{
    std::ifstream words(filename);
    std::string word;
    while (words >> word)
        insert(word);
}

~Trie()
{
    delete root;
}

void insert(const std::string& word)
{
    Node* temp = root;   
    size_t i;

    for (char c : word) {
        i = c - 'a';
        if (!temp->nodes[i])
            temp->nodes[i] = new Node;
        temp = temp->nodes[i];
    }
}

size_t check(const std::string& word)
{
    Node* temp = root;
    size_t i;
    size_t pos = 0;

    for (auto c : word) {
        i = c - 'a';
        if (temp->nodes[i])
            temp = temp->nodes[i];
        else
            break;
        pos++;
    }

    return pos;
}

private:

class Node
{
public:

Node* nodes[26] {};

~Node()
{
    for (auto node : nodes)
        if (node)
            delete node;
}

};

Node* root;

};

int main()
{
    Trie trie("../enable1.txt");
    std::ifstream infile("input1.txt");
    std::string w;
    size_t p;

    while (infile >> w) {
        if ((p = trie.check(w)) < w.size())
            std::cout << w.substr(0, p+1) << "<" << w.substr(p+1) << "\n";
        else
            std::cout << w << "\n";
    }
}
