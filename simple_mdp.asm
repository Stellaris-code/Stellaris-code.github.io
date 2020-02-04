BITS 64

	global    _start
	extern printf
	extern scanf
	extern strcmp
	extern exit

	section   .text
_start:
	mov rdi, welcome
	call printf	

	mov rdi, scanf_str
	mov rsi, buffer
	call scanf	



	mov rdi, mdp
	mov rsi, buffer
	call strcmp
	jnz .bad
	
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
welcome:
db	  "Entrez le mot de passe :", 10, 0
scanf_str:
db "%s",0
out_msg:
db        "Hello, World", 10, 0      ; note the newline at the end
mdp:
db	  "x86isbae",0
goodboi:
db "Bravo, c'est le bon mot de passe!",10,0
badboi:
db "Invalide!",10,0

section .bss
buffer:
resb 50
