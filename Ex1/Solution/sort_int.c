#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int* list, size_t len){
    for (int i = 0; i < len - 1; i++){
        // Last i elements are already in place
        for (int j = 0; j < len - i - 1; j++){
            if (list[j] > list[j + 1]){
                swap(&list[j], &list[j + 1]);
            }
        }
    }
}

int main( int argc, char *argv[] )  {
    printf("%d\n", argc);
    if (argc != 3) {
        printf("Error, number of arguments");
        return 1;
    }

    FILE *f_in;
    FILE *f_out;
    char buffer;
    int current_number;
    bool is_first = true;
    int *list_of_element;
    list_of_element = malloc(1);
    size_t list_len = 0;

    f_in = fopen(argv[1], "r");
    f_out = fopen(argv[2], "w");

    if ((f_in == NULL) || (f_out == NULL)){
        printf("Errore apertura file.");
        return 1;
    }

    printf("Debug - inizio lettura\n");

    while (fread(&buffer, sizeof(char), 1, f_in) != 0){
        if (isnumber(buffer)){
            current_number *= 10;
            current_number +=  atoi(&buffer);
        }
        else if (buffer == '-'){
            current_number *= -1;
        }
        else{
            if (!is_first){
                printf("Debug - number: %d\n", current_number);
                printf("Debug - index: %d\n", (int)list_len);
                list_of_element = realloc(list_of_element, sizeof(int) * (list_len + 1));
                list_of_element[list_len] = current_number;
                list_len++;
                printf("Debug - index: %d\n", (int)list_len);
            }
            current_number = 0;
            if ((buffer != '\n') && (!isblank(buffer))){
                break;
            }
            is_first = true;
            continue;
        }
        is_first = false;
    }

    sort(list_of_element, list_len);

    for (int i = 0; i < list_len; i++){
        fprintf(f_out, "%d\n", list_of_element[i]);
    }

    fclose(f_in);
    fclose(f_out);
    free(list_of_element);

    return 0;
}