/*
 * WRITTEN BY: nicooolo
 */
#include "tasking/task.h"
#include "memory/pmm/pmm.h"
#include <stddef.h>
static task_struct* current_task = NULL; //the current active task
static task_struct* task_list = NULL; //points to the first task
static uint32_t next_id = 0; //the next task id, each task has an id

static void task_exit(void){ //stops the task
    current_task->state = TASK_DEAD; //sets the state of the task to TASK_DEAD
    while(1){
        __asm__ __volatile__("hlt"); //stops the CPU/halts the CPU
    }
}

void task_init(){
    task_struct* task = (task_struct*)pmm_alloc_page();
    task->id = next_id++; //since the next_id variable is currently 0, we add 1 to it to get the first task id
    task->esp = 0; //the esp is set to 0 initiallly since it only changes with the PIT/IRQ 0/timer
    task->stack_base = NULL; //since we don't need another stack and the kernel already comes with one, we set it to NULL
    task->state = TASK_RUNNING; //sets the task to running
    task->next_task = task; //points the next task to itself

    current_task = task; //makes the current task become the task
    task_list = task; //when the OS turns on, there is only 1 task, so the task_list points to the first task
}

task_struct* create_task(void (*function)(void)){
    task_struct* new_task = (task_struct*)pmm_alloc_page(); //allocates memory for the task
    void* stack = pmm_alloc_page(); //allocates memory for the stack, each task has it's own stack
    new_task->id = next_id++; //since the next_id variable is currently 0, we add 1 to it to get the first task id
    new_task->stack_base = stack; //the task's base of the stack of the task is the stack we allocated in memory
    new_task->state = TASK_READY; //sets the task to ready

    uint32_t stack_top = (uint32_t)stack + STACK_SIZE; //the size of the stack is equal to the size of a stack(4096 bytes) + the base of the stack
    stack_top -= sizeof(registers_struct); //since the stack grows down, we subtract the top of the stack by the size of all the registers
    registers_struct* registers = (registers_struct*)stack_top; //since the top of the stack points to the registers struct

    for(uint32_t i = 0; i < sizeof(registers_struct); i++){
        ((uint8_t*)registers)[i] = 0; //set all the registers to 0 to remove garbage that came from memory, type is uint8_t because it treats the elements in the struct as 1 byte each so that when C jumps to the next element it jumps correctly: 12(elements) * 4(bytes) = 48 bytes, if it was uint32_t C would jump 4 bytes to get to the next element and it would be: 47 * 4 = 188 and it causes an overflow and it would write to un-wanted places in memory
    }

    registers->ds = 0x10; //data segment
    registers->cs = 0x08; //code segment
    registers->eip = (uint32_t)function; //the eip points to the function
    registers->eflags = 0x202; //if 0 the interruptions get turned off and the timer will never be able to use, 0000 0010 0000 0010 in binary, 0x02 means reserved for the architecture x86, so we set it to 1, 0x200 is the IF(interrupt flag), this bit is also 1, the CPU accepts hardware interruptions when it is 1, when 0 the hardware interruptions are disabled

    new_task->esp = stack_top; //updates the stack pointer to the top of the configured esp(stack pointer) that is the stack_top
    new_task->next_task = new_task; //the next task is the new task we created and configurated
    return new_task; //returns the new stack
}

uint32_t schedule(uint32_t current_stack_pointer){
    if(current_task == NULL){
        return current_stack_pointer; //if there is no current task, we
    }
    current_task->esp = current_stack_pointer; //saves the stack pointer

    do{
        current_task = current_task->next_task;
    }while(current_task->state == TASK_DEAD); //jumps dead tasks

    return current_task->esp; //returns the stack pointer that points to the new task so that our code in assembly can load it in register esp
}
