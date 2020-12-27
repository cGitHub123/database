//
// Created by Administrator on 2020/12/27.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
   uint32_t id;
   // TODO 缺少容量.
   char username[];
   char email[];
} Row;

typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

// 定义数据大小.
const uint32_t ID_SIZE =  (Row, id);
const uint32_t USER_SIZE = sizeof;
const uint32_t EMAIL_SIZE = ;

// 定义对应的偏移量.
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + USER_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USER_SIZE;

// 每条数据的总大小
const uint32_t ROW_SIZE = ID_SIZE + USER_SIZE + EMAIL_SIZE;


// 序列化方法.
void serialize_row(Row* source, void* destination) {
    // C和C++使用的内存拷贝函数.
    memcpy(destination + ID_OFFSET, &(source -> id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source -> username), USER_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source -> email), EMAIL_SIZE);
}

// 反序列化方法.
void derialize_row(void* source, Row* destination) {
    memcpy(&(destination -> id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination -> username), source + USERNAME_OFFSET, USER_SIZE);
    memcpy(&(destination -> email), source + EMAIL_OFFSET, EMAIL_SIZE);
}



MetaCommandResult doMetaCommand(InputBuffer *input_buffer) {
    // strcmp的意思是比较两个字符串的意思.
    //printf(input_buffer->buffer);
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return MEAT_COMMAND_ERROR;
    }
}

PrepareResult doPrepareResult(InputBuffer *input_buffer, Statement *statement) {
    // 在第三节，首先我们要新修改插入的代码.
    if (strcmp(input_buffer->buffer, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        // sscanf就是一个格式化的输入.
        int arg_assigned = sscanf(input_buffer -> buffer, "insert %d %s %s", &(statement-> ));

        if (arg_assigned < 3) {
            // TODO 报错.
            return ;
        }

        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_ERROR;
}

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
        if (input_buffer->buffer[0] == '.') {
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

