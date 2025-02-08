global render_copy_asm
extern SDL_SetRenderDrawColor
extern SDL_RenderDrawPoint
extern printf

section .text

; rdi = *rend , rsi = *exist_color, rdx = rect.x , rcx = rect.y , r8 = rect.w, r9 = rect.h;

render_copy_asm:
    sub rsp, 8

	mov rbx, rsi
    mov [rect_x], rdx     ; SDL_Renderer* in rdi (unchanged)
    mov [rect_y], rcx     ; Unit8* in rsi (unchanged)
    mov [rect_w], r8     ; now address color_array in rdx (unchanged)
	mov [rect_h], r9

    ; Initialize x = 0, y = 0 , x = r11, y = r12
    xor r12, r12
    xor r13, r13       
    mov r15, 8       ; delta = 8

	jmp while_condition

while_condition:
	cmp r13, [rect_h] ;if y >= rect.h ->> end else while_body
	jge end_render_copy
	
while_body:
    ; Load RGBA values
	xor rax, rax
    mov rax, [rbx]    

    ; Check if pixel is not black
    test rax, rax
    jnz draw_pixel
    jmp update_xy

draw_pixel:
    ; Call SDL_RenderDrawPoint(renderer, x + rect->x, y + rect->y)

    ;rdi = SDL_Renderer* (unchanged)
	mov rsi, r12 ; second argument
	add rsi, [rect_x] ; third argument

    mov rdx, r13
	add rdx, [rect_y]

	mov r14, rdi
	call SDL_RenderDrawPoint

after_call:

	;mov rdi, format
	;call printf

	mov rdi, r14

	jmp update_xy

update_xy:
    ; increament rbx by delta * 4 (int size)
    mov rax, 4
	mov rdx, r15
	mul rdx

	add rbx, rax

	;increment x by delta
    add r12, r15

	; if x >= rect_w ->> correct x and  y 
	cmp r12, [rect_w]
    jge correct_xy      

    jmp while_condition

correct_xy:
	sub r12, [rect_w]
	inc r13

	cmp r12, [rect_w]
	jge correct_xy

	jmp while_condition

end_render_copy:
    add rsp, 8
    ret

section .data
	format: db "ttttt", 10, 0
    delta: dd 8

section .bss
    rect_w resq 1
	rect_h resq 1
	rect_x resq 1
	rect_y resq 1



