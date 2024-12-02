#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

char* read_file(const char* filename) {
    printf("Trying to open file: %s\n", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen failed");
        //fprintf(stderr, "Failed to open file.\n");
        return NULL;
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the file content
    char* content = (char*)malloc((file_size + 1) * sizeof(char));
    if (content == NULL) {
        fprintf(stderr, "Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file
    fread(content, sizeof(char), file_size, file);
    content[file_size] = '\0';
    fclose(file);

    return content;
}