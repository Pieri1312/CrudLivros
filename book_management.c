/**
 * Book Management System - CRUD application in C
 * 
 * This program implements a console-based book management system with CRUD operations.
 * Features include:
 * - Adding new books
 * - Listing all books
 * - Searching for books
 * - Updating book information
 * - Deleting books
 * - Sorting books by various criteria
 * - Binary search for efficient lookups
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_ISBN_LENGTH 20
#define MAX_INPUT_LENGTH 100

// Structure to represent a book
typedef struct {
    int id;                         // Unique identifier for the book
    char title[MAX_TITLE_LENGTH];   // Book title
    char author[MAX_AUTHOR_LENGTH]; // Book author
    char isbn[MAX_ISBN_LENGTH];     // ISBN number
    int year;                       // Publication year
    float price;                    // Book price
    int available;                  // Flag to indicate if the book is currently available (1) or not (0)
} Book;

// Global variables
Book library[MAX_BOOKS];  // Array to store books
int bookCount = 0;        // Current number of books in the library
int nextId = 1;           // ID to assign to the next book

// Function declarations
void clearInputBuffer();
void waitForEnter();
void displayMenu();
void addBook();
void listAllBooks();
void searchBookById();
void searchBookByTitle();
void updateBook();
void deleteBook();
void sortBooks();
int binarySearchById(int id, int start, int end);
int binarySearchByTitle(const char* title, int start, int end);
void swapBooks(int i, int j);
void bubbleSortById();
void bubbleSortByTitle();
void bubbleSortByAuthor();
void bubbleSortByYear();
int validateInput();
int getIntInput(const char* prompt);
float getFloatInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, int maxLength);
int searchBookIndexById(int id);
int searchBookIndexByTitle(const char* title);
void displayBook(const Book* book);

int main() {
    int choice;
    
    printf("===================================\n");
    printf("  BOOK MANAGEMENT SYSTEM\n");
    printf("===================================\n");
    printf("Welcome to the Book Management System!\n\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                listAllBooks();
                break;
            case 3:
                searchBookById();
                break;
            case 4:
                searchBookByTitle();
                break;
            case 5:
                updateBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                sortBooks();
                break;
            case 0:
                printf("Thank you for using Book Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        if (choice != 0) {
            waitForEnter();
        }
        
    } while (choice != 0);
    
    return 0;
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to wait for Enter key
void waitForEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

// Function to display the main menu
void displayMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Add a new book\n");
    printf("2. List all books\n");
    printf("3. Search a book by ID\n");
    printf("4. Search a book by title\n");
    printf("5. Update a book\n");
    printf("6. Delete a book\n");
    printf("7. Sort books\n");
    printf("0. Exit\n");
}

// Function to add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Error: Library is full. Cannot add more books.\n");
        return;
    }
    
    printf("\n===== ADD A NEW BOOK =====\n");
    
    Book newBook;
    newBook.id = nextId++;
    
    getStringInput("Enter title", newBook.title, MAX_TITLE_LENGTH);
    getStringInput("Enter author", newBook.author, MAX_AUTHOR_LENGTH);
    getStringInput("Enter ISBN", newBook.isbn, MAX_ISBN_LENGTH);
    
    newBook.year = getIntInput("Enter publication year");
    newBook.price = getFloatInput("Enter price");
    newBook.available = 1;  // New book is available by default
    
    library[bookCount++] = newBook;
    
    printf("\nBook added successfully with ID: %d\n", newBook.id);
}

// Function to list all books
void listAllBooks() {
    printf("\n===== ALL BOOKS =====\n");
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    printf("Total books: %d\n\n", bookCount);
    printf("%-5s %-30s %-25s %-15s %-6s %-10s %-10s\n", 
           "ID", "Title", "Author", "ISBN", "Year", "Price", "Available");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < bookCount; i++) {
        Book book = library[i];
        printf("%-5d %-30s %-25s %-15s %-6d $%-9.2f %s\n", 
               book.id, book.title, book.author, book.isbn, book.year, book.price, 
               (book.available ? "Yes" : "No"));
    }
}

// Function to search a book by ID (using binary search)
void searchBookById() {
    printf("\n===== SEARCH BOOK BY ID =====\n");
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    int id = getIntInput("Enter book ID to search");
    
    // Sort books by ID before binary search
    bubbleSortById();
    
    int index = binarySearchById(id, 0, bookCount - 1);
    
    if (index != -1) {
        printf("\nBook found:\n");
        displayBook(&library[index]);
    } else {
        printf("\nBook with ID %d not found.\n", id);
    }
}

// Function to search a book by title
void searchBookByTitle() {
    printf("\n===== SEARCH BOOK BY TITLE =====\n");
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    char title[MAX_TITLE_LENGTH];
    getStringInput("Enter book title to search", title, MAX_TITLE_LENGTH);
    
    // Sort books by title before binary search
    bubbleSortByTitle();
    
    int index = binarySearchByTitle(title, 0, bookCount - 1);
    
    if (index != -1) {
        printf("\nBook found:\n");
        displayBook(&library[index]);
    } else {
        printf("\nBook with title '%s' not found.\n", title);
    }
}

// Function to update a book
void updateBook() {
    printf("\n===== UPDATE BOOK =====\n");
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    int id = getIntInput("Enter book ID to update");
    
    int index = searchBookIndexById(id);
    
    if (index == -1) {
        printf("\nBook with ID %d not found.\n", id);
        return;
    }
    
    printf("\nCurrent book details:\n");
    displayBook(&library[index]);
    
    printf("\nEnter new details (leave blank to keep current value):\n");
    
    char input[MAX_INPUT_LENGTH];
    
    getStringInput("Enter new title", input, MAX_TITLE_LENGTH);
    if (input[0] != '\0') {
        strcpy(library[index].title, input);
    }
    
    getStringInput("Enter new author", input, MAX_AUTHOR_LENGTH);
    if (input[0] != '\0') {
        strcpy(library[index].author, input);
    }
    
    getStringInput("Enter new ISBN", input, MAX_ISBN_LENGTH);
    if (input[0] != '\0') {
        strcpy(library[index].isbn, input);
    }
    
    printf("Enter new publication year (current: %d, leave blank to keep): ", library[index].year);
    fgets(input, MAX_INPUT_LENGTH, stdin);
    if (input[0] != '\n') {
        int year = atoi(input);
        if (year > 0) {
            library[index].year = year;
        }
    }
    
    printf("Enter new price (current: %.2f, leave blank to keep): ", library[index].price);
    fgets(input, MAX_INPUT_LENGTH, stdin);
    if (input[0] != '\n') {
        float price = atof(input);
        if (price >= 0) {
            library[index].price = price;
        }
    }
    
    printf("Is the book available? (1 for yes, 0 for no, current: %d, leave blank to keep): ", 
           library[index].available);
    fgets(input, MAX_INPUT_LENGTH, stdin);
    if (input[0] != '\n') {
        int available = atoi(input);
        if (available == 0 || available == 1) {
            library[index].available = available;
        }
    }
    
    printf("\nBook updated successfully.\n");
}

// Function to delete a book
void deleteBook() {
    printf("\n===== DELETE BOOK =====\n");
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    int id = getIntInput("Enter book ID to delete");
    
    int index = searchBookIndexById(id);
    
    if (index == -1) {
        printf("\nBook with ID %d not found.\n", id);
        return;
    }
    
    printf("\nBook to delete:\n");
    displayBook(&library[index]);
    
    char confirmation;
    printf("\nAre you sure you want to delete this book? (y/n): ");
    scanf("%c", &confirmation);
    clearInputBuffer();
    
    if (tolower(confirmation) == 'y') {
        // Shift all elements after the deleted book one position back
        for (int i = index; i < bookCount - 1; i++) {
            library[i] = library[i + 1];
        }
        bookCount--;
        printf("\nBook deleted successfully.\n");
    } else {
        printf("\nDeletion cancelled.\n");
    }
}

// Function to display a book
void displayBook(const Book* book) {
    printf("ID: %d\n", book->id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("ISBN: %s\n", book->isbn);
    printf("Publication Year: %d\n", book->year);
    printf("Price: $%.2f\n", book->price);
    printf("Available: %s\n", (book->available ? "Yes" : "No"));
}

// Function to swap two books in the array
void swapBooks(int i, int j) {
    Book temp = library[i];
    library[i] = library[j];
    library[j] = temp;
}

// Function to sort books by ID using bubble sort
void bubbleSortById() {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (library[j].id > library[j + 1].id) {
                swapBooks(j, j + 1);
            }
        }
    }
}

// Function to sort books by title using bubble sort
void bubbleSortByTitle() {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (strcmp(library[j].title, library[j + 1].title) > 0) {
                swapBooks(j, j + 1);
            }
        }
    }
}

// Function to sort books by author using bubble sort
void bubbleSortByAuthor() {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (strcmp(library[j].author, library[j + 1].author) > 0) {
                swapBooks(j, j + 1);
            }
        }
    }
}

// Function to sort books by year using bubble sort
void bubbleSortByYear() {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (library[j].year > library[j + 1].year) {
                swapBooks(j, j + 1);
            }
        }
    }
}

// Function to sort books menu
void sortBooks() {
    printf("\n===== SORT BOOKS =====\n");
    
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    printf("Sort by:\n");
    printf("1. ID\n");
    printf("2. Title\n");
    printf("3. Author\n");
    printf("4. Publication Year\n");
    
    int choice = getIntInput("Enter your choice");
    
    switch (choice) {
        case 1:
            bubbleSortById();
            printf("\nBooks sorted by ID.\n");
            break;
        case 2:
            bubbleSortByTitle();
            printf("\nBooks sorted by title.\n");
            break;
        case 3:
            bubbleSortByAuthor();
            printf("\nBooks sorted by author.\n");
            break;
        case 4:
            bubbleSortByYear();
            printf("\nBooks sorted by publication year.\n");
            break;
        default:
            printf("\nInvalid choice. Books not sorted.\n");
            return;
    }
    
    listAllBooks();
}

// Function to perform binary search by ID
int binarySearchById(int id, int start, int end) {
    if (start > end) {
        return -1;  // Not found
    }
    
    int mid = start + (end - start) / 2;
    
    if (library[mid].id == id) {
        return mid;  // Found at index mid
    }
    
    if (library[mid].id > id) {
        return binarySearchById(id, start, mid - 1);  // Search in left half
    } else {
        return binarySearchById(id, mid + 1, end);  // Search in right half
    }
}

// Function to perform binary search by title
int binarySearchByTitle(const char* title, int start, int end) {
    if (start > end) {
        return -1;  // Not found
    }
    
    int mid = start + (end - start) / 2;
    
    int comparison = strcmp(library[mid].title, title);
    
    if (comparison == 0) {
        return mid;  // Found at index mid
    }
    
    if (comparison > 0) {
        return binarySearchByTitle(title, start, mid - 1);  // Search in left half
    } else {
        return binarySearchByTitle(title, mid + 1, end);  // Search in right half
    }
}

// Function to search a book by ID using sequential search
int searchBookIndexById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            return i;
        }
    }
    return -1;  // Not found
}

// Function to search a book by title using sequential search
int searchBookIndexByTitle(const char* title) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].title, title) == 0) {
            return i;
        }
    }
    return -1;  // Not found
}

// Function to get integer input with validation
int getIntInput(const char* prompt) {
    char input[MAX_INPUT_LENGTH];
    int value;
    
    while (1) {
        printf("%s: ", prompt);
        fgets(input, MAX_INPUT_LENGTH, stdin);
        
        // Remove newline character
        input[strcspn(input, "\n")] = '\0';
        
        // Check if input is empty
        if (input[0] == '\0') {
            printf("Error: Input cannot be empty. Please try again.\n");
            continue;
        }
        
        // Check if input is a valid integer
        char* endptr;
        value = strtol(input, &endptr, 10);
        
        if (*endptr != '\0') {
            printf("Error: Invalid input. Please enter a number.\n");
            continue;
        }
        
        break;
    }
    
    return value;
}

// Function to get float input with validation
float getFloatInput(const char* prompt) {
    char input[MAX_INPUT_LENGTH];
    float value;
    
    while (1) {
        printf("%s: ", prompt);
        fgets(input, MAX_INPUT_LENGTH, stdin);
        
        // Remove newline character
        input[strcspn(input, "\n")] = '\0';
        
        // Check if input is empty
        if (input[0] == '\0') {
            printf("Error: Input cannot be empty. Please try again.\n");
            continue;
        }
        
        // Check if input is a valid float
        char* endptr;
        value = strtof(input, &endptr);
        
        if (*endptr != '\0') {
            printf("Error: Invalid input. Please enter a number.\n");
            continue;
        }
        
        break;
    }
    
    return value;
}

// Function to get string input with validation
void getStringInput(const char* prompt, char* buffer, int maxLength) {
    while (1) {
        printf("%s: ", prompt);
        fgets(buffer, maxLength, stdin);
        
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Check if input is empty (allow empty for update operation)
        if (buffer[0] == '\0' && strcmp(prompt, "Enter new title") != 0 && 
            strcmp(prompt, "Enter new author") != 0 && 
            strcmp(prompt, "Enter new ISBN") != 0) {
            printf("Error: Input cannot be empty. Please try again.\n");
            continue;
        }
        
        break;
    }
}
