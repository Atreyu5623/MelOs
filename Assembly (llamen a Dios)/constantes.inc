; ID de las interrupciones XDDD
%define INT_VIDEO      0x10
    %define imp_letra      0x0e
        %define pant_visible 0
    %define modo_texto 3
    %define cambiarPagActiva 5 ; 0=pant visible (pantalla principal), 1 pantalla de bloc de notas
    %define movercursor 2
    %define desplazarzona 6
        %define borrarventana 0
%define INT_EQUIPO     0x11   ; lista de equipo instalado
%define INT_MEMORIA    0x12
%define INT_DISCO      0x13
    %define leer_sectores 2
    %define escribir_sectores 3
%define INT_SISTEMA    0x15
%define INT_TECLADO    0x16
    %define Esp_tecla  0
%define INT_REINICIO   0x19
%define INT_RELOJ      0x1A
; direcciones
%define bootDirection 0x7c00
%define Phase2Direction 0x7e00
;cosas utiles
%define finlin 0x0D,0x0A
%define Sectores 18
;colores:
%define gris 7