#include "schoolmanagersystem.h"
#include "student.h"
#include "course.h"
#include<iostream>
#include<sstream>
using namespace std;

PA4::SchoolManagementSystem::SchoolManagementSystem() : studentNum(0), courseNum(0)
{
    selectedCourse = nullptr;
    selectedStudent = nullptr;
    allStudents = nullptr;
    allCourses = nullptr;
}

PA4::SchoolManagementSystem::~SchoolManagementSystem()
{
    delete [] allCourses;
    delete [] allStudents;
}

void PA4::SchoolManagementSystem::mainMenu()
{   
    int mainMenu;
    cout << "Main_Menu\n";
    do
    {
        cout << "0 exit\n";
        cout << "1 student\n";
        cout << "2 course \n";
        cout << "3 list_all_students\n";
        cout << "4 list_all_courses\n";

        cin >> mainMenu;
        cin.ignore(100,'\n');

        if(mainMenu == (int) MenuF::student)
            subStudentMenu();
        

        else if(mainMenu == (int) MenuF::course)
            subCourseMenu();
        
        else if(mainMenu == (int) MenuF::list_all_std)
            listAllStudents();
        

        else if(mainMenu == (int) MenuF::list_all_crs)
            listAllCourses();

    } while(mainMenu != (int)MenuF::exit);


}

void PA4::SchoolManagementSystem::subStudentMenu()
{
    int choice;
    string name, id;

    do{

        cout << "0 up\n";
        cout << "1 add_student\n";
        cout << "2 select_student\n";

        cin >> choice;
        cin.ignore(100, '\n');

        if(choice == 1)
        {   /*  the user enters student name and ID */ 
            /* A student object is created and added to system  */
            getStudentInfo(name, id);
            addStudenttoSystem(name, id); 
            continue;
        }

        else if(choice == 2){
            /* the user enters student name and ID*/
            /* student is selected  */
            getStudentInfo(name, id);
            selectStudent(name, id);
            subSelectStudentMenu();
        }

    } while(choice != 0);

}


void PA4::SchoolManagementSystem::getStudentInfo(string &name, string &id)
{

    string line;
    getline(std::cin, line);
    std::stringstream ss(line);
    string firstName, lastName;
    /* get the first-last name and id*/
    ss >> firstName >> lastName >> id;

    /* truncate the first and last name into one    */
    name = firstName + " " + lastName;
}

bool PA4::SchoolManagementSystem::addStudenttoSystem(string& name, string& id)
{
    Student newStudent(name, id);
    int oldNum = studentNum;

    Student * temp = new Student[++studentNum];
    /* copy all the old array elements  */
    for(int i = 0; i < oldNum; i++)
        temp[i] = allStudents[i];
    /* add the new Student element  */
    temp[oldNum] = newStudent;

    /* if old number of students were not 0*/
    if(oldNum)
        delete [] allStudents;
    
    allStudents = temp;
    return true;
}

bool PA4::SchoolManagementSystem::addCoursetoSystem(string &name, string &code)
{
    Course newCourse(name, code);
    int oldNum = courseNum;

    Course * temp = new Course[++courseNum];
    /* copy all the old array elements  */
    for(int i = 0; i < oldNum; i++)
        temp[i] = allCourses[i];
    /* add the new Course element   */
    temp[oldNum] = newCourse;

    if(oldNum)
        delete [] allCourses;
    
    allCourses = temp;
    return true;
}

void PA4::SchoolManagementSystem::subSelectStudentMenu()
{
    int choice;

    do{
        cout << "0 up\n";
        cout << "1 delete_student\n";
        cout << "3 add_selected_student_to_a_course\n";
        cout << "4 drop_selected_student_from_a_course\n";

        cin >> choice;
        cin.ignore(100, '\n');
        if(choice == 1){
            deleteSelectedStudent();
            return;
        }
        else if(choice == 3){
            addSelectedToACourse();
        }
        else if(choice == 4){
            dropSelectedFromACourse();
        }

    }while(choice != 0);

}

