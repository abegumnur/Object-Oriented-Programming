#include "../include/BookEntry.h"
#include "../include/CatalogException.h"
#include <iostream>

BookEntry::BookEntry() : CatalogEntry(), authors(""), tags("")
{}

/// @brief constructs an object from the given vector of strings
/// @param bookvec vector of strings
BookEntry::BookEntry(std::vector<std::string> &bookvec) 
{
    /// if the vector size is not equal to the number
    /// of fields bookentry class contains
    /// throws an exception
    if((int)bookvec.size() != this->getFieldCount()){
        throw CatalogException("missing field");//, bookvec);
    }

    this->setTitle(bookvec.at(0));
    authors = bookvec.at(1);
    this->setYear(bookvec.at(2));
    tags = bookvec.at(3);
}

BookEntry::BookEntry(std::string theTitle, std::string theAuthors, std::string theYear, std::string theTags)
          : CatalogEntry(theTitle, theYear), authors(theAuthors), tags(theTags)  
{}

std::ostream &operator<<(std::ostream &out, BookEntry &entry)
{
    out << "\"" << entry.getTitle()<< "\" \"" << entry.getAuthors();
    out << "\" \""  << entry.getYear()<< "\" \""<< entry.getTags();
    out << "\"\n";

    return out;

}


/// @brief virtual function that searches for the given string in a specific field var
/// @param searchString 
/// @param field 
/// @return return if found, false otherwise
bool BookEntry::searchField(const std::string &searchString, const std::string &field) const
{
    if(field == "year" || field == "title")
        return CatalogEntry::searchField(searchString, field);
    else if(field == "authors")
        return (authors.find(searchString) != std::string::npos);
    else if(field == "tags")
        return (tags.find(searchString) != std::string::npos);
    else
        throw CatalogException("command is wrong");

}

void BookEntry::printEntry(std::ostream &out) const
{
    out << "\" " << getTitle()<< "\" \"" << getAuthors();
    out << "\"\" "  << getYear()<< "\" \" "<< getTags();
    out << "\"\n";


}

/// @brief virtual function that compares two BookEntry objects using 
/// CatalogEntry pointers
/// @param cat2 second object for comparison
/// @param field one of the data members, if not an exception is thrown
/// @return true if the calling object's field value is less than the other one
bool BookEntry::compareByField(CatalogEntry* cat2, std::string field){
    BookEntry* book = dynamic_cast<BookEntry*>(cat2);

    if(!cat2)   
        throw std::bad_cast();

    if(field == "title" || field == "year")
        return CatalogEntry::compareByField(cat2, field);
    else if(field == "authors")
        return  this->authors < book->authors;
    else if(field == "tags")
        return this->tags < book->tags;
    else
        throw CatalogException("command is wrong");
}