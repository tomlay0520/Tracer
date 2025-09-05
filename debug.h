#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdint.h>
#include <stddef.h>

// C99 standard to get the current function name
#define CURRENT_FUNCTION __func__ 

// MACRO DEF APIS
#define DEBUGGER_ENTER_FUNCTION() \
    debugger_enter_function(CURRENT_FUNCTION, __FILE__, __LINE__)
    
#define DEBUGGER_EXIT_FUNCTION() \
    debugger_exit_function(CURRENT_FUNCTION, __FILE__, __LINE__)
    
#define DEBUGGER_TRACE() \
    debugger_trace_statement(CURRENT_FUNCTION, __FILE__, __LINE__)
    
// Generic variable tracing macro, supports multiple types
#define DEBUGGER_VAR(var) \
    _Generic((var), \
        int: debugger_trace_variable_int, \
        unsigned int: debugger_trace_variable_uint, \
        float: debugger_trace_variable_float, \
        double: debugger_trace_variable_double, \
        char: debugger_trace_variable_char, \
        char*: debugger_trace_variable_string, \
        const char*: debugger_trace_variable_string, \
        void*: debugger_trace_variable_pointer, \
        default: debugger_trace_variable_generic \
    )(CURRENT_FUNCTION, __FILE__, __LINE__, #var, var)




// Function entry/exit and statement tracing functions
void debugger_enter_function(const char* func, const char* file, int line);
void debugger_exit_function(const char* func, const char* file, int line);
void debugger_trace_statement(const char* func, const char* file, int line);


// Variable tracing functions for different types
void debugger_trace_variable_int(const char* func, const char* file, int line, const char* var_name, int var_value);
void debugger_trace_variable_uint(const char* func, const char* file, int line, const char* var_name, unsigned int var_value);
void debugger_trace_variable_float(const char* func, const char* file, int line, const char* var_name, float var_value);
void debugger_trace_variable_double(const char* func, const char* file, int line, const char* var_name, double var_value);
void debugger_trace_variable_char(const char* func, const char* file, int line, const char* var_name, char var_value);
void debugger_trace_variable_string(const char* func, const char* file, int line, const char* var_name, const char* var_value);
void debugger_trace_variable_pointer(const char* func, const char* file, int line, const char* var_name, const void* var_value);
void debugger_trace_variable_generic(const char* func, const char* file, int line, const char* var_name, const void* var_value, size_t size);



typedef union {
    int int_val;
    unsigned int uint_val;
    float float_val;
    double double_val;
    char char_val;
    const char* string_val;
    const void* pointer_val;
} VAR_VALUE;

typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_UINT,
    VAR_TYPE_FLOAT,
    VAR_TYPE_DOUBLE,
    VAR_TYPE_CHAR,
    VAR_TYPE_STRING,
    VAR_TYPE_POINTER,
    VAR_TYPE_GENERIC
} VAR_TYPE;

typedef struct VAR_CONTEXT_NODE {
    const char* var_name;
    VAR_TYPE var_type;
    VAR_VALUE var_value;
    size_t var_size; 
    struct VAR_CONTEXT_NODE* next;
    struct VAR_CONTEXT_NODE* prev;
    struct FUNCTION_CONTEXT* parent_func;
} VAR_CONTEXT_NODE;

typedef struct FUNCTION_CONTEXT {
    uint32_t id;
    long long start_time_stamp;
    long long end_time_stamp;
    const char* func;
    const char* file;
    int start_line;
    int end_line;
    struct FUNCTION_CONTEXT* parent;
    struct FUNCTION_CONTEXT* child;
    struct VAR_CONTEXT_NODE* var_list_ptr;
} FUNCTION_CONTEXT;

#endif