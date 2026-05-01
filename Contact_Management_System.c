#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Contact {
    char name[50];
    char phone[15];
    struct Contact* prev;
    struct Contact* next;
} Contact;

typedef struct StackNode {
    Contact* data;
    struct StackNode* next;
} StackNode;

typedef struct QueueNode {
    Contact* data;
    struct QueueNode* next;
} QueueNode;

// Global Pointers
Contact* head = NULL;
Contact* tail = NULL;
StackNode* stackTop = NULL;
QueueNode* queueFront = NULL;
QueueNode* queueRear = NULL;

int i; // Global for C89 compatibility

// Function Prototypes
void pushStack(Contact* contact);
Contact* popStack();
int isStackEmpty();
void enqueue(Contact* contact);
int isQueueEmpty();
void insertEnd(Contact* newContact);
void insertFront(Contact* newContact);
void deleteContact(char* name);
void displayList();
int compareNames(const char* name1, const char* name2);
void bubbleSort();
Contact* searchContact(char* name);
void displayQueue();
void displayStack();

// Implementation
int compareNames(const char* name1, const char* name2) {
    char n1[50], n2[50];
    strcpy(n1, name1); strcpy(n2, name2);
    for (i = 0; n1[i]; i++) n1[i] = tolower(n1[i]);
    for (i = 0; n2[i]; i++) n2[i] = tolower(n2[i]);
    return strcmp(n1, n2);
}

void bubbleSort() {
    if (head == NULL) return;
    int swapped;
    Contact* ptr1;
    Contact* lptr = NULL;
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (compareNames(ptr1->name, ptr1->next->name) > 0) {
                char tempName[50], tempPhone[15];
                strcpy(tempName, ptr1->name); strcpy(ptr1->name, ptr1->next->name); strcpy(ptr1->next->name, tempName);
                strcpy(tempPhone, ptr1->phone); strcpy(ptr1->phone, ptr1->next->phone); strcpy(ptr1->next->phone, tempPhone);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Contacts sorted alphabetically by name using bubble sort!\n");
}

Contact* searchContact(char* name) {
    Contact* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}

void insertEnd(Contact* newContact) {
    newContact->next = NULL;
    newContact->prev = tail;
    if (tail == NULL) head = tail = newContact;
    else { tail->next = newContact; tail = newContact; }
    enqueue(newContact);
    printf("Contact '%s' added successfully!\n", newContact->name);
}

void insertFront(Contact* newContact) {
    newContact->prev = NULL;
    newContact->next = head;
    if (head == NULL) head = tail = newContact;
    else { head->prev = newContact; head = newContact; }
    enqueue(newContact);
    printf("Contact '%s' added to front!\n", newContact->name);
}

void deleteContact(char* name) {
    Contact* contact = searchContact(name);
    if (contact == NULL) {
        printf("Contact '%s' not found!\n", name);
        return;
    }
    if (contact->prev != NULL) contact->prev->next = contact->next;
    else head = contact->next;
    if (contact->next != NULL) contact->next->prev = contact->prev;
    else tail = contact->prev;

    pushStack(contact);
    printf("Contact '%s' deleted (can be undone with '9')!\n", name);
}

void displayList() {
    if (head == NULL) { printf("No contacts in the list!\n"); return; }
    printf("\n=== CONTACT LIST ===\n");
    Contact* current = head;
    int index = 1;
    while (current != NULL) {
        printf("%d. Name: %s\n   Phone: %s\n\n", index++, current->name, current->phone);
        current = current->next;
    }
}

void pushStack(Contact* contact) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = contact;
    newNode->next = stackTop;
    stackTop = newNode;
}

Contact* popStack() {
    if (isStackEmpty()) return NULL;
    StackNode* temp = stackTop;
    Contact* contact = temp->data;
    stackTop = stackTop->next;
    free(temp);
    return contact;
}

int isStackEmpty() { return stackTop == NULL; }

