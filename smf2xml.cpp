#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> // for std::strerror
#include <cerrno>

#include "midifile.h"

static const char versionString[] = "0.1";
static bool debugMode = false;

void printVersion()
{
    std::cout << "This is xml2smf version " << versionString << std::endl;
}

void usage()
{
    printVersion();
    std::cout << "Usage: xml2smf [args] [infile] [outfile]\n"
              << "   args:\n"
              << "      -v      print version\n"
              << "      -d      debug mode\n";
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        usage();
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-v")
        {
            printVersion();
            return 0;
        }
        else if (arg == "-d")
        {
            debugMode = true;
        }
    }

    std::ifstream inFile(inputFile);
    if (!inFile.is_open())
    {
        std::cerr << "Cannot open input file: " << inputFile << " - " << std::strerror(errno) << std::endl;
        return -1;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open())
    {
        std::cerr << "Cannot open output file: " << outputFile << " - " << std::strerror(errno) << std::endl;
        return -1;
    }

    MidiFile mf;
    if (!mf.readFromFile(inFile))
    { // Assuming readFromFile is correctly implemented
        std::cerr << "Failed to read MIDI data from input file." << std::endl;
        return -1;
    }

    if (!mf.writeToFile(outFile))
    { // Assuming writeToFile is correctly implemented
        std::cerr << "Failed to write MIDI data to output file." << std::endl;
        return -1;
    }

    return 0;
}
