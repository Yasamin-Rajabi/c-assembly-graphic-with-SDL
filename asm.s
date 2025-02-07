global get_asm_xy
extern printf

section .text

get_asm_xy:
    sub rsp, 8   ; Align stack to 16 bytes for printf

	movlhps xmm1, xmm1
	movlhps xmm2, xmm3
	
    ; (degree) xmm0 = xmm0 / 180
    movsd xmm3, qword [pi_deg]
    divsd xmm0, xmm3

    ; xmm0 = (degree / 180) * pi
    movsd xmm3, qword [pi]
    mulsd xmm0, xmm3

	movsd xmm3, xmm0

    ; xmm0 = cos(r) // first double - r -> degree in radians 
    movsd [temp], xmm0
    fld qword [temp]
    fcos
    fstp qword [temp]
    movsd xmm0, [temp]

	; xmm0 = sin(r) // second double
	movsd [temp], xmm3
	fld qword [temp]
	fsin
	fstp qword [temp]
	movhpd xmm0, [temp]

    ; xmm0 = xmm0 * speed -- vector mull
    mulpd xmm0, xmm1

    ; xmm0 = xmm0 + x0 -- vector add
    addpd xmm0, xmm2

	movhlps xmm1, xmm0

    add rsp, 8   ; Restore stack alignment
    ret

section .data
    printf_format: db "%lf", 10, 0
    pi  dq  3.141592653589793
    pi_deg dq 180.0

section .bss
    temp resq 1

