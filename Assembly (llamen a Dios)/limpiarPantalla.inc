%ifndef LimpiarPantallaIsDefined
%define LimpiarPantallaIsDefined
limpiarpantalla:
    push ax
    mov ax,modo_texto
    int INT_VIDEO
    pop ax
    ret
%endif