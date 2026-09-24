;Macros For Setting The Right IDT Entries That Are Responsible For Exceptions
extern ExceptionHandler
global ISR_Stub_Table
ISR_Stub_Table:
    %assign i 0 ;Creates A Variable
    %rep 32 ;Repeats The Code Inside 32 Times(32 Exception Vectors)
    dd ISR_Stub_%+i ;Vector Number
    %assign i i+1 ;Next Vector Number
    %endrep ;Finishes The Repetition When It Repeats 32 Times

%macro ISR_Error_Stub 1 ;This Macro Receives 1 Parameter
ISR_Stub_%+%1: ;Automatically Makes A Label With The Right Number
    call ExceptionHandler
    iret ;Interrupt Return, Returns With An Interruption
%endmacro

%macro ISR_No_Error_Stub 1
ISR_Stub_%+%1:
    call ExceptionHandler
    iret
%endmacro

;IDT Vectors Configuration
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31
