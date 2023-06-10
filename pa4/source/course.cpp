#include "course.h"
#include "student.h" 
#include <iostream>
using namespace std;

PA4::Course::Course() : course_name("uninitialized"), course_code("uninitialized"), students(nullptr)
{
}

PA4::Course::Course(string newName, string newCode) : course_name(newName), course_code(newCode), students(nullptr)
{
}

PA4::Course::Course(string newName, string newCode, Student *studentList) : course_name(newName), course_code(newCode)
{
    students = studentList;
}
/* copy constructor */
PA4::Course::Course(const Course &other)
{
    students = new Student[other.numStudents];

    numStudents = other.numStudents;
    /* makes a deep copy of the student array   */
    for (int i = 0; i < numStudents; i++)
        students[i] = other.students[i];

    course_name = other.course_name;
    course_code = other.course_code;
}

PA4::Course &PA4::Course::operator=(const Course &rhs)
{
    /* if rhs and lhs has the same number of students*/
    if (numStudents != rhs.numStudents)
    {
        delete[] students;
        students = new Student[rhs.numStudents];
    }

    numStudents = rhs.numStudents;
    /* copy all the students    */
    for (int i = 0; i < numStudents; i++)
        students[i] = rhs.students[i];

    course_name = rhs.course_name;
    course_code = rhs.course_code;

    return *this;
}

PA4::Course::~Course()
{
    delete[] students;
}

/* add a given student to the course    */
bool PA4::Course::addStudent(Student &student)
{
    int oldnum = numStudents;
    /* new Student array has 1 more elements  */
    Student *temp = new Student[++numStudents];
    /* copy the old elements    */
    for (int i = 0; i < oldnum; i++)
        temp[i] = students[i];
    /* assign the new Student element to the end    */
    temp[oldnum] = student;

    if (oldnum) /* if old number of students were not 0*/
        delete[] students;

    students = temp;

    return true;
}
/* remove the given student from the course */
bool PA4::Course::removeStudent(Student &student)
{
    int oldnum = numStudents;
    Student *temp;
    /* if the old number of students were 1*/
    if (oldnum == 1)
    {
        temp = nullptr;
        numStudents = 0;
    }
    else
    { /*if the old number of students were greater than 1*/
        /* allocate space for the new array */
        temp = new Student[numStudents - 1];
        numStudents--;
        /*  copy the old array elements  */
        /*  except the one to be removed    */
        for (int i = 0, k = 0; i < oldnum; i++)
        {
            if (students[i].getName() == student.getName() &&
                students[i].getID() == student.getID())
                continue;

            temp[k++] = students[i];
        }
    }
    /* delete the old Student array */
    if (students != nullptr)
        delete[] students;
    /* assign the new array */
    students = temp;

    return true;
}

void PA4::Course::printStudents()
{

    cout << "For the course" << course_name
         << " with the ID " << course_code << std::endl;

    for (int i = 0; i < numStudents; i++)
        cout << "\t" << students[i].getName() << std::endl;
}

/// @brief check if the given student is enrolled to the course 
/// @param std is the Student to check
/// @return true if student is enrolled, false otherwise
bool PA4::Course::isStudentIn(Student std)
{
    for (int i = 0; i < numStudents; i++)
    {
        if (students[i].getID() == std.getID())
            return true;
    }
    return false;
}

ostream &PA4::operator<<(ostream &out, Course &crs)
{
    out << "For the course " << crs.course_name
        << " with the ID " << crs.course_code << " student list is as given " << endl;

    for (int i = 0; i < crs.numStudents; i++)
    {
        out << crs.students[i].getName() << " ";
        out << crs.students[i].getID() << endl;
    }

    return out;
}

bool PA4::addStudenttoaCourse(Student &std, Course &crs)
{
    //  if(!(std.isInCourse(crs) && crs.isStudentIn(std))){
    std.addCourse(crs);
    crs.addStudent(std);

    return true;

    // }
    //  return false;
}

bool PA4::dropStudentfromaCourse(Student &std, Course &crs)
{
    // if( !(std.isInCourse(crs)) )
    std.removeCourse(crs);
    crs.removeStudent(std);

    return true;
}
