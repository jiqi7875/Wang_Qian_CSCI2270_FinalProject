#include <iostream>
#include <fstream>
#include <sstream>
#include "Book.h"

using namespace std;

int main()
{
    Book BT;
    ifstream inFile;
    string data;
    inFile.open("Book.txt");
    while (getline(inFile,data))
    {
        stringstream ss(data);
        string word;
        //ranking of the book
        getline(ss,word,',');
        int ranking;
        istringstream(word)>>ranking;
        //title of the book
        getline(ss,word,',');
        string title=word;
        //author of the book
        getline(ss,word,',');
        string author=word;
        getline(ss,word,',');
        //total quantity of the book
        int quantity;
        istringstream(word)>>quantity;
        getline(ss,word,',');

        BT.addBookNode(ranking,title,author,quantity);
    }
    BT.menu();
    int selection;
    cin>>selection;
    while (selection!=7)
    {
        if (selection<7)
        {
            if (selection==1)
            {
                string title;
                cout<<"Enter title:"<<endl;
                cin.ignore();
                getline(cin,title);
                BT.findBook(title);
                BT.menu();
                cin>>selection;
            }
            else if (selection==2)
            {
                string title;
                cout<<"Enter title:"<<endl;
                cin.ignore();
                getline(cin,title);
                BT.rentBook(title);
                BT.buildBookList(title);
                BT.menu();
                cin>>selection;
            }
            else if (selection==3)
            {
                BT.printBook();
                BT.menu();
                cin>>selection;
            }
            else if(selection==4)
            {
                string title;
                cout<<"Enter title:"<<endl;
                cin.ignore();
                getline(cin,title);
                BT.returnBook(title);
                BT.menu();
                cin>>selection;
            }
            else if (selection==5)
            {
                BT.booklist();
                BT.menu();
                cin>>selection;
            }
            else if (selection==6)
            {
                string title;
                cout<<"Enter title:"<<endl;
                cin.ignore();
                getline(cin,title);
                BT.deleteBook(title);
                BT.menu();
                cin>>selection;
            }
        }
        else
        {
            cout<<"Error! Please input a number between 1 and 7!"<<endl;
            BT.menu();
            cin>>selection;
        }

    }
    BT.totalBookRent();
    BT.DeleteAll();
    cout<<"Goodbye!"<<endl;

    return 0;
}

