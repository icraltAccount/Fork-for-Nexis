
extern ExceptionHandler
global ISR_Stub_Table
ISR_Stub_Table:
    %assign i 0
    %rep 32 
    dd ISR_Stub_%+i
    %assign i i+1
    %endrep

%macro ISR_Error_Stub 1
ISR_Stub_%+%1:
    call ExceptionHandler
    iret
%endmacro

%macro ISR_No_Error_Stub 1
ISR_Stub_%+%1:
    call ExceptionHandler
    iret
%endmacro

ISR_No_Error_Stub 0
ISR_No_Error_Stub 1
ISR_No_Error_Stub 2
ISR_No_Error_Stub 3
ISR_No_Error_Stub 4
ISR_No_Error_Stub 5
ISR_No_Error_Stub 6
ISR_No_Error_Stub 7
ISR_Error_Stub 8
ISR_No_Error_Stub 9
ISR_Error_Stub 10
ISR_Error_Stub 11
ISR_Error_Stub 12
ISR_Error_Stub 13
ISR_Error_Stub 14
ISR_No_Error_Stub 15
ISR_No_Error_Stub 16
ISR_Error_Stub 17
ISR_No_Error_Stub 18
ISR_No_Error_Stub 19
ISR_No_Error_Stub 20
ISR_No_Error_Stub 21
ISR_No_Error_Stub 22
ISR_No_Error_Stub 23
ISR_No_Error_Stub 24
ISR_No_Error_Stub 25
ISR_No_Error_Stub 26
ISR_No_Error_Stub 27
ISR_No_Error_Stub 28
ISR_No_Error_Stub 29
ISR_Error_Stub 30
ISR_No_Error_Stub 31

