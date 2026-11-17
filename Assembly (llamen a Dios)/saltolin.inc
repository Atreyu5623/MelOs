%ifndef SALTODELINEADEFINIDO
%define SALTODELINEADEFINIDO
    saltolinea:
    push ax
    push bx
    mov ah,imp_letra
    mov al,0x0D
    mov bh,pant_visible
    int INT_VIDEO
    mov al,0x0A
    mov bh,pant_visible
    int INT_VIDEO
    pop bx
    pop ax
    ret
%endif