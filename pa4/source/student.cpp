#include "student.h"
#include "course.h"
#include<iostream>
using namespace std;

PA4::Student::Student() : name("no name yet"), ID("0"), courses(nullptr)
{}

PA4::Student::Student(std::string newName, std::string newID) : name(newName), ID(newID), courses(nullptr)
{}

PA4::Student::Student(string newName, string newID, Course *newCourses) :name(newName), ID(newID)
{
    courses = newCourses;
}

/* copy costructor  */
PA4::Student::Student(const Student &rhs)
{
    numCourses = rhs.numCourses;
    name = rhs.name;
    ID  = rhs.ID;

    courses = new Course[rhs.numCourses];

    for(int i = 0; i < numCourses; i++)
        courses[i] = rhs.courses[i];
    
}

/* assignment operator  */
PA4::Student &PA4::Student::operator=(const Student &rhs)
{
    if(numCourses != rhs.numCourses)
    {
        numCourses = rhs.numCourses;
        delete [] courses;
        courses = new Course[numCourses];
    }

    for(int i = 0; i < numCourses; i++)
        courses[i] = rhs.courses[i];

    ID = rhs.ID;
    name = rhs.name;

    return *this;

}

bool PA4::Student::removeCourse(Course& crs)
{
    int oldnum = numCourses;
    Course * temp;
    /* number of courses were 1*/
    if(oldnum == 1){
        /* set temp to nullptr*/
        temp = nullptr;
        numCourses = 0;
    }   else{   
        /* number of courses were greater than 1*/
        temp = new Course[--numCourses];

        /* copy all the courses except the one to drop  */
        for(int i = 0, k = 0; i < oldnum; i++)
        {
            if(courses[i].getCourseName() == crs.getCourseName()
            && courses[i].getCourseCode() == crs.getCourseCode())
                continue;

            temp[k++] = courses[i];
        }
    }
    /* delete old courses array */
    if(courses != nullptr)
        delete [] courses;
    /* assign the new array */
    courses = temp;

    return true;
}

bool PA4::Student::addCourse(Course& crs)
{
    int oldnum = numCourses;
    /* allocate space for the new Course array  */
    Course * temp = new Course[++numCourses];
    /*  copy the old contents of the array  */
    for(int i = 0; i < oldnum; i++)
        temp[i] = courses[i];
    /* assign the given course to the end of the array  */
    temp[oldnum] = crs;

    /* if old number of courses were not 0 */
    /* delete the old Course array  */
    if(oldnum)
        delete [] courses;
        
    courses = temp;

    return true;

}

PA4::Student::~Student()
{
    delete [] courses;
}
/* check if the student is enrolled in the given course */
bool PA4::Student::isInCourse(Course crs)
{
    /* loop through the course array for the student    */
    for(int i = 0; i < numCourses; i++){
        /* if the course is on the array    */
        if(courses[i].getCourseName() == crs.getCourseName() 
           && courses[i].getCourseCode() == crs.getCourseCode())
            return true;
    }

    return false;
}

ostream &PA4::operator<<(ostream &out, Student &std)
{
    out <<"For the student "<<std.name
    <<" with the ID "<<std.ID <<" course list is as given: "<< endl;

    for(int i = 0; i < std.numCourses; i++){
        out << std.courses[i].getCourseName() << " " ; 
        out << std.courses[i].getCourseCode() << endl;
    }

    return out;

}