void PA4::SchoolManagementSystem::subSelectCourseMenu()
{    
    int choice;

    do{
        cout << "0 up\n";
        cout << "1 delete_course\n";
        cout << "2 list_students_registered_to_the_selected_course\n";

        cin >> choice;
        cin.ignore(100, '\n');

        if(choice == 1){
            deleteSelectedCourse();
            return;
        }
        else if(choice == 2){
            listStudentsOfSelectedCourse();
        }

    }while(choice != 0);
}
/* add the selected student to a course chosen by the user  */
void PA4::SchoolManagementSystem::addSelectedToACourse()
{
    int course_choice;
    int numTaken = selectedStudent->getNumCourses();
    /* number of courses the selected student is not enrolled in    */
    int size = courseNum - numTaken;
    /* allocate the memory for courses not taken    */
    Course * notTaken = new Course[size];

    for(int i = 0, k = 0; i < courseNum; i++){
        /* fill in the array    */
        if(!selectedStudent->isInCourse(allCourses[i]))
            notTaken[k++] = allCourses[i];
    }
    /* menu print*/
    cout << "0 up\n";   
    /* print the courses not taken by the student   */
    for(int i = 0; i < size; i++){
        cout << i + 1 << " " << notTaken[i].getCourseCode();
        cout << notTaken[i].getCourseName() << "\n";
    }

    /* ge the user input    */
    cin >> course_choice;
    if( course_choice == 0)
        return;

    /* get the index of the chosen course   */
    int index = findCourse(notTaken[course_choice - 1].getCourseCode());

    if(index == -1){
        throw std::invalid_argument("Invalid index value!");
        exit(EXIT_FAILURE);
    }
    /* add the student to the chosen course */
    addStudenttoaCourse(*selectedStudent, allCourses[index]); 
    
    delete [] notTaken;

}
/* drop the slected student from a course xchosen by the user   */
void PA4::SchoolManagementSystem::dropSelectedFromACourse()
{
    int course_choice;
    int takenNum = selectedStudent->getNumCourses();
    /* array that holds the courses the student is enrolled in  */
    Course * coursesTaken = new Course[takenNum];
    /* fill the array with the courses  */
    for(int i = 0, k = 0; i < courseNum; i++){
        if(selectedStudent->isInCourse(allCourses[i])){
            coursesTaken[k++] = allCourses[i];
        }

    }
    /* menu print*/
    cout << "0 up\n";
    /* print the courses taken by the selected student  */
    for(int i = 0; i < takenNum ; i++){
        cout << i + 1 << " " << coursesTaken[i].getCourseCode();
        cout << coursesTaken[i].getCourseName() << "\n";
    }

    cin >> course_choice;
    if(course_choice == 0)
        return;

    /* get the index of the course to drop   */
    int index = findCourse(coursesTaken[course_choice - 1].getCourseCode());
    /* if the course does not exists    */
    if(index == -1){
        throw std::invalid_argument("Invalid index value!");
        exit(EXIT_FAILURE);
    }
    /* drop the selected student from the course    */
    dropStudentfromaCourse(*selectedStudent, allCourses[index]);    
    /* delete the coursesTaken array to avoid memory leaks  */
    if(coursesTaken != nullptr)
        delete [] coursesTaken;

}

/// @brief finds the course by the given code 
/// @param code string code of the course
/// @return index value of the course in the allCourses array, -1 if invalid
int PA4::SchoolManagementSystem::findCourse(string code)
{
    for(int i = 0; i < courseNum; i++){
        if(code == allCourses[i].getCourseCode())
            return i;
    }

    return -1;
}


void PA4::SchoolManagementSystem::listStudentsOfSelectedCourse()
{
    if(selectedCourse == nullptr){
        throw std::invalid_argument("No course is selected!");
        exit(EXIT_FAILURE);
    }
    /* studentList will hold all the students enrolled in the selected course*/
    int courseSize = selectedCourse->getNumStudents();
    Student * studentList = new Student[courseSize];

    for(int i = 0, k = 0; i < studentNum; i++){
        /* assign all the students enrolled in the course   */
        if(allStudents[i].isInCourse(*selectedCourse)){
            studentList[k++] = allStudents[i];
        }
    }
    /* print the student one by one */
    for(int i = 0; i < courseSize; i++){
        cout << studentList[i].getName();
        cout << " " << studentList[i].getID() << std::endl;
    }
    /* delete the allocated array   */
    delete [] studentList;

}

/* delete the selected student from the system  */
void PA4::SchoolManagementSystem::deleteSelectedStudent()
{
    if (selectedStudent == nullptr) {
        throw std::invalid_argument("No student is selected!");
        exit(EXIT_FAILURE);
    }
    int oldNum = studentNum;
    Student * temp;

    if(oldNum == 1){
        temp = nullptr;
        studentNum = 0;
    }   else{   /* if the old number of student were greater than 1*/
        temp = new Student[--studentNum];
        for(int i = 0, k = 0; i < oldNum; i++){
            /* copy all the students except the one to delete   */
            if(allStudents[i].getID() != selectedStudent->getID())
                temp[k++] = allStudents[i];
        }
    }
    /* delete the student from all the courses s/he was enrolled    */
    for (int i = 0; i < courseNum; i++) {
        if(selectedStudent->isInCourse(allCourses[i]))
            dropStudentfromaCourse(*selectedStudent, allCourses[i]);
    }
    /* delete the old student array*/
    if(allStudents != nullptr)
        delete [] allStudents;
    /* set the new allStudent array */
    allStudents = temp;
    /* set the selectedStudent to nullptr*/
    selectedStudent = nullptr;

}

