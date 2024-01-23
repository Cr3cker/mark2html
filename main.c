#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// TODO: try to implement simple tags, like h's:
// 1 Hello -> <h1>Hello</h1>


char* h_tags(char *string, int tag_num) {
    char *buffer = malloc(90 * sizeof(char));
    char open_tag[9];
    char close_tag[10];
    char index[2];

    return buffer;
}


int main() {
    FILE* file = fopen("index.txt", "r");
    FILE* output = fopen("index.html", "w");

    if (file == NULL || output == NULL) {
        exit(1);
    }

    char string[80];

    while (fgets(string, 80, file) != NULL) {
        string[strlen(string) - 1] = '\0';
        if (string[0] == '1') {
            char *result = h_tags(string, 1);
            result[strlen(result) - 2] = '\0';
            fprintf(output, result);
        }
    }

    return 0;
}