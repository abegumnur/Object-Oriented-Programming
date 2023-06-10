#ifndef __MUSICENTRY_H
#define __MUSICENTRY_H
#include "CatalogEntry.h"

const int MUSICFIELDNUM = 4;

class MusicEntry : public CatalogEntry{

    public:
        MusicEntry();
        MusicEntry(std::vector<std::string>& musvec);
        MusicEntry(std::string theTitle, std::string theArtists, std::string theYear, std::string theGenre);
        inline void setArtists(const std::string theArtists)    {artists = theArtists;  }
        inline void setGenre(const std::string theGenre) {    genre = theGenre; }
        inline std::string getArtists() const { return artists; }
        inline std::string getGenre() const {    return genre;    }
        inline int getFieldCount() const {  return MUSICFIELDNUM;   }
        bool compareByField(CatalogEntry* cat2, std::string field) override;
        bool searchField(const std::string &searchString, const std::string &field) const override;
        void printEntry(std::ostream& out) const override;

        friend std::ostream & operator<<(std::ostream & out, MusicEntry& entry);
    private:
        std::string artists;
        std::string genre;
};

#endif