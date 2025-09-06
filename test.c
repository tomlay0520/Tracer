#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定义结构体类型
typedef struct {
    int id;
    char name[50];
    float score;
    int is_active;
} Student;

typedef struct {
    int width;
    int height;
    float area;
    float perimeter;
} Rectangle;

typedef struct {
    Student* students;
    int count;
    int capacity;
} Classroom;

// 函数声明
void test_struct_operations();
void test_nested_structs();
void test_struct_arrays();
Student create_student(int id, const char* name, float score);
Rectangle create_rectangle(int width, int height);
void print_student_info(const Student* student);
void print_rectangle_info(const Rectangle* rect);
void modify_student(Student* student);
void modify_rectangle(Rectangle* rect);

int main() {
    DEBUGGER_ENTER_FUNCTION();
    
    printf("=== 结构体测试用例 ===\n");
    
    // 测试结构体操作
    test_struct_operations();
    
    // 测试嵌套结构体操作
    test_nested_structs();
    
    // 测试结构体数组
    test_struct_arrays();
    
    printf("=== 结构体测试完成 ===\n");
    
    DEBUGGER_EXIT_FUNCTION();
    return 0;
}

// 结构体操作测试
void test_struct_operations() {
    DEBUGGER_ENTER_FUNCTION();
    
    // 创建结构体实例
    Student student1 = create_student(1, "Alice", 95.5f);
    Student student2 = create_student(2, "Bob", 88.0f);
    
    // 跟踪结构体成员变量
    DEBUGGER_VAR(student1.id);
    DEBUGGER_VAR(student1.name);
    DEBUGGER_VAR(student1.score);
    DEBUGGER_VAR(student1.is_active);
    
    DEBUGGER_VAR(student2.id);
    DEBUGGER_VAR(student2.name);
    DEBUGGER_VAR(student2.score);
    
    // 修改结构体成员
    student1.score += 2.5f;
    student2.score = 90.0f;
    student1.is_active = 1;
    
    DEBUGGER_VAR(student1.score);
    DEBUGGER_VAR(student2.score);
    DEBUGGER_VAR(student1.is_active);
    
    // 使用结构体指针（但不直接跟踪指针）
    Student* student_ptr = &student1;
    DEBUGGER_VAR(student_ptr->id);    // 通过指针访问成员
    DEBUGGER_VAR(student_ptr->name);
    
    // 调用处理结构体的函数
    modify_student(&student1);
    DEBUGGER_VAR(student1.score);
    
    // 结构体赋值
    Student student3 = student1;
    student3.id = 3;
    DEBUGGER_VAR(student3.id);
    DEBUGGER_VAR(student3.name);
    DEBUGGER_VAR(student3.score);
    
    DEBUGGER_EXIT_FUNCTION();
}

// 嵌套结构体测试
void test_nested_structs() {
    DEBUGGER_ENTER_FUNCTION();
    
    // 创建矩形结构体
    Rectangle rect1 = create_rectangle(10, 5);
    Rectangle rect2 = create_rectangle(7, 7);
    
    // 跟踪矩形属性
    DEBUGGER_VAR(rect1.width);
    DEBUGGER_VAR(rect1.height);
    DEBUGGER_VAR(rect1.area);
    DEBUGGER_VAR(rect1.perimeter);
    
    DEBUGGER_VAR(rect2.width);
    DEBUGGER_VAR(rect2.height);
    DEBUGGER_VAR(rect2.area);
    
    // 修改并重新计算
    rect1.width = 15;
    rect1.area = rect1.width * rect1.height;
    rect1.perimeter = 2 * (rect1.width + rect1.height);
    
    DEBUGGER_VAR(rect1.width);
    DEBUGGER_VAR(rect1.area);
    DEBUGGER_VAR(rect1.perimeter);
    
    // 调用处理函数
    modify_rectangle(&rect2);
    DEBUGGER_VAR(rect2.width);
    DEBUGGER_VAR(rect2.area);
    
    DEBUGGER_EXIT_FUNCTION();
}

