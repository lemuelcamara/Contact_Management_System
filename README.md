# Contact_Management_System

### Project Overview

The Contact Management System is a command-line application designed for efficient storage and manipulation of contact information. Its main purpose is to demonstrate the practical application of data structures and algorithms in managing real-world data, providing features such as contact creation, deletion with undo capabilities, and sorted data visualization.



### Data Structures and Algorithms Used
This application used several core data structures to support its feature set:

* Doubly Linked List 
- Features: Acts as the primary storage for contact records. It supports bidirectional traversal, allowing for efficient insertions at both the front and end of the list.

* Stack 
- Features: Powers the Undo functionality. When a contact is deleted, the pointer to that contact is "pushed" onto the stack. Selecting the undo option "pops" the most recently deleted contact and restores it to the main list.

* Queue 
- Features: Manages the Recent Additions history. Every time a contact is created, it is enqueued, providing a chronological log of added entries separate from the alphabetical list.

* Bubble Sort Algorithm 
- Features: Implements alphabetical sorting by name. It iteratively compares adjacent nodes in the doubly linked list and swaps their data until the entire list is organized.

* Linear Search Algorithm 
- Features: Facilitates the "Search Contact" feature by traversing the linked list from the head until a matching name is found.



### Compilation and Execution Instructions

To run this application, make sure you have a C compiler such as 'Dev C++' installed on your system.

1. Create a New Project or File:

- Open Dev-C++.

- Go to File > New > Source File (or press Ctrl + N).

- Copy the source code from Contact_Management_System.c and paste it into the editor.  
 
- Go to File > Save As, name the file Contact_Management_System.c, and ensure the "Save as type" is set to C source files (*.c).  

2. Configure the Compiler:

- Because the code uses i as a global variable for C89 compatibility, ensure your compiler is set to a standard C profile. 
 
- Go to Tools > Compiler Options.

- In the "Settings" tab, under "Code Generation", ensure "Language standard (-std)" is set to a C standard (like ISO C90 or GNU90) if you encounter errors, though the default "TDM-GCC" settings usually work fine for this code.

3. Compile the Code:

- Go to the Execute menu at the top.

- Select Compile (or press F9).

- Check the "Compile Log" at the bottom of the screen. It should say "Errors: 0" and "Warnings: 0".

4. Run the Application:

- Once compiled, go to Execute > Run (or press F10).

- Alternatively, you can use Compile & Run (press F11) to do both steps at once.

- A console window will appear showing the CONTACT MANAGEMENT SYSTEM menu.
