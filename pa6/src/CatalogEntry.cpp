#include "../include/CatalogEntry.h"

CatalogEntry::CatalogEntry() : title(""), year("")
{}

CatalogEntry::CatalogEntry(std::string theTitle, std::string theYear) : title(theTitle), year(theYear)
{}

bool CatalogEntry::operator==(const CatalogEntry &other)
{
    return this->title == other.title;
}


/// @brief search for the given string in a specific data member
/// @param searchString string to search for
/// @param field data member of the CatalogEntry class (title/year)
/// @return true if found, false otherwise
bool CatalogEntry::searchField(const std::string &searchString, const std::string &field) const
{
    if(field == "title")
        return (title.find(searchString) != std::string::npos);
    else if(field == "year")
        return (year.find(searchString) != std::string::npos);
    else
        return false;
}

void CatalogEntry::printEntry(std::ostream &out) const
{
    out << "\"" << title << "\" \"";
    out << year << "\"\n";
}


/// @brief compare two objects by the given field information
/// throws CatalogException if the field is an invalid string
/// @param cat2 second object to be compared
/// @param field one of the member datas of the class (title/year)
/// @return true if the calling object is less than the other one
bool CatalogEntry::compareByField(CatalogEntry *cat2, std::string field)
{
    if(field == "title")
        return this->title < cat2->title;
    else if(field == "year")
        return this->year < cat2->year;
    else
        return false;
}


std::ostream& operator<<(std::ostream &out, CatalogEntry &cat)
{
    out << "\"" << cat.getTitle() << "\" \"";
    out << cat.getYear() << "\"\n";

    return out;
}

