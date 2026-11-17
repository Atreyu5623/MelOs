%ifndef Imprimir16bitsEstaDefinido
%define Imprimir16bitsEstaDefinido
imprimir_txt: ;guardar datos de si ax bx
    push si
    push ax
    push bx
.loop:
    lodsb ; mov al,[si] / inc si (en un solo comando jeje)
    or al,al ;para las flags y asi
    jz .terminao
    mov ah,imp_letra
    mov bh,pant_visible
    int INT_VIDEO
    jmp .loop
.terminao: ;devolvar los datos y volver a donde se llamo xD
    pop bx
    pop ax
    pop si
    ret
%endif