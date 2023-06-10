#include <fstream>
#include <sstream>
#include <vector>
using std::ifstream;
using std::ofstream;
using std::getline;
using std::string;
using std::vector;
#include <algorithm>

#include "../include/pa6.h"
#include "../include/BookEntry.h"
#include "../include/MovieEntry.h"
#include "../include/MusicEntry.h"
#include "../include/CatalogException.h"
#include "../include/Catalog.h"

bool search_command_printed = false;
bool sort_command_printed = false;


/// @brief parses the read line from command.txt into acceptable strings
/// @param field data member type of the catalogentry classes or its subclasses
/// @param searchFor if the command is search, this string is used for getting the
/// variable for searching on the field
void parseCommand(string line, string& command, string& field, string& searchFor){

    std::stringstream ss(line);
    std::vector<string> tempv;
    /// first string defined the command
    ss >> command;

    /// sort "field"
    if(command == "sort"){

    /// second strig is the field type with quoted strings
    parseQuoted(ss.str(), tempv);

    /// if the parsed field type contains more than one word, 
    /// indicates a wrong command, throw exception
    if(tempv.size() != 1)
        throw CatalogException("command is wrong");

    field = tempv[0];
    }
    /// search "particular string" in "field"
    else if(command == "search"){

        parseQuoted(line, tempv);

        /// if the parsed vector of strings contains
        /// more than 2 variables, throw wrong command exception
        if(tempv.size() != 2){
            throw CatalogException("command is wrong");
        }

        searchFor = tempv[0];
        field = tempv[1];
    }
    else
        throw CatalogException("command is wrong");

}


/// @brief Wrapper function for the polymorphic call of the CatalogEntry pointer
/// @param out output stream to print the catalog variable if the searched string
/// exists in that particular field
/// @param catalog a catalogentry pointer that is used for late binding
/// @param field hopefully a data member of the catalogentry class or its subclasses
/// @param searchFor string to search 
/// @param command the whole command is also taken as an argument for easily
/// printing it on the ouput stream in the case of an exception
void SearchField(ofstream& out,Catalog<CatalogEntry*>& catalog, const string field, const string searchFor, const string command){

    try
    {
        for(int i = 0; i < catalog.getSize(); i++){
            if(catalog[i]->searchField(searchFor, field)){
                if(!search_command_printed){
                    out << command << "\n";
                    search_command_printed = true;
                }        
                            
                catalog[i]->printEntry(out);
            }
        }
        if(!search_command_printed){
            out << command << "\n";
            search_command_printed = true;            
        }

 
    }
    catch(const CatalogException& e)    
    {
        if(!search_command_printed)
            search_command_printed = true;

        out << "Exception: "<<e.what() << "\n";
        out << command << "\n";


    }

}


/// @brief Custom comparator function for std::sort
/// @param field specific field type for the objects
/// @return true if the first object is less than the second
/// according to the field type, if the field type is invalid
/// for the particular class an exception is thrown by the
/// virtual function compareByField which will be catched 
/// and rethrown here for later processing
bool compareCatalogEntries(CatalogEntry* cat1, CatalogEntry* cat2, const std::string& field) {
    
    try
    {   
        /// polymorphic call for the catalogentry class and its subclasses
        return cat1->compareByField(cat2, field);
    }
    catch(const CatalogException& e)
    {
        /// rethrow the catched exception for later processing
        throw;
    }
    
}


