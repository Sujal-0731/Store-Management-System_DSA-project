#include <iostream>
#include<iomanip>
#include<string.h>
#include<cstring>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include <windows.h>
using namespace std;
struct order_data_queue{
    string username;
    int no_of_items;
    string *item;
    string *quantity;
    string time_of_order;
    order_data_queue *next;
    order_data_queue *prev;
};
string getCurrentTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    ostringstream oss;
    oss << put_time(localTime, "%Y-%m-%d %H:%M:%S");

    return oss.str(); // Return time as a string
}
class order{
public:
     order_data_queue *head=NULL;
    void add_order(string user_name){
        cout<<"HELLO "<<user_name<<"!\n";
        cout<<"----------------------\n";
        cout<<"PLEASE PLACE YOUR ORDER\n";
        cout<<"----------------------\n";
        order_data_queue *newnode=new order_data_queue;
        newnode->username=user_name;
        if (head==NULL){
            head=newnode;
            newnode->next=NULL;
            newnode->prev=NULL;
        }
        else{
            order_data_queue *temp=head;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->prev=temp;
            newnode->next=NULL;
        }
        newnode->time_of_order=getCurrentTime();
        cout<<" ENTER NO OF ITEMS YOU WANT TO ORDER:";
        cin>>newnode->no_of_items;
        cout<<"----------------------\n";
        newnode->item=new string[newnode->no_of_items];
        newnode->quantity=new string[newnode->no_of_items];
        for(int i=0;i<newnode->no_of_items;i++){
            cout<<"ENTER ITEM NAME THEN ITS QUANTITY:\n";
            cin>>newnode->item[i]>>newnode->quantity[i];
        }
        cout<<user_name<<",your order has been placed.\n";

     }
     void handover_order() {
    order_data_queue *temp = head;
    if (temp == NULL) {
        cout << "NO ORDER PLACED YET\n";
    }
    else {
        cout<<"=====BEFORE HANDOVER=====\n";
         cout<<"=====ORDER DETAILS=====\n";
            order_data_queue *temp1=head;
            while(temp1!=NULL){
                cout<<"ORDER FROM "<<temp1->username<<" AT "<<temp1->time_of_order<<endl;
                for(int i=0;i<temp1->no_of_items;i++){
                    cout<<(i+1)<<":ITEM NAME:"<<temp1->item[i]<<"\tQUANTITY:"<<temp1->quantity[i]<<endl;
                }
                temp1=temp1->next;
            }
        head = temp->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        cout << "ORDER BEING PROCESSED\n";
        for (int i = 0; i < temp->no_of_items; i++) {
            cout << (i + 1) << ": ITEM NAME: " << temp->item[i] << "\tQUANTITY: " << temp->quantity[i] << endl;
        }
        cout << "ORDER HAS BEEN HANDED OVER TO " << temp->username << endl;
        cout << "TIME OF ORDER: " << temp->time_of_order << endl;
        cout << "TIME OF HANDOVER: " << getCurrentTime() << endl;
        delete[] temp->item;
        delete[] temp->quantity;
        delete temp;
         cout<<"=====AFTER HANDOVER=====\n";
         cout<<"=====ORDER DETAILS=====\n";
            order_data_queue *temp2=head;
            if(temp2==NULL){
                cout<<"NO MORE ORDER REMAINING\n";
            }
            while(temp2!=NULL){
                cout<<"ORDER FROM "<<temp2->username<<" AT "<<temp2->time_of_order<<endl;
                for(int i=0;i<temp2->no_of_items;i++){
                    cout<<(i+1)<<":ITEM NAME:"<<temp2->item[i]<<"\tQUANTITY:"<<temp2->quantity[i]<<endl;
                }
                temp2=temp2->next;
            }
    }
    cout << "Press any key to return to the owner menu...\n";
    getch();
    system("CLS");
}

