#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;

//use to create BST
struct BookNode{
    int ranking;
    std::string title;
    std::string author;
    int quantity;
    BookNode *parent;
    BookNode *leftChild;
    BookNode *rightChild;
    int browse;
    int borrow;
    BookNode(){};

    BookNode(int in_ranking, std::string in_title, std::string in_name, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        author = in_name;
        quantity = in_quantity;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
        browse=0;
        borrow=0;
    }

};

//use to create single linked list
struct BookList
{
    std::string title;
    BookList *next;

    BookList(){};

    BookList(std::string in_title)
    {
        title=in_title;
        next=NULL;
    }
};

class Book
{
    public:
        Book();
        ~Book();
        void menu();
        void printBook();
        void deleteBook(std::string title);
        void addBookNode(int ranking, std::string title, std::string author, int quantity);
        void findBook(std::string title);
        void rentBook(std::string title);
        void returnBook(std::string title);
        void totalBookRent();
        void buildBookList(std::string title);
        void booklist();
        void DeleteAll();

    protected:
    private:
        void DeleteAll(BookNode * node);
        void printBook(BookNode * node);
        int totalBookRent(BookNode *node);
        void countBookNodes(BookNode *node, int *c);
        BookNode *root=NULL;
        int borrow=0;
        BookList *head=NULL;
};

#endif // BOOK_H
