#ifndef STUDENT_H
#define STUDENT_H

#include<string>

namespace PA4{

    class Course; // forward declaration
    
    class Student
    {
        public:
            Student();
            Student(std::string newName, std::string newID);
            Student(std::string newName, std::string newID, Course * newCourses);
            Student(const Student & rhs);
            Student & operator = (const Student & rhs);
            bool removeCourse(Course& crs); /* drop a course    */
            bool addCourse(Course& crs);    /* add the student to a course  */
            ~Student();
            // getters-setters
            std::string getName() { return name; }
            std::string getID() { return ID; }
            Course * getCourses() { return courses; }
            int getNumCourses() { return numCourses; }
            void setName(std::string theName) { name = theName; }
            void setID(std::string theId) { ID = theId; }
            void setNumCourses(int theNumCourses) { numCourses = theNumCourses; }
            bool isInCourse(Course crs);
        private:
            std::string name;    /* name of the student  */
            std::string ID;      /* id of the student    */
            Course * courses;   /* courses taken by the student */
            int numCourses = 0; /* number of courses taken  */

            friend std::ostream& operator<<(std::ostream& out, Student & std);
            /* friends of Student and Course classes*/
            friend bool addStudenttoaCourse(Student& std, Course& crs);
            friend bool dropStudentfromaCourse(Student& std, Course& crs);

    };

        std::ostream& operator<<(std::ostream& out, Student & std);

}


#endif