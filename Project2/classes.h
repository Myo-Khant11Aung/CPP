// Project2(2nd file)
// Myo Khant Aung #10709461
// 12/04/24
#include <string>
using namespace std;

/// Base Class: Book /////////
class Book
{
public:
    Book();
    Book(int, string, int, int);
    virtual ~Book();

    // Setters
    void set_code(int);
    void set_title(string);
    void set_available(int);
    void set_rented(int);
    virtual void set_age(int) = 0;
    virtual void set_publisher(string) = 0;
    virtual void set_publish_year(int) = 0;
    virtual void set_author(string) = 0;

    // Getters
    int get_code();
    string get_title();
    int get_available();
    int get_rented();
    virtual int get_age() = 0;
    virtual string get_publisher() = 0;
    virtual int get_publish_year() = 0;
    virtual string get_author() = 0;

private:
    int code;
    string title;
    int available;
    int rented;
};

// Derived Classes
class ChildrenBook : public Book
{
public:
    ChildrenBook(int code, string title, int available, int rented, int age);
    ChildrenBook();

    // Relevant methods
    void set_age(int) override;
    int get_age() override;

    // Irrelevant methods with default implementations
    void set_publisher(string) override {}
    string get_publisher() override { return ""; }
    void set_publish_year(int) override {}
    int get_publish_year() override { return 0; }
    void set_author(string) override {}
    string get_author() override { return ""; }

private:
    int age;
};

class ComputerBook : public Book
{
public:
    ComputerBook(int code, string title, int available, int rented, string publisher);
    ComputerBook();

    // Relevant methods
    void set_publisher(string) override;
    string get_publisher() override;

    // Irrelevant methods with default implementations
    void set_age(int) override {}
    int get_age() override { return 0; }
    void set_publish_year(int) override {}
    int get_publish_year() override { return 0; }
    void set_author(string) override {}
    string get_author() override { return ""; }

private:
    string publisher;
};

class Novel : public Book
{
public:
    Novel(int code, string title, int available, int rented, int publish_year);
    Novel();

    // Relevant methods
    void set_publish_year(int) override;
    int get_publish_year() override;

    // Irrelevant methods with default implementations
    void set_age(int) override {}
    int get_age() override { return 0; }
    void set_publisher(string) override {}
    string get_publisher() override { return ""; }
    void set_author(string) override {}
    string get_author() override { return ""; }

private:
    int publish_year;
};

class HistoryBook : public Book
{
public:
    HistoryBook(int code, string title, int available, int rented, string author);
    HistoryBook();

    // Relevant methods
    void set_author(string) override;
    string get_author() override;

    // Irrelevant methods with default implementations
    void set_age(int) override {}
    int get_age() override { return 0; }
    void set_publisher(string) override {}
    string get_publisher() override { return ""; }
    void set_publish_year(int) override {}
    int get_publish_year() override { return 0; }

private:
    string author;
};

/////////////////////////////////

/// Base Class: Person /////////
class Person
{
public:
    Person();
    Person(int id, string name, int count);
    virtual ~Person();

    // Setters
    void set_id(int id);
    void set_name(string name);
    void set_count(int count);

    virtual void set_staff_code(int *) = 0;
    virtual void set_student_code(int *) = 0;
    virtual void set_adult_code(int *) = 0;

    // Getters
    virtual int *get_staff_code() = 0;
    virtual int *get_student_code() = 0;
    virtual int *get_adult_code() = 0;

    int get_id() { return this->id; };
    string get_name() { return this->name; };
    int get_count() { return this->count; };

private:
    int id;
    string name;
    int count;
};

// Derived Class: Staff
class Staff : public Person
{
public:
    Staff();
    Staff(int id, string name, int count, int *codes);

    void set_staff_code(int *codes) override;
    int *get_staff_code() override;

    // Irrelevant functions
    void set_student_code(int *) override {}
    void set_adult_code(int *) override {}
    int *get_student_code() override { return nullptr; }
    int *get_adult_code() override { return nullptr; }

private:
    int code[3] = {0, 0, 0};
};

// Derived Class: Student
class Student : public Person
{
public:
    Student();
    Student(int id, string name, int count, int *codes);

    void set_student_code(int *codes) override;
    int *get_student_code() override;

    // Irrelevant functions
    void set_staff_code(int *) override {}
    void set_adult_code(int *) override {}
    int *get_staff_code() override { return nullptr; }
    int *get_adult_code() override { return nullptr; }

private:
    int code[2] = {0, 0};
};

// Derived Class: Adult
class Adult : public Person
{
public:
    Adult();
    Adult(int id, string name, int count, int *codes);

    void set_adult_code(int *codes) override;
    int *get_adult_code() override;

    // Irrelevant functions
    void set_staff_code(int *) override {}
    void set_student_code(int *) override {}
    int *get_staff_code() override { return nullptr; }
    int *get_student_code() override { return nullptr; }

private:
    int code[4] = {0, 0, 0, 0};
};
