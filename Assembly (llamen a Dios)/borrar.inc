%ifndef BORRARDEFINIDO
%define BORRARDEFINIDO
borrar:
    push ax
    push bx
    push cx
    push dx
    push si
    mov bx,.MelOs
    call COMPARARSTRINGS
    jz .Nopermitido
    mov [.InicioStr],si
    mov bx,SisAlmacen
    mov al,[carpeta_actual]
    mov ch,[elementos_actuales]
    mov cl,1
.bucle:
    cmp ch,0
    je .noEncontrado
    mov ah,[bx+30]
    cmp ah,al
    je .comparar
.sig:
    add bx,32
    dec ch
    inc cl
    jmp .bucle
.exit:
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
.comparar:
    mov si,[.InicioStr]
    call COMPARARSTRINGS
    jnz .sig
.borrarArchivos:
    .marcarhijos:
    mov si,SisAlmacen
    mov ch,[elementos_actuales]
    .bucleMarca:
    cmp ch,0
    je .continuar
    cmp [si+30],cl
    jne .sigMarcar
    mov byte [si+30],0xFF
    .sigMarcar:
    add si,32
    dec ch
    jmp .bucleMarca
    .continuar:
    mov ch,[elementos_actuales]
    sub ch,cl
    inc ch
    cmp ch,1
    je .ExcepcionSolo0
    mov ah,32
.borrarRam:
    cmp ah,0
    je .SigRam
    mov dl,[bx+32]
    mov [bx],dl
    inc bx
    dec ah
    jmp .borrarRam
.SigRam:
    mov ah,32
    dec ch
    cmp ch,1
    jne .borrarRam
.ExcepcionSolo0:
    mov ah,32
.ExcepcionBucle:
    mov byte [bx],0
    inc bx
    cmp ah,1
    je .ajustarPadres
    dec ah
    jmp .ExcepcionBucle
.ajustarPadres:
    dec byte [elementos_actuales]
    mov si,SisAlmacen
    mov ch,[elementos_actuales]
.bucleAjuste:
    cmp ch,0
    je .buscarHuerfanos
    cmp byte [si+30],0xFF
    je .sigAjuste
    cmp [si+30],cl
    jle .sigAjuste
    dec byte [si+30]
.sigAjuste:
    add si,32
    dec ch
    jmp .bucleAjuste
.buscarHuerfanos:
    mov bx,SisAlmacen
    mov cl,1
    mov ch,[elementos_actuales]
.bucleHuerfano:
    cmp ch,0
    je .borrarDisco
    cmp byte [bx+30],0xFF
    je .marcarhijos
    add bx,32
    inc cl
    dec ch
    jmp .bucleHuerfano
.borrarDisco:
    mov ah,escribir_sectores
    mov al,2
    mov bx,SisAlmacen
    mov dh,0
    mov dl,[disco]
    mov ch,0
    mov cl,Sectores
    int INT_DISCO
    jc .ERROR
    jmp .exit
.Nopermitido: 
mov si,.txtNoPermitido
call imprimir_txt
jmp .exit
.noEncontrado:
mov si,.txtNoenc
call imprimir_txt
jmp .exit
.ERROR:
    mov [.codigoerror],ah
    mov si,.txtError
    call imprimir_txt
    jmp .exit
.txtNoenc: db "El archivo no se ha podido encontrar en la carpeta actual",finlin,0
.MelOs: db "MelOs",0
.txtNoPermitido: db "No se puede  borrar el archivo melOs.",finlin,0
.InicioStr: dw 0
.txtError: db "Ha ocurrido un error al ejecutar el comando, id:"
.codigoerror: db 0,0
%endif