     void view_customer_order(string user_name){
         bool user=false;
        order_data_queue *temp=head;
        if(temp==NULL){
            cout<<"NO ORDER FOUND YET \n";
        }
        else{
            while(temp!=NULL){
                if(temp->username==user_name){
                    user=true;
                    cout<<"ORDER FROM "<<temp->username<<" AT "<<temp->time_of_order<<endl;
                     for(int i=0;i<temp->no_of_items;i++){
                         cout<<(i+1)<<":ITEM NAME:"<<temp->item[i]<<"\tQUANTITY:"<<temp->quantity[i]<<endl;
                    }
                    temp=temp->next;
                }
            }
            if(!user){
            cout<<"NO ORDER HAS BEEN PLACED BY "<<user_name;
        }
        }

     }
     void view_all_orders(){
        cout<<"VIEWING ALL ORDERS...\n";
        Sleep(3000);
        system("CLS");
        order_data_queue *temp=head;
        if(temp==NULL){
            cout<<"NO ORDER PLACED YET\nRETURNING TO OWNER MENU PAGE";
            Sleep(3000);
            system("CLS");
        }
        else{
        cout<<"=====ORDER DETAILS=====\n";
            while(temp!=NULL){
                cout<<"ORDER FROM "<<temp->username<<" AT "<<temp->time_of_order<<endl;
                for(int i=0;i<temp->no_of_items;i++){
                    cout<<(i+1)<<":ITEM NAME:"<<temp->item[i]<<"\tQUANTITY:"<<temp->quantity[i]<<endl;
                }
                temp=temp->next;
            }
        }
        cout<<"ENTER ANY KEY TO CONTINUE.."<<endl;
        getch();
        cout<<"RETURNING TO OWNER MENU PAGE...";
        Sleep(3000);
        system("CLS");
     }


};

