#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelist.h"  // Includes the FileRec definition and extern lists

// Function to create a new file. Allocates memory for name, bytes, and sets size/suspicious.
FileRec* create_file(const char *name, const unsigned char *data, size_t size) {
    FileRec* new_file = (FileRec*)malloc(sizeof(FileRec));
    if (!new_file) {
        printf("Error: Not enough memory to create the file!\n");
        return NULL;
    }
    new_file->name = strdup(name);  // Copy the name
    new_file->size = size;
    if (data && size > 0) {
        new_file->bytes = (unsigned char*)malloc(size);
        if (!new_file->bytes) {
            printf("Error: Not enough memory for file bytes!\n");
            free(new_file->name);
            free(new_file);
            return NULL;
        }
        memcpy(new_file->bytes, data, size);  // Copy the data
    } else {
        new_file->bytes = NULL;  // No data provided
    }
    new_file->suspicious = 0;  // Default to clean
    new_file->next = NULL;
    return new_file;
}

// Add a file to the head of the list.
void insert_file(FileRec **head, FileRec *node) {
    if (!node) return;
    node->next = *head;
    *head = node;
}

// Remove a file by name and return it (or NULL if not found).
FileRec* remove_file(FileRec **head, const char *name) {
    FileRec* current = *head;
    FileRec* prev = NULL;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            return current;  // Return the removed node
        }
        prev = current;
        current = current->next;
    }
    return NULL;  // Not found
}

// Find a file by name.
FileRec* find_file(FileRec *head, const char *name) {
    FileRec* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Move a file from one list to another.
void move_file(FileRec **from, FileRec **to, const char *name) {
    FileRec* file = remove_file(from, name);  // Remove and get the node
    if (file) {
        insert_file(to, file);  // Insert into the destination
    }
}

// Print the list with a title. Shows name, size, and if bytes are present.
void print_list(const char *title, FileRec *head) {
    printf("%s:\n", title);
    FileRec* current = head;
    if (!current) {
        printf("  (Empty list)\n");
        return;
    }
    while (current) {
        printf("  File: %s, Size: %zu bytes, Suspect: %s, Has Bytes: %s\n",
               current->name, current->size, current->suspicious ? "yes" : "no",
               current->bytes ? "yes" : "no");
        current = current->next;
    }
}

// Free the entire list, including name and bytes.
void free_list(FileRec **head) {
    FileRec* current = *head;
    while (current) {
        FileRec* temp = current;
        current = current->next;
        free(temp->name);
        if (temp->bytes) free(temp->bytes);
        free(temp);
    }
    *head = NULL;
}

// Small main for testing (as per step 2). Simulates the global lists.
int main() {
    // Simulate global lists (in a real project, these would be defined elsewhere)
    FileRec* Clean = NULL;
    FileRec* Suspect = NULL;
    FileRec* Quarantine = NULL;

    printf("=== Step 2 Test: File Management ===\n");

    // Sample data for testing
    unsigned char sample_data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};  // "Hello" in hex
    size_t sample_size = sizeof(sample_data);

    // 1. Create and insert files
    printf("Creating and inserting files...\n");
    FileRec* f1 = create_file("virus.exe", sample_data, sample_size);
    FileRec* f2 = create_file("safe.txt", NULL, 0);  // No data
    insert_file(&Clean, f1);
    insert_file(&Clean, f2);
    print_list("Clean List", Clean);

    // 2. Find a file
    printf("\nSearching for 'virus.exe'...\n");
    FileRec* found = find_file(Clean, "virus.exe");
    if (found) {
        printf("Found: %s\n", found->name);
    } else {
        printf("Not found.\n");
    }

    // 3. Move a file to Suspect
    printf("\nMoving 'virus.exe' to Suspect...\n");
    move_file(&Clean, &Suspect, "virus.exe");
    print_list("Clean List", Clean);
    print_list("Suspect List", Suspect);

    // 4. Remove a file (and show it was removed)
    printf("\nRemoving 'virus.exe' from Suspect...\n");
    FileRec* removed = remove_file(&Suspect, "virus.exe");
    if (removed) {
        printf("Removed: %s\n", removed->name);
        free(removed->name);
        if (removed->bytes) free(removed->bytes);
        free(removed);
    }
    print_list("Suspect List", Suspect);

    // 5. Clean up
    printf("\nFreeing memory...\n");
    free_list(&Clean);
    free_list(&Suspect);
    free_list(&Quarantine);
    printf("All cleaned up!\n");

    return 0;
}