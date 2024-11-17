#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record {
    int id;
    char name[20];
    int age;
};

void writeRecords(const char *filename, const char *indexfile) {
    FILE *file = fopen(filename, "w");
    FILE *indexFile = fopen(indexfile, "w");
    if (file == NULL || indexFile == NULL) {
        return;
    }

    struct record recs[3] = {
        {1, "Alice", 25},
        {2, "Bob", 30},
        {3, "Charlie", 22}
    };

    for (int i = 0; i < 3; i++) {
        fwrite(&recs[i], sizeof(struct record), 1, file);
        fprintf(indexFile, "%d %ld\n", recs[i].id, ftell(file) - sizeof(struct record));
    }

    fclose(file);
    fclose(indexFile);
}

void searchById(const char *filename, const char *indexfile, int searchId) {
    FILE *file = fopen(filename, "r");
    FILE *indexFile = fopen(indexfile, "r");
    if (file == NULL || indexFile == NULL) {
        return;
    }

    int id;
    long position;
    struct record rec;

    while (fscanf(indexFile, "%d %ld", &id, &position) != EOF) {
        if (id == searchId) {
            fseek(file, position, SEEK_SET);
            fread(&rec, sizeof(struct record), 1, file);
            printf("Record found - ID: %d, Name: %s, Age: %d\n", rec.id, rec.name, rec.age);
            fclose(file);
            fclose(indexFile);
            return;
        }
    }

    fclose(file);
    fclose(indexFile);
}

int main() {
    const char *filename = "indexed.dat";
    const char *indexfile = "index.txt";
    writeRecords(filename, indexfile);
    searchById(filename, indexfile, 2);
    return 0;
}
