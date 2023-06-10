#ifndef COURSE_H
#define COURSE_H

#include<string>

namespace PA4
{   
    class Student; /* forward declaration   */

    class Course
    {
        public:
            Course();
            Course(std::string newName, std::string newCode);
            Course(std::string newName, std::string newCode, Student * studentList);
            Course(const Course &other);
            Course & operator=(const Course & rhs); 
            ~Course();
            /* add and remove students*/
            bool addStudent(Student& student);
            bool removeStudent(Student& student);
            void printStudents(); /* prints the student enrolled    */
            /* getter-setters   */
            std::string getCourseName() { return course_name; }
            std::string getCourseCode() { return course_code; }
            int getNumStudents() { return numStudents; }
            Student * getStudents() { return students; }
            void setName(std::string crsName) { course_name = crsName; }
            void setCode(std::string crsCode) { course_code = crsCode; }
            void setNumStudents(int theNumb) { numStudents = theNumb; }
            bool isStudentIn(Student std); /* checks if the given student enrolled    */

        private:
            std::string course_name; /* name of the course   */
            std::string course_code; /* code of the course   */
            Student * students; /* dynamic array to hold the students enrolled  */
            int numStudents = 0; /* number of students enrolled */

            friend std::ostream & operator<<(std::ostream & out, Course & crs);
            /* friends to both classes*/
            friend bool addStudenttoaCourse(Student& std, Course& crs);
            friend bool dropStudentfromaCourse(Student& std, Course& crs);

    };

        std::ostream & operator<<(std::ostream & out, Course & crs);
        bool addStudenttoaCourse(Student& std, Course& crs);
        bool dropStudentfromaCourse(Student& std, Course& crs);

}


#endif
