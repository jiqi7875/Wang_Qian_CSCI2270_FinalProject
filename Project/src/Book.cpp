#include "Book.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Book::Book()
{
    //ctor
}

Book::~Book()
{
    //dtor
}

//print out the menu
void Book::menu()
{
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Find a Book"<<endl;
    cout<<"2. Rent a Book"<<endl;
    cout<<"3. Print the inventory"<<endl;
    cout<<"4. Return Books"<<endl;
    cout<<"5. Your booklist"<<endl;
    cout<<"6. Delete a Book from your booklist"<<endl;
    cout<<"7. Quit"<<endl;

}

//build the BST for the book
void Book::addBookNode(int ranking, std::string title, std::string author, int quantity)
{
    BookNode *temp=root;
    BookNode *node=new BookNode;
    node->parent=NULL;
    node->leftChild=NULL;
    node->rightChild=NULL;
    node= new BookNode(ranking,title,author,quantity);
    BookNode *p=NULL;
    while (temp!=NULL)
    {
        p=temp;
        if (node->title<temp->title)
            temp=temp->leftChild;
        else
            temp=temp->rightChild;
    }

    if (p==NULL)
        root=node;

    else if (node->title<p->title)
    {
        p->leftChild=node;
        node->parent=p;
    }

    else
    {
        p->rightChild=node;
        node->parent=p;
    }
}

//find the book in the BST
void Book::findBook(string title)
{
    BookNode *foundBook=root;

    int flag=0;

    while (foundBook!=NULL)
    {
        if (foundBook->title>title)
            foundBook=foundBook->leftChild;
        else if (foundBook->title<title)
            foundBook=foundBook->rightChild;

        else
        {
            cout<<"Book Info:"<<endl;
            cout<<"==========="<<endl;
            cout<<"Ranking:"<<foundBook->ranking<<endl;
            cout<<"Title:"<<foundBook->title<<endl;
            cout<<"Author:"<<foundBook->author<<endl;
            cout<<"Quantity:"<<foundBook->quantity<<endl;
            foundBook->browse=foundBook->browse+1;
            cout<<"Browse: "<<foundBook->browse<<endl;
            cout<<"Rent: "<<foundBook->borrow<<endl;
            flag=1;
            break;
        }
    }

    if (flag==0)
        cout<<"Book not found."<<endl;
}

//find the book in the BST, quantity-1, borrow+1
void Book::rentBook(string title)
{
    BookNode *foundBook=root;
    int flag=0;
    while (foundBook!=NULL)
    {
        if (foundBook->title>title)
            foundBook=foundBook->leftChild;
        else if (foundBook->title<title)
            foundBook=foundBook->rightChild;

        else
        {
            if (foundBook->quantity==0)
                    cout<<"Book out of stock."<<endl;
            else
            {
                cout<<"Book has been rented."<<endl;
                cout<<"Book Info:"<<endl;
                cout<<"==========="<<endl;
                cout<<"Ranking:"<<foundBook->ranking<<endl;
                cout<<"Title:"<<foundBook->title<<endl;
                cout<<"Author:"<<foundBook->author<<endl;
                foundBook->quantity=foundBook->quantity-1;
                cout<<"Quantity:"<<foundBook->quantity<<endl;
                foundBook->borrow=foundBook->borrow+1;
                cout<<"Rent:"<<foundBook->borrow<<endl;
            }
            flag=1;
            break;
        }
    }

    if (flag==0)
        cout<<"Book not found."<<endl;
}

//print out all the books in the BST
void Book::printBook(BookNode *node)
{
    if (node->leftChild!=NULL)
        printBook(node->leftChild);
    cout<<node->title<<" "<<node->quantity<<endl;
    if (node->rightChild!=NULL)
        printBook(node->rightChild);
}

//call this function in main.cpp to print out all the book in the BST
void Book::printBook()
{
    BookNode *node=root;
    printBook(node);
}

//when someone returns the book, quantity+1, borrow-1
void Book::returnBook(string title)
{
    BookNode *foundBook=root;

    int flag=0;

    while (foundBook!=NULL)
    {
        if (foundBook->title>title)
            foundBook=foundBook->leftChild;
        else if (foundBook->title<title)
            foundBook=foundBook->rightChild;

        else
        {
            foundBook->quantity=foundBook->quantity+1;
            foundBook->borrow=foundBook->borrow-1;
            cout<<"Book has been returned."<<endl;
            cout<<"Book Info:"<<endl;
            cout<<"==========="<<endl;
            cout<<"Ranking:"<<foundBook->ranking<<endl;
            cout<<"Title:"<<foundBook->title<<endl;
            cout<<"Author:"<<foundBook->author<<endl;
            cout<<"Quantity:"<<foundBook->quantity<<endl;
            cout<<"Rent:"<<foundBook->borrow<<endl;
            int flag=1;
            break;
        }
    }
    //book title is not found
    if (flag==0)
        cout<<"Yon did not borrow this book from here. Nothing return."<<endl;

}

//when someone rents a book, print out the list of books that he/she chooses to rent
void Book::buildBookList(string title)
{
    BookList *node=new BookList(title);
    if (head==NULL)
        head=node;
    else
    {
        BookList *temp=head;
        while (temp->next!=NULL)
            temp=temp->next;
        temp->next=node;
    }
}

//call this function in main.cpp to print out the booklist
void Book::booklist()
{
    BookList *node=head;
    if (head==NULL)
        cout<<"You do not rent any book!"<<endl;
    else
    {
        while (node!=NULL)
        {
            cout<<node->title<<endl;
            node=node->next;
        }
    }

}

//delete the book in the booklist when people do not want to rent that book
void Book::deleteBook(string title)
{
    BookList *node=head;
    if (head==NULL)
        cout<<"You do not rent any book!"<<endl;
    else
    {
        if (head->title==title)
        head=head->next;
        else
        {
            while (node!=NULL)
            {
                if (node->next->title==title)
                {
                    BookList *temp=node->next;
                    node->next=temp->next;
                    node=temp;
                    break;
                }
                else
                    node=node->next;
            }
        }
        delete node;

        BookNode *foundBook=root;
        while (foundBook!=NULL)
        {
            if (foundBook->title>title)
                foundBook=foundBook->leftChild;
            else if (foundBook->title<title)
                foundBook=foundBook->rightChild;
            else
            {
                foundBook->quantity=foundBook->quantity+1;
                foundBook->borrow=foundBook->borrow-1;
                break;
            }
        }
    }

}

//calculate how many books are rented today
int Book::totalBookRent(BookNode *node)
{
    if (node->leftChild!=NULL)
        totalBookRent(node->leftChild);
    borrow=borrow+node->borrow;
    if (node->rightChild!=NULL)
        totalBookRent(node->rightChild);
}

//call this function in main.cpp to show how many books are rented today
void Book::totalBookRent()
{
    totalBookRent(root);
    cout<<"Today, we rent "<<borrow<<" books."<<endl;
}

//When people select quit, delete all the book in the BST
void Book::DeleteAll(BookNode *node)
{
    if (node->leftChild!=NULL)
        DeleteAll(node->leftChild);
    if (node->rightChild!=NULL)
        DeleteAll(node->rightChild);
}

//call this function in main.cpp to delete all the book
void Book::DeleteAll()
{
    DeleteAll(root);
}
