#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <thread>   // For sleep functionality
#include <chrono>   // For duration
#include <iomanip>  // For setw
#define NOMINMAX
#include <windows.h> // For SetConsoleTextAttribute
#include<limits>

using namespace std;
void setConsoleColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}


// time
string getCurrentTimestamp()
{
    time_t now = time(0);
    char dt[26];
    ctime_s(dt, sizeof(dt), &now);
    return string(dt);
}

// Signup functionality (Account creation)
class Signup
{
public:
    string email_address;
    string phone;
    string user_name;
    string password;
    string gender;
    string city;
    int age;
    ofstream fout_login;
    ofstream fout_name;
    ofstream fout_message;
    bool ok;
    string st1, st2, st3, st4;
    Signup()
    {
        email_address = " ";
        phone = " ";
        user_name = " ";
        password = " ";
        gender = " ";
        city = " ";
        st1 = "male";
        st2 = "Male";
        st3 = "female";
        st4 = "Female";
        age = 0;
        ok = false;

    }
    void signup()
    {
        fout_login.open("login.txt", ios::app);

        // username
        cout << endl;
        do
        {
            ok = true;
            setConsoleColor(6);
            cout << "User_name (unique) : ";
            cin.ignore();
            setConsoleColor(11);
            getline(cin, user_name);
            for (int i = 0; i < user_name.length(); ++i)
            {
                if (user_name[i] == ' ')
                {
                    setConsoleColor(4);
                    cout << "User Name should be without space ";
                    setConsoleColor(6);
                    cout << ":(" << endl;
                    setConsoleColor(11);
                    ok = false;
                }
            }
            if (ok && !is_unique_username(user_name))
            {
                setConsoleColor(4);
                cout << "User Name already exists. Please choose a different name.";
                setConsoleColor(6);
                cout << ":(" << endl;
                ok = false;
            }
        } while (!ok);
        fout_name.open("name.txt", ios::app);
        fout_name << user_name << endl;
        fout_name.close();
        cout << endl;

        fout_message.open("message.txt", ios::app);
        fout_message << "->" << user_name << endl;
        fout_message.close();
        cout << endl;
        // password
        do
        {
            ok = true;
            setConsoleColor(6);
            cout << "Password : ";
            //cin.ignore();
            setConsoleColor(11);
            getline(cin, password);
            for (int i = 0; i < password.length(); ++i)
            {
                if (password[i] == ' ')
                {
                    setConsoleColor(4);
                    cout << "Password should be without space ";
                    setConsoleColor(6);
                    cout << ":(" << endl;
                    ok = false;
                }
            }
        } while (!ok);

        cout << endl;
        // age
        setConsoleColor(6);
        cout << "Age : ";
        setConsoleColor(11);
        cin >> age;
        if (age < 15)
        {
            setConsoleColor(4);
            cout << "You are Underage, cannot create and use account  ";
            setConsoleColor(6);
            cout << ":(" << endl;
            exit(0);
        }

        cout << endl;
        // email address
        do
        {
            ok = true;
            setConsoleColor(6);
            cout << "Gmail Address : ";
            cin.ignore();
            setConsoleColor(11);
            getline(cin, email_address);
            for (int i = 0; i < email_address.length(); ++i)
            {
                if (email_address[i] == ' ')
                {
                    setConsoleColor(4);
                    cout << "Invalid Email should not contain spaces ";
                    setConsoleColor(6);
                    cout << ":(" << endl;
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                if (email_address.length() >= 10 && email_address.substr(email_address.length() - 10) == "@gmail.com")
                {
                    ok = true;
                }
                else
                {
                    setConsoleColor(4);
                    cout << "Invalid Email must end with '@gmail.com'.";
                    setConsoleColor(6);
                    cout << ":(" << endl;
                    ok = false;
                }
            }
        } while (!ok);

        cout << endl;
        // gender
        do
        {
            ok = true;
            setConsoleColor(6);
            cout << "Gender (Male / Female) : ";
            setConsoleColor(11);
            getline(cin, gender);
            if (gender != st1 && gender != st2 && gender != st3 && gender != st4)
            {
                setConsoleColor(4);
                cout << "Invalid Input. Please enter 'Male' or 'Female': ";
                setConsoleColor(6);
                cout << ":(" << endl;
                ok = false;
            }
        } while (!ok);

        cout << endl;
        // phone number
        do
        {
            ok = true;
            setConsoleColor(6);
            cout << "Phone Number : ";
            setConsoleColor(11);
            getline(cin, phone);
            if (phone.length() != 11)
            {
                setConsoleColor(4);
                cout << "Phone Number should contain 11 characters ";
                setConsoleColor(6);
                cout << ":(" << endl;
                ok = false;
            }
            for (int i = 0; i < phone.length(); ++i)
            {
                if (!isdigit(phone[i]))
                {
                    setConsoleColor(4);
                    cout << "Phone Number should contain only digits ";
                    setConsoleColor(6);
                    cout << ":(" << endl;
                    ok = false;
                    break;
                }
            }
        } while (!ok);

        cout << endl;
        // city
        setConsoleColor(6);
        cout << "City : ";
        setConsoleColor(11);
        getline(cin, city);
        cout << endl;

        fout_login << user_name << endl;
        fout_login << password << endl;
        fout_login << age << endl;
        fout_login << email_address << endl;
        fout_login << gender << endl;
        fout_login << phone << endl;
        fout_login << city << endl;

        system("cls");
        cout << " \n\n\n\t\t\t";
        setConsoleColor(5);
        cout << user_name;
        setConsoleColor(10);
        cout << " your INSTAGRAM account has been created successfully ";
        setConsoleColor(6);
        cout << ";)" << endl;
        system("cls");

        fout_login.close();
    }
    bool is_unique_username(const string& user_name)
    {
        ifstream fin_login("login.txt");
        string line;

        while (getline(fin_login, line))
        {
            if (line == user_name)
            {

                fin_login.close();
                return false;
            }
            for (int i = 0; i < 5; ++i)
            {
                getline(fin_login, line);
            }
        }

        fin_login.close();
        return true;
    }

};

class NotificationQueue {
private:
    struct NotificationNode {
        string message;
        NotificationNode* next;

