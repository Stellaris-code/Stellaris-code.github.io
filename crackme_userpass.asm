BITS 64

	global    _start
	extern printf
	extern scanf
	extern strcmp
	extern exit
	extern memcmp

	section   .text
_start:
	mov rdi, user_str
	call printf	

	mov rdi, scanf_str
	mov rsi, user
	call scanf

	mov rdi, passwd_str
	call printf

	mov rdi, scanf_str
	mov rsi, passwd
	call scanf	

	mov rax, 0
	mov rcx, 0

	mov rsi, user
.user_loop:
	mov dl, [rsi]
	cmp dl, 0
	jz .user_out
	add al, dl
	inc rsi
	jmp .user_loop	
.user_out:

	mov rsi, passwd
.passwd_loop:
	mov dl, [rsi]
	cmp dl, 0
	jz .passwd_out
	add cl, dl
	add cl, dl
	inc rsi
	jmp .passwd_loop	
.passwd_out:

	sub cl, al
	cmp cl, 0
	jnz .bad
.good:
	mov rdi, goodboi
	call printf
	jmp .out
.bad:
	mov rdi, badboi
	call printf
.out:
	mov rdi, 0
	call exit
	
	


section   .rodata
user_str:
db	  "username: ", 0
passwd_str:
db	  "activation key: ", 0
scanf_str:
db "%s",0
goodboi:
db "Bravo, c'est le bon mot de passe!",10,0
badboi:
db "Invalide!",10,0

section .bss
user:
resb 50
passwd:
resb 50

