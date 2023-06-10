#ifndef __PA6_H
#define __PA6_H
#include "Catalog.h"

#include <exception>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;

/// @brief basically trims the preceding and leading spaces
/// from the given string
/// @param str string var for trimming
/// @return trimmed string 
std::string trim(const std::string& str) {
    std::size_t first = str.find_first_not_of(" \t\n\r");
    std::size_t last = str.find_last_not_of(" \t\n\r");

    if (first == std::string::npos || last == std::string::npos)
        return "";

    return str.substr(first, last - first + 1);
}


/// @brief check if the given string contains only white spaces
/// @param str string to do the checking
/// @return true is so, false otherwise
bool containsOnlyWhitespaces(const std::string& str) {
    for (char c : str) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

/// @brief parses a given string into multiple strings 
/// according to quotes, and stores the trimmed strings
/// in the vec vector
void parseLine(const std::string& line, std::vector<std::string>& vec) {
    std::istringstream iss(line);
    std::string word;
    int i = 0; 

    while (std::getline(iss, word, '\"')) {
        if ( word == " ")
            continue;

        if(word.empty() && i != 0){ vec.push_back(word); continue;}
        word = trim(word);
        if(containsOnlyWhitespaces(word))
            continue;
        vec.push_back(word);
        i++;
        
    }
}

/// @brief parses a string with quotes and stores them in 
/// a vector of strings
void parseQuoted(std::string line, std::vector<std::string>& vec){

    std::regex regex("\"([^\"]*)\"");
    std::smatch match;

    try
    {
        // Find and push all quoted strings into the vector
        while (std::regex_search(line, match, regex)) {

            std::string quotedString = match[1].str();
            /// trim the leading and preceding whitespaces
            if(quotedString.empty()){
                throw std::runtime_error("Empty quoted string found.");
            }

            quotedString = trim(quotedString);

            vec.push_back(quotedString);
            line = match.suffix();
        }        
    }
    catch(const std::exception& e)
    {
        throw; //rethrow the ezxception
    }
    
}

/// @brief templated function for reading catalog entries from
/// a given stream, storing those entries based on a few conditons
/// and printing them to the given output stream
/// @tparam T CatalogEntry and its subclasses
/// @param inFile input stream to read the entries
/// @param cat Catalog object for storing the entries
/// @param outFile output stream to write the entries
template<typename T>
void ReadFile(ifstream &inFile, Catalog<T>& cat, ofstream& outFile){

    string line;
    std::vector<string> vec;

    setbuf(stdout, NULL);

    while(getline(inFile, line)){
        vec.clear();
        /// parse the line according to the conditions
        /// for quoted strings
        parseLine(line, vec);
        
        try
        {
            /// if the construction fails a CatalogException
            /// will be thrown
            /// constructor checks for missing field exception
            T entry(vec);

            /// add the constructed object into the Catalog 
            /// checks for the duplicate entry exception
            /// if two of the entries shares the same first field values
            cat.addEntry(entry);
            
            //cout << entry;

        }
            /// catch and print the exception into output stream 
            /// also print the line that cause exception
        catch(const CatalogException& e)
        {
            outFile <<"Exception: "<< e.what() << '\n';
            outFile << line << "\n";
        }

    }
    
    /// print the number of unique entries
    outFile << cat.getEntries().size() << " unique entries\n";
        
}






#endif

