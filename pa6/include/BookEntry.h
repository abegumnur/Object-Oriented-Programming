#ifndef __BOOKENTRY_H
#define __BOOKENTRY_H
#include "CatalogEntry.h"

const int BOOKFIELDNUM = 4;

class BookEntry : public CatalogEntry{

    public:
        BookEntry();
        BookEntry(std::vector<std::string>& bookvec);
        BookEntry(std::string theTitle, std::string theAuthors,
                std::string year, std::string theTags);
        inline void setAuthors(const std::string theAuthors)    {authors = theAuthors;  }
        inline void setTags(const std::string theTags) {    tags = theTags; }
        inline std::string getAuthors() const { return authors; }
        inline std::string getTags() const {    return tags;    }
        inline int getFieldCount() const { return BOOKFIELDNUM; }
        bool compareByField(CatalogEntry* cat2, std::string field) override;
        bool searchField(const std::string &searchString, const std::string &field) const override;
        void printEntry(std::ostream& out)  const override;     

        friend std::ostream & operator<<(std::ostream & out, BookEntry& entry);

    private:
        std::string authors;
        std::string tags;

};

#endif