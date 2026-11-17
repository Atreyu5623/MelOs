%ifndef TIPOSARCHIVOS
%define TIPOSARCHIVOS
decirTipo:
push ax
push si
cmp al,0
je .file
cmp al,1
je .note
jmp .invalid
.file:
mov si,Casefile
call imprimir_txt
jmp .exit
.note:
mov si,Casenote
call imprimir_txt
jmp .exit
.invalid:
mov si,CaseInvalid
call imprimir_txt
jmp .exit

.exit:
pop si
pop ax
ret
Casefile: db "Carpeta",0
Casenote: db ".txt",0
CaseInvalid: db "?",0
DefinirTipoInverso:
    push si
    push bx
    push si
    mov al,[si]
    call BusquedaComandos.minusculas
    pop si
    mov bx,.carpetaCMD
    call COMPARARSTRINGS
    jz .carpeta
    mov bx,.dirCMD
    call COMPARARSTRINGS
    jz .carpeta
    mov bx,.txtCMD
    call COMPARARSTRINGS
    jz .txt
    jmp .false

    .carpeta:
    mov ah,0
    jmp .true

    .txt:
    mov ah,1
    jmp .true

    .false:
    or al,1
    pop bx
    pop si
    ret
    .true:
    xor al,al
    pop bx
    pop si
    ret
    .carpetaCMD: db "carpeta",0
    .dirCMD: db "dir",0
    .txtCMD: db "txt",0
%endif