        NotificationNode(const string& msg) : message(msg), next(nullptr) {}
    };

    NotificationNode* front;
    NotificationNode* rear;

public:
    NotificationQueue() : front(nullptr), rear(nullptr) {}

    // Add a notification to the queue
    void addNotification(const string& msg) {
        NotificationNode* newNode = new NotificationNode(msg);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Show all notifications
    void showAllNotifications() {
        if (front == nullptr) {
            setConsoleColor(3);
            cout << "No new notifications.";
            setConsoleColor(6);
            cout << ":(\n";
            return;
        }

        NotificationNode* temp = front;
        setConsoleColor(3);
        cout << "Notifications:\n";
        while (temp != nullptr) {
            setConsoleColor(3);
            cout << "- " << temp->message << endl;
            temp = temp->next;
        }
    }

    // Remove the oldest notification
    void viewNotification() {
        if (front == nullptr) {
            setConsoleColor(3);
            cout << "No new notifications.";
            setConsoleColor(6);
            cout << ":(\n";
            return;
        }

        NotificationNode* temp = front;
        cout << "Notification: " << temp->message << endl;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};


// post

class post_Node
{
public:
    string post;
    post_Node* next;
    string timestamp;

    post_Node()
    {
        cout << "Share Your Post: ";
        cin.ignore();
        cin.clear();
        getline(cin, post);

        timestamp = getCurrentTimestamp();
        next = NULL;
    }
};
class post_stack
{
public:
    post_Node* top;
    post_stack()
    {
        top = NULL;
    }
    void push()
    {
        if (top == NULL)
        {
            top = new post_Node();
            return;
        }
        post_Node* temp = top;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp = new post_Node();
        top = temp;

    }
    void pop(const string& username)
    {
        if (top == NULL)
        {
            cout << "No posts from ";
            setConsoleColor(5);
            cout << username;
            setConsoleColor(6);
            cout << ";(" << endl;
            return;
        }

        ofstream fout("post.txt", ios::app);
        if (!fout)
        {
            setConsoleColor(2);
            cout << "Error: Could not write to post.txt";
            setConsoleColor(6);
            cout << ";(" << endl;
            return;
        }

        fout << "Username: ";
        fout << username << endl;

        fout << "Post: ";

        fout << top->post << endl;

        fout << "Date and Time: ";

        fout << top->timestamp << endl;

        fout << "---END---" << endl;
        fout.close();

        post_Node* temp = top;
        top = top->next;
        delete temp;
    }

    void show_post(const string& username)
    {
        ifstream fin_post("post.txt");
        if (!fin_post)
        {
            setConsoleColor(2);
            cout << "Error: Could not open post.txt";
            setConsoleColor(6);
            cout << ":(\n";
            return;
        }
        string line;
        bool userFound = false;
        while (getline(fin_post, line))
        {
            if (line == "Username: " + username)
            {
                userFound = true;

                cout << line << endl;
                while (getline(fin_post, line) && line != "---END---")
                {
                    setConsoleColor(3);
                    cout << line << endl;
                }
            }
        }

        if (!userFound)
        {
            cout << "No posts found for " << username << endl;
        }

        fin_post.close();
    }


};


void displayPostsForUserAndFriends(const string& username) {
    ifstream graphFile("graph.txt");
    if (!graphFile) {
        cout << "Error: Could not open graph.txt\n";
        return;
    }

    string line;
    post_stack userPosts;

    while (getline(graphFile, line)) {
        size_t pos = line.find("->");
        if (pos == string::npos) continue;

        string user1 = line.substr(0, pos - 1);
        string user2 = line.substr(pos + 3);

        if (user1 == username) {
            cout << "Displaying posts for friend: " << user2 << endl;
            userPosts.show_post(user2);
        }

    }

    graphFile.close();
}

class message_node
{
public:
    string message;
    string to;
    string timestamp;
    message_node* next;

    message_node()
    {
        getMessage();
        getRecipient();
        setTimestamp();
        next = NULL;
    }

private:
    void getMessage()
    {
        cout << "Message: ";
        cin.ignore();
        getline(cin, message);
    }

    void getRecipient()
    {
        while (true)
        {
            cout << "To: ";
            getline(cin, to);

            if (isValidRecipient(to))
                break;

            cout << "User does not exist. Please try again." << endl;
        }
    }

    bool isValidRecipient(const string& recipient)
    {
        ifstream fin("name.txt");
        string line;

        while (fin >> line)
        {
            if (line == recipient)
                return true;
        }

        return false;
    }

    void setTimestamp()
    {
        time_t now;
        char dt[26];
        now = time(0);
        if (ctime_s(dt, sizeof(dt), &now) != 0)
        {
            cerr << "Error converting time to string." << endl;
            dt[0] = '\0';
        }
        timestamp = string(dt);
    }
};
class message_stack
{
    NotificationQueue notifications;
public:
    message_node* top;

    message_stack()
    {
        top = NULL;
    }

    void push()
    {
        message_node* new_node = new message_node();

        if (top == NULL)
        {
            top = new_node;
        }
        else
        {
            new_node->next = top;
            top = new_node;
        }
    }


    void pop(const string& username)
    {
        if (top == NULL)
        {
            cout << "No message" << endl;
            return;
        }

        ofstream fout("message.txt", ios::app);
        if (!fout.is_open())
        {
            cout << "Failed to open message file" << endl;
            return;
        }

        fout << "To: " << top->to << endl;
        fout << "From: " << username << endl;
        fout << "Message: " << top->message << endl;
        fout << "Date and Time: " << top->timestamp << endl;
        fout << "----------------------" << endl;
        fout.close();

        message_node* temp = top;
        top = top->next;
        delete temp;
    }

    void show_message(const string& username)
    {
        ifstream fin_message("message.txt");
        string line;
        bool userFound = false;
        while (getline(fin_message, line))
        {
            if (line == "To: " + username)
            {
                userFound = true;
                cout << line << endl;
                while (getline(fin_message, line) && line != "----------------------")
                {
                    cout << line << endl;
                }
            }
        }

        if (!userFound)
        {
            cout << "No Message found for " << username << endl;
        }

        fin_message.close();
    }

    void showNotifications() {
        notifications.showAllNotifications();
    }
};


class FollowRequest {
private:
    NotificationQueue notifications;
    struct Request {
        string sender;
        string receiver;
        string status;
    };

    void updateFile(const string& filename, const string& sender, const string& receiver, const string& status) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            setConsoleColor(2);
            cout << "Error: Unable to open file." << endl;
            return;
        }
        file << sender << "," << receiver << "," << status << endl;
        file.close();
    }

