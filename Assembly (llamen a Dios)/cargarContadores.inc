%ifndef CARGARCONTADORESDEFINIDO
%define CARGARCONTADORESDEFINIDO
CargaContadores:
    push ax
    push si
    mov si,SisAlmacen
    mov byte [elementos_actuales],0
    mov al,[elementos_max]
.bucle:
    cmp al,0
    je .exit
    cmp byte [si],0
    je .exit
    inc byte [elementos_actuales]
    cmp byte [si+29],0
    je .sig
.sig:
    add si,32
    dec al
    jmp .bucle
.exit:
    pop si
    pop ax
    ret
%endif