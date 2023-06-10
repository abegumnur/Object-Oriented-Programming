#include "../include/MusicEntry.h"
#include "../include/CatalogException.h"

MusicEntry::MusicEntry() : CatalogEntry(), artists(""), genre("")
{}

/// @brief construct an object with the given vector of strings
/// @param musvec vector of strings,
/// if the vector size is insufficient throw exception
MusicEntry::MusicEntry(std::vector<std::string> &musvec) 
{
    if((int)musvec.size() != this->getFieldCount())
        throw CatalogException("missing field");//, musvec);

    this->setTitle(musvec.at(0));
    artists = musvec.at(1);
    this->setYear(musvec.at(2));
    genre = musvec.at(3);

}

MusicEntry::MusicEntry(std::string theTitle, std::string theArtists, std::string theYear, std::string theGenre)
    : CatalogEntry(theTitle, theYear), artists(theArtists), genre(theGenre)

{}

std::ostream &operator<<(std::ostream &out, MusicEntry &entry)
{
    out << "\"" << entry.getTitle() << "\" \"" << entry.getArtists();
    out << "\" \""  << entry.getYear() << "\" \""<< entry.getGenre();
    out << "\"\n";

    return out;

}

/// @brief virtual function for searching the given field for a specific string
/// @param searchString string to search for 
/// @param field data member of this class (artist, year etc..)
/// @return true is searchString is found, false otherwise
/// also if the field part is invalid, exception is thrown
bool MusicEntry::searchField(const std::string &searchString, const std::string &field) const
{
    if(field == "title" || field == "year")
        return CatalogEntry::searchField(searchString, field);
    else if(field == "artists")
        return (artists.find(searchString) != std::string::npos);
    else if(field == "genre")
        return (genre.find(searchString) != std::string::npos);
    else
        throw CatalogException("command is wrong");              

}

void MusicEntry::printEntry(std::ostream &out) const
{
    out << "\"" << getTitle() << "\" \"" << getArtists();
    out << "\" \""  << getYear() << "\" \""<< getGenre();
    out << "\"\n";

}

/// @brief virtual function to compare two classes deriven from
/// the CatalogEntry class according to the given field type
/// @param cat2  second object for comparison    
/// @param field title, year, genre etc..
/// @return true if the first object is less than the second one
/// based on the field type, false otherwise
/// also throws an exception if the field is invalid 
bool MusicEntry::compareByField(CatalogEntry *cat2, std::string field)
{
    MusicEntry* mus = dynamic_cast<MusicEntry*>(cat2);
    
    if(!mus){
        throw std::bad_cast();
    }

    if(field == "title" || field == "year")
        return CatalogEntry::compareByField(cat2, field);
    else if(field == "artists")
        return this->artists < mus->artists;
    else if(field == "genre")
        return this->genre < mus->genre;
    else
        throw CatalogException("command is wrong");
}
