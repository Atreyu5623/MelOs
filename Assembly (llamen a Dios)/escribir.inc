%ifndef EXISTEELESCRIBIRINC
%define EXISTEELESCRIBIRINC
leertexto:
    push cx
    mov cx,ax
    dec cx
    push ax
    push bx
    push si
    mov bh,0
    push dx
    mov dx,si
    push di
    mov di,si ;di = fin de lo escrito, si = posicion del cursor, dx = inicio del margen, cx= duracion del texto máxima (entra por ax)
    .bucle:
    mov ah,Esp_tecla
    int INT_TECLADO
    cmp al, 0x0D
    je .fin
    cmp al, 0x08
    je .backspace
    cmp al, 0x0
    je .esp
    cmp si,di
    je .comp
    .follow:
    mov [si],al
    cmp si,di
    jne .NoUltimoCaracter
    inc di
    dec cx
    .NoUltimoCaracter:
    inc si
    mov ah,imp_letra
    int INT_VIDEO
    jmp .bucle
    .comp:
    cmp cx,0
    je .bucle
    jmp .follow
    .fin:
    mov byte [di],0
    pop di
    pop dx
    pop si
    pop bx
    pop ax
    pop cx
    call saltolinea
    ret
    .backspace:
    cmp si,dx
    je .bucle
    cmp si,di
    jne .desigual
    dec di
    inc cx
    .desigual:    
    dec si
    mov ah,imp_letra
    int INT_VIDEO
    mov al,0x20
    int INT_VIDEO
    mov al,0x08
    int INT_VIDEO
    mov byte [si],0x20
    jmp .bucle
    .flecha_izq:
    cmp si,dx
    je .bucle
    dec si
    mov ah,imp_letra
    mov al,0x08
    int INT_VIDEO
    jmp .bucle
    .esp:
    cmp ah,0x4B
    je .flecha_izq
    cmp ah,0x4D
    je .flecha_der
    jmp .bucle
    .flecha_der:
    cmp si,di
    je .bucle
    mov al,[si]
    mov ah,imp_letra
    int INT_VIDEO
    inc si
    jmp .bucle
%endif