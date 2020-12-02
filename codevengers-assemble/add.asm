			global	main
			extern	atoi
			extern	printf
			extern	puts

			section	.text
main:
			cmp	rdi, 3
			jne	incorrectArgumentCount

			mov     r12, [rsi + 8]    ; move first command line argument into r12
			mov     r13, [rsi + 16]   ; move second command line argument into r13



			push	r12			      ; The necessity of these will depend on implementation;
			push	r13			      ; this is mainly a reminder to preserve any callee-save
			push	r14			      ; registers that you might use.

			; Implement addition here!
convertArgs:
			mov     rdi, r12          ; atoi(string_to_convert) <--- r12
			call    atoi              ; Result will be in rax (calling convention!).
			mov     r12, rax          ; move result back into r12

			mov     rdi, r13          ; atoi(string_to_convert) <--- r13
			call    atoi              ; Result will be in rax (calling convention!).
			mov     r13, rax          ; move result back into r13
			jmp     generateSum       ; jump to generateSum
generateSum:
			mov     rax, r12          ; move first summand into rax
			add     rax, r13          ; add first and second summand (r12 and r13) 
			mov     r14, rax          ; move sum into r14
			jmp     formatResult      ; jump to formatResult
formatResult:
			mov     rdi, format       ; printf(resultFormat, number) <--- args in rdi then rsi, rdc, etc. 
			mov     rsi, r12          ; move first summand into first %d
			mov     rdx, r13          ; move second summand into second %d
			mov     rcx, r14          ; move sum into third %d
			xor     rax, rax          ; printf is special: needs rax to be 0.
			call	printf            ; call printf
			jmp     done              ; jump to done 
done:
			pop	    r14
			pop	    r13
			pop	    r12
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

			section	.data
incorrectArgumentCountMessage:
			db	"Two arguments are needed in order to perform addition.", 0
format:			db	"%d + %d = %d", 10, 0