/// @brief wrapper function for sorting the catalog entries 
/// in ascending ordder according to the given field type
/// @param out output stream is needed for writing possible 
/// exceptions and printing the entries after sorting
/// @param cats catalog variable that contains vector of pointers
/// to catalogentry, used for polymorphism
/// @param field specific field to sort entries accordingly (title, starring etc...)
/// @param command the whole command line is given as a parameter 
/// to make printing the cause of exception easier
void sortField(ofstream& out, Catalog<CatalogEntry*>& cats, const string field, const string command){

    try
    {
        /// sort the catalog entries using late binding by
        /// calling compareCatalogEntries
        std::sort(cats.getEntries().begin(), cats.getEntries().end(),
        [&](CatalogEntry* cat1, CatalogEntry* cat2)
        {   
            try
            {
                return compareCatalogEntries(cat1, cat2, field);
            }
            /// this try-catch block is needed because
            /// the compareCatalogEntries function rethrows any
            /// exception it encounters
            catch(const CatalogException& e)
            {
                //  throw the exception to the outer catch block
                throw;
            }   

          });

        if(!sort_command_printed){
            out << command <<"\n";
            sort_command_printed = true;
        }
        //  print the sorted entries one by one
        for(int i = 0; i < cats.getSize(); i++)
            cats[i]->printEntry(out);
        
    }
    catch(const CatalogException& e)
    {
        if(!sort_command_printed)
            sort_command_printed = true;
        out << "Exception: "<<e.what() << '\n';
        out << command << "\n";
    }
    
}

/// @brief reads the commands from the input string
/// line by line and executes them on the constructed catalog object
/// and prints them to ouput stream along with exceptions
/// parseCommand and SearchField functions can throw exception
/// for this reason a try-catch block is crucial
/// @param in input stream for reading the commands
/// @param cat catalog object that stores the (book/movie/music) entries
/// @param out output stream for writing the result of the commands
void ExecuteCommands(ifstream& in, Catalog<CatalogEntry*>& cat, ofstream& out){

    string line, field, command, searchFor;

    while(getline(in, line))
    {
        try
        {
            parseCommand(line, command, field, searchFor);
            
            if(command == "search"){
                search_command_printed = false;
                SearchField(out, cat, field, searchFor, line);
            }
            else if(command == "sort"){
                sort_command_printed = false;
                sortField(out, cat, field, line);
            }
            
        }
        catch(const CatalogException& e)
        {
            out << "Exception: "<<e.what() << '\n';
            out << line << "\n";
        }
        catch(...)  // any other type of exception occured
        {           // indicating an error with the command
            out << "Exception: command is wrong\n";
            out << line << "\n";
        }
            
    }

}

/// @brief assigns the catalog variable entries to its parent class pointer
/// @tparam T subclass ex : BookEntry
/// @tparam U parent class used for late binding. In this case its CatalogEntry*
template<typename T, typename U>
void assignCatalog(Catalog<U>& catalogVector, Catalog<T>& catalog){
    U catptr;

    for(int i = 0; i < catalog.getSize(); i++){
        catptr = &catalog[i];
        catalogVector.addEntry(catptr);
    }

}


/// @brief template function for reading and executing the data
/// @tparam T indicates the type of the mode to run ex: BookEntry
/// @tparam U CatalogEntr* is used for late binding with its subclasses
/// @param data file to read the entries from
/// @param command file to read the commands from
/// @param out output file for writing the results of operation
template<typename T, typename U = CatalogEntry*>
void organizerMode(ifstream& data, ifstream& command, ofstream& out)
{
    Catalog<T> catalog;
    ReadFile<T>(data, catalog, out);

    Catalog<U> catvec;
    assignCatalog<T,U>(catvec, catalog);
    
    ExecuteCommands(command, catvec, out);
}


int main(){

    /// open the files needed
    ifstream dataFile("data.txt");
    ifstream commandFile("command.txt");
    ofstream outputFile("output.txt");
    
    /// first line specifies the type of
    /// catalog entry (book, music or movie)
    string catalogType;
    getline(dataFile, catalogType);

    //  run in the organizer mode based on the given type
    if(catalogType == "book"){
        outputFile << "Catalog Read: book\n";
        organizerMode<BookEntry>(dataFile, commandFile, outputFile);
    }
    else if(catalogType == "movie"){
        outputFile << "Catalog Read: movie\n";
        organizerMode<MovieEntry>(dataFile, commandFile, outputFile); 
    }
    else if(catalogType == "music"){
        outputFile << "Catalog Read: music\n";
        organizerMode<MusicEntry>(dataFile, commandFile, outputFile);
    }
    else{
        outputFile << "Exception: Invalid catalog type." << "\n";
        outputFile << "Valid types are \"music\", \"movie\" and \"book\".";
    }

    /// close the files after the operation
    dataFile.close();
    commandFile.close();
    outputFile.close();

}
