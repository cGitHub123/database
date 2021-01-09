#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer() {
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer *input_buffer) {
    ssize_t bytes_read =
            getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// 系统命令枚举.if
typedef enum {
    MEAT_COMMAND_SUCCESS,
    MEAT_COMMAND_ERROR
} MetaCommandResult;

// 普通命令枚举.
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_ERROR
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
} Statement;

MetaCommandResult doMetaCommand(InputBuffer *input_buffer) {
    // strcmp的意思是比较两个字符串的意思.
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return MEAT_COMMAND_ERROR;
    }
}

PrepareResult doPrepareResult(InputBuffer *input_buffer, Statement *statement) {
    if (strcmp(input_buffer->buffer, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_ERROR;
}
`
void excute_statement(Statement *statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("insert\n");
            break;
        case (STATEMENT_SELECT):
            printf("select\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);
        // 系统命令.
        if (input_buffer->buffer[0] == ".") {
            switch (doMetaCommand(input_buffer)) {
                case (MEAT_COMMAND_SUCCESS):
                    continue;
                case (MEAT_COMMAND_ERROR) :
                    printf("unrecognized\n");
                    continue;
            }
        }
        // 检查语法
        Statement statement;
        switch (doPrepareResult(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_ERROR):
                printf("unrecognized\n");
                continue;
        }

        excute_statement(&statement);
        printf("excute!.\n");
    }
}


