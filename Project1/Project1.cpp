// Project1(1st file)
// Myo Khant Aung #10709461
// 10/21/24
#include <iostream>
#include "students.cpp" // Includes student-related classes/functions
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// Struct definition for a course containing its title, number of students, and a list of students
struct Course
{
    string title;
    int number_of_students;
    Student *list;
};

// Function prototypes
void file_reader(string filename, int &num_of_students, string &course_name, Student *&list);
void sorter(int num_of_students, Student *&list);
int overlap_finder(const Course arr_of_course[], int demanded_overlap, int index), index_finder(int id, Student *list, int num_of_students);
void menu_one(const Course arr_of_courses[], const int SIZE), menu_two(const Course arr_of_courses[], const int SIZE), menu_three(const Course arr_of_courses[], const int SIZE), menu_four(const Course arr_of_courses[], const int SIZE), menu_five(Course arr_of_courses[], int SIZE);
void finding_top_three(Student *list, int SIZE, int &top1, int &top2, int &top3);

int main()
{
    const int SIZE = 3;          // Number of courses
    Course arr_of_courses[SIZE]; // Array of courses

    string filename1, filename2, filename3;
    // Get filenames from the user
    cout << "Enter filename #1 : ";
    getline(cin, filename1);
    cout << "Enter filename #2 : ";
    getline(cin, filename2);
    cout << "Enter filename #3 : ";
    getline(cin, filename3);

    string filenames[SIZE] = {filename1, filename2, filename3};

    // Read each file and populate the course data
    for (int i = 0; i < SIZE; i++)
    {
        Course course;
        file_reader(filenames[i], course.number_of_students, course.title, course.list);
        arr_of_courses[i] = course;
    }

    // Sort students in each course by their ID
    for (int i = 0; i < SIZE; i++)
    {
        sorter(arr_of_courses[i].number_of_students, arr_of_courses[i].list);
    }

    int choice;
    do
    {
        // Main menu for user interaction
        cout << "===================== Menu ====================" << endl;
        cout << "  1. Show all course list (sorting)\n"
             << "  2. List of students who take all courses\n "
             << " 3. List of students who take two courses\n "
             << " 4. Print out top three scores for each course\n "
             << " 5. Exit\n "
             << "-------> Select : ";
        cin >> choice;

        // Call appropriate menu function based on user choice
        switch (choice)
        {
        case 1:
            menu_one(arr_of_courses, SIZE);
            break;
        case 2:
            menu_two(arr_of_courses, SIZE);
            break;
        case 3:
            menu_three(arr_of_courses, SIZE);
            break;
        case 4:
            menu_four(arr_of_courses, SIZE);
            break;
        case 5:
            menu_five(arr_of_courses, SIZE);
            break;
        default:
            break;
        }

    } while (choice < 5); // Loop until user chooses to exit

    return 0;
}

// Function to read student data from a file into a course structure
void file_reader(string filename, int &num_of_students, string &course_name, Student *&list)
{
    int student_id, score;
    string student_name;
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail())
    {
        cout << "File opening failed"; // Error handling for file open failure
        exit(1);
    }
    inFile >> course_name >> num_of_students; // Read course name and number of students
    list = new Student[num_of_students];      // Dynamically allocate memory for students
    int index = 0;
    while (!inFile.eof())
    {
        inFile >> student_id >> student_name >> score; // Read student data
        list[index] = Student(student_id, student_name, score);
        index++;
    }
    inFile.close(); // Close the file
}

// Function to sort students by their ID
void sorter(int num_of_students, Student *&list)
{
    for (int i = 0; i < num_of_students - 1; i++)
    {
        for (int j = i + 1; j < num_of_students; j++)
        {
            if (list[i].get_id() > list[j].get_id()) // Compare student IDs
            {
                swap(list[i], list[j]); // Swap if out of order
            }
        }
    }
}

// Menu function to display sorted student lists for all courses
void menu_one(const Course arr_of_courses[], const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << "===========   " << arr_of_courses[i].title << "   ===========" << endl
             << endl;
        for (int j = 0; j < arr_of_courses[i].number_of_students; j++)
        {
            arr_of_courses[i].list[j].print(); // Print student details
        }
    }
    cout << endl;
}

