//
// Created by Administrator on 2020/12/27.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

// 限制每个表的总页数.
#define TABLE_MAX_PAGES 100

typedef struct {
    int file_descripter;
    uint32_t file_length;
    void *pages[TABLE_MAX_PAGES];
} Pager;

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

// 系统命令枚举.
typedef enum {
    MEAT_COMMAND_SUCCESS,
    MEAT_COMMAND_ERROR
} MetaCommandResult;

// 验证表是否满了的枚举.
typedef enum {
    EXECUTE_SUCCESS, EXECUTE_TABLE_FULL
} ExecuteResult;

// 普通命令枚举.
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_NEGTIVE_ERROR,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_ERROR
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

// 定义数据大小.
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USER_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

// 定义对应的偏移量.
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + USER_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USER_SIZE;

// 每条数据的总大小
const uint32_t ROW_SIZE = ID_SIZE + USER_SIZE + EMAIL_SIZE;


// 序列化方法.
void serialize_row(Row *source, void *destination) {
    // C和C++使用的内存拷贝函数.
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    strncpy(destination + USERNAME_OFFSET, source->username, USER_SIZE);
    strncpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

// 反序列化方法.
void derialize_row(void *source, Row *destination) {
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USER_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}


// 每个页的页大小.
const uint32_t PAGE_SIZE = 4096;

// 平均每页的行数,行不要跨页存储.
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;

// 表中总的行数.
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    uint32_t num_rows;
    Pager *pager;
} Table;

// 如果没有命中内存，就去硬盘去取.
void *getPage(Pager *pager, uint32_t page_num) {
    if (page_num > TABLE_MAX_PAGES) {
        printf("get page error");
        exit(EXIT_FAILURE);
    }
    if (pager->pages[page_num] == NULL) {
        // 分配内存空间.
        void *page = malloc(PAGE_SIZE);
        // 根据文件的大小需要分配页数.
        uint32_t num_pages = pager->file_length / PAGE_SIZE;
        // 如果有余数,书名还得多来一个页.
        if (pager->file_length % PAGE_SIZE) {
            num_pages = num_pages + 1;
        }
        if (page_num <= num_pages) {
            lseek(pager->file_descripter, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descripter, page, PAGE_SIZE);
            if (bytes_read == -1) {
                printf("reading file error");
                exit(EXIT_FAILURE);
            }
        }
        pager->pages[page_num] = page;
    }
    return pager->pages[page_num];
}


void pager_flush(Pager *pager, uint32_t page_num, uint32_t size) {
    // 做一个基本的检查.
    if (pager -> pages[page_num] == NULL) {
        printf("error page\n");
        exit(EXIT_FAILURE);
    }
    // 获取文件大小.
    off_t offset = lseek(pager->file_descripter, page_num * PAGE_SIZE, SEEK_SET);

    if (offset == -1) {
        printf("seek file error\n");
        exit(EXIT_FAILURE);
    }
    // 开始写文件.
    ssize_t bytes_written = write(pager -> file_descripter, pager -> pages[page_num], size);

    if (bytes_written == -1) {
      printf("Error writing\n");
      exit(EXIT_FAILURE);
    }
}

void db_close(Table *table) {
    Pager *pager = table->pager;
    // 一共有多少页,先去掉不完整的页.
    uint32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;
    for (uint32_t i = 0; i < num_full_pages; i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }
        // 刷新到磁盘.
        pager_flush(pager, i, PAGE_SIZE);
        // 释放内存.
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }
    uint32_t additional_row = table->num_rows % ROWS_PER_PAGE;
    // 如果存在部分页.
    if (additional_row > 0) {
        // 取出最后一个.
        uint32_t page_num = num_full_pages;
        if (pager->pages[page_num] != NULL) {
            pager_flush(pager, page_num, additional_row * ROW_SIZE);
            free(pager->pages[page_num]);
            pager->pages[page_num] = NULL;
        }
    }
    // 关闭文件描述符.
    int result = close(pager->file_descripter);
    // 如果没有关闭成功就报错.
    if (result == -1) {
        printf("Error close file\n");
        exit(EXIT_FAILURE);
    }
    // 再确认一遍.
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        void *page = pager->pages[i];
        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}