    bool updateRequestStatus(const string& filename, const string& sender, const string& receiver, const string& newStatus) {
        ifstream file(filename);
        ofstream tempFile("temp_friends.txt");

        if (!file.is_open() || !tempFile.is_open())
        {
            setConsoleColor(2);
            cout << "Error: Unable to open file." << endl;
            return false;
        }

        bool requestFound = false;
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');

            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
                tempFile << line << endl;
                continue;
            }

            string senderInFile = line.substr(0, pos1);
            string receiverInFile = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string statusInFile = line.substr(pos2 + 1);

            if (senderInFile == sender && receiverInFile == receiver && statusInFile == "pending") {
                tempFile << senderInFile << "," << receiverInFile << "," << newStatus << endl;
                requestFound = true;
            }
            else {
                tempFile << line << "\n";
            }
        }

        file.close();
        tempFile.close();

        remove(filename.c_str());
        rename("temp_friends.txt", filename.c_str());

        return requestFound;
    }

public:
    void sendRequest(const string& sender, const string& receiver) {
        if (!Search(receiver))
        {
            setConsoleColor(2);
            cout << "Error: Receiver does not exist.";
            setConsoleColor(6);
            cout << ";(" << endl;
            return;
        }

        ofstream file("friends.txt", ios::app);
        if (file.is_open()) {
            file << sender << "," << receiver << ",pending request" << endl;
            file.close();
            cout << "Friend request sent to " << receiver << "." << endl;
        }
        else {
            setConsoleColor(2);
            cout << "Error: Unable to open 'friends.txt' for writing.";
            setConsoleColor(6);
            cout << ";(" << endl;
        }
    }

    void acceptRequest(const string& receiver, const string& sender) {
        ifstream file("friends.txt");
        if (!file.is_open()) {
            setConsoleColor(2);
            cout << "Error: Unable to open 'friends.txt' for reading.";
            setConsoleColor(6);
            cout << ";(" << endl;
            return;
        }

        ofstream tempFile("temp_friends.txt");
        if (!tempFile.is_open())
        {
            setConsoleColor(2);
            cout << "Error: Unable to open 'temp_friends.txt' for writing.";
            setConsoleColor(6);
            cout << ";(" << endl;
            file.close();
            return;
        }

        bool requestFound = false;
        string line;

        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');

            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
                tempFile << line << endl;
                continue;
            }

            string senderName = line.substr(0, pos1);
            string receiverName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string status = line.substr(pos2 + 1);

            if (receiverName == receiver && senderName == sender && status == "pending request") {
                tempFile << senderName << "," << receiverName << ",accepted" << endl;
                requestFound = true;
            }
            else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        remove("friends.txt");
        rename("temp_friends.txt", "friends.txt");

        if (requestFound)
        {
            setConsoleColor(3);
            cout << "Friend request from '";
            setConsoleColor(5);
            cout << sender;
            setConsoleColor(3);
            cout << "' accepted successfully.";
            setConsoleColor(6);
            cout << ";)" << endl;
            createGraphFromRequests();
        }
        else {
            setConsoleColor(9);
            cout << "No pending friend request from '" << sender << "' found.";
            setConsoleColor(6);
            cout << ";(" << endl;
        }
    }

    bool Search(const string& friendName) {
        ifstream file("login.txt");
        string line;
        while (getline(file, line)) {
            if (line == friendName) {
                return true;
            }
        }
        return false;
    }


    void showPendingRequests(const string& currentUser) {
        ifstream file("friends.txt");
        if (!file.is_open())
        {
            setConsoleColor(2);
            cout << "Error: Unable to open 'friends.txt' for reading.";
            setConsoleColor(6);
            cout << ";(" << endl;
            return;
        }

        string line;
        bool foundRequest = false;

        cout << "\nPending requests for " << currentUser << ":" << endl;

        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');

            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
                continue;
            }

            string sender = line.substr(0, pos1);
            string receiver = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string status = line.substr(pos2 + 1);

            if (receiver == currentUser && status == "pending request")
            {
                setConsoleColor(3);
                cout << "Request from: ";
                setConsoleColor(5);
                cout << sender;
                setConsoleColor(3);
                cout << " Status: ";
                setConsoleColor(6);
                cout << status << endl;
                foundRequest = true;
            }
        }

        if (!foundRequest) {
            cout << "No pending requests." << endl;
            setConsoleColor(6);
            cout << ";(" << endl;
        }

        file.close();
    }

    void createGraphFromRequests() {
        ifstream friendsFile("friends.txt");
        ofstream graphFile("graph.txt");

        if (!friendsFile.is_open())
        {
            setConsoleColor(2);
            cout << "Error: Unable to open 'friends.txt'.";
            setConsoleColor(6);
            cout << ";(" << endl;
            return;
        }

        if (!graphFile.is_open())
        {
            setConsoleColor(2);
            cout << "Error: Unable to open 'graph.txt'.";
            setConsoleColor(6);
            cout << ";(" << endl;
            friendsFile.close();
            return;
        }

        string line;

        while (getline(friendsFile, line)) {
            int pos1 = -1, pos2 = -1;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos1 = i;
                    break;
                }
            }

            for (int i = line.length() - 1; i >= 0; i--) {
                if (line[i] == ',') {
                    pos2 = i;
                    break;
                }
            }

            if (pos1 == -1 || pos2 == -1 || pos1 == pos2) {
                continue;
            }
            string user = line.substr(0, pos1);
            string friendName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string status = line.substr(pos2 + 1);

            if (status == "accepted") {
                graphFile << user << " -> " << friendName << endl;
                graphFile << friendName << " -> " << user << endl;
            }
        }

        friendsFile.close();
        graphFile.close();
        setConsoleColor(2);
        cout << "Graph edges saved to 'graph.txt'." << endl;
    }
    void showNotifications() {
        notifications.showAllNotifications();
    }

};


