%ifndef DIRDEFINIDO
%define DIRDEFINIDO
DIR:
mov [.archivoActual],si
push ax
push bx
push dx
mov dl,ah
push si
mov si,.titulo
call imprimir_txt
pop si
push si
mov bh,0
cmp dl,0
je .imp_MelOs
.bucle:
mov si,[.archivoActual]
cmp byte [si],0
je .exit
call .sig
add word [.archivoActual],32
jmp .bucle
.exit:
pop si
pop dx
pop bx
pop ax
ret
.sig:
add si,30
cmp dl,[si]
jne .ret
sub si,30
call .imprimir_Nombre_Archivo
mov al,[si]
call decirTipo
call saltolinea
ret

.ret:
ret
.retax:
pop ax
ret
.imprimir_Nombre_Archivo:
mov bl,28
push ax
mov ah,imp_letra
.bucle_imprimir_nombre:
mov al,[si]
int INT_VIDEO
inc si
cmp bl,0
je .retax
dec bl
jmp .bucle_imprimir_nombre
.imp_MelOs:
push si
mov si,.OsTXT
call imprimir_txt
pop si
jmp .bucle
.OsTXT:db "MelOs"
times 29-($-.OsTXT) db 0x20
db "img",finlin,0
.archivoActual: dw 0x0000
.titulo: db"Nombre" 
times 29-($-.titulo) db 0x20
db "Tipo de archivo",finlin,0
%endif