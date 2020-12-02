; ----------------------------------------------------------------------------------------
; Pretends to rename a folder from one console arg to another using system calls. Renames  
; to PRANKED and makes a file in the folder with a fun name. Runs on 64-bit Linux only.
; 
; ----------------------------------------------------------------------------------------
    global main

    section .text

main: 
     validateInput:                       ; check to see if the correct amount of args given 
         cmp rdi, 3                       ; compare: value in rdi == 3? Checks for correct number of args
         jne printErrorInvalidArgs        ; jump to print error message
    rename:                               ; renames the folder to prank name instead of desired new name 
         mov rax, 82                      ; syscall for rename
         add rsi, 8                       ; looks at the next array element by adding 8 to the pointer in rsi
         mov rdi, [rsi]                   ; move the old name into rdi
         mov rsi, prankedName             ; move prankName into rsi instead of new name
         syscall                          ; invoke syscall
         jmp validateSyscallResult        ; jump to validate result 
    makeFile:                             ; makes new file 
         mov rax, 85                      ; syscall for make file
         mov rdi, newFile                 ; moves the prank pathname into rdi 
         mov rsi, 700q                    ; allocates file permissions for the user 
         syscall                          ; invoke syscall 
         jmp done                         ; jump to exit
    validateSyscallResult:                ; checks if syscall had an error or not 
         cmp rax, 0                       ; compare: value in rax == 0? 
         jne printErrorSyscall            ; print fail message
         je printSuccessSyscall           ; print success message
    printErrorInvalidArgs:                ; print error message for invalid args
         mov rax, 1                       ; put the syscall number in RAX
         mov rdi, 1                       ; move write destination into rdi
         mov rsi, argsErrorMessage        ; move error message into rsi
         mov rdx, 58                      ; move number of bytes to print into rdx
         syscall 
         jmp done                         ; jump to exit 
     printErrorSyscall:                   ; print error message for syscall error
         mov rax, 1                       ; put the syscall number in RAX
         mov rdi, 1                       ; move write destination into rdi
         mov rsi, syscallErrorMessage     ; move error message into rsi
         mov rdx, 80                      ; move number of bytes to print into rdx
         syscall 
         jmp done                         ; jump to exit
     printSuccessSyscall:                 ; print success message for syscall 
         mov rax, 1                       ; put the syscall number in RAX
         mov rdi, 1                       ; move write destination into rdi
         mov rsi, syscallSuccessMessage   ; move error message into rsi
         mov rdx, 38                      ; move number of bytes to print into rdx
         syscall 
         jmp makeFile                     ; jump to exit //jump to make new file
    done:                                 ; exit program 
         mov rax, 60                      ; syscall for exit
         mov rdi, 0                       ; exit code 0
         syscall 



section .data 
    argsErrorMessage: db "This program takes in exactly two command line arguments.", 10, 0
    syscallErrorMessage: db "Something went wrong. Please make sure the folder that you're renaming exists.", 10, 0 
    syscallSuccessMessage: db "Your folder was renamed successfully!", 10, 0
    prankedName: db "PRANKED", 0
    newFile: db "PRANKED/You_just_got_pranked!", 0 