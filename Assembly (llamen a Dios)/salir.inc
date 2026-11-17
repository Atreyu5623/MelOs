%ifndef SALIRDEFINIDO
%define SALIRDEFINIDO
salir:
push ax
push si
mov ah,[carpeta_actual]
cmp ah,0
je .Carpeta0
mov si,SisAlmacen
dec ah
.bucle:
    cmp ah,0
    je .Encontrado
    add si,32
    dec ah
    jmp .bucle
.Encontrado:
    mov ah,[si+30]
    mov [carpeta_actual],ah
    cmp ah,0
    je .Raiz
    mov si,SisAlmacen
    dec ah
.bucle2:
    cmp ah,0
    je .CopiarNombre
    add si,32
    dec ah
    jmp .bucle2
.CopiarNombre:
    mov ah,28
    push bx
    push cx
    mov bx,.Carpeta
.PonerNombre:
    cmp ah,0
    je .Sig
    mov word cx,[si]
    mov word [bx],cx
    add bx,2
    add si,2
    sub ah,2
    jmp .PonerNombre
.Sig:
    pop cx
    pop bx
    mov si,.Exitosotxt
    call imprimir_txt
    call saltolinea
.exit:
    pop si
    pop ax
    ret
.Carpeta0:
    mov si,.Carpeta0txt
    call imprimir_txt
    jmp .exit
.Raiz:
    mov si,.ExitosoRaiz
    call imprimir_txt
    jmp .exit
.Carpeta0txt: db "Ya te encuentras en la carpeta raiz.",finlin,0
.Exitosotxt: db "Se ha salido a la carpeta: "
.Carpeta: times 28 db 0
db 0
.ExitosoRaiz: db "Se ha salido a la carpeta Raiz.",finlin,0
%endif