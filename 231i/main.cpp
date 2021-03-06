#include <iostream>
#include <fstream>
#include <vector>

// Returns true if the three cards form a valid set
bool is_valid_set(const std::string& c1, const std::string& c2, 
                    const std::string& c3)
{
    int truth;
    for (int i = 0; i < 4; ++i) {
        truth = (c1[i] != c2[i]) + (c1[i] != c3[i]) + (c2[i] != c3[i]);
        if (truth == 2) return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " FILENAME\n";
        return 0; 
    }
    
    std::ifstream               f(argv[1]);
    std::string                 line;
    std::vector<std::string>    c;
    const uint                  n = 12;
    
    if (f.good()) 
        while (std::getline(f, line)) c.push_back(line);
    else return 0;

    for (uint i = 0; i < n; ++i)
        for (uint j = i + 1; j < n; ++j)
            for (uint k = j + 1; k < n; ++k)
                if (is_valid_set(c[i], c[j], c[k])) 
                    std::cout << c[i] << " " << c[j] << " " << c[k] << "\n";
}
