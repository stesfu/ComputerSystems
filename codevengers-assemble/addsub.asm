			global	main
			extern	atoi
			extern	strlen			; The specific externs that you will need
			extern	strncmp			; depend on your implementation; edit this
			extern	printf			; list as necessary.
			extern	puts

			section	.text
main:
			cmp	rdi, 4
			jne	incorrectArgumentCount

			mov     r12, [rsi + 8]    ; move first command line argument into r12
			mov     r13, [rsi + 16]   ; move second command line argument into r13
			mov     r14, [rsi + 24]   ; move third command line argument into r14

			push	r12			; The necessity of these will depend on implementation;
			push	r13			; this is mainly a reminder to preserve any callee-save
			push	r14			; registers that you might use.
			push    r15

	                ; Implement add/subtract here!
			; - operand conversion
			; - operator check
			; - the actual operation
			; - result display
convertArgs: 
            mov     rdi, r12           ; atoi(string_to_convert) <--- r12
			call    atoi               ; Result will be in rax (calling convention!).
			mov     r12, rax           ; move result back into r12

			mov     rdi, r14           ; atoi(string_to_convert) <--- r14
			call    atoi               ; Result will be in rax (calling convention!).
			mov     r14, rax           ; move result back into r14
			jmp     operatorCheck      ; jump to operatorCheck
operatorCheck:
            mov     rdi, r13           ; move operator into rdi
			call    strlen             ; put length of char in r13 into rax 
			cmp     rax, 1             ; length of operator should be one  
			jne     incorrectOperator  ; jump to incorrect operator

            mov     rdi, r13           ; move operator into rdi
			mov     rsi, plusOperator  ; move plus operator into rsi
			mov     rdx, 1             ; known length of plus operator 
			call    strncmp            ; strncmp(argv[1], plus, 1);
			cmp     rax, 0             ; Check if result is 0 
			je      generateSum        ; jump to generate sum

			mov     rsi, minusOperator ; move minus operator into rsi
			mov     rdx, 1             ; known length of minus operator 
			call    strncmp            ; strncmp(argv[1], plus, 1);
			cmp     rax, 0             ; Check if result is 0 
			je      generateDif        ; jump to generate difference
generateSum:
			mov     rax, r12           ; move first summand into rax
			add     rax, r14           ; add first and second summand (r12 and r13) 
			mov     r15, rax           ; move sum into r14
			jmp     formatResult       ; jump to formatResult
generateDif:
			mov     rax, r12           ; move minuend into rax
			sub     rax, r14           ; subtract subtrahend from minuend  (r12 and r13) 
			mov     r15, rax           ; move difference into r14
			jmp     formatResult       ; jump to formatResult
formatResult:
			mov     rdi, resultFormat  ; printf(resultFormat, number) <--- args in rdi then rsi, rdc, etc. 
			mov     rsi, r12           ; move first number into first %d
			mov     rdx, r13           ; move operator into first %s
			mov     rcx, r14           ; move second number into second %d
			mov     r8,  r15           ; move total into third %d
			xor     rax, rax           ; printf is special: needs rax to be 0.
			call	printf             ; call printf
			jmp     finished           ; jump to finish 

finished:
			pop r15
			pop	r14
			pop	r13
			pop	r12
			ret

incorrectArgumentCount:
			mov	rdi, incorrectArgumentCountMessage
			call	puts
			ret

incorrectOperator:
			mov	rdi, incorrectOperatorMessage
			call	puts
			jmp	finished

			section	.data
plusOperator:		db	"+", 0
minusOperator:		db	"-", 0
resultFormat:		db	"%d %s %d = %d", 10, 0

incorrectArgumentCountMessage:
			db	"To use this program, either enter <number> + <number> or <number> - <number>.", 0

incorrectOperatorMessage:
			db	"This program only recognizes + or -.", 0
