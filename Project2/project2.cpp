// Project2(1st file)
// Myo Khant Aung #10709461
// 12/04/24
#include <iostream>
#include "classes.cpp"
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

// Define structures for linked lists to store books and people
struct Books_node
{
    Book *book;       // Pointer to a book
    Books_node *link; // Pointer to the next node in the linked list
};
typedef Books_node *Bptr;

struct People_node
{
    Person *person;    // Pointer to a person
    People_node *link; // Pointer to the next node in the linked list
};
typedef People_node *Pptr;

// Constants for library and people sizes
const int library_size = 4, person_size = 3, staff_size = 3, student_size = 2, adult_size = 4;
const int staff_limit = 3, student_limit = 2, adult_limit = 4;

// Function prototypes
void insertBookNode(Bptr &head, Book *book);
void insertPeopleNode(Pptr &head, Person *person);
void menu6(Bptr library[], Pptr person[]);
void displayBookDetails(Book *book);
Book *searchBookByTitle(Bptr head, const string &title);
void menu1(Bptr library[]);
Person *searchPersonByID(Pptr head, int id);
void displayBorrowedBooks(Person *person, Bptr library[]);
void menu2(Pptr person[], Bptr library[]);
void menu5(Bptr library[]);
void detail_edit(Book *book, Person *person);
void add_book(Book *book, Person *person);
void menu3(Bptr library[], Pptr person[]);
void menu4(Bptr library[], Pptr person[]);
void detail_edit_menu4(Book *book, Person *person);

