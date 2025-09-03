#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <stdlib.h>

// Function instrumentation hooks
// These functions are called at the entry and exit of every function
// when compiled with -finstrument-functions flag.
// We use this_fn to get the address of the current function,
// and the dladdr to get the function names from addresses.
void __attribute__((no_instrument_function)) 
__cyg_profile_func_enter(void *this_fn, void *call_site)
{
    Dl_info info;
    if (dladdr(this_fn, &info)) {
        printf("ENTER: %p -> %s\n", this_fn, info.dli_sname ? info.dli_sname : "unknown");
    } else {
        printf("ENTER: %p -> unknown \n", this_fn);
    }
}

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *this_fn, void *call_site)
{
    Dl_info info;  
    if (dladdr(this_fn, &info)) {
        printf("EXIT: %p -> %s\n", this_fn, info.dli_sname ? info.dli_sname : "unknown");
    } else {
        printf("EXIT: %p -> unknown \n", this_fn);
    }
}

// the following is just a sample program to demonstrate the instrumentation
void process_data(int value);
double calculate_stats(int a, int b);
void validate_input(int input);
void log_message(const char* message);
void save_result(double result);
void display_output(double result);
int helper_function(int x);
void recursive_function(int n);

int call_count = 0;

void log_message(const char* message) {
    printf("LOG: %s\n", message);
}

void validate_input(int input) {
    if (input < 0) {
        log_message("Input validation failed - negative value");
    } else {
        log_message("Input validation passed");
    }
}

int helper_function(int x) {
    call_count++;
    return x * 2 + 1;
}

double calculate_stats(int a, int b) {
    log_message("Calculating statistics");
    int sum = a + b;
    int product = a * b;
    
    double avg = (double)sum / 2.0;
    double variation = (double)(abs(a - b)) / 2.0;
    
    return variation;
}

void recursive_function(int n) {
    if (n <= 0) {
        log_message("Recursion base case reached");
        return;
    }
    
    log_message("Recursive call");
    helper_function(n);
    recursive_function(n - 1);
}

void save_result(double result) {
    log_message("Saving result to memory");
    printf("Result saved: %.2f\n", result);
}

void display_output(double result) {
    log_message("Displaying output");
    printf("Final result: %.3f\n", result);
    printf("Total function calls: %d\n", call_count);
}

void process_data(int value) {
    log_message("Starting data processing");
    validate_input(value);
    
    int processed_value = helper_function(value);
    double stats = calculate_stats(value, processed_value);
    
    if (stats > 10.0) {
        log_message("High standard deviation detected");
        recursive_function(3);
    }
    
    save_result(stats);
    display_output(stats);
}

int main() {
    log_message("Program started");
    
    process_data(5);
    process_data(10);
    process_data(-2); 
    
    log_message("Program completed");
    return 0;
}