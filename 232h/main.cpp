/**
 * Divides a state into n districts of (almost) equal populations
 * Uses the Short Splitline Algorithm <http://rangevoting.org/SSArecursive.txt>
*/

#include <iostream> // cout
#include <fstream> // ifstream
#include <vector> // vector
#include <cmath> // abs
#include <iomanip> // setw
#include <limits> // numeric_limits<int>::max()

double ratio(double a, double b) { return a/b; }

/* After which row (or col, if split is vertical) does the split occur */
struct Split { bool horizontal; uint after; };

/* Grid positions of the first and last cells of a district */
struct District { uint r1, c1, r2, c2; };

class State
{

public:

/* Read data from stream, then call split function over the whole state */
State(std::istream& istr)
{
    istr >> _n >> _r >> _c;

    _grid.resize(_r * _c);
    for (uint i = 0; i < _r; ++i)
        for (uint j = 0; j < _c; ++j)
            istr >> _grid[i * _c + j];

    split(District{0, 0, _r - 1, _c - 1}, _n);
}

/* Display grid with lines drawn at district borders */
void as_grid()
{
    /* The output grid: space out _grid to display district borders */
    uint rr = (_r * 2 + 1);
    uint cc = (_c * 2 + 1);
    std::vector<std::string> output(rr * cc, "");
    
    /* Copy over data from _grid to output grid */
    for (uint i = 0; i < _r; ++i)
        for (uint j = 0; j < _c; ++j)
            output[(i * 2 + 1) * cc + (j * 2 + 1)] = 
                std::to_string(_grid[i * _c + j]);

    /* Draw borders for each district */
    for (auto d: _districts) {
        for (uint i = 2 * d.r1 + 0; i <= 2 * d.r2 + 2; ++i) 
            output[i * cc + 2 * d.c1 + 0] = "|";
        for (uint i = 2 * d.r1 + 0; i <= 2 * d.r2 + 2; ++i) 
            output[i * cc + 2 * d.c2 + 2] = "|";
        for (uint i = 2 * d.c1 + 0; i <= 2 * d.c2 + 2; ++i) 
            output[(d.r1 * 2 + 0) * cc + i] = "-";
        for (uint i = 2 * d.c1 + 0; i <= 2 * d.c2 + 2; ++i) 
            output[(d.r2 * 2 + 2) * cc + i] = "-";
    }

    /* Display the output vector */
    for (uint i = 0; i < rr; ++i) {
        for (uint j = 0; j < cc; ++j)
            std::cout << std::setw(2) << output[i * cc + j];
        std::cout << "\n";
    }
}


/* Display list of districts with populations */
void as_list()
{
    std::cout << "The " << _districts.size() << " districts are: \n";
    for (auto d: _districts)
        std::cout << "District (" 
        << std::setw(2) << d.r1 << ", " << std::setw(2) << d.c1 << ")    (" 
        << std::setw(2) << d.r2 << ", " << std::setw(2) << d.c2 << ")     "
        << "Population: " << std::setw(4) << pop(d) << "\n";
}

private:

/* The total population of a district */
uint pop(District district)
{
    uint sum = 0;
    for (uint i = district.r1; i <= district.r2; ++i)
        for (uint j = district.c1; j <= district.c2; ++j)
            sum += _grid[i * _c + j];
    return sum;
}

/* Keep splitting up districts until n is 1 */
void split(District d, uint n)
{
    if (n == 1) {
        _districts.push_back(d);
        return;
    };

    uint a = n / 2;
    uint b = n - a;
    auto ds = get_ds(d, best_split(d, ratio(a, b)));

    split(ds.first, a);
    split(ds.second, b);
}

/* Split dividing the district into two with population ratio close to r */
Split best_split(District d, double r)
{
    std::vector<Split> possible_splits;
    for (uint i = d.r1; i < d.r2; ++i)
        possible_splits.push_back(Split{true, i});
    for (uint i = d.c1; i < d.c2; ++i)
        possible_splits.push_back(Split{false, i});

    Split best;
    double best_delta = std::numeric_limits<int>::max();

    for (auto split: possible_splits) {
        auto ds = get_ds(d, split);

        double delta = std::abs(r - ratio(pop(ds.first), pop(ds.second)));
        if (delta < best_delta) {
            best = split;
            best_delta = delta;
        }
    }

    return best;
}

/* Pair of districts formed by dividing the district with the split */
std::pair<District, District> get_ds(const District& d, const Split& split)
{
    District da, db;
    if (split.horizontal) {
        da = District{ d.r1, d.c1, split.after, d.c2};
        db = District{ split.after + 1, d.c1, d.r2, d.c2 };
    }
    else {
        da = District{ d.r1, d.c1, d.r2, split.after};
        db = District{ d.r1, split.after + 1, d.r2, d.c2};
    }
    return std::make_pair(da, db);
}

uint _r, _c, _n; /* rows, columns and the number of districts to carve */
std::vector<uint> _grid;
std::vector<District> _districts;

};

int main(int argc, char* argv[])
{
    std::string filename;
    filename = (argc > 1) ? argv[1] : "input1.txt";
    std::ifstream infile(filename);
    State s{infile};
    s.as_list();
    std::cout << "\n";
    s.as_grid();
}
