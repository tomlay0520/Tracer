#include "debug.h"
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <stdlib.h>


struct FUNCTION_CONTEXT* func_stack;
uint32_t func_id_counter = 1;



//                   +-------------------------------+
// top of stack ---> |FUNCTION_CONTEXT               |
//                   +-------------------------------+
//                   |FUNCTION_CONTEXT_PARENT        |
//                   +-------------------------------+
//                   |FUNCTION_CONTEXT_PARENT_PARENT |
//                   +-------------------------------+


// Implementations of debugging functions
void debugger_enter_function(const char* func, const char* file, int line) {
    printf("[ENTER] Function: %s | File: %s | Line: %d\n", func, file, line);
    FUNCTION_CONTEXT* fc = malloc(sizeof(FUNCTION_CONTEXT));
    if (fc == NULL) {
        printf("Failed to allocate memory for FUNCTION_CONTEXT");
        return;
    }

    fc->id = func_id_counter++;
    fc->func = func;
    fc->file = file;
    fc->start_line = line;
    fc->end_line = -1; // Unknown at entry yet
    fc->parent = func_stack;
    fc->child = NULL;
    fc->var_list_ptr = NULL;
    fc->next = NULL;

    // time stamp to get the start time
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    fc->start_time_stamp = (long long)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    // printf("Start Timestamp (μs): %llu\n", fc->start_time_stamp);
    
    if (func_stack != NULL) {
        func_stack->child = fc;
    }
    fc->next = func_stack;
    func_stack = fc; // push onto stack
}

void debugger_exit_function(const char* func, const char* file, int line) {
     printf("[EXIT] Function: %s | File: %s | Line: %d\n", func, file, line);

    if (func_stack == NULL) {
        printf("Warning: Mismatched exit (no active function context)\n");
        return;
    }

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    func_stack->end_time_stamp = (long long)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    func_stack->end_line = line;

    int delta = (int)(func_stack->end_time_stamp - func_stack->start_time_stamp);
    printf("[Duration]: Function: %s | %d (μs) \n", func, delta);
    // printf("End Timestamp (μs): %llu | Function ID: %u\n", 
    //        func_stack->end_time_stamp, func_stack->id);

    FUNCTION_CONTEXT* temp = func_stack;
    func_stack = func_stack->next;  // pop from stack
    free(temp);

}

void debugger_trace_statement(const char* func, const char* file, int line) {
    printf("[TRACE] Function: %s | File: %s | Line: %d\n", func, file, line);
}

void debugger_trace_variable_int(const char* func, const char* file, int line, const char* var_name, int var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = %d\n", func, file, line, var_name, var_value);
}

void debugger_trace_variable_uint(const char* func, const char* file, int line, const char* var_name, unsigned int var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = %u\n", func, file, line, var_name, var_value);
}

void debugger_trace_variable_float(const char* func, const char* file, int line, const char* var_name, float var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = %f\n", func, file, line, var_name, var_value);
}

void debugger_trace_variable_double(const char* func, const char* file, int line, const char* var_name, double var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = %lf\n", func, file, line, var_name, var_value);
}

void debugger_trace_variable_char(const char* func, const char* file, int line, const char* var_name, char var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = '%c'\n", func, file, line, var_name, var_value);
}

void debugger_trace_variable_string(const char* func, const char* file, int line, const char* var_name, const char* var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = \"%s\"\n", func, file, line, var_name, var_value ? var_value : "NULL");
}

void debugger_trace_variable_pointer(const char* func, const char* file, int line, const char* var_name, const void* var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = %p\n", func, file, line, var_name, var_value);
}

// void debugger_trace_variable_generic(const char* func, const char* file, int line, const char* var_name, const void* var_value, size_t size) {
//     printf("[VAR] %s | File: %s | Line: %d | %s = (generic pointer: %p, size: %zu bytes)\n", func, file, line, var_name, var_value, size);
// }

void debugger_trace_variable_generic(const char* func, const char* file, int line, const char* var_name, const void* var_value) {
    printf("[VAR] %s | File: %s | Line: %d | %s = (generic pointer: %p)\n", func, file, line, var_name, var_value);
}