void enqueue(Contact* contact) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = contact;
    newNode->next = NULL;
    if (queueRear == NULL) queueFront = queueRear = newNode;
    else { queueRear->next = newNode; queueRear = newNode; }
}

int isQueueEmpty() { return queueFront == NULL; }

void displayQueue() {   
    if (isQueueEmpty()) { printf("No recent additions!\n"); return; }
    printf("\n=== RECENT ADDITIONS (Queue) ===\n");
    QueueNode* current = queueFront;
    int index = 1;
    while (current != NULL) {
        printf("%d. %s\n", index++, current->data->name);
        current = current->next;
    }
}

void displayStack() {
    if (isStackEmpty()) { printf("Undo stack is empty!\n"); return; }
    printf("\n=== DELETED CONTACTS (Undo Stack) ===\n");
    StackNode* current = stackTop;
    int index = 1;
    while (current != NULL) {
        printf("%d. %s\n", index++, current->data->name);
        current = current->next;
    }
}

int main() {
    int choice;
    char name[50];
	char phone[15];
	char searchName[50];
    
    printf("=== CONTACT MANAGEMENT SYSTEM ===\n");
    
    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add Contact (End)\n");
        printf("2. Add Contact (Front)\n");
        printf("3. Display All Contacts\n");
        printf("4. Search Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Sort Contacts (Bubble Sort)\n");
        printf("7. Show Recent Additions (Queue)\n");
        printf("8. Show Deleted (Undo Stack)\n");
        printf("9. Undo Last Delete\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice); 
        getchar(); // Consumes the newline character
        
        switch (choice) {
            case 1:
                printf("Name: "); fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;
                printf("Phone: "); fgets(phone, 15, stdin); phone[strcspn(phone, "\n")] = 0;
                Contact* nc1 = (Contact*)malloc(sizeof(Contact));
                strcpy(nc1->name, name); strcpy(nc1->phone, phone);
                insertEnd(nc1); 
                break;
            case 2:
                printf("Name: "); fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;
                printf("Phone: "); fgets(phone, 15, stdin); phone[strcspn(phone, "\n")] = 0;
                Contact* nc2 = (Contact*)malloc(sizeof(Contact));
                strcpy(nc2->name, name); strcpy(nc2->phone, phone);
                insertFront(nc2); 
                break;
            case 3: displayList(); break;
            case 4:
                printf("Enter name to search: "); fgets(searchName, 50, stdin); searchName[strcspn(searchName, "\n")] = 0;
                Contact* f = searchContact(searchName);
                if (f) printf("FOUND: %s | Phone: %s\n", f->name, f->phone);
                else printf("Contact not found!\n"); 
                break;
            case 5:
                printf("Enter name to delete: "); fgets(searchName, 50, stdin); searchName[strcspn(searchName, "\n")] = 0;
                deleteContact(searchName); 
                break;
            case 6: bubbleSort(); displayList(); break;
            case 7: displayQueue(); break;
            case 8: displayStack(); break;
            case 9: {
                Contact* u = popStack();
                if (u) { insertEnd(u); printf("Restored: %s\n", u->name); }
                else printf("Nothing to undo!\n"); 
                break;
            }
            case 0: 
			exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* Citation: Implementation of Contact Management System and Linked List Logic.
   Surendra, BH. Sai, et al. Contact Management System: Mini Project for 
   C-Programming. Raghu Institute of Technology, 2019. Scribd, 
   www.scribd.com/document/439870540/Contact-management-system-C-programming-project-by-Raghu.
*/	


/* CITATION: Logic for Undo/Redo mechanisms using Stacks and Doubly Linked Lists.
   Reference: Sedgewick, Robert, and Kevin Wayne. "Algorithms, 4th Edition." 
   Pearson Education, 2011. Linked List Implementations.
   Link: https://algs4.cs.princeton.edu/13stacks/
*/
