// Project1(3rd file)
// Myo Khant Aung #10709461
// 10/21/24
#include <string>
using namespace std;
class Student
{
private:
    int id;
    string name;
    int score;

public:
    Student();
    Student(int, string, int);
    void set_id(int);
    void set_name(string);
    void set_score(int);
    int get_id();
    string get_name();
    int get_score();
    void print();
};
