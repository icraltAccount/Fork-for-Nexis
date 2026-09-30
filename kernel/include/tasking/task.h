/*
 * WRITTEN BY: nicooolo
 */
#ifndef TASK_H
#define TASK_H
#include <stdint.h>
#define STACK_SIZE 4096 //since each program needs a completly new stack, we set the size of a basic stack

typedef enum{
    TASK_READY, //ready to execute task
    TASK_RUNNING, //executing right now
    TASK_SLEEPING, //waiting for something/exists but not activated
    TASK_DEAD //finished task
} task_states_enum; //every possible state that a task can have

typedef struct{
    uint32_t ds; //data segment
    uint32_t cs; //the code segment
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //all the 32 bit registers
    uint32_t eip; //instruction pointer
    uint32_t eflags; //the CPU flags
} registers_struct; //registers, we use __attribute__((packed)) because if we add extra bytes of alignment to the struct

typedef struct task{
    uint32_t id; //the task ID, every task has an ID
    uint32_t esp; //stores the how was stack before freezing the task
    void* stack_base; //stores the address of the stack base, since it is an address it needs to be a pointer to that address of type void since we can't make any operations in it
    task_states_enum state; //state of the task
    struct task* next_task; //pointer to the next task
} __attribute__((packed)) task_struct;

void task_init(void);
task_struct* create_task(void (*function)(void)); //pointer to a function that doesn't return anything and that doesn't receive any parameters
uint32_t schedule(uint32_t current_stack_pointer); //the one that calls the PIT, the PIT is the timer and it is the IRQ 0 in the IDT
static void task_exit(void); //the function that ends the task
#endif
