section .text
GLOBAL _speakerHandler
EXTERN delay
speakerHandler:
	push rbp
	mov rbp,rsp
	xor rax,rax

	mov al, 10110110b

	out 43h, al

	mov al, 54

 	out 42h, al

 	mov al, 124

	out 42h, al

	in al, 61h
	or al, 00000011b     ;prende beep
	out 61h, al

	call delay

	in al, 61h 
	and al, 252			 ;apaga beep
	out 61h, al

	mov rsp,rbp
	pop rbp

