#include <stdio.h>
#define TRACE_IN_FILE() printf("Line %d is in %s\n", __LINE__, __FILE__)
#define TRACE_IN_FUNCTION() printf("Line %d is in function %s\n", __LINE__, __func__)


void 
original_function() 
{
    TRACE_IN_FILE();
    TRACE_IN_FUNCTION();
    int x = 1;
    TRACE_IN_FILE();
    TRACE_IN_FUNCTION();
    x += 1;
    TRACE_IN_FILE();
    TRACE_IN_FUNCTION();
    printf("x = %d\n", x);
}

int main() {
    original_function();
    return 0;
}