class login_register:public order{
    string designation;
    string username;
    string password;
    string address,phone_no;
    string fileuser,filepass;
    int choice;
public:
    void userregister(){
        cout << "\n==== SHOPKEEPER MANAGEMENT SYSTEM ====\n";
        cout << "\n==== WELCOME TO REGISTER PAGE!! ====\n";
        cout<<"ENTER YOUR DESIGNATION (customer/owner):";
        cin>>designation;
        if(designation!="customer"&&designation!="owner"){
            cout<<"INVALID DESIGNATION...\n";
            cout<<"RETURNING TO HOME PAGE...\n";
            Sleep(3000);
            system("CLS");
        }
        else{
        if(designation=="customer"){
            cout<<"ENTER YOUR USERNAME:";
            cin>>username;
            cout<<"ENTER YOUR ADDRESS:";
            cin>>address;
            cout<<"ENTER YOU PHONE NO:";
            cin>>phone_no;
            cout<<"ENTER YOUR PASSWORD:";
            cin>>password;
            fstream file;
            fstream fdet;
            file.open("customer.txt",ios::app|ios::in);
            fdet.open("cutomerdetails.txt",ios::app|ios::in);
            file<<username<<"  "<<password<<"\n";
            fdet<<username<<"  "<<address<<"  "<<phone_no<<"\n";
            cout<<"CONGRATULATIONS!!\n"<<username<<" HAS BEEN REGISTERED AS CUSTOMER."<<endl;
            cout<<"RETURNING TO HOME PAGE....\n";
            Sleep(3000);
            system("CLS");
            file.close();
            fdet.close();
        }
        else if(designation=="owner"){
            cout<<"ENTER YOUR USERNAME:";
            cin>>username;
            cout<<"ENTER YOUR PASSWORD:";
            cin>>password;
            fstream file;
            file.open("owner.txt",ios::app|ios::out);
            file<<username<<"  "<<password<<"\n";
            cout<<"CONGRATULATIONS!!\n"<<username<<" HAS BEEN REGISTERED AS OWNER."<<endl;
            cout<<"RETURNING TO HOME PAGE....\n";
            Sleep(3000);
            system("CLS");
            file.close();
        }
        }

    }
    void login() {
    bool success=false;
    int choice;
    do{
    cout << "=======LOGIN PAGE========\n";
    cout << "ENTER \n1 TO LOGIN AS CUSTOMER \n2 TO LOGIN AS OWNER\n3 TO EXIT \n->";
    cin >> choice;

    fstream file;
    switch (choice) {
        case 1:
            system("CLS");
            cout<<"LOGGING IN AS CUSTOMER\n";
            cout<<"----------------------\n";
            cout << "ENTER YOUR USERNAME AND PASSWORD CORRECTLY\n";
            cout<<"----------------------\n";
            cout << "ENTER USERNAME: ";
            cin >> username;
            cout << "ENTER YOUR PASSWORD: ";
            cin >> password;
            file.open("customer.txt",ios::in);
            if(!file){
                cout << "Error opening file!\n";
                break;
            }
            while (file >> fileuser >> filepass) {
                if (fileuser == username && filepass == password) {
                    cout << "Customer Login successful!\n";
                    success=true;
                    cout<<"OPENING CUSTOMER MENU PAGE...";
                    Sleep(1000);
                    system("CLS");
                    customer_menu(username);
                    file.close();
                }
            }
            if(!success){
                cout<<"INCORRECT USERNAME OR PASSWORD\nRETURNING TO LOGIN PAGE.... \n";
                Sleep(3000);
                system("CLS");
                login();
            }
            break;
        case 2:
                system("CLS");
                cout<<"LOGGING IN AS OWNER\n";
                cout<<"----------------------\n";
                cout << "ENTER YOUR USERNAME AND PASSWORD CORRECTLY\n";
                cout<<"----------------------\n";
                cout << "ENTER USERNAME: ";
                cin >> username;
                cout << "ENTER YOUR PASSWORD: ";
                cin >> password;
            file.open("owner.txt", ios::in);
            if (!file) {
                cout << "Error opening file!\n";
                break;
            }
            while (file >> fileuser >> filepass) {
                if (fileuser == username && filepass == password) {
                        success=true;
                    cout << "Owner Login successful!\nOpening owner menu...";
                    Sleep(3000);
                    system("CLS");
                    owner_menu();
                    file.close();
                }
            }
            if(!success){
                cout<<"INCORRECT USERNAME OR PASSWORD\nRETURNING TO LOGIN PAGE.... \n";
                Sleep(3000);
                system("CLS");
                login();
            }
            break;
        case 3:
            cout<<"EXITING LOGIN PAGE....";
            Sleep(3000);
            system("CLS");

        default:
            cout << "Invalid choice! Please enter 1 or 2.\n";
        }
    }
        while(choice!=3);
    }
    void view_user_details(){
        string user,addr,no;
        cout<<"VIEWING USER DETAILS...\n";
        Sleep(3000);
        system("CLS");
        cout<<"Enter User Name:";
        cin>>user;
        fstream fdet;
        fdet.open("cutomerdetails.txt",ios::in);
         if (!fdet) {
                cout << "Error opening file!\n";
        }
        while (fdet >> fileuser >> addr >> no) {
            if (fileuser == user ) {
                    cout << "USER DETAILS OF "<<user<<":"<<endl;
                    cout<<"ADDRESS:"<<addr<<"\nPHONE NO:"<<no<<endl;
                    fdet.close();
                }
            }
            cout<<"ENTER ANY KEY TO CONTINUE..."<<endl;
            getch();
            cout<<"RETURNING TO OWNER MENU PAGE...";
            Sleep(3000);
            system("CLS");

    }
    void customer_menu(string user){
        int c;
        do{
        cout<<"=======CUSTOMER MENU PAGE=======\n";
        cout<<"HELLO ,"<<user<<endl;
        cout<<"--------------------------------\n";
        cout<<"ENTER 1 TO VIEW YOUR ORDERS \nENTER 2 TO ADD YOUR ORDERS \nENTER 3 TO LOG OUT \n";
        cout<<"--------------------------------\nENTER YOUR CHOICE:";
        cin>>c;
        switch(c){
        case 1:
            cout<<"VIEWING YOUR ORDER "<<user<<"...\n";
            Sleep(3000);
            system("CLS");
            view_customer_order(user);
            cout<<"ENTER ANY KEY TO CONTINUE.."<<endl;
            getch();
            cout<<"\nRETURNING TO CUSTOMER MENU PAGE...";
            Sleep(3000);
            system("CLS");
            break;
        case 2:
            system("CLS");
            add_order(user);
            cout<<"RETURNING TO CUTOMER MENU PAGE...";
            Sleep(2000);
            system("CLS");
            break;
        case 3:
            cout<<"LOGGING OUT...\n";
            Sleep(2000);
            system("CLS");
            break;
        default:
            cout<<"Invalid choice! Try again.\n";
        }
        }while(c!=3);
    }
    void owner_menu(){
        int c;

        do {
            cout<<"=======OWNER MENU PAGE=======\n";

            cout << "1. View All Orders\n2. View User Details \n3 To hand over the order with Highest priority\n4. Logout\n";
            cout<<"------------------------------\nEnter choice: ";
            cin >> c;
            switch (c) {
                case 1:
                    view_all_orders();
                    break;
                case 2:
                    view_user_details();
                    break;
                case 3:
                    handover_order();
                    cout<<"RETURNING TO OWNER MENU PAGE\n";
                    Sleep(3000);
                    system("CLS");
                    break;
                case 4: cout << "Logging out...\n";
                    Sleep(3000);
                    system("CLS");
                    return;

                default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);
    }

};
int main()
{
    login_register l;
    int c;
    while(1){

    do{
    cout << "\n==== STORE MANAGEMENT SYSTEM ====\n      ==== HOME PAGE ====\n";
    cout<<"ENTER \n1 TO REGISTER \n2 TO LOGIN \n3 TO EXIT\n-------------------------------------\nENTER YOUR CHOICE->";
    cin>>c;
    system("CLS");
    switch(c){
    case 1:
        l.userregister();
        system("CLS");
        break;
    case 2:
        l.login();
        system("CLS");
        break;
    case 3:
        system("CLS");

        return 0;
        break;
    default:
        cout<<"invalid input\n";
        break;
    }
    }while(c!=3);
    }
}