int main()
{
    // Indexes for different categories of books and people
    int chb = 0, cob = 1, nb = 2, hib = 3, staff = 0, student = 1, adult = 2;

    // File input handling
    ifstream infile_b;
    ifstream infile_p;
    string filename_book, filename_people;

    cout << "Enter filename1 : ";
    cin >> filename_book;
    cout << "Enter filename2 : ";
    cin >> filename_people;

    // Open files and handle errors
    infile_b.open(filename_book);
    if (infile_b.fail())
    {
        cout << "File open error";
        exit(0);
    }
    infile_p.open(filename_people);
    if (infile_p.fail())
    {
        cout << "File open error";
        exit(0);
    }

    // Arrays of linked lists for books and people
    Books_node *library[library_size];
    People_node *person[person_size];

    /////////////////// Library Data structure ///////////////////
    int code, available, rented, age, publish_year;
    string title, publisher, author;

    // Pointers to linked lists for each book category
    Bptr chbhead = nullptr, cobhead = nullptr, nbhead = nullptr, hibhead = nullptr;

    // Read book data from file and insert into appropriate linked list
    while (infile_b >> code)
    {
        if (code >= 1001 && code <= 2000)
        {
            infile_b >> title >> age >> available >> rented;
            Book *chbptr = new ChildrenBook(code, title, available, rented, age);
            insertBookNode(chbhead, chbptr);
        }
        else if (code >= 2001 && code <= 3000)
        {
            infile_b >> title >> publisher >> available >> rented;
            Book *cobptr = new ComputerBook(code, title, available, rented, publisher);
            insertBookNode(cobhead, cobptr);
        }
        else if (code >= 3001 && code <= 4000)
        {
            infile_b >> title >> publish_year >> available >> rented;
            Book *nbptr = new Novel(code, title, available, rented, publish_year);
            insertBookNode(nbhead, nbptr);
        }
        else if (code >= 4001 && code <= 5000)
        {
            infile_b >> title >> author >> available >> rented;
            Book *hibptr = new HistoryBook(code, title, available, rented, author);
            insertBookNode(hibhead, hibptr);
        }
    }
    library[chb] = chbhead;
    library[cob] = cobhead;
    library[nb] = nbhead;
    library[hib] = hibhead;

    /////////////////////// People Data structure ///////////////////////
    int id, count;
    string name;

    // Arrays to store book codes for each person type
    int staff_code[staff_size] = {0, 0, 0}, student_code[student_size] = {0, 0}, adult_code[adult_size] = {0, 0, 0, 0};
    Pptr staffhead = nullptr, studenthead = nullptr, adulthead = nullptr;

    // Read people data from file and insert into appropriate linked list
    while (infile_p >> id)
    {
        if (id >= 1 && id <= 100)
        {
            infile_p >> name >> count;
            for (int i = 0; i < count; ++i)
            {
                infile_p >> staff_code[i];
            }

            // Sort staff codes
            sort(staff_code, staff_code + count);
            Person *staffptr = new Staff(id, name, count, staff_code);
            insertPeopleNode(staffhead, staffptr);
        }
        else if (id >= 101 && id <= 300)
        {
            infile_p >> name >> count;
            for (int i = 0; i < count; ++i)
            {
                infile_p >> student_code[i];
            }

            // Sort student codes
            sort(student_code, student_code + count);
            Person *studentptr = new Student(id, name, count, student_code);
            insertPeopleNode(studenthead, studentptr);
        }
        else if (id >= 301 && id <= 1000)
        {
            infile_p >> name >> count;
            for (int i = 0; i < count; ++i)
            {
                infile_p >> adult_code[i];
            }

            // Sort adult codes
            sort(adult_code, adult_code + count);
            Person *adultptr = new Adult(id, name, count, adult_code);
            insertPeopleNode(adulthead, adultptr);
        }
    }
    person[staff] = staffhead;
    person[student] = studenthead;
    person[adult] = adulthead;

    ///////////// Menu Options ///////////////
    cout << endl
         << endl;

    int choice;
    do
    {
        // Display menu
        cout << setw(40) << setfill('-') << "" << endl;
        cout << right << setw(22) << setfill(' ') << "MENU" << endl;
        cout << setw(40) << setfill('-') << "" << endl
             << " 1. Search a book\n"
             << " 2. Show my information\n"
             << " 3. Rent a book\n"
             << " 4. Return a book\n"
             << " 5. Show all books\n"
             << " 6. Exit the program\n";

        cout << endl;
        cout << " Choose one menu [1-6] : ";
        cin >> choice;

        // Execute chosen menu option
        switch (choice)
        {
        case 1:
            menu1(library); // Search a book by title
            break;
        case 2:
            menu2(person, library); // Show information about a person
            break;
        case 3:
            menu3(library, person); // Rent a book
            break;
        case 4:
            menu4(library, person); // Return a book
            break;
        case 5:
            menu5(library); // Show all books
            break;
        case 6:
            menu6(library, person); // Exit the program and clean up memory
            break;
        default:
            break;
        }
    } while (choice != 6);

    return 0;
}
void insertBookNode(Bptr &head, Book *book)
{
    // Create a new node for the book
    Bptr newNode = new Books_node{book, nullptr};

    // If the linked list is empty or the new book's code is smaller, insert at the head
    if (!head || book->get_code() < head->book->get_code())
    {
        newNode->link = head;
        head = newNode;
        return;
    }

    // Traverse the list to find the correct position for insertion
    Bptr current = head;
    while (current->link && current->link->book->get_code() < book->get_code())
    {
        current = current->link;
    }

    // Insert the new node
    newNode->link = current->link;
    current->link = newNode;
}
void insertPeopleNode(Pptr &head, Person *person)
{
    // Create a new node for the person
    Pptr newNode = new People_node{person, nullptr};

    // If the linked list is empty or the new person's ID is smaller, insert at the head
    if (!head || person->get_id() < head->person->get_id())
    {
        newNode->link = head;
        head = newNode;
        return;
    }

    // Traverse the list to find the correct position for insertion
    Pptr current = head;
    while (current->link && current->link->person->get_id() < person->get_id())
    {
        current = current->link;
    }

    // Insert the new node
    newNode->link = current->link;
    current->link = newNode;
}
void menu6(Bptr library[], Pptr person[])
{
    // Free all book nodes in the library
    for (int i = 0; i < library_size; ++i)
    {
        while (library[i])
        {
            Bptr temp = library[i];
            library[i] = library[i]->link;
            delete temp->book; // Free book memory
            delete temp;       // Free node memory
        }
    }

    // Free all person nodes
    for (int i = 0; i < person_size; ++i)
    {
        while (person[i])
        {
            Pptr temp = person[i];
            person[i] = person[i]->link;
            delete temp->person; // Free person memory
            delete temp;         // Free node memory
        }
    }

    cout << "Exiting the program..." << endl;
}
Book *searchBookByTitle(Bptr head, const string &title)
{
    Bptr current = head;

    // Traverse the linked list to find the book with the given title
    while (current)
    {
        if (current->book->get_title() == title)
        {
            return current->book; // Return the book if found
        }
        current = current->link;
    }

    // If not found, throw an exception
    throw string("The book \"" + title + "\" does not exist.");
}
void displayBookDetails(Book *book)
{
    string title = book->get_title();

    // Replace underscores in the title with spaces for better display
    for (int i = 0; i < title.size(); ++i)
    {
        if (title[i] == '_')
        {
            title[i] = ' ';
        }
    }

    // Display common book details
    cout << "Code: " << book->get_code() << "\n";
    cout << "Title: " << title << "\n";

    // Display specific details based on the book's category
    if (book->get_code() >= 1001 && book->get_code() <= 2000)
    {
        cout << "Age : " << book->get_age() << '\n';
    }
    else if (book->get_code() >= 2001 && book->get_code() <= 3000)
    {
        cout << "Publisher : " << book->get_publisher() << '\n';
    }
    else if (book->get_code() >= 3001 && book->get_code() <= 4000)
    {
        cout << "Publish year : " << book->get_publish_year() << '\n';
    }
    else
    {
        cout << "Author : " << book->get_author() << '\n';
    }

    // Display availability and rented count
    cout << "Available: " << book->get_available() << "\n";
    cout << "Rented: " << book->get_rented() << "\n";
}
void menu1(Bptr library[])
{
    string title;
    cout << "Enter the book title : ";
    cin >> title;

    try
    {
        Book *foundBook = nullptr;

        // Search through all library categories
        for (int i = 0; i < library_size; ++i)
        {
            try
            {
                foundBook = searchBookByTitle(library[i], title);
                break; // Stop searching once the book is found
            }
            catch (const string &) // Ignore exceptions and continue searching
            {
            }
        }

        // If no book is found, throw an exception
        if (!foundBook)
        {
            throw string("Book with title \"" + title + "\" doesn't exist.");
        }

        // Display book details
        displayBookDetails(foundBook);
    }
    catch (const string &errorMsg)
    {
        cout << errorMsg << endl;
    }
}
Person *searchPersonByID(Pptr head, int id)
{
    Pptr current = head;

    // Traverse the linked list to find the person with the given ID
    while (current)
    {
        if (current->person->get_id() == id)
        {
            return current->person; // Return the person if found
        }
        current = current->link;
    }

    // If no person is found, throw an exception
    throw string("ID " + to_string(id) + " does not exist");
}
void displayBorrowedBooks(Person *person, Bptr library[])
{
    int count = person->get_count();
    int *codes = nullptr;

    // Determine the type of person and retrieve their borrowed book codes
    if (Staff *staff = dynamic_cast<Staff *>(person))
    {
        codes = staff->get_staff_code();
    }
    else if (Student *student = dynamic_cast<Student *>(person))
    {
        codes = student->get_student_code();
    }
    else if (Adult *adult = dynamic_cast<Adult *>(person))
    {
        codes = adult->get_adult_code();
    }

    cout << "You borrowed " << count << " books." << endl;

    // Traverse through borrowed book codes and display book details
    for (int i = 0; i < count; ++i)
    {
        Book *book = nullptr;

        // Search for the book in all library categories
        for (int j = 0; j < library_size; ++j)
        {
            Bptr current = library[j];
            while (current)
            {
                if (current->book->get_code() == codes[i])
                {
                    book = current->book;
                    break;
                }
                current = current->link;
            }
            if (book)
                break;
        }

        // Print book title if found
        if (book)
        {
            string title = book->get_title();
            for (int i = 0; i < title.size(); ++i)
            {
                if (title[i] == '_')
                {
                    title[i] = ' ';
                }
            }
            cout << i + 1 << ". " << title << " (" << book->get_code() << ")" << endl;
        }
    }
}
void menu2(Pptr person[], Bptr library[])
{
    int id;
    cout << "Enter your ID: ";
    cin >> id;

    try
    {
        Person *foundPerson = nullptr;

        // Search through all categories of people to find the person by ID
        for (int i = 0; i < person_size; ++i)
        {
            try
            {
                foundPerson = searchPersonByID(person[i], id);
                break; // Stop searching once the person is found
            }
            catch (const string &) // Ignore exceptions and continue searching
            {
            }
        }

        // If no person is found, throw an exception
        if (!foundPerson)
        {
            throw string("ID " + to_string(id) + " does not exist");
        }

        // Display person details and their borrowed books
        cout << "You are '" << foundPerson->get_name() << "'." << endl;
        displayBorrowedBooks(foundPerson, library);
    }
    catch (const string &errorMsg)
    {
        cout << errorMsg << endl;
    }
}
void menu5(Bptr library[])
{
    cout << endl;

    // Array of category titles for the library sections
    string arr[library_size]{"< Children Book >", "< Computer Book >", "< Novel > ", "< History Book >"};
    Bptr current = nullptr; // Pointer to traverse the linked list of books

    // Iterate through each category in the library
    for (int i = 0; i < library_size; i++)
    {
        // Display header and books for "Children Book" category
        if (i == 0)
        {
            cout << right << setfill(' ') << setw(35) << arr[i] << endl; // Display category title
            cout << setw(50) << setfill('-') << "" << endl;              // Display a separator
            current = library[i];                                        // Set pointer to the head of the current category

            // Traverse the linked list of books in the current category
            while (current != nullptr)
            {
                string title = current->book->get_title();

                // Replace underscores with spaces in the title for readability
                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == '_')
                    {
                        title[i] = ' ';
                    }
                }

                // Print book details
                cout << setw(5) << setfill(' ') << current->book->get_code()
                     << right << setw(25) << title
                     << setw(4) << current->book->get_age()
                     << setw(4) << current->book->get_available()
                     << setw(4) << current->book->get_rented() << endl;

                current = current->link; // Move to the next book in the category
            }
        }
        // Display header and books for "Computer Book" category
        else if (i == 1)
        {
            cout << right << setw(35) << arr[i] << endl;    // Display category title
            cout << setw(60) << setfill('-') << "" << endl; // Display a separator
            current = library[i];                           // Set pointer to the head of the current category

            // Traverse the linked list of books in the current category
            while (current != nullptr)
            {
                string title = current->book->get_title();

                // Replace underscores with spaces in the title
                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == '_')
                    {
                        title[i] = ' ';
                    }
                }

                string publisher = current->book->get_publisher();

                // Replace hyphens with spaces in the publisher name for readability
                for (int i = 0; i < publisher.size(); ++i)
                {
                    if (publisher[i] == '-')
                    {
                        publisher[i] = ' ';
                    }
                }

                // Print book details
                cout << setw(5) << setfill(' ') << current->book->get_code()
                     << right << setw(25) << title
                     << setw(18) << publisher
                     << setw(4) << current->book->get_available()
                     << setw(4) << current->book->get_rented() << endl;

                current = current->link; // Move to the next book in the category
            }
        }
        // Display header and books for "Novel" category
        else if (i == 2)
        {
            cout << right << setw(35) << arr[i] << endl;    // Display category title
            cout << setw(50) << setfill('-') << "" << endl; // Display a separator
            current = library[i];                           // Set pointer to the head of the current category

            // Traverse the linked list of books in the current category
            while (current != nullptr)
            {
                string title = current->book->get_title();

                // Replace underscores with spaces in the title
                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == '_')
                    {
                        title[i] = ' ';
                    }
                }

                // Print book details
                cout << setw(5) << setfill(' ') << current->book->get_code()
                     << right << setw(25) << title
                     << setw(7) << current->book->get_publish_year()
                     << setw(4) << current->book->get_available()
                     << setw(4) << current->book->get_rented() << endl;

                current = current->link; // Move to the next book in the category
            }
        }
        // Display header and books for "History Book" category
        else
        {
            cout << right << setw(35) << arr[i] << endl;    // Display category title
            cout << setw(60) << setfill('-') << "" << endl; // Display a separator
            current = library[i];                           // Set pointer to the head of the current category

            // Traverse the linked list of books in the current category
            while (current != nullptr)
            {
                string title = current->book->get_title();

                // Replace underscores with spaces in the title
                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == '_')
                    {
                        title[i] = ' ';
                    }
                }

                // Print book details
                cout << setw(5) << setfill(' ') << current->book->get_code()
                     << right << setw(25) << title
                     << setw(15) << current->book->get_author()
                     << setw(4) << current->book->get_available()
                     << setw(4) << current->book->get_rented() << endl;

                current = current->link; // Move to the next book in the category
            }
        }

        cout << endl; // Add space between categories
    }
}
void detail_edit(Book *book, Person *person)
{
    // Check if the book is available for rent
    if (book->get_available() == 0)
    {
        throw string("The book \"" + book->get_title() + "\" is not available");
    }
    else
    { // Add the book to the person's borrowed list
        add_book(book, person);
        // Update book availability and rented count
        book->set_available(book->get_available() - 1);
        book->set_rented(book->get_rented() + 1);

        // Display success message
        cout << "You are '" << person->get_name() << "'. The book '" << book->get_title() << "' is now rented." << endl;
    }
}
void add_book(Book *book, Person *person)
{
    int *tempcodes;

    // Determine the person's type and update their borrowed list
    if (person->get_id() >= 1 && person->get_id() <= 100) // Staff
    {
        if (person->get_count() == staff_limit)
        {
            throw string(person->get_name() + " cannot rent anymore books");
        }
        tempcodes = person->get_staff_code();
    }
    else if (person->get_id() >= 101 && person->get_id() <= 300) // Student
    {
        if (person->get_count() == student_limit)
        {
            throw string(person->get_name() + " cannot rent anymore books");
        }
        tempcodes = person->get_student_code();
    }
    else if (person->get_id() >= 301 && person->get_id() <= 1000) // Adult
    {
        if (person->get_count() == adult_limit)
        {
            throw string(person->get_name() + " cannot rent anymore books");
        }
        tempcodes = person->get_adult_code();
    }

    // Add the book code and increment count
    tempcodes[person->get_count()] = book->get_code();
    person->set_count(person->get_count() + 1);

    // Sort the borrowed book codes
    for (int i = 0; i < person->get_count() - 1; ++i)
    {
        for (int j = 0; j < person->get_count() - i - 1; ++j)
        {
            if (tempcodes[j] > tempcodes[j + 1])
            {
                swap(tempcodes[j], tempcodes[j + 1]);
            }
        }
    }
}
void menu3(Bptr library[], Pptr person[])
{
    int id;
    string book_name;

    // Prompt the user for their ID and the book title
    cout << endl;
    cout << "Enter your id : ";
    cin >> id;
    cout << "Enter book title : ";
    cin >> book_name;

    bool success = false;          // Flag to check if the operation succeeds
    Book *foundBook = nullptr;     // Pointer to hold the found book
    Person *foundPerson = nullptr; // Pointer to hold the found person

    // Search for the book in all library categories
    for (int i = 0; i < library_size; ++i)
    {
        try
        {
            foundBook = searchBookByTitle(library[i], book_name);
            break; // Exit loop once the book is found
        }
        catch (const string &)
        {
            // Ignore exception and continue searching in the next category
        }
    }

    // Search for the person by their ID in all person categories
    for (int i = 0; i < person_size; ++i)
    {
        try
        {
            foundPerson = searchPersonByID(person[i], id);
            break; // Exit loop once the person is found
        }
        catch (const string &)
        {
            // Ignore exception and continue searching in the next category
        }
    }

    // Try renting the book to the person
    try
    {
        detail_edit(foundBook, foundPerson); // Rent the book
        success = true;                      // Mark success if no exceptions are thrown
    }
    catch (const string &errorMsg)
    {
        // Catch and display errors if renting fails
        cout << errorMsg << endl;
    }

    string number; // Variable to store the count of books in word form
    int num;

    // If the rent operation was successful
    if (success == true)
    {
        num = foundPerson->get_count(); // Get the number of books the person has borrowed

        // Convert the count to a word for display
        switch (num)
        {
        case 1:
            number = "one";
            break;
        case 2:
            number = "two";
            break;
        case 3:
            number = "three";
            break;
        case 4:
            number = "four";
            break;
        default:
            break;
        }

        // Display success message
        cout << "Rent succeed. Now You borrowed " << number << " books." << endl;

        // Get the list of borrowed book codes
        int *tempcodes;
        if (foundPerson->get_id() >= 1 && foundPerson->get_id() <= 100)
        {
            tempcodes = foundPerson->get_staff_code();
        }
        else if (foundPerson->get_id() >= 101 && foundPerson->get_id() <= 300)
        {
            tempcodes = foundPerson->get_student_code();
        }
        else if (foundPerson->get_id() >= 301 && foundPerson->get_id() <= 1000)
        {
            tempcodes = foundPerson->get_adult_code();
        }

        // Display the details of the borrowed books
        for (int i = 0; i < foundPerson->get_count(); ++i)
        {
            Book *book = nullptr;

            // Search for the book in the library using its code
            for (int j = 0; j < library_size; ++j)
            {
                Bptr current = library[j];
                while (current)
                {
                    if (current->book->get_code() == tempcodes[i])
                    {
                        book = current->book;
                        break; // Exit loop once the book is found
                    }
                    current = current->link;
                }
                if (book)
                    break; // Exit outer loop if the book is found
            }

            // Display the book details
            if (book)
            {
                string title = book->get_title();

                // Replace underscores with spaces in the title for readability
                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == '_')
                    {
                        title[i] = ' ';
                    }
                }
                cout << i + 1 << ". " << title << endl;
            }
        }
    }
}

