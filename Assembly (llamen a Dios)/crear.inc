%ifndef CREARARCHIVOSDEFINIDO
%define CREARARCHIVOSDEFINIDO
%define punto 0x2E
crear_arch:
    push ax
    push si
    push bx
    mov bx,.MelOsTXT
    call COMPARARARCHIVO
    jz .EntradaMelOs
    pop bx
    push bx
    push dx
    mov dh,[elementos_actuales]
    mov dl,[elementos_max]
    cmp dh,dl
    je .SinEspacio
    pop dx
    mov ah,29
    mov bx,si
.bucle:
mov al,[si]
cmp al,punto
je .encontrado
cmp al,0
je .invalidoArch
inc si
dec ah
cmp ah,1
je .invalido
jmp .bucle
.exit:
mov byte [.noescarpeta],0
mov byte [.sectorGuardable],Sectores+2
pop bx
pop si
pop ax
ret 
.encontrado:
cmp si,bx
je .invalidoArch
mov [.finNombre],Si
inc si
call DefinirTipoInverso
jnz .invalidoArch
jmp .guardar
.invalido:
mov si,.txtinvalido
call imprimir_txt
jmp .exit
.invalidoArch:
mov si,.archivoinvalido
call imprimir_txt
jmp .exit
.SinEspacio: 
mov si,.SinEspaciotxt
call imprimir_txt
pop dx
jmp .exit
.txtinvalido: db "El nombre es demasiado largo, por favor intenta con un nombre mas corto.",finlin,0
.archivoinvalido: db "El tipo de archivo es invalido, por favor intenta con un nombre valido",finlin,0
.SinEspaciotxt: db "Se ha quedado sin espacio en el gestor de archivos, por favor, borre algun archivo",finlin,0
.guardar:
    mov al,[elementos_actuales]
    mov si,SisAlmacen
.LlegarAlArchivo:
    cmp al,0
    je .ArchivoParaEscribir
    dec al
    add si,32
    jmp .LlegarAlArchivo
.ArchivoParaEscribir:
    mov al,29
    push dx
    push Si
    .BucleEscribirNombre:
    cmp bx,[.finNombre]
    je .EscribirTipo
    mov dh,[bx]
    mov [si],dh
    inc si
    inc bx
    dec al
    cmp al,1
    je .EscribirTipo
    jmp .BucleEscribirNombre
    .EscribirTipo:
    Pop si
    add si,29
    mov [si],ah
    .EscribirPadre:
    inc si
    mov dh,[carpeta_actual]
    mov [si],dh
    inc si
    mov byte [si],0
    .Guardable:
    cmp ah,0
    je .NoGuardable
    mov byte [.noescarpeta],1
    mov ch,[elementos_actuales]
    mov cl,[.sectorGuardable]
    mov bx,SisAlmacen
.BuscarSectorLibre:
    cmp ch,0
    je .SectorLibreEncontrado
    cmp cl,[bx+31]
    je .remp
    add bx,32
    dec ch
    jmp .BuscarSectorLibre
    .remp:
    inc cl
    mov bx,SisAlmacen
    mov ch,[elementos_actuales]
    jmp .BuscarSectorLibre
    .SectorLibreEncontrado:
    mov [.SectorAEscribir],cl
    mov [si],cl
    .NoGuardable:
    pop dx
    push dx
.GuardarenDisco:
    mov ah,escribir_sectores
    mov ch,0
    mov dh,0
    mov cl,Sectores
    sub cl,[sectoresAlmacen]
    add cl,2
    mov al,[sectoresAlmacen]
    mov dl,[disco]
    mov bx,SisAlmacen
    int INT_DISCO
    jc .errorDisco
    inc byte [elementos_actuales]
    pop dx
    mov si,.Completado
    call imprimir_txt
.GuardarEnMemoria:
    mov ah,[.noescarpeta]
    cmp ah,0
    je .exit
    mov cl,[.SectorAEscribir]
    mov ah,escribir_sectores
    mov al,1
    mov ch,0
    mov dh,0
    mov dl,[disco]
    mov bx,DocTexto
    int INT_DISCO
    jc .errorAsignacion
    jmp .exit
.errorDisco:
    pop dx
    mov si,.codigoError
    mov [si],ah
    mov si,.txtErrorDisco
    call imprimir_txt
    jmp .exit
.errorAsignacion:
    mov si,.codigoError2
    mov [si],ah
    mov si,.txtErrorDisco2
    call imprimir_txt
    jmp .exit
.EntradaMelOs:
mov si,.MelOsTXTreservado
call imprimir_txt
jmp .exit
.finNombre: dw 0
.SectorAEscribir: db 0
.txtErrorDisco: db "Ha ocurrido un error con el disco(Sistema de archivos)",finlin,"Codigo de error:"
.codigoError: db 0,finlin,0
.Completado:  db "Se ha guardado correctamente en el sistema de archivos",finlin,0
.noescarpeta: db 0
.txtErrorDisco2: db "Ha ocurrido un error con el disco(Reserva de espacio para el documento)",finlin,"Codigo de error:"
.codigoError2: db 0,finlin,0
.sectorGuardable: db Sectores + 2
.MelOsTXT: db "MelOs",punto
.MelOsTXTreservado: db "El nombre MelOs no se puede utilizar, esta reservado.",finlin,0
%endif