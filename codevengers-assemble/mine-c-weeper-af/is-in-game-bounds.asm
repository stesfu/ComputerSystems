			global	is_in_game_bounds

			section	.text
is_in_game_bounds:
			; ***** IMPLEMENT ME! *****
			cmp     esi, 0          ; if esi (int x) is less than 0 jump to false
			jl	    false

			cmp     edx, 0          ; if edx (int y) is less than 0 jump to false
			jl	    false

			mov     rax, rdi        ; move rdi into rax 
			mov     eax, [rax]      ; move first item in rax (width) into eax

			cmp     eax, esi        ; compare eax to esi (width and x)
			jle     false           ; jump to false if width is less than or equal to x   

			mov    rax, rdi         ; move rdi into rax
			mov    eax, [rax + 4]   ; move second item in rax (height) into eax 

			cmp    eax, edx         ; compare eax to edx (height and y)
			jle    false            ; jump to false if height is less than or equal to y 
			jmp    true             ; jump to true if no conflict arrises 
			
	
			

true:
			mov  	rax, 1
			ret

false:
			xor	    rax, rax
			ret
