#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// gcc main.c -o main; .\main

typedef struct{
    char *buffer; // stores pointer to the memory to be allocated
    size_t buffer_length; // size of allocated buffer
    ssize_t input_length; // size of input stored in buffer
} InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    (*input_buffer).buffer = NULL;
    (*input_buffer).buffer_length = 0;
    (*input_buffer).input_length = 0;

    return input_buffer;
}

void print_prompt() { printf("db > "); }

// ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer* input_buffer) {
    // allocates memory for input_buffer->buffer
    ssize_t bytes_read = getline(&(input_buffer)->buffer, &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0){
        printf("Error reading input!\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    // frees the memory allocated by read_input
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'. \n", input_buffer->buffer);
        }
    }
}