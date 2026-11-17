%ifndef COMPARARSTRINGSDEFINIDO
%define COMPARARSTRINGSDEFINIDO
COMPARARARCHIVO:
mov byte [byteacomparar],0x2E
jmp COMPARARSTRINGS.comparacion
COMPARARPALABRA:
mov byte [byteacomparar],0x20
jmp COMPARARSTRINGS.comparacion
COMPARARSTRINGS:
mov byte [byteacomparar],0
    .comparacion:
    push bx
    push si
    push ax
    push cx
    mov ch,[byteacomparar]
    .bucle:
    mov al,[bx]
    mov ah,[si]
    cmp al,ah
    jne .FALSO
    inc bx
    inc si
    cmp ah,ch
    je .VERDADERO
    jmp .bucle
.FALSO:
    or ax,1
    pop cx
    pop ax
    pop si
    pop bx
    ret
.VERDADERO:
    xor ax,ax
    pop cx
    pop ax
    pop si
    pop bx
    ret
byteacomparar: db 0
%endif