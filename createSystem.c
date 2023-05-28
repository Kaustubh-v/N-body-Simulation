#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define MAX_FIELD_LENGTH 100
#define MAX_NUM_FIELDS 10

typedef struct {
    char fields[MAX_NUM_FIELDS][MAX_FIELD_LENGTH];
    int numFields;
} CSVRow;

void readCSV(const char* filename, CSVRow** rows, int* numRows) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the CSV file.\n");
        return;
    }

    char line[MAX_FIELD_LENGTH * MAX_NUM_FIELDS];
    *numRows = 0;
    *rows = NULL;

    while (fgets(line, sizeof(line), file)) {
        char* token;
        CSVRow row;
        row.numFields = 0;

        token = strtok(line, ",");
        while (token != NULL) {
            strncpy(row.fields[row.numFields], token, MAX_FIELD_LENGTH);
            row.fields[row.numFields][MAX_FIELD_LENGTH - 1] = '\0';
            row.numFields++;
            token = strtok(NULL, ",");
        }

        (*numRows)++;
        *rows = (CSVRow*)realloc(*rows, sizeof(CSVRow) * (*numRows));
        (*rows)[(*numRows) - 1] = row;
    }

    fclose(file);
}

int main() {
    CSVRow* rows;
    int numRows;
    system_node s1;

    readCSV("particles.csv", &rows, &numRows);

    for (int i = 0; i < numRows; i++) {
        particle * p1;
        p1 = (particle*)malloc(sizeof(particle));
        for (int j = 0; j < rows[i].numFields; j++) {
            if(j == 0){
                p1->mass = strtold(rows[i].fields[j], NULL);
            }
            else if(j == 1){
                p1->pos[0] = strtof(rows[i].fields[j], NULL);
            }
            else if(j == 2){
                p1->pos[1] = strtof(rows[i].fields[j], NULL);
            }
            else if (j==3)
            {
                p1->pos[2] = strtof(rows[i].fields[j], NULL);
            }
            else if (j == 4)
            {
                p1->vel[0] = strtof(rows[i].fields[j], NULL);
            }
            else if (j == 5)
            {
                p1->vel[1] = strtof(rows[i].fields[j], NULL);
            }
            else if (j==6)
            {
                p1->vel[2] = strtof(rows[i].fields[j], NULL);
            }
            
            if( i == 0){
                s1.p1 = p1;
            }
            else s1.p2 = p1;
            
        }
        printf("\n");
    }

    free(rows);
    printf("mass of p1 = %Lf , mass of p2 = %Lf\n" , s1.p1->mass , s1.p2->mass);

    return 0;
}