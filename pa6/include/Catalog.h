#ifndef __CATALOG_H
#define __CATALOG_H
#include "../include/CatalogException.h"
#include <vector>
#include <iostream>

/// @brief Catalog class can contain a vector of a templated parameter T 
/// @tparam T variable is to be of type CatalogEntry and its child classes
template<class T>
class Catalog{

    public:
    Catalog(){}
    ~Catalog(){}
    /// @brief adds an element to the vector of entries
    /// if the entry already exists in the vector throws
    /// an exception 
    /// @param entry is the entity to add
    void addEntry(const T& entry){
        for(auto i = entries.begin(); i != entries.end(); i++){
            if(*i == entry){
                throw CatalogException("duplicate entry");
            }
        }

        entries.push_back(entry);
    }

    T operator[](int index) const{
        return entries.at(index);
    }

    T& operator[](int index){
        return entries.at(index);
    }

    std::vector<T>& getEntries(){
        return entries;
    }
    /// @brief get the size of the vector of entries
    /// @return size variable
    int getSize() const {
        return entries.size();
    }

    template<class U>
    friend std::ostream & operator<<(std::ostream & out, Catalog<U>& cat);

    private:
        std::vector<T> entries;

};

template<class U>
std::ostream &operator<<(std::ostream &out, Catalog<U> &cat)
{
    for(auto entry : cat.entries)
        out << entry;
    
    return out;

}

#endif