class user_node
{
public:
    string data;
    user_node* left;
    user_node* right;

    user_node(string val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }

};
class BST
{
private:
    user_node* root;


    user_node* insert(user_node* node, string value)
    {
        if (node == NULL)
        {
            return new user_node(value);
        }
        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }
        return node;
    }
    bool search(user_node* node, const string& st)
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->data == st)
        {
            return true;
        }
        if (st < node->data)
        {
            return search(node->left, st);
        }
        else
        {
            return search(node->right, st);
        }
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(const string& value)
    {
        root = insert(root, value);
    }

    bool search(const string& st)
    {
        return search(root, st);
    }
};

bool Search(const string& st)
{
    ifstream fin_name("name.txt");
    if (!fin_name)
    {
        setConsoleColor(2);

        cout << "Error: Unable to open file 'name.txt'.";
        setConsoleColor(6);
        cout << ";(" << endl;
        return 0;
    }

    BST bst;
    string line;


    while (getline(fin_name, line))
    {
        bst.insert(line);
    }
    fin_name.close();

    if (bst.search(st))
    {
        setConsoleColor(3);
        cout << st;
        setConsoleColor(2);
        cout << " Found" << endl;
        return 1;
    }
    else
    {
        setConsoleColor(2);
        cout << st << " Not Found";
        setConsoleColor(6);
        cout << ":(";

        return 0;
    }
}

