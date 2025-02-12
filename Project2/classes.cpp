// Project2(3rd file)
// Myo Khant Aung #10709461
// 12/04/24
#include <iostream>
#include "classes.h"
#include <string>
/// Book ////////////////
Book::Book() {};
Book::Book(int code, string title, int available, int rented)
{
    this->code = code;
    this->title = title;
    this->available = available;
    this->rented = rented;
};
Book::~Book() {};
void Book::set_code(int code) { this->code = code; };
void Book::set_title(string title) { this->title = title; };
void Book::set_available(int available) { this->available = available; };
void Book::set_rented(int rented) { this->rented = rented; };

int Book::get_code() { return this->code; };
string Book::get_title() { return this->title; };
int Book::get_available() { return this->available; };
int Book::get_rented() { return this->rented; };

ChildrenBook::ChildrenBook(int code, string title, int available, int rented, int age) : Book(code, title, available, rented) { this->age = age; };
ChildrenBook::ChildrenBook() {};
void ChildrenBook::set_age(int age) { this->age = age; };
int ChildrenBook::get_age() { return this->age; };

ComputerBook::ComputerBook(int code, string title, int available, int rented, string publisher) : Book(code, title, available, rented) { this->publisher = publisher; };
ComputerBook::ComputerBook() {};
void ComputerBook::set_publisher(string publisher) { this->publisher = publisher; };
string ComputerBook::get_publisher() { return this->publisher; };

Novel::Novel(int code, string title, int available, int rented, int publish_year) : Book(code, title, available, rented) { this->publish_year = publish_year; };
Novel::Novel() {};
void Novel::set_publish_year(int publish_year) { this->publish_year = publish_year; };
int Novel::get_publish_year() { return this->publish_year; };

HistoryBook::HistoryBook(int code, string title, int available, int rented, string author) : Book(code, title, available, rented) { this->author = author; };
HistoryBook::HistoryBook() {};
void HistoryBook::set_author(string author) { this->author = author; };
string HistoryBook::get_author() { return this->author; };
////////////////////////////////

/////// People //////////
Person::Person() {};
Person::Person(int id, string name, int count)
{
    this->id = id;
    this->name = name;
    this->count = count;
};
Person::~Person() {};
void Person::set_id(int id) { this->id = id; };
void Person::set_name(string name) { this->name = name; };
void Person::set_count(int count) { this->count = count; };

Staff::Staff() {};
Staff::Staff(int id, string name, int count, int *code) : Person(id, name, count)
{
    for (int i = 0; i < 3; i++)
    {
        this->code[i] = code[i];
    }
};
void Staff::set_staff_code(int *code)
{
    for (int i = 0; i < 3; i++)
    {
        this->code[i] = code[i];
    }
};
int *Staff::get_staff_code() { return this->code; };

Student::Student() {};
Student::Student(int id, string name, int count, int *code) : Person(id, name, count)
{
    for (int i = 0; i < 2; i++)
    {
        this->code[i] = code[i];
    }
};
void Student::set_student_code(int *code)
{
    for (int i = 0; i < 2; i++)
    {
        this->code[i] = code[i];
    }
};
int *Student::get_student_code() { return this->code; };

Adult::Adult() {};
Adult::Adult(int id, string name, int count, int *code) : Person(id, name, count)
{
    for (int i = 0; i < 4; i++)
    {
        this->code[i] = code[i];
    }
};
void Adult::set_adult_code(int *code)
{
    for (int i = 0; i < 4; i++)
    {
        this->code[i] = code[i];
    }
};
int *Adult::get_adult_code() { return this->code; };
////////////////////////////