#ifndef SCHOOLMANAGERSYSTEM_H
#define SCHOOLMANAGERSYSTEM_H

#include<string>
using std::string;

namespace PA4
{   
    /* enum class for the menu choices  */
    enum class MenuF : short { exit, student, course, list_all_std, list_all_crs };
    class Student;  /* forward declaration of Student and Course classes    */
    class Course;

    class SchoolManagementSystem
    {
        public:
            SchoolManagementSystem();
            ~SchoolManagementSystem();
            /*  menu related functions  */
            void mainMenu();
            void subStudentMenu();
            void subCourseMenu();
            void subSelectStudentMenu();
            void subSelectCourseMenu();
            /*  selects the student/course  */
            void selectStudent(string& name, string& id);
            void selectCourse(string& name, string& code);
            /* lists all the students/courses present   */
            void listAllStudents();
            void listAllCourses();
            /* add a student/course to the system   */
            bool addStudenttoSystem(string& name, string& id);
            bool addCoursetoSystem(string& name, string& code);
            /* get the student/course information from stdin   */
            void getCourseInfo(string& name, string& code);
            void getStudentInfo(string& name, string& id);
            /* delete the selected student/course   */
            void deleteSelectedStudent();
            void deleteSelectedCourse();
            /* add the selected student to a course */
            void addSelectedToACourse();
            /* delete the selected student from a course    */
            void dropSelectedFromACourse();
            /* lists all the students enrolled to the selected course   */
            void listStudentsOfSelectedCourse();
            /* find the given course and return its index value */
            int findCourse(string code);
        private:
            Student * allStudents;  /* all the students in the system   */
            Course * allCourses;    /* all the courses in the system    */
            Student * selectedStudent;  /* selected student */
            Course * selectedCourse;    /* selected couurse */
            int studentNum;         /* number of students in the system */
            int courseNum;          /* number of courses in the system  */

    };

}

#endif