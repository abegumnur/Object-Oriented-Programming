#include "../include/MovieEntry.h"
#include "../include/CatalogException.h"


MovieEntry::MovieEntry() : CatalogEntry(), director(""), genre(""), starring("")
{}

/// @brief constructs an onject with the given vector of strings
/// @param movvec vector of string var
MovieEntry::MovieEntry(std::vector<std::string> &movvec) 
{
    if((int)movvec.size() !=  getFieldCount())
        throw CatalogException("missing field");//, movvec);

    setTitle(movvec.at(0));
    director = movvec.at(1);
    setYear(movvec.at(2));
    genre = movvec.at(3);
    starring = movvec.at(4);

}

MovieEntry::MovieEntry(std::string theTitle, std::string theDirector, std::string theYear, std::string theGenre, std::string theStarring)
    : CatalogEntry(theTitle, theYear), director(theDirector), genre(theGenre), starring(theStarring)

{}

std::ostream &operator<<(std::ostream &out, MovieEntry &entry)
{
    out << "\"" << entry.getTitle() << "\" \"" << entry.getDirector();
    out << "\" \""  << entry.getYear() << "\" \""<< entry.getGenre();
    out << "\" \"" << entry.getStarring() << "\"\n";

    return out;

}

/// @brief virtual function that searches for the given string in a field
/// @return if the string is found true, false otherwise
/// Also the field string is not valid for this class,
/// throws an exception
bool MovieEntry::searchField(const std::string &searchString, const std::string &field) const
{
    if(field == "title" || field == "year")
        return CatalogEntry::searchField(searchString, field);
    else if(field == "director")
        return (director.find(searchString) != std::string::npos);
    else if(field == "genre")
        return (genre.find(searchString) != std::string::npos);
    else if(field == "starring")
        return (starring.find(searchString) != std::string::npos);      
    else        
        throw CatalogException("command is wrong");   
}

void MovieEntry::printEntry(std::ostream &out) const
{
    out << "\"" << getTitle() << "\" \"" << getDirector();
    out << "\" \""  << getYear() << "\" \""<< getGenre();
    out << "\" \"" << getStarring() << "\"\n";

}

/// @brief virtual function for comparing two objects according
/// to the given field variable
/// @return true if the caller object is less than the other one
/// according to the field type, if field is not valid throw exception
bool MovieEntry::compareByField(CatalogEntry *cat2, std::string field)
{
    MovieEntry* mov = dynamic_cast<MovieEntry*>(cat2);

    if(!mov){
        throw std::bad_cast();
    }

    if(field == "title" || field == "year")
        return CatalogEntry::compareByField(cat2, field);
    else if(field == "director")
        return this->director < mov->director;
    else if(field == "genre")
        return this->genre < mov->genre;
    else if(field == "starring")
        return this->starring < mov->starring;
    else
        throw CatalogException("command is wrong");

}