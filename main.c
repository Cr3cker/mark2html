#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INITIAL_SIZE 80

char* append_char(char* str, char c) {
    size_t len = strlen(str);
    char* new_str = realloc(str, len + 2);
    if (new_str == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return new_str;
}

void create_start_skeleton(FILE *output) {
    fprintf(output, "<!DOCTYPE html>\n<html>\n");
    fprintf(output, "\t<body>\n");
}

void create_end_skeleton(FILE *output) {
    fprintf(output, "\t<body>\n");
    fprintf(output, "</html>\n");
}

int main(int argc, char *argv[]) {
    FILE* file;
    FILE* output;

    if (argc == 3) {
        file = fopen(argv[1], "r");
        output = fopen(argv[2], "w");
    }

    if (file == NULL || output == NULL) {
        exit(1);
    }

    create_start_skeleton(output);

    char* string = malloc(INITIAL_SIZE);
    char* ptr = string;

    while (fgets(string, INITIAL_SIZE, file) != NULL) {
        ptr = string;

        if (*ptr == '#') {
            int h_counter = 0;
            while (*ptr == '#') {
                h_counter++;
                ptr++;
            }
            if (h_counter <= 6) {
                size_t len = strlen(string);
                string[len - 1] = '\0';
                fprintf(output, "\t\t<h%d>%s</h%d>\n", h_counter, ptr + 1, h_counter);
            } else {
                printf("Unknown number for the h tag!\n");
            }
        } else if (isalpha(*ptr)) {
            int asterisk_count = 0;
            string[strlen(string) - 1] = '\0';
            char *first_part = malloc(INITIAL_SIZE);  
            if (first_part == NULL) {
                exit(1);
            }

            first_part[0] = '\0';            
            while (*ptr != '\0' && (isalnum(*ptr) || *ptr == ' ')) {
                first_part = append_char(first_part, *ptr);
                ptr++;
            }

            while (*ptr == '*') {
                asterisk_count++;
                ptr++;
            }

            char *bold_string = malloc(INITIAL_SIZE);

            if (bold_string == NULL) {
                exit(1);
            }

            *bold_string = '\0';

            strcat(bold_string, "<strong>");

            while (*ptr != '*') {
                bold_string = append_char(bold_string, *ptr);
                ptr++;
            }

            if (*ptr++ == '*') {
                strcat(bold_string, "</strong>");
            }

            first_part = realloc(first_part, strlen(first_part) + strlen(bold_string) + 1);
            strcat(first_part, bold_string);

            ptr++;

            while (*ptr != '\0') {
                first_part = append_char(first_part, *ptr);
                ptr++;
            }

            fprintf(output, "\t\t<p>%s</p>\n", first_part);
            free(first_part);
            free(bold_string);
        }
    }

    create_end_skeleton(output);

    fclose(file);
    fclose(output);
    free(string);

    return 0;
}