class Login
{
private:
    string currentUser;
    message_stack& messageStack;
    post_stack postStack;
    Signup& signupHandler;
    FollowRequest follow;

public:
    Login(message_stack& msgStack, Signup& signup)
        : messageStack(msgStack), signupHandler(signup) {}

    bool authenticate()
    {
        string username, password;
        bool loggedIn = false;
        setConsoleColor(6);
        cout << "\nEnter username: ";
        setConsoleColor(11);
        cin >> username;
        setConsoleColor(6);
        cout << "Enter password: ";
        setConsoleColor(11);
        cin >> password;

        ifstream fin("login.txt");
        string line;
        while (getline(fin, line))
        {
            if (line == username)
            {
                getline(fin, line);
                if (line == password)
                {
                    loggedIn = true;
                    currentUser = username;
                    setConsoleColor(2);
                    cout << "\nLogin successful." << endl;
                    break;
                }
            }
        }

        if (!loggedIn)
        {
            setConsoleColor(4);
            cout << "\nInvalid username or password." << endl;
        }

        return loggedIn;
    }

    void showMenu()
    {
        if (currentUser.empty())
        {
            setConsoleColor(4);
            cout << "No user is currently logged in." << endl;
            return;
        }

        int userChoice;
        do
        {

            setConsoleColor(11);
            cout << "\t\t\t-------";
            setConsoleColor(6);
            cout << "MENU";
            setConsoleColor(11);
            cout << "-------- - \n" << endl;
            setConsoleColor(11);
            cout << "\nLogged in as ";
            setConsoleColor(5);
            cout << currentUser << endl;
            setConsoleColor(11);
            cout << "\t\t\t1. Send Friend Request" << endl;
            cout << "\t\t\t2. Display NewsFeed" << endl;
            cout << "\t\t\t3. Send Message" << endl;
            cout << "\t\t\t4. Show Messages" << endl;
            cout << "\t\t\t5. Share a Post" << endl;
            cout << "\t\t\t6. Search User" << endl;
            cout << "\t\t\t7. Notifications" << endl;
            cout << "\t\t\t8. Accept Friend Request" << endl;
            cout << "\t\t\t9. Logout" << endl;
            setConsoleColor(6);
            cout << "Enter your choice: ";
            setConsoleColor(11);
            cin >> userChoice;
            cin.ignore();
            system("cls");
            if (cin.fail())
            {
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                setConsoleColor(2);
                cout << "Invalid input. Please enter a valid choice." << endl;
                continue;
            }
            switch (userChoice)
            {
            case 1:
            {
                string friendName;
                setConsoleColor(6);
                cout << "Enter friend's name: ";
                setConsoleColor(11);
                getline(cin, friendName);

                if (Search(friendName))
                {
                    follow.sendRequest(currentUser, friendName);
                }
                else
                {
                    setConsoleColor(4);
                    cout << "User '";
                    setConsoleColor(5);
                    cout << friendName;
                    setConsoleColor(4);
                    cout << "' not found." << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Displaying posts for user: " << currentUser << endl;
                postStack.show_post(currentUser);
                displayPostsForUserAndFriends(currentUser);
                break;
            }
            case 3:
                messageStack.push();
                messageStack.pop(currentUser);
                break;
            case 4:
                messageStack.show_message(currentUser);
                break;
            case 5:
                postStack.push();
                postStack.pop(currentUser);
                break;
            case 6:
            {
                string searchName;
                char cho;
                setConsoleColor(6);
                cout << "Enter username to search: ";
                setConsoleColor(11);
                getline(cin, searchName);

                if (Search(searchName))
                {
                }
                else
                {
                    setConsoleColor(2);
                    cout << "User '" << searchName << "' not found." << endl;
                }
                break;
            }
            case 7:
                setConsoleColor(11);
                cout << "Showing notifications for ";
                setConsoleColor(5);
                cout << currentUser;
                setConsoleColor(11);
                cout << "..." << endl;
                messageStack.show_message(currentUser);
                follow.showPendingRequests(currentUser);
                break;
            case 8:
            {
                string friendName;
                follow.showPendingRequests(currentUser);
                cout << "Enter Friend Name to accept request: ";
                cin >> friendName;

                follow.acceptRequest(currentUser, friendName);
                break;
            }
            case 9:
                setConsoleColor(13);
                cout << "Logging out..." << endl;
                currentUser.clear();
                break;
            default:
                setConsoleColor(2);
                cout << "Invalid choice. Try again.";
                setConsoleColor(6);
                cout << ":(" << endl;
            }
        } while (userChoice != 9);
    }

};
int main()
{
    int numUsers = 10;
    message_stack ms;
    Signup s;
    Login loginHandler(ms, s);
    int choice;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set text color to red (foreground: red, background: black)
    SetConsoleTextAttribute(hConsole, 12);
    cout << "\n\n\n\n\n";
    // Print each line explicitly, centering with std::setw
    cout << setw((80 - 19) / 2 + 19) << "                               *******************" << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *************  * " << endl;
    //cout << setw((80 - 23) / 2 + 23) << " *  *           *   " << endl;
    //cout << setw((80 - 23) / 2 + 23) << " *  *           *  * " << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *           *  * " << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *    ***    *  * " << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *   *   *   *  * " << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *    ***    *  * " << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *           *  * " << endl;
    //cout << setw((80 - 23) / 2 + 23) << " *  *           *  * " << endl;
    //cout << setw((80 - 23) / 2 + 23) << " *  *           *  * " << endl;
    cout << setw((80 - 23) / 2 + 23) << " *  *************  * " << endl;

    cout << setw((80 - 19) / 2 + 19) << "                               *******************" << endl;
    cout << "\n\n\n\n\n";
    SetConsoleTextAttribute(hConsole, 8);
    cout << setw(55) << "Welcome to Instagram Buddy";
    setConsoleColor(06);
    cout << ";)" << endl;

    // Reset text color to default (white text on black background)
    SetConsoleTextAttribute(hConsole, 7);

    // Pause for 6 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("cls");
    do
    {
        setConsoleColor(11);

        cout << "\n\t\t\t----------";
        SetConsoleTextAttribute(hConsole, 6);
        cout << "INSTAGRAM";
        setConsoleColor(11);
        cout << "----------" << endl;
        cout << "\t\t\t1. Sign up" << endl;
        cout << "\t\t\t2. Login" << endl;
        cout << "\t\t\t3. Exit" << endl;
        setConsoleColor(06);
        cout << "Enter your choice: ";
        setConsoleColor(11);
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setConsoleColor(04);
            cout << "Invalid input. Please enter a valid choice." << endl;
            setConsoleColor(06);
            continue;
        }
        switch (choice)
        {
        case 1:
            s.signup();
            break;

        case 2:
        {
            if (loginHandler.authenticate())
            {
                loginHandler.showMenu();
            }
            break;
        }

        case 3:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);
          system("pause");
    return 0;
}