void detail_edit_menu4(Book *book, Person *person)
{
    bool in_rented_books = false; // Flag to check if the book is currently rented by the person
    int index = -1;               // Index of the book in the borrowed list
    int *tempcodes = nullptr;     // Pointer to the person's borrowed book codes

    // Determine the type of person and retrieve their borrowed book codes
    if (person->get_id() >= 1 && person->get_id() <= 100)
    {
        tempcodes = person->get_staff_code();
    }
    else if (person->get_id() >= 101 && person->get_id() <= 300)
    {
        tempcodes = person->get_student_code();
    }
    else if (person->get_id() >= 301 && person->get_id() <= 1000)
    {
        tempcodes = person->get_adult_code();
    }

    // Check if the book is in the person's borrowed list
    for (int i = 0; i < person->get_count(); i++)
    {
        if (book->get_code() == tempcodes[i])
        {
            in_rented_books = true;
            index = i; // Store the index of the book in the list
            break;
        }
    }

    // If the book is not found in the borrowed list, throw an exception
    if (!in_rented_books)
    {
        throw string("The book \"" + book->get_title() + "\" is not rented by " + person->get_name());
    }

    // Update the book's availability and rented count
    book->set_available(book->get_available() + 1);
    book->set_rented(book->get_rented() - 1);

    // Remove the book code from the person's borrowed list
    tempcodes[index] = 0;
    swap(tempcodes[index], tempcodes[person->get_count() - 1]); // Move the removed code to the end
    person->set_count(person->get_count() - 1);                 // Decrease the count of borrowed books

    // Sort the remaining borrowed book codes
    for (int i = 0; i < person->get_count() - 1; ++i)
    {
        for (int j = 0; j < person->get_count() - i - 1; ++j)
        {
            if (tempcodes[j] > tempcodes[j + 1])
            {
                swap(tempcodes[j], tempcodes[j + 1]);
            }
        }
    }

    // Display success message
    cout << "You are '" << person->get_name() << "'. The book '" << book->get_title() << "' has been returned." << endl;
}
void menu4(Bptr library[], Pptr person[])
{
    int id;
    string book_name;

    // Prompt user for ID and book title
    cout << endl;
    cout << "Enter your id : ";
    cin >> id;
    cout << "Enter book title : ";
    cin >> book_name;

    bool success = false; // Flag to track success of the return operation
    Book *foundBook = nullptr;
    Person *foundPerson = nullptr;

    // Search for the book in all library categories
    for (int i = 0; i < library_size; ++i)
    {
        try
        {
            foundBook = searchBookByTitle(library[i], book_name);
            break; // Exit loop once the book is found
        }
        catch (const string &) // Ignore exceptions and continue searching
        {
        }
    }

    // Search for the person in all categories
    for (int i = 0; i < person_size; ++i)
    {
        try
        {
            foundPerson = searchPersonByID(person[i], id);
            break; // Exit loop once the person is found
        }
        catch (const string &) // Ignore exceptions and continue searching
        {
        }
    }

    // Try to process the book return
    try
    {
        detail_edit_menu4(foundBook, foundPerson);
        success = true; // Mark the operation as successful
    }
    catch (const string &errorMsg)
    {
        cout << errorMsg << endl;
    }

    // If the return operation succeeded, display the updated borrowed list
    if (success)
    {
        string number; // Word representation of the count of borrowed books
        int num = foundPerson->get_count();

        // Convert count to words for better display
        switch (num)
        {
        case 1:
            number = "one";
            break;
        case 2:
            number = "two";
            break;
        case 3:
            number = "three";
            break;
        case 4:
            number = "four";
            break;
        default:
            break;
        }

        // Display success message
        cout << "Return succeeded. Now you borrowed " << number << " books." << endl;

        // Retrieve the updated list of borrowed books
        int *tempcodes;
        if (foundPerson->get_id() >= 1 && foundPerson->get_id() <= 100)
        {
            tempcodes = foundPerson->get_staff_code();
        }
        else if (foundPerson->get_id() >= 101 && foundPerson->get_id() <= 300)
        {
            tempcodes = foundPerson->get_student_code();
        }
        else if (foundPerson->get_id() >= 301 && foundPerson->get_id() <= 1000)
        {
            tempcodes = foundPerson->get_adult_code();
        }

        // Display the titles of currently borrowed books
        for (int i = 0; i < foundPerson->get_count(); ++i)
        {
            Book *book = nullptr;

            // Find the book using its code
            for (int j = 0; j < library_size; ++j)
            {
                Bptr current = library[j];
                while (current)
                {
                    if (current->book->get_code() == tempcodes[i])
                    {
                        book = current->book;
                        break;
                    }
                    current = current->link;
                }
                if (book)
                    break;
            }

            // Display book title if found
            if (book)
            {
                string title = book->get_title();
                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == '_')
                    {
                        title[i] = ' '; // Replace underscores with spaces
                    }
                }
                cout << i + 1 << ". " << title << endl;
            }
        }
    }
}
