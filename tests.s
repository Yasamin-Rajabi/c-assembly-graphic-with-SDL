global draw_point_asm
extern SDL_RenderDrawPoint

section .text

draw_point_asm:
	sub rsp, 8
	
	;rax -> SDL_Renderer* , rcx = x, rdx = y;

	;System V AMD64 Calling Convention
	;For integer arguments (like pointers and integers), the first six are passed in:

	;rdi - First argument
	;rsi - Second argument
	;rdx - Third argument

	mov rdi, rax
	mov rsi, rcx
    call SDL_RenderDrawPoint


	add rsp, 8
	ret

section .data
    printf_format: db "%lf", 10, 0
    delta: dd 8

section .bss
    rect_w resd 1
	rect_h resd 1
	rect_x resd 1
	rect_y resd 1


