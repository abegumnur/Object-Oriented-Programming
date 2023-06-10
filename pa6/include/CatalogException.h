#ifndef __CATALOGEXCEPTION_H
#define __CATALOGEXCEPTION_H
#include <exception>
#include <string>
#include <vector>
#include <iostream>


/// @brief This class is a special excepion class
/// to be used with the CatalogEntry and its child classes
class CatalogException : public std::exception{

    public:
        CatalogException(std::string errormessage)
            :   message(errormessage)   
        {}
        const char* what() const noexcept override{
            return message.c_str();
        }
    private:
        std::string message;
};


#endif