void PA4::SchoolManagementSystem::deleteSelectedCourse()
{
    if (selectedCourse == nullptr) {
        throw std::invalid_argument("Selected course does not exists!");
        exit(EXIT_FAILURE);
    }

    int oldNum = courseNum;
    Course * temp;

    if (oldNum == 1) {
        temp = nullptr;
        courseNum = 0;
    }
    else {  /* if the number of courses were greater than 1 */
        temp = new Course[--courseNum];
        /* copy all the courses exccept the one to delete   */
        for (int i = 0, k = 0; i < oldNum && temp != nullptr; i++) {
            if (allCourses[i].getCourseCode() == selectedCourse->getCourseCode())
                continue;
            temp[k++] = allCourses[i];
        }
    }
    /* delete the course from all the enrolled Students' array   */
    for (int i = 0; i < studentNum; i++) {
        if (selectedCourse->isStudentIn(allStudents[i]))
            dropStudentfromaCourse(allStudents[i], *selectedCourse);
    }

 //   if (temp == nullptr) {
 //       delete[] allCourses;
 //       allCourses = nullptr;
 //   } else {
        if(allCourses != nullptr)
            delete[] allCourses;
        allCourses = temp;
//    }

}
/// @brief selects the student with the matching name and id
/// @param name name of the student to select
/// @param id   id of the student to select
void PA4::SchoolManagementSystem::selectStudent(string& name, string& id)
{

    for(int i = 0; i < studentNum; i++){

        if(allStudents[i].getName() == name &&
           allStudents[i].getID() == id){
            /*  selectedStudent now points to the student   */
            selectedStudent = &allStudents[i];
            break;
           }
    }

    if(selectedStudent == nullptr){
        throw std::invalid_argument("Selected student does not exists!");
        exit(EXIT_FAILURE);    
    }


}
/// @brief selects the course with the matching name and code
/// @param name name of the course
/// @param code code of the course
void PA4::SchoolManagementSystem::selectCourse(string &name, string &code)
{
    for(int i = 0; i < courseNum; i++){

        if(allCourses[i].getCourseName() == name &&
           allCourses[i].getCourseCode() == code){

            selectedCourse = &allCourses[i];
            break;
           }
    }

    if(selectedCourse == nullptr){
        throw std::invalid_argument("Selected course does not exists!");
        exit(EXIT_FAILURE);
    }
}

void PA4::SchoolManagementSystem::subCourseMenu()
{
    int choice;
    string name, code;

    do{

        cout << "0 up\n";
        cout << "1 add_course\n";
        cout << "2 select_course\n";
        /* get the user choice and ignore newlines  */
        cin >> choice;
        cin.ignore(100, '\n');
        if(choice == 1){
            /* get the course information and add it to system  */
            getCourseInfo(name, code);
            addCoursetoSystem(name, code);
        }

        else if(choice == 2){
            /* get the course informaation and select it*/
            getCourseInfo(name, code);
            selectCourse(name, code);        
            /* print subselectmenu  */
            subSelectCourseMenu();
        }


    } while(choice != 0);

}

void PA4::SchoolManagementSystem::getCourseInfo(string &name, string &code)
{
    string line;
    getline(std::cin, line);
    std::stringstream ss(line);
    /* parse the input into the code and name*/
    /* the first string is taken as the code of the course*/
    ss >> code;
    /* the rest is the name of the course   */
    getline(ss, name);
}

/* list all the students in the system  */
void PA4::SchoolManagementSystem::listAllStudents()
{
    for(int i  = 0; i < studentNum; i++){
        cout << allStudents[i].getName() << " ";
        cout << allStudents[i].getID() << "\n";

    }
    
}
/* list all the courses in the system   */
void PA4::SchoolManagementSystem::listAllCourses()
{
    for(int i  = 0; i < courseNum; i++){
        cout << allCourses[i].getCourseCode();
        cout << allCourses[i].getCourseName() << "\n";

    }
}
