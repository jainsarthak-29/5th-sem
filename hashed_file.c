#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

struct record {
    int id;
    char name[20];
    int age;
};

struct record hashTable[TABLE_SIZE];

int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void insertRecords() {
    struct record recs[3] = {
        {1, "Alice", 25},
        {2, "Bob", 30},
        {12, "Charlie", 22}
    };

    for (int i = 0; i < 3; i++) {
        int index = hashFunction(recs[i].id);
        while (hashTable[index].id != 0) {
            index = (index + 1) % TABLE_SIZE;
        }
        hashTable[index] = recs[i];
    }
}

void searchRecord(int id) {
    int index = hashFunction(id);
    int startIndex = index;
    while (hashTable[index].id != 0) {
        if (hashTable[index].id == id) {
            printf("Record found - ID: %d, Name: %s, Age: %d\n", hashTable[index].id, hashTable[index].name, hashTable[index].age);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) break;
    }
}

void displayTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].id != 0) {
            printf("Index %d -> ID: %d, Name: %s, Age: %d\n", i, hashTable[i].id, hashTable[i].name, hashTable[i].age);
        }
    }
}

int main() {
    insertRecords();
    searchRecord(12);
    displayTable();
    return 0;
}