// Function to find students who overlap in a given number of courses
int overlap_finder(const Course arr_of_courses[], int demanded_overlap, int index)
{
    int number_overlap = 0;
    for (int i = 0; i < 3; i++) // Check all three courses
    {
        for (int j = 0; j < arr_of_courses[i].number_of_students; j++)
        {
            if (arr_of_courses[0].list[index].get_id() == arr_of_courses[i].list[j].get_id())
            {
                number_overlap++; // Increase overlap count if student found in another course
                break;
            }
        }
    }
    // Return the student ID if the overlap matches the demand
    if (number_overlap == demanded_overlap)
    {
        return arr_of_courses[0].list[index].get_id();
    }
    else
    {
        return 0;
    }
}
int overlap_finder_two(const Course arr_of_course[], string title1, string title2, int demanded_overlap, int index)
{
    int number_overlap = 1;

    if (title1 == "Cpp" && title2 == "Java")
    {

        for (int j = 0; j < arr_of_course[1].number_of_students; j++)
        {
            if (arr_of_course[0].list[index].get_id() == arr_of_course[1].list[j].get_id())
            {
                number_overlap++;
                break;
            }
        }

        for (int k = 0; k < arr_of_course[2].number_of_students; k++)
        {
            if (arr_of_course[0].list[index].get_id() == arr_of_course[2].list[k].get_id())
            {
                return 0;
            }
        }
        if (number_overlap == demanded_overlap)
        {
            return arr_of_course[0].list[index].get_id();
        }
        else
        {
            return 0;
        }
    }

    else if (title1 == "Cpp" && title2 == "Python")
    {

        for (int j = 0; j < arr_of_course[2].number_of_students; j++)
        {
            if (arr_of_course[0].list[index].get_id() == arr_of_course[2].list[j].get_id())
            {
                number_overlap++;
                break;
            }
        }

        for (int k = 0; k < arr_of_course[1].number_of_students; k++)
        {
            if (arr_of_course[0].list[index].get_id() == arr_of_course[1].list[k].get_id())
            {
                return 0;
            }
        }
        if (number_overlap == demanded_overlap)
        {
            return arr_of_course[0].list[index].get_id();
        }
        else
        {
            return 0;
        }
    }

    else
    {

        for (int j = 0; j < arr_of_course[2].number_of_students; j++)
        {
            if (arr_of_course[1].list[index].get_id() == arr_of_course[2].list[j].get_id())
            {
                number_overlap++;
                break;
            }
        }
        for (int k = 0; k < arr_of_course[0].number_of_students; k++)
        {
            if (arr_of_course[1].list[index].get_id() == arr_of_course[0].list[k].get_id())
            {
                return 0;
            }
        }
        if (number_overlap == demanded_overlap)
        {
            return arr_of_course[1].list[index].get_id();
        }
        else
        {
            return 0;
        }
    }
}

// Function to find the index of a student by ID
int index_finder(int id, Student *list, int num_of_students)
{
    for (int i = 0; i < num_of_students; i++)
    {
        if (id == list[i].get_id()) // Compare student ID
        {
            return i;
        }
    }
    return -1; // Return -1 if not found
}

// Menu function to list students who take all courses
void menu_two(const Course arr_of_courses[], const int SIZE)
{
    const int size = arr_of_courses[0].number_of_students;
    int num = 0;
    int temparr[size]; // Temporary array to store overlapping student IDs
    for (int i = 0; i < size; i++)
    {
        temparr[i] = 0; // Initialize temp array
    }
    for (int i = 0; i < size; i++)
    {
        int num2 = overlap_finder(arr_of_courses, 3, i); // Find students who take all 3 courses

        if (num2 != 0)
        {
            temparr[num++] = num2; // Add student to list if they take all courses
        }
    }

    cout << right << setw(10) << "There are " << num << " students who take 3 courses." << endl
         << endl;
    cout << "--------------------------------------------------" << endl;

    // Print the details of students who take all three courses
    for (int i = 0; i < num; i++)
    {
        int id_cpp = index_finder(temparr[i], arr_of_courses[0].list, arr_of_courses[0].number_of_students);
        int id_java = index_finder(temparr[i], arr_of_courses[1].list, arr_of_courses[1].number_of_students);
        int id_python = index_finder(temparr[i], arr_of_courses[2].list, arr_of_courses[2].number_of_students);

        if (id_cpp >= 0 && id_java >= 0 && id_python >= 0)
        {
            cout << right << setw(10) << temparr[i]
                 << setw(8) << arr_of_courses[0].list[id_cpp].get_name()
                 << setw(5) << arr_of_courses[0].title << "(" << arr_of_courses[0].list[id_cpp].get_score() << ")"
                 << setw(7) << arr_of_courses[1].title << "(" << arr_of_courses[1].list[id_java].get_score() << ")"
                 << setw(7) << arr_of_courses[2].title << "(" << arr_of_courses[2].list[id_python].get_score() << ")" << endl;
        }
    }
}

