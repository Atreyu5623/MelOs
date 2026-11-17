;si estás leyendo este código te deseo suerte
;cuando lo escribí, solo Dios sabia que estaba haciendo
;Ya no me responde cuando le rezo pidiendo ayuda

%include "constantes.inc"
%define firma 0xAA55
[bits 16] ; El compilador de nasm ahora sabe q esta mierda esta en 16 bits y no en 67
[org bootDirection] ; La dirección de memoria jeje (la que la bios lee y toda esa puta mierda)
boot:
    jmp .inicio
    times 90-($-$$) db 0 ; por si acaso la bios tiene BPB que puede usar hasta 89 bytes
.inicio:
    xor ax,ax
    mov ds,ax
    mov es,ax
    mov ss,ax ;la pila empieza en 0 ekide
    mov cx,ax
    mov dh,ah
    mov sp, 0x7C00 ; la direccion de memoria donde se encuentra el código, como la cima de la pila esta ahi, no tendremos problemas.
    cld
    mov ah,leer_sectores
    mov al,Sectores
    mov bx,Phase2Direction ; direccion de la memoria
    mov cl,2 ; sector del disco al q vamos
    int INT_DISCO
    jc .error
    jmp 0x0000:Phase2Direction
    .error:
    mov si,textoError
    call imprimir_txt
    mov si,codigoError
    mov [si],ah
    call imprimir_txt
    .halt:
    hlt
    jmp .halt
    %include "imprimir.inc"
    textoError: db "Error con el envio a la Fase 2 de booteo, codigo de error: "
    codigoError: db 0
    times 510-($-$$) db 0; $ = Linea actual, $$= Inicio del código
    dw firma