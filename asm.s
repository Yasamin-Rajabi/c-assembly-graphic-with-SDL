global get_asm_x
global get_asm_y
extern printf

section .text

get_asm_x:
    sub rsp, 8   ; Align stack to 16 bytes for printf

    ; Print ddegree (xmm0)
    ;movq rsi, xmm0
    ;mov rdi, printf_format
    ;call printf

    ; Print dSpeed (xmm1)
	;movsd xmm0, [rsp + 24];
    ;movq rsi, xmm0
    ;mov rdi, printf_format
    ;call printf

    ; Print ballX (xmm2)
	;movsd xmm0, [rsp + 32]
    ;movq rsi, xmm0
    ;mov rdi, printf_format
    ;call printf

    ; (degree) xmm0 = xmm0 / 180
    movsd xmm3, qword [pi_deg]
    divsd xmm0, xmm3

    ; xmm0 = (degree / 180) * pi
    movsd xmm3, qword [pi]
    mulsd xmm0, xmm3

    ; xmm0 = cos(xmm0)
    movsd [temp], xmm0
    fld qword [temp]
    fcos
    fstp qword [temp]
    movsd xmm0, [temp]

    ; xmm0 = xmm0 * speed
    mulsd xmm0, xmm1

    ; xmm0 = xmm0 + x0
    addsd xmm0, xmm2

    add rsp, 8   ; Restore stack alignment
    ret

get_asm_y:
    sub rsp, 8   ; Align stack

    ; (degree) xmm0 = xmm0 / 180
    movsd xmm3, qword [pi_deg]
    divsd xmm0, xmm3

    ; xmm0 = (degree / 180) * pi
    movsd xmm3, qword [pi]
    mulsd xmm0, xmm3

    ; xmm0 = sin(xmm0)
    movsd [temp], xmm0
    fld qword [temp]
    fsin
    fstp qword [temp]
    movsd xmm0, [temp]

    ; xmm0 = xmm0 * speed
    mulsd xmm0, xmm1

    ; xmm0 = xmm0 + x0
    addsd xmm0, xmm2
    
    add rsp, 8  ; Restore stack alignment
    ret

section .data
    printf_format: db "%lf", 10, 0
    pi  dq  3.141592653589793
    pi_deg dq 180.0

section .bss
    temp resq 1

