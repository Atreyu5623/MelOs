Recomendaciones para leer el código:

Utilizamos visual code studio con la libreria de assembly x86_64 durante todo el desarrollo, por lo que recomendamos esa.
Name: x86 and x86_64 Assembly
Id: 13xforever.language-x86-64-assembly
Description: Cutting edge x86 and x86_64 assembly syntax highlighting
Version: 3.1.5
Publisher: 13xforever
VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=13xforever.language-x86-64-assembly

Instrucciones para compilar

REQUISITOS
- NASM instalado y agregado al PATH.
- QEMU instalado y agregado al PATH (se usa qemu-system-i386).
- Sistema Operativo Windows instalado

Para comprobar que estan en el PATH, abrir una terminal y escribir:
    nasm -v
    qemu-system-i386 --version

COMPILAR Y EJECUTAR
La forma fácil es hacer doble clic en compilar.bat, que ejecuta todos los
pasos de abajo en orden. Si se quiere hacer a mano, abrir una terminal en la
carpeta del proyecto y escribir los comandos uno por uno:

1) nasm -f bin boot.asm -o boot.bin
   Ensambla el bootloader (primera etapa) en binario.

2) nasm -f bin Fase2.asm -o Fase2.bin
   Ensambla el código principal en binario.

3) copy /b boot.bin+Fase2.bin os.img
   Une los 2 binarios en un archivo img

4) powershell -NoProfile -Command "$f=[IO.File]::Open('os.img','Open','Write'); $f.SetLength(1048576); $f.Close()"
   Agranda el tamaño del img a 1mb artificialmente para que QEMU pueda guardar y cargar documentos de texto (los documentos se guardan afuera de los sectores del sistema)

5) qemu-system-i386 -drive format=raw,file=os.img
   Abre el .img en el emulador

NOTA
Los archivos que se crean en melOs se guardan dentro de os.img. Si se vuelve
a ejecutar compilar.bat (o los pasos 1 al 4) se genera un os.img nuevo y se
pierde lo guardado. Para volver a abrir el sistema sin perder nada, usar solo
el comando del paso 5.