// Menu function to list students who take two courses
void menu_three(const Course arr_of_courses[], const int SIZE)
{
    // Handle overlap for C++ and Java courses
    int cpp_java_count = 0;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        int overlap_id = overlap_finder_two(arr_of_courses, "Cpp", "Java", 2, i);
        if (overlap_id != 0)
        {
            cpp_java_count++;
        }
    }

    cout << "There are " << cpp_java_count << " students who take C++ and Java" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        int overlap_id = overlap_finder_two(arr_of_courses, "Cpp", "Java", 2, i);
        if (overlap_id != 0)
        {
            int id_cpp = index_finder(overlap_id, arr_of_courses[0].list, arr_of_courses[0].number_of_students);
            int id_java = index_finder(overlap_id, arr_of_courses[1].list, arr_of_courses[1].number_of_students);
            cout << setw(10) << overlap_id << setw(8) << arr_of_courses[0].list[id_cpp].get_name() << setw(5)
                 << "C++(" << arr_of_courses[0].list[id_cpp].get_score() << ")"
                 << setw(10) << "Java(" << arr_of_courses[1].list[id_java].get_score() << ")"
                 << endl;
        }
    }
    cout << endl;

    // Handle overlap for C++ and Python courses
    int cpp_python_count = 0;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        int overlap_id = overlap_finder_two(arr_of_courses, "Cpp", "Python", 2, i);
        if (overlap_id != 0)
        {
            cpp_python_count++;
        }
    }

    cout << "There are " << cpp_python_count << " students who take C++ and Python" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        int overlap_id = overlap_finder_two(arr_of_courses, "Cpp", "Python", 2, i);
        if (overlap_id != 0)
        {
            int id_cpp = index_finder(overlap_id, arr_of_courses[0].list, arr_of_courses[0].number_of_students);
            int id_python = index_finder(overlap_id, arr_of_courses[2].list, arr_of_courses[2].number_of_students);
            cout << setw(10) << overlap_id << setw(8) << arr_of_courses[0].list[id_cpp].get_name() << setw(5)
                 << "C++(" << arr_of_courses[0].list[id_cpp].get_score() << ")"
                 << setw(10) << "Python(" << arr_of_courses[2].list[id_python].get_score() << ")"
                 << endl;
        }
    }
    cout << endl;

    // Handle overlap for Java and Python courses
    int java_python_count = 0;
    for (int i = 0; i < arr_of_courses[1].number_of_students; i++)
    {
        int overlap_id = overlap_finder_two(arr_of_courses, "Java", "Python", 2, i);
        if (overlap_id != 0)
        {
            java_python_count++;
        }
    }

    cout << "There are " << java_python_count << " students who take Java and Python" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < arr_of_courses[1].number_of_students; i++)
    {
        int overlap_id = overlap_finder_two(arr_of_courses, "Java", "Python", 2, i);
        if (overlap_id != 0)
        {
            int id_java = index_finder(overlap_id, arr_of_courses[1].list, arr_of_courses[1].number_of_students);
            int id_python = index_finder(overlap_id, arr_of_courses[2].list, arr_of_courses[2].number_of_students);
            cout << setw(10) << overlap_id << setw(8) << arr_of_courses[1].list[id_java].get_name() << setw(5)
                 << "Java(" << arr_of_courses[1].list[id_java].get_score() << ")"
                 << setw(10) << "Python(" << arr_of_courses[2].list[id_python].get_score() << ")"
                 << endl;
        }
    }
    cout << endl;
}

// Function to find the top three scores for each course
void finding_top_three(Student *list, int SIZE, int &top1, int &top2, int &top3)
{
    top1 = 0;
    top2 = 0;
    top3 = 0;

    // Loop through students and determine the top three scores
    for (int i = 0; i < SIZE; i++)
    {
        int current_score = list[i].get_score();

        if (current_score > top1)
        {
            top3 = top2;
            top2 = top1;
            top1 = current_score;
        }
        else if (current_score > top2 && current_score != top1)
        {
            top3 = top2;
            top2 = current_score;
        }
        else if (current_score > top3 && current_score != top2 && current_score != top1)
        {
            top3 = current_score;
        }
    }
}

