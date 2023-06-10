#ifndef __CATALOGENTRY_H
#define __CATALOGENTRY_H
#include <vector>
#include <string>
#include <iostream>

/// @brief Base class for the other Entry classes 
class CatalogEntry{

    public:
        CatalogEntry();
        //CatalogEntry(std::vector<std::string> catvec);  
        CatalogEntry(std::string theTitle, std::string theYear);    
        inline std::string getTitle() const  {  return title;   }
        inline void setTitle(const std::string theTitle)    {   title = theTitle;   }
        inline std::string getYear() const {   return year;    }
        inline void setYear(const std::string theYear) {   year = theYear; }
        bool operator==(const CatalogEntry& other);
        inline virtual int getFieldCount() const { return 2; }
        virtual bool searchField(const std::string& searchString, const std::string& field) const;
        virtual void printEntry(std::ostream& out) const;
        virtual bool compareByField(CatalogEntry* cat2, std::string field);

        friend std::ostream& operator<<(std::ostream& out, CatalogEntry& cat);

    private:
        std::string title;
        std::string year;

};

#endif