%ifndef COMANDOSDEFINIDOS
%define COMANDOSDEFINIDOS
BusquedaComandos:
    push si
    push ax
    mov al,[si]
    push si
    call .minusculas
    pop si
    .start:
    mov bx,.abrirCMD
    call COMPARARPALABRA
    jz .abrir
    mov bx,.ayudaCMD
    call COMPARARSTRINGS
    jz .ayuda
    mov bx,.borrarCMD
    call COMPARARPALABRA
    jz .borrar
    mov bx,.crearCMD
    call COMPARARPALABRA
    jz .crear
    mov bx,.ecoCMD
    call COMPARARPALABRA
    jz .eco
    mov bx,.dirCMD
    call COMPARARSTRINGS
    jz .dir
    mov bx,.limpiarCMD
    call COMPARARSTRINGS
    jz .limpiar
    mov bx,.salirCMD
    call COMPARARSTRINGS
    jz .salir
    jmp .fallido

    .abrir:
    add si,6
    call abrir
    jmp .exit

    .ayuda:
    mov si,.ayudatxt
    call imprimir_txt
    jmp .exit

    .borrar:
    add si,7
    call borrar
    jmp .exit

    .crear:
    add si,6
    call crear_arch
    jmp .exit
    
    .dir:
    mov ah,[carpeta_actual]
    mov si,SisAlmacen
    call DIR
    jmp .exit
    
    .eco:
    add si,4  
    call imprimir_txt
    call saltolinea
    jmp .exit
    
    .limpiar:
    call limpiarpantalla
    jmp .exit
    
    .salir:
    call salir
    jmp .exit

    .exit:
    pop ax
    pop si
    ret

    .fallido:
    mov si,.textofalla
    call imprimir_txt
    jmp .exit

    .minusculas:
    cmp al,0x41
    jl .NoLetras
    cmp al,0x5A
    jg .NoLetras
    add al,0x20
    mov [si],al
    .NoLetras:
    cmp al,0
    je .ret
    cmp al,0x20
    je .ret
    .sig:
    inc si
    mov al,[si]
    jmp .minusculas
    .ret:
    ret
    .textofalla: db "Comando erroneo, prueba escribir ayuda para ver la lista de comandos",finlin,0
    .ayudatxt: db "LISTA DE COMANDOS:",finlin
    .ayudaabrir: db "Abrir: abre una carpeta, o un archivo",finlin
    .ayudaayuda: db "Ayuda: Muestra esta lista",finlin
    .ayudaCrear: db "Crear nombre.tipo: crea un archivo con el nombre y tipo dados en la carpeta actual",finlin
    .ayudaBorrar: db "Borrar nombre: borra el archivo con el nombre dado en la carpeta actual",finlin
    .ayudaeco: db "Eco: repite tu mensaje",finlin
    .ayudaDir: db "Dir: Muestra los archivos del directorio (Carpeta)",finlin
    .ayudalimpiar: db "Limpiar: Limpia la pantalla",finlin
    .ayudasalir: db "Salir: sal de la carpeta actual",finlin
    .ayudaFin : db 0
    .abrirCMD: db "abrir",0x20
    .ayudaCMD: db "ayuda",0
    .borrarCMD: db "borrar",0x20
    .crearCMD: db "crear",0x20
    .dirCMD: db "dir",0
    .ecoCMD: db "eco",0x20
    .limpiarCMD: db "limpiar",0
    .salirCMD: db "salir",0
%endif