%include "constantes.inc"
[bits 16]
[org Phase2Direction]
boot2:
mov [disco],dl
call CargaContadores
call limpiarpantalla
mov si,Frase
call imprimir_txt
mov si,texto
mov ax,64
bucle:
    call leertexto
    call BusquedaComandos
    jmp bucle
.halt:
    hlt
    jmp .halt
%include "imprimir.inc"
%include "limpiarPantalla.inc"
%include "escribir.inc"
%include "saltolin.inc"
%include "comandos.inc"
%include "DefinirTipo.inc"
%include "DIRScript.inc"
%include "crear.inc"
%include "cargarContadores.inc"
%include "CompararStrings.inc"
%include "borrar.inc"
%include "abrir.inc"
%include "salir.inc"
%include "txteditor.inc"
Frase: db "melOs",finlin, "Bienvenido a melOs",finlin,"Escribe ayuda para ver la lista de comandos",finlin,0
texto: times 64 db 0
elementos_actuales: db 0
%define max_elementos 32 ;CADA SECTOR PUEDE TENER 16 ENTRADAS
elementos_max:db max_elementos
sectoresAlmacen: db 2
carpeta_actual: db 0
disco: db 0
DocTexto: times 512 db 0
times (512*Sectores-($-$$))-(max_elementos)*32 db 0
SisAlmacen: times (max_elementos)*32 db 0