; ----------------------------------------------------------------------------------------
; Renames a folder from one console arg to another using system calls. 
; Runs on 64-bit Linux only.
; ----------------------------------------------------------------------------------------
    
    global main

    section .text

main: 
     validateInput:                       ; check to see if the correct amount of args given 
         cmp rdi, 3                       ; compare: value in rdi == 3? Checks for correct number of args
         jne printErrorInvalidArgs        ; jump to print error message

    rename:                               ; renames the folder to desired new name 
         mov rax, 82                      ; syscall for rename
         add rsi, 8                       ; looks at the next array element (old name) by adding 8 to the pointer in rsi
         mov rdi, [rsi]                   ; move the old name into rdi
         add rsi, 8                       ; looks at the next array element (new name) by adding 8 to the pointer in rsi
         mov rdx, [rsi]                   ; to avoid concurrent modification temporarily move new name to rdx
         mov rsi, rdx                     ; move new name from rdx to rsi 
         syscall                          ; invoke syscall
         jmp validateSyscallResult        ; jump to validate result 
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
         jmp done                         ; jump to exit
    done:                                 ; exit program 
         mov rax, 60                      ; syscall for exit
         mov rdi, 0                       ; exit code 0
         syscall 



section .data 
    argsErrorMessage: db "This program takes in exactly two command line arguments.", 10, 0
    syscallErrorMessage: db "Something went wrong. Please make sure the folder that you're renaming exists.", 10, 0 
    syscallSuccessMessage: db "Your folder was renamed successfully!", 10, 0
