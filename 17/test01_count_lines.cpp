#include <algorithm>                   // std::transform
#include <fstream>                     // std::ifstream
#include <iostream>                    // std::cout/endl
#include <iterator>                    // std::distance
#include <numeric>                     // std::accumulate
#include <vector>                      // std::vector
#include <nvwa/istream_line_reader.h>  // nvwa::istream_line_reader

using namespace std;
using nvwa::istream_line_reader;

int count_file(const char* name)
{
    ifstream ifs(name);
    istream_line_reader reader(ifs);
    return distance(reader.begin(), reader.end());
}

int count_lines(const char** begin, const char** end)
{
    vector<int> count(end - begin);
    transform(begin, end, count.begin(), count_file);
    return accumulate(count.begin(), count.end(), 0);
}

int main(int argc, const char** argv)
{
    int total_lines = count_lines(argv + 1, argv + argc);
    cout << "Total lines: " << total_lines << endl;
}
