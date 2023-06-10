#ifndef __MOVIEENTRY_H
#define __MOVIEENTRY_H

#include "CatalogEntry.h"

const int MOVIEFIELDNUM = 5;


class MovieEntry : public CatalogEntry{ 
    public:
        MovieEntry();
        MovieEntry(std::vector<std::string>& movvec);
        MovieEntry(std::string theTitle, std::string theDirector, std::string theYear,  
                    std::string theGenre, std::string theStarring);
        inline void setDirector(const std::string theDirector)  {   director = theDirector; }
        inline void setGenre(const std::string theGenre)    {   genre = theGenre;   }
        inline void setStarring(const std::string theStarring)  {   starring = theStarring; }
        inline std::string getDirector() const  {   return director;    }
        inline std::string getGenre() const {   return genre;   }
        inline std::string getStarring() const {    return starring;   }
        inline int getFieldCount() const {  return MOVIEFIELDNUM;   }
        bool compareByField(CatalogEntry* cat2, std::string field) override;
        bool searchField(const std::string &searchString, const std::string &field) const override;
        void printEntry(std::ostream& out) const override;

        friend std::ostream & operator<<(std::ostream & out, MovieEntry& entry);
    private:
        std::string director;
        std::string genre;
        std::string starring;

};





#endif