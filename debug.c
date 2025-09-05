#include "debug.h"
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <stdlib.h>


// Implementations of debugging functions


void debugger_enter_function(const char* func, const char* file, int line) {
    printf("[ENTER] Function: %s | File: %s | Line: %d\n", func, file, line);
    FUNCTION_CONTEXT* fc = malloc(sizeof(FUNCTION_CONTEXT));
    fc->func = func;
    fc->file = file;


    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    fc->start_time_stamp = (long long)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    printf("Start Timestamp (μs): %llu\n", fc->start_time_stamp);
}

void debugger_exit_function(const char* func, const char* file, int line) {
    printf("[EXIT] Function: %s | File: %s | Line: %d\n", func, file, line);

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

void debugger_trace_variable_generic(const char* func, const char* file, int line, const char* var_name, const void* var_value, size_t size) {
    printf("[VAR] %s | File: %s | Line: %d | %s = (generic pointer: %p, size: %zu bytes)\n", func, file, line, var_name, var_value, size);
}




void foo(int);

void foo(int x) {
    DEBUGGER_ENTER_FUNCTION();
    DEBUGGER_VAR(x);
    x = 10; DEBUGGER_TRACE();
    x --; // simulate the unexpected change
    DEBUGGER_VAR(x); DEBUGGER_TRACE();
    DEBUGGER_EXIT_FUNCTION();
}

int main() {
    // Example usage of the debugging macros
    DEBUGGER_ENTER_FUNCTION(); DEBUGGER_TRACE();

    int a = 42;
    float b = 3.14f;
    const char* str = "Hello, Debugger!";
    void* ptr = (void*)0xDEADBEEF;

    foo(1);
    DEBUGGER_VAR(a);
    DEBUGGER_VAR(b);
    DEBUGGER_VAR(str);
    DEBUGGER_VAR(ptr);

    // DEBUGGER_TRACE();

    DEBUGGER_EXIT_FUNCTION();
    return 0;
}