#include <iostream> // getline, cout
#include <sstream> // istringstream
#include <fstream> // ifstream
#include <vector> // vector
#include <algorithm> // max_element
#include <random> // random_device, mt19937, uniform_int_distribution

class TextLife
{

public:

TextLife(uint rows, uint cols) : rs(rows), cs(cols), t(0)
{
    g.resize(rs + 2);
    for (uint i = 0; i < rs + 2; ++i)
        g[i].resize(cs + 2, ' ');
}

void update()
{
    auto tmp(g);

    for (uint r = 1; r <= rs; ++r)
        for (uint c = 1; c <= cs; ++c) {
            tmp[r][c] = '0' + neighbours(r, c);
            switch (neighbours(r, c)) {
                case 2: 
                    tmp[r][c] = g[r][c];
                    break;
                case 3: 
                    tmp[r][c] = chars[get_random()]; 
                    break;
                default: 
                    tmp[r][c] = ' ';
                    break;
            }
        }
    
    chars.clear();
    for (uint r = 1; r <= rs; ++r)
        for (uint c = 1; c <= cs; ++c)
                if ((g[r][c] = tmp[r][c]) != ' ')
                    chars.push_back(g[r][c]);
                
    t++;
}

void fill_from(const std::vector<std::string>& v)
{
    for (uint r = 0; r < v.size(); ++r) {
        std::string line = v[r];
        for (uint c = 0; c < line.size(); ++c) {
            if ((g[r + 1][c + 1] = line[c]) != ' ')
                chars.push_back(g[r + 1][c + 1]);
        }
    }
}

void display() const
{
    std::cout << rs << "x" << cs << " t=" << t << "\n";
    
    for (uint r = 0; r < rs + 2; ++r) {
        for (uint c = 0; c < cs + 2; ++c) {
            std::cout << g[r][c] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * Random distribution to get an index in the 'chars' vector
*/
uint get_random()
{
    uint n = chars.size() - 1;
    return std::uniform_int_distribution<uint>{0, n}(rnd);
}

private:

uint neighbours(uint r, uint c) const
{
    uint n = 0;
    for (uint i = r - 1; i <= r + 1; ++i)
        for (uint j = c - 1; j <= c + 1; ++j)
            n += (g[i][j] != ' ');
    return n - (g[r][c] != ' ');
}

uint rs; // number of rows
uint cs; // number of cols
uint t; // the current generation
std::vector<std::vector<char>> g; // the 2D grid
std::vector<char> chars; // all chars currently in the grid
std::mt19937 rnd{std::random_device{}()}; // random engine
};

/**
 * Main
*/
int main(int argc, char* argv[])
{
    std::string line;
    std::vector<std::string> lines;
    std::string filename;
    uint n = 100;
    
    // look for CL args for filename and the no. of generations to show
    filename = (argc > 1) ? argv[1] : __FILE__;
    if (argc > 2) {
        std::istringstream ss(argv[2]);
        ss >> n;
    }

    std::ifstream infile(filename);    

    if (infile.good()) {
        while (std::getline(infile, line))
            lines.push_back(line);
        // find the longest line to determine no. of columns
        auto ll = std::max_element(lines.begin(), lines.end(), 
            [](auto x, auto y) { return x.size() < y.size(); });
        
        TextLife tl( lines.size(), (*ll).size());
        tl.fill_from(lines);

        for (uint i = 0; i <= n; ++i) {
            std::cout << "\033[2J\033[1;1H"; // clear screen + cursor pos
            tl.display();
            tl.update();
            std::cin.get(); // wait for keypress to continue
        }
    }
}