// Menu function to print top three scores for each course
void menu_four(const Course arr_of_courses[], const int SIZE)
{
    int top1 = 0, top2 = 0, top3 = 0;

    // Find and print top three scores for the first course
    finding_top_three(arr_of_courses[0].list, arr_of_courses[0].number_of_students, top1, top2, top3);
    cout << "[" << arr_of_courses[0].title << " Top Three Scores ]" << endl;
    cout << "1." << setw(1) << top1 << endl;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        if (arr_of_courses[0].list[i].get_score() == top1)
        {
            cout << right << setw(8) << arr_of_courses[0].list[i].get_id() << setw(10) << arr_of_courses[0].list[i].get_name() << endl;
        }
    }
    cout << "2." << setw(1) << top2 << endl;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        if (arr_of_courses[0].list[i].get_score() == top2)
        {
            cout << right << setw(8) << arr_of_courses[0].list[i].get_id() << setw(10) << arr_of_courses[0].list[i].get_name() << endl;
        }
    }
    cout << "3." << setw(1) << top3 << endl;
    for (int i = 0; i < arr_of_courses[0].number_of_students; i++)
    {
        if (arr_of_courses[0].list[i].get_score() == top3)
        {
            cout << right << setw(8) << arr_of_courses[0].list[i].get_id() << setw(10) << arr_of_courses[0].list[i].get_name() << endl;
        }
    }
    cout << endl;

    // Repeat the process for the second and third courses
    finding_top_three(arr_of_courses[1].list, arr_of_courses[1].number_of_students, top1, top2, top3);
    cout << "[" << arr_of_courses[1].title << " Top Three Scores ]" << endl;
    cout << "1." << setw(1) << top1 << endl;
    for (int i = 0; i < arr_of_courses[1].number_of_students; i++)
    {
        if (arr_of_courses[1].list[i].get_score() == top1)
        {
            cout << right << setw(8) << arr_of_courses[1].list[i].get_id() << setw(10) << arr_of_courses[1].list[i].get_name() << endl;
        }
    }
    cout << "2." << setw(1) << top2 << endl;
    for (int i = 0; i < arr_of_courses[1].number_of_students; i++)
    {
        if (arr_of_courses[1].list[i].get_score() == top2)
        {
            cout << right << setw(8) << arr_of_courses[1].list[i].get_id() << setw(10) << arr_of_courses[1].list[i].get_name() << endl;
        }
    }
    cout << "3." << setw(1) << top3 << endl;
    for (int i = 0; i < arr_of_courses[1].number_of_students; i++)
    {
        if (arr_of_courses[1].list[i].get_score() == top3)
        {
            cout << right << setw(8) << arr_of_courses[1].list[i].get_id() << setw(10) << arr_of_courses[1].list[i].get_name() << endl;
        }
    }
    cout << endl;

    finding_top_three(arr_of_courses[2].list, arr_of_courses[2].number_of_students, top1, top2, top3);
    cout << "[" << arr_of_courses[2].title << " Top Three Scores ]" << endl;
    cout << "1." << setw(1) << top1 << endl;
    for (int i = 0; i < arr_of_courses[2].number_of_students; i++)
    {
        if (arr_of_courses[2].list[i].get_score() == top1)
        {
            cout << right << setw(8) << arr_of_courses[2].list[i].get_id() << setw(10) << arr_of_courses[2].list[i].get_name() << endl;
        }
    }
    cout << "2." << setw(1) << top2 << endl;
    for (int i = 0; i < arr_of_courses[2].number_of_students; i++)
    {
        if (arr_of_courses[2].list[i].get_score() == top2)
        {
            cout << right << setw(8) << arr_of_courses[2].list[i].get_id() << setw(10) << arr_of_courses[2].list[i].get_name() << endl;
        }
    }
    cout << "3." << setw(1) << top3 << endl;
    for (int i = 0; i < arr_of_courses[2].number_of_students; i++)
    {
        if (arr_of_courses[2].list[i].get_score() == top3)
        {
            cout << right << setw(8) << arr_of_courses[2].list[i].get_id() << setw(10) << arr_of_courses[2].list[i].get_name() << endl;
        }
    }
    cout << endl;
}

// Function to clean up and exit the program
void menu_five(Course arr_of_courses[], int SIZE)
{
    cout << "Exiting...." << endl;
    for (int i = 0; i < SIZE; i++)
    {
        delete[] arr_of_courses[i].list; // Free dynamically allocated memory
    }
}
