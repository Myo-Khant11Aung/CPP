// Project1(2nd file)
// Myo Khant Aung #10709461
// 10/21/24
#include <iostream>
#include "students.h"
#include <iomanip>
Student::Student() : id(0), name(" "), score(0) {};

Student::Student(int tempid, string tempname, int tempscore)
{
    id = tempid;
    name = tempname;
    score = tempscore;
};

void Student::set_id(int tempid)
{
    id = tempid;
};

void Student::set_name(string tempname)
{
    name = tempname;
};

void Student::set_score(int tempscore)
{
    score = tempscore;
};

int Student::get_id()
{
    return id;
};
string Student::get_name()
{
    return name;
};
int Student::get_score()
{
    return score;
};

void Student::print()
{
    cout << right << setw(10) << id << setw(10) << name << setw(5) << score << endl;
}