section .data
	x: db 0
	name: times 100 db 0
	scanf_prompti: db "Enter integer",10,0
	scanf_prompts: db "Enter String: ",10,0
	printf_prompti: db "Integer: ",10,0
	formats: db "%s",0	
	formati: db "%d",0

section .text
	global main
	extern scanf
	extern printf

main:
	push rbp
	lea rdi,[scanf_prompti]
	lea rsi,[name]
	lea rdx,[x]
	xor eax,eax
	call printf

	lea rsi,[x]
	lea rdi,[formati]
	xor eax,eax
	call scanf

	lea rdi,[formati]
	mov rsi,[x]
	xor eax,eax
	call printf 

	lea rdi,[scanf_prompts]
	lea rsi,[name]
	lea rdx,[x]
	xor eax,eax
	call printf
	
	lea rdi,[formats]
	lea rsi,[name]
	xor eax,eax
	call scanf

	lea rdi,[formats]
	lea rsi,[name]
	xor eax,eax
	call printf
	mov rax,0
	pop rbp
	ret
	

