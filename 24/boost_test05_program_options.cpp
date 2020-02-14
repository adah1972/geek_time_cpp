#include <iostream>
#include <string>
#include <stdlib.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using std::cout;
using std::endl;
using std::string;

string locale;
string lang;
int width = 72;
bool keep_indent = false;
bool verbose = false;

int main(int argc, char* argv[])
{
    po::options_description desc(
        "Usage: breaktext [OPTION]... <Input File> [Output File]\n"
        "\n"
        "Available options");
    desc.add_options()
        ("locale,L", po::value<string>(&locale),
         "Locale of the console (system locale by default)")
        ("lang,l", po::value<string>(&lang),
         "Language of input (asssume no language by default)")
        ("width,w", po::value<int>(&width),
         "Width of output text (72 by default)")
        ("help,h", "Show this help message and exit")
        (",i", po::bool_switch(&keep_indent), "Keep space indentation")
        (",v", po::bool_switch(&verbose), "Be verbose");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    }
    catch (po::error& e) {
        cout << e.what() << endl;
        exit(1);
    }
    vm.notify();

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(1);
    }
    cout << "Locale:   " << locale << endl;
    cout << "Lang:     " << lang << endl;
    cout << "Width:    " << width << endl;
    cout << "Verbose:  " << verbose << endl;
}
