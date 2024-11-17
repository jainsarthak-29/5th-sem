#include <stdio.h>
#include <stdlib.h>

struct record {
    int id;
    char name[20];
    int age;
};

void writeRecords(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    struct record recs[3] = {
        {1, "Alice", 25},
        {2, "Bob", 30},
        {3, "Charlie", 22}
    };

    for (int i = 0; i < 3; i++) {
        fwrite(&recs[i], sizeof(struct record), 1, file);
    }

    fclose(file);
}

void readRecords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    struct record rec;
    while (fread(&rec, sizeof(struct record), 1, file)) {
        printf("ID: %d, Name: %s, Age: %d\n", rec.id, rec.name, rec.age);
    }

    fclose(file);
}

int main() {
    const char *filename = "sequential.dat";
    writeRecords(filename);
    readRecords(filename);
    return 0;
}
