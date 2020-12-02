			global	main
			extern	puts
			extern	sscanf
			extern	printf
			extern	emit_utf_8

			section	.text
main:
			; You can use the echo.asm sample program as a starting point
			; for this, but note that the solution differs in significant
			; ways so be ready to modify it as needed.
			cmp     rdi, 2                              ; check how many args typed in
			jl      argumentsError                      ; jump to argumentsError if less than two args typed in
			
			push    rdi                                 ; save registers 
			push    rsi 
			sub     rsp, 8                              ; must align stack before call 

			jnz     clear                               ; if not done counting keep going 

clear: 
            add     rsp, 8                              ; restore %rsp to pre-aligned value
			pop     rsi                                 ; restore registers used 
			pop     rdi                                 

			add     rsi, 8                              ; point to next argument 
			dec     rdi                                 ; count down
			jnz     convertArgs                         ; if not done counting keep going  
			jmp     done                                ; jump to done 
convertArgs:
            push    rdi 
			push    rsi 
			sub     rsp, 8 

			mov     r12, [rsi]                          ; move code point string into r13
			mov     rdi, r12                            ; move code point into rdi (for sscanf)
			mov     rsi, codePointFormat                ; move code point format into rsi
			mov     rdx, codePoint                      ; move code point format into rdx 
			call    sscanf                              ; sscanf(code_point_string, codePointFormat, codePoint) 
			cmp     rax, 1                              ; compare if rax is equal to 1 
			jne     formatError                         ; if not equal to 1 jump to formatError
			mov     rdi, [codePoint]                    ; move codePoint into rdi 
			call    emit_utf_8                          ; emit_utf_8(codePoint) 
			jmp     clear                               ; jump to clear 

formatError:
            mov     rsi, r12                            ; move r12 into rsi 
			mov     rdi, incorrectFormat                ; put incorrect message into rdi 
			xor     rax, rax                            ; printf is special: needs rax to be 0  
			call    printf                
			jmp     clear                               ; jump to clear 
argumentsError:	
        	mov	    rdi, argumentsRequiredMessage
			call	puts

			mov	    rdi, argumentDescription
			call	puts

			xor	    rax, rax
			inc	    rax
			ret

			section	.data
			; The following definitions are here to get you started and to standardize
			; error messages but of course, feel free to define more as needed.
done:
            mov     rdi, newLine                         ; make a new line 
			xor     rax, rax                             ; printf is special: needs rax to be 0 
			call    printf
			ret                      

argumentsRequiredMessage:
			db	"This program requires one or more command line arguments,", 0
argumentDescription:
        	db	"one for each code point to encode as UTF-8.", 0
incorrectFormat:	
            db	"(%s incorrect format)", 0
codePointFormat:	
            db	"U+%6X", 0
newLine:
            db "", 10

			section	.bss
codePoint:		
            resb	8			; The code point from sscanf should go here.

