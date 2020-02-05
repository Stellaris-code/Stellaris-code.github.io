; Command : nasm -f elf64 subst_mdp.asm -o chal3.o && ld chal3.o -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc -m elf_x86_64



BITS 64

	global    _start
	extern printf
	extern scanf
	extern strcmp
	extern exit
	extern memcmp

	section   .text
_start:
	mov rdi, welcome
	call printf	

	mov rdi, scanf_str
	mov rsi, buffer
	call scanf

subst_init:
	mov rcx, 32
	mov dl, 127
	sub dl, cl
	mov [substitution+rax], 	

	mov rsi, buffer
subst_loop:
	mov al, byte [rsi]
	cmp al, 0
	jz .subst_loop_out
        mov al, byte [substitution+rax]
	mov byte [rsi], al
	inc rsi
	jmp subst_loop
.subst_loop_out:


	mov rdi, mdp
	mov rsi, buffer
	mov rdx, 8
	call memcmp
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
db	  0xe3, 0xa3, 0xad, 0x92, 0xe8, 0x99, 0x9a, 0x9e
goodboi:
db "Bravo, c'est le bon mot de passe!",10,0
badboi:
db "Invalide!",10,0

section .bss
buffer:
resb 50
substitution:
resb 128
