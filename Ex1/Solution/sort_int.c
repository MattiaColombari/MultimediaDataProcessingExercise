#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void write_result(FILE* f, int* list_of_element, size_t list_len){
    for (int i = 0; i < list_len; i++){
        fprintf(f, "%d\n", list_of_element[i]);
    }
}

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
    if (argc != 3) {
        printf("Error, number of arguments\n");
        return 1;
    }

    FILE *f_in;
    FILE *f_out;
    char buffer;
    int current_number;
    bool is_first = true;
    bool is_neg = false;
    int *list_of_element;
    list_of_element = malloc(1);
    size_t list_len = 0;

    f_in = fopen(argv[1], "r");
    f_out = fopen(argv[2], "w");

    if (f_in == NULL){
        printf("Errore apertura file: \"%s\".\n", argv[1]);
        return 1;
    }
    if (f_out == NULL){
        printf("Errore apertura file: \"%s\".\n", argv[2]);
        return 1;
    }

    printf("Inizio lettura.\n");

    buffer = fgetc(f_in);
    while ( !feof(f_in) ){
        if (isnumber(buffer)){
            current_number *= 10;
            current_number +=  atoi(&buffer);
            is_first = false;
        }
        else if (buffer == '-'){
            is_neg = true;
            is_first = false;
        }
        else{
            if (!is_first){
                if (is_neg){
                    current_number *= -1;
                }
                list_of_element = realloc(list_of_element, sizeof(int) * (list_len + 1));
                list_of_element[list_len] = current_number;
                list_len += 1;
            }

            current_number = 0;
            if ((buffer != '\n') && (!isspace(buffer))){
                printf("Identificato carattere estraneo: \'%c\'\n", buffer);
                //sort(list_of_element, list_len);
                qsort(list_of_element, list_len, sizeof(int), cmpfunc);
                write_result(f_out, list_of_element, list_len);
                fclose(f_in);
                fclose(f_out);
                free(list_of_element);
                return 0;
            }
            is_neg = false;
            is_first = true;
        }
        buffer = fgetc(f_in);
    }
    if (!is_first){
        if (is_neg){
            current_number *= -1;
        }
        list_of_element = realloc(list_of_element, sizeof(int) * (list_len + 1));
        list_of_element[list_len] = current_number;
        list_len += 1;
    }

    printf("Lettura completata.\n");
    printf("Identificati %d elementi.\n", (int) list_len);

    //sort(list_of_element, list_len);
    qsort(list_of_element, list_len, sizeof(int), cmpfunc);

    printf("Sorting completo.\n");

    write_result(f_out, list_of_element, list_len);

    printf("Chiusura risorse.\n");

    fclose(f_in);
    fclose(f_out);
    free(list_of_element);

    return 0;
}