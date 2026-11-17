%ifndef ABRIRDEFINIDO
%define ABRIRDEFINIDO
abrir:
    push ax
    push bx
    push si
    push cx
    mov bx,borrar.MelOs
    call COMPARARSTRINGS
    jz .ArchivoF
    mov bx,SisAlmacen
    mov ah,[elementos_actuales]
    mov al,[carpeta_actual]
    mov ch,1
.bucle:
    cmp ah,0
    je .NotFounded
    cmp [bx+30],al
    jne .sig
    call COMPARARSTRINGS
    jz .Founded
.sig:
    add bx,32
    inc ch
    dec ah
    jmp .bucle
.exit:
    mov byte [SectorAbierto],0
    pop cx
    pop si
    pop bx
    pop ax
    ret
.NotFounded:
    mov si,.txtNoencontrado
    call imprimir_txt
    jmp .exit
.Founded:
    cmp byte [bx+29],0
    jne .Archivo
    mov [carpeta_actual],ch
    mov si,.nombre
    mov ah,28
.BucleNombre:
    cmp ah,0
    je .Imp_encontrado
    mov word cx,[bx]
    mov word [si],cx
    add bx,2
    add si,2
    sub ah,2
    jmp .BucleNombre
.Imp_encontrado:
    mov si,.txtencontrado
    call imprimir_txt
    call saltolinea
    jmp .exit
.txtNoencontrado: db "No se ha podido encontrar el archivo buscado.",finlin,0
.txtencontrado: db "Se ha abierto la carpeta "
.nombre: times 29 db 0
db 0
.Archivo:
    cmp byte [bx+29],1
    je .txt
.ArchivoF:
    mov si,.ArchivoNoAbrible
    call imprimir_txt
    jmp .exit
.ArchivoNoAbrible: db "No se pudo abrir este archivo",finlin,0
.txt:
    mov ah,[bx+31]
    mov [SectorAbierto],ah
    call txtEdit
    jmp .exit
SectorAbierto: db 0
%endif