// 读取特定的一行.
void *row_slot(Table *table, uint32_t row_num) {
    // 根据行号获取它在哪一页.
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    //
    void *page = getPage(table->pager, page_num);

    uint32_t row_offset = row_num % ROWS_PER_PAGE;

    uint32_t byte_offset = row_offset % ROW_SIZE;

    return page + byte_offset;
}

MetaCommandResult doMetaCommand(InputBuffer *input_buffer, Table *table) {
    // strcmp的意思是比较两个字符串的意思.
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        db_close(table);
        exit(EXIT_SUCCESS);
    } else {
        return MEAT_COMMAND_ERROR;
    }
}

PrepareResult doPrepareInsert(InputBuffer *input_buffer, Statement *statement) {
    // 先确定为插入.
    statement->type = STATEMENT_INSERT;
    // 分解字符串 str 为一组字符串.
    // 第一次调用时，strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL,每次调用成功则返回指向被分割出片段的指针.
    char *keyword = strtok(input_buffer->buffer, " ");
    char *id_string = strtok(NULL, " ");
    char *username = strtok(NULL, " ");
    char *email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL) {
        return PREPARE_SYNTAX_ERROR;
    }

    // 转id为整形.
    int id = atoi(id_string);

    if (id < 0) {
        return PREPARE_NEGTIVE_ERROR;
    }


    if (strlen(username) > COLUMN_USERNAME_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }

    if (strlen(email) > COLUMN_EMAIL_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }
    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}


PrepareResult doPrepareResult(InputBuffer *input_buffer, Statement *statement) {
    // 插入校验.
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        return doPrepareInsert(input_buffer, statement);
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_ERROR;
}

ExecuteResult excute_insert(Statement *statement, Table *table) {
    // 如果表已经满了,就返回错误.
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }
    // &取地址符.
    Row *row_to_insert = &(statement->row_to_insert);
    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;
    return EXECUTE_SUCCESS;
}

void print_row(Row *row) {
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

ExecuteResult excute_select(Statement *statement, Table *table) {
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++) {
        derialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult excute_statement(Statement *statement, Table *table) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            return excute_insert(statement, table);
        case (STATEMENT_SELECT):
            return excute_select(statement, table);
    }
}

Pager *pageOpen(const char *filename) {
    // 首先我们打开这个文件.
    int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    if (fd == -1) {
        printf("unable open file");
        exit(EXIT_FAILURE);
    }
    // 获取文件的长度.
    off_t file_length = lseek(fd, 0, SEEK_END);

    // 这个Page就代表了这个文件.
    Pager *pager = malloc(sizeof(Pager));

    pager->file_descripter = fd;
    pager->file_length = file_length;

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }
    return pager;
}

Table *db_open(const char *filename) {
    // malloc分配所需的内存空间，并返回一个指向它的指针.
    // sizeof分配的是字节大小.
    Pager *pager = pageOpen(filename);
    uint32_t num_rows = pager->file_length / ROW_SIZE;
    Table *table = malloc(sizeof(Table));
    table->pager = pager;
    table->num_rows = num_rows;
    return table;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("please give a fileName");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];
    Table* table = db_open(filename);

    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);
        // 系统命令.
        if (input_buffer->buffer[0] == '.') {
            switch (doMetaCommand(input_buffer, table)) {
                case (MEAT_COMMAND_SUCCESS):
                    continue;
                case (MEAT_COMMAND_ERROR) :
                    printf("unrecognized\n");
                    continue;
            }
        }

        // 检查语法.
        Statement statement;
        switch (doPrepareResult(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_NEGTIVE_ERROR):
                printf("ID error");
                continue;
            case (PREPARE_STRING_TOO_LONG):
                printf("String is too Long\n");
                continue;
            case (PREPARE_SYNTAX_ERROR):
                printf("syntax error\n");
                continue;
            case (PREPARE_ERROR):
                printf("unrecognized\n");
                continue;
        }

        // 执行SQL.
        switch (excute_statement(&statement, table)) {
            case (EXECUTE_SUCCESS):
                printf("Executed.\n");
                break;
            case (EXECUTE_TABLE_FULL):
                printf("full.\n");
                break;
        }
    }
}