// 结构体数组测试
void test_struct_arrays() {
    DEBUGGER_ENTER_FUNCTION();
    
    // 创建结构体数组
    Student students[3] = {
        create_student(1, "Charlie", 85.0f),
        create_student(2, "Diana", 92.5f),
        create_student(3, "Eve", 78.0f)
    };
    
    // 跟踪数组元素成员
    DEBUGGER_VAR(students[0].id);
    DEBUGGER_VAR(students[0].name);
    DEBUGGER_VAR(students[0].score);
    
    DEBUGGER_VAR(students[1].id);
    DEBUGGER_VAR(students[1].name);
    DEBUGGER_VAR(students[1].score);
    
    DEBUGGER_VAR(students[2].id);
    DEBUGGER_VAR(students[2].name);
    DEBUGGER_VAR(students[2].score);
    
    // 修改数组元素
    students[0].score += 3.0f;
    students[1].score = 95.0f;
    strcpy(students[2].name, "Eva");
    
    DEBUGGER_VAR(students[0].score);
    DEBUGGER_VAR(students[1].score);
    DEBUGGER_VAR(students[2].name);
    
    // 遍历结构体数组
    float total_score = 0.0f;
    for (int i = 0; i < 3; i++) {
        total_score += students[i].score;
        if (i == 1) {
            DEBUGGER_VAR(total_score); // 中间结果
        }
    }
    
    float average_score = total_score / 3.0f;
    DEBUGGER_VAR(total_score);
    DEBUGGER_VAR(average_score);
    
    // 动态结构体数组（但不直接跟踪指针）
    Student* dynamic_students = malloc(2 * sizeof(Student));
    if (dynamic_students) {
        dynamic_students[0] = create_student(4, "Frank", 88.5f);
        dynamic_students[1] = create_student(5, "Grace", 91.0f);
        
        DEBUGGER_VAR(dynamic_students[0].id);
        DEBUGGER_VAR(dynamic_students[0].name);
        DEBUGGER_VAR(dynamic_students[1].score);
        
        free(dynamic_students);
    }
    
    DEBUGGER_EXIT_FUNCTION();
}

// 创建学生结构体
Student create_student(int id, const char* name, float score) {
    DEBUGGER_ENTER_FUNCTION();
    DEBUGGER_VAR(id);
    DEBUGGER_VAR(name);
    DEBUGGER_VAR(score);
    
    Student student;
    Student* s2 = &student;
    student.id = id;
    strncpy(student.name, name, sizeof(student.name) - 1);
    student.name[sizeof(student.name) - 1] = '\0';
    student.score = score;
    student.is_active = 0;
    
    printf("*****************break point here***************\n");
    DEBUGGER_VAR(s2);
    DEBUGGER_VAR(student.id);
    DEBUGGER_VAR(student.name);
    DEBUGGER_VAR(student.score);
    
    DEBUGGER_EXIT_FUNCTION();
    return student;
}

// 创建矩形结构体
Rectangle create_rectangle(int width, int height) {
    DEBUGGER_ENTER_FUNCTION();
    DEBUGGER_VAR(width);
    DEBUGGER_VAR(height);
    
    Rectangle rect;
    rect.width = width;
    rect.height = height;
    rect.area = width * height;
    rect.perimeter = 2 * (width + height);
    
    DEBUGGER_VAR(rect.width);
    DEBUGGER_VAR(rect.height);
    DEBUGGER_VAR(rect.area);
    DEBUGGER_VAR(rect.perimeter);
    
    DEBUGGER_EXIT_FUNCTION();
    return rect;
}

// 修改学生信息
void modify_student(Student* student) {
    DEBUGGER_ENTER_FUNCTION();
    
    if (student) {
        DEBUGGER_VAR(student->id);
        DEBUGGER_VAR(student->name);
        DEBUGGER_VAR(student->score);
        
        // 修改学生信息
        student->score += 5.0f;
        student->is_active = 1;
        
        DEBUGGER_VAR(student->score);
        DEBUGGER_VAR(student->is_active);
    }
    
    DEBUGGER_EXIT_FUNCTION();
}

// 修改矩形信息
void modify_rectangle(Rectangle* rect) {
    DEBUGGER_ENTER_FUNCTION();
    
    if (rect) {
        DEBUGGER_VAR(rect->width);
        DEBUGGER_VAR(rect->height);
        DEBUGGER_VAR(rect->area);
        
        // 修改矩形尺寸并重新计算
        rect->width += 2;
        rect->height += 1;
        rect->area = rect->width * rect->height;
        rect->perimeter = 2 * (rect->width + rect->height);
        
        DEBUGGER_VAR(rect->width);
        DEBUGGER_VAR(rect->height);
        DEBUGGER_VAR(rect->area);
        DEBUGGER_VAR(rect->perimeter);
    }
    
    DEBUGGER_EXIT_FUNCTION();
}

// 打印学生信息（不用于调试，仅演示）
void print_student_info(const Student* student) {
    if (student) {
        printf("Student %d: %s, Score: %.1f, Active: %d\n",
               student->id, student->name, student->score, student->is_active);
    }
}

// 打印矩形信息（不用于调试，仅演示）
void print_rectangle_info(const Rectangle* rect) {
    if (rect) {
        printf("Rectangle %dx%d: Area=%.1f, Perimeter=%.1f\n",
               rect->width, rect->height, rect->area, rect->perimeter);
    }
}