GLOBAL getKeyPressed

getKeyPressed:
	push rbp
	mov rbp,rsp

	xor rax,rax
    in al, 60h

    mov rsp,rbp
	pop rbp
    ret