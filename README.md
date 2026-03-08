# Instagram Buddy (Console Based Social Media Simulation)

Instagram Buddy is a console-based social media simulation developed in C++.  
The project mimics core features of a social networking platform such as user registration, login authentication, friend requests, messaging, notifications, and posting content.

This project demonstrates the practical implementation of various Data Structures and File Handling concepts in C++.

Features

 1. User Authentication
- Sign Up with unique username
- Login with username and password
- User information stored using file handling

2. Friend System
- Send friend requests
- Accept friend requests
- Graph structure used to represent friendships

 3. Messaging System
- Send messages to other users
- Receive messages
- Messages stored with timestamps

 4. Posting System
- Users can create posts
- Posts include timestamp information
- News feed shows posts from the user and their friends

 5. Notifications
- Notification queue for alerts
- Shows new messages and friend requests

 6. User Search
- Search users using Binary Search Tree (BST)



 Data Structures Used

The project demonstrates multiple data structures:

Stack
- Used for managing posts
- Used for managing messages

Queue
- Used for notifications

Binary Search Tree (BST)
- Used for efficient user searching

Graph
- Used to represent friendships between users

Linked List
- Used for message nodes and notification nodes



## File Handling

The program stores data in text files:

login.txt  
Stores user credentials and profile data.

name.txt  
Stores usernames for searching.

friends.txt  
Stores friend requests and friendship status.

graph.txt  
Stores friendship graph.

message.txt  
Stores messages between users.

post.txt  
Stores user posts with timestamps.



 Technologies Used

Language: C++  
Concepts:  
- Object Oriented Programming (OOP)  
- Data Structures  
- File Handling  
- Console UI  
- Dynamic Memory Allocation  


