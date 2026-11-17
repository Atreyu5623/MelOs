%ifndef TXTEDITORDEFINIDO ;64 bytes por linea, 512 bytes , 8 lineas
%define TXTEDITORDEFINIDO
    txtEdit:
    push ax
    push bx
    push cx
    push dx
    push si
    mov ah,cambiarPagActiva
    mov al,1
    int INT_VIDEO
    mov ah,movercursor
    mov bh,1
    mov dh,0
    mov dl,0
    int INT_VIDEO
    .CargarTexto:
    mov ah,leer_sectores
    mov al,1
    mov bx,DocTexto
    mov ch,0
    mov dh,0
    mov cl,[SectorAbierto]
    mov dl,[disco]
    int INT_DISCO
    jc .errorCarga
    mov si,DocTexto
    mov cx,0
    mov dl,0
    mov dh,0
    .BucleCarga:
    cmp cx,512
    je .Cargado
    cmp dl,64
    je .FinLinCARGA
    mov ah,imp_letra
    mov al,[si]
    mov bh,1
    int INT_VIDEO
    inc cx
    inc si
    inc dl
    jmp .BucleCarga
    .Cargado:
    mov ah,movercursor
    mov bh,1
    mov dh,0
    mov dl,0
    int INT_VIDEO
    mov si,DocTexto
    mov dh,0
    mov dl,0
    .BucleEspera:
    mov ah,Esp_tecla
    int INT_TECLADO
    cmp al,0x1B
    je .guardar
    cmp al,0
    je .Especiales
    cmp al,0x0D
    je .Enter
    cmp al,0x08
    je .backspace
    cmp al,0x20
    jb .BucleEspera
    cmp dl,64
    je .FinLin
    cmp si,DocTexto+512
    je .BucleEspera
    mov ah,imp_letra
    mov bh,1
    int INT_VIDEO
    
    mov [si],al
    inc si
    inc dl
    jmp .BucleEspera
    .Especiales:
    cmp ah,0x4B
    je .flecha_izq
    cmp ah,0x4D
    je .flecha_der
    cmp ah,0x48
    je .flecha_arriba
    cmp ah,0x50
    je .flecha_abajo
    jmp .BucleEspera
    .guardar:
    mov ah,escribir_sectores
    mov al,1
    mov bx,DocTexto
    mov ch,0
    mov dh,0
    mov cl,[SectorAbierto]
    mov dl,[disco]
    int INT_DISCO
    jc .errorGuardado
    .limpiarPantalla:
    mov ah,desplazarzona
    mov al,borrarventana
    mov bh,gris
    mov ch,0
    mov cl,0
    mov dh,0x18
    mov dl,0x4F
    int INT_VIDEO
    mov ah,movercursor
    mov bh,1
    mov dh,0
    mov dl,0
    int INT_VIDEO
    .exit:
    mov bx,0
    mov si,DocTexto
    .bucleLimpieza:
    cmp bx,512
    je .exit2
    mov byte [si],0
    inc si
    inc bx
    jmp .bucleLimpieza
    .exit2:
    mov ah,cambiarPagActiva
    mov al,pant_visible
    int INT_VIDEO
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
    .errorCarga:
    mov ah,cambiarPagActiva
    mov al,pant_visible
    int INT_VIDEO
    mov si,.msg_error0
    call imprimir_txt
    jmp .exit
    .errorGuardado:
    mov ah,cambiarPagActiva
    mov al,pant_visible
    int INT_VIDEO
    mov si,.msg_error1
    call imprimir_txt
    jmp .exit
    .msg_error0: db "No se ha podido cargar el archivo del disco correctamente.",finlin,0
    .msg_error1: db "No se ha podido guardar el archivo al disco correctamente.",finlin,0
    .FinLinCARGA:
    inc dh
    mov dl,0
    mov ah,movercursor
    mov bh,1
    int INT_VIDEO
    jmp .BucleCarga
    .FinLin:
    cmp dh,7
    je .BucleEspera
    inc dh
    mov dl,0
    jmp .ActLinea
    .InLin:
    cmp dh,0
    je .BucleEspera
    dec si
    dec dh
    mov dl,63
    jmp .ActLinea
    .BajarLinea:
    cmp dh,7
    je .BucleEspera
    add si,64
    inc dh
    jmp .ActLinea
    .SubirLinea:
    cmp dh,0
    je .BucleEspera
    add si,64
    dec dh
    jmp .ActLinea
    .ActLinea:
    mov ah,movercursor
    mov bh,1
    int INT_VIDEO
    jmp .BucleEspera
    .flecha_izq:
    cmp dl,0
    je .InLin
    dec si
    dec dl
    jmp .ActLinea
    .flecha_der:
    cmp dl,64
    je .FinLin
    inc si
    inc dl
    jmp .ActLinea
    .flecha_arriba:
    cmp dh,0
    je .BucleEspera
    sub si,64
    dec dh
    jmp .ActLinea
    .flecha_abajo:
    cmp dh,7
    je .BucleEspera
    add si,64
    inc dh
    jmp .ActLinea
    .backspace:
    cmp dl,0
    je .InLin
    mov bh,1
    int INT_VIDEO
    mov ah,imp_letra
    mov al,0
    int INT_VIDEO
    mov ah,imp_letra
    mov al,8
    int INT_VIDEO
    dec si
    dec dl
    mov byte [si],0
    jmp .BucleEspera
    .Enter:
    cmp dh,7
    je .BucleEspera
    cmp dh,0
    jle .Lin1
    cmp dh,1
    jle .Lin2
    cmp dh,2
    jle .Lin3
    cmp dh,3
    jle .Lin4
    cmp dh,4
    jle .Lin5
    cmp dh,5
    jle .Lin6
    jmp .Lin7
    .FinEnter:
    jmp .FinLin
    .Lin1:
    mov si,DocTexto+64
    jmp .FinEnter
    .Lin2:
    mov si,DocTexto+128
    jmp .FinEnter
    .Lin3:
    mov si,DocTexto+192
    jmp .FinEnter
    .Lin4:
    mov si,DocTexto+256
    jmp .FinEnter
    .Lin5:
    mov si,DocTexto+320
    jmp .FinEnter
    .Lin6:
    mov si,DocTexto+384
    jmp .FinEnter
    .Lin7:
    mov si,DocTexto+448
    jmp .FinEnter
%endif