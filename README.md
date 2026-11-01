# Plane Crazy

Juego en desarrollo hecho en C con Raylib. Actualmente contiene un menu principal, musica y un fondo animado. Las pantallas de juego y opciones aun no estan implementadas.

## Autores

- [@juanchairez](https://www.github.com/juanchairez)
- [@adrianhumberto](https://www.github.com/adev-hash)
- [@Leo-sbl](https://www.github.com/Leo-sbl)
- [@jisuscries428](https://www.github.com/jisuscries428)
- [@ICaballero07](https://www.github.com/ICaballero07)

## Requisitos

- Windows con MSYS2 UCRT64.
- GCC compatible con C17.
- Raylib instalada para el entorno UCRT64.

Para instalar GCC y Raylib desde la terminal **MSYS2 UCRT64**:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib
```

## Compilar y ejecutar

Las rutas de imagen y audio del programa son relativas al directorio `src`. Compila y ejecuta el juego desde ese directorio.

Desde PowerShell, en la raiz del repositorio:

```powershell
cd .\src
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c17 -Wall -Wextra principal.c assets\ui\menu.c assets\ui\fondo.c assets\ui\animaciones.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
.\main.exe
```

Para compilar desde VS Code, abre `src` como carpeta de trabajo y ejecuta **Terminal > Run Build Task** o presiona `Ctrl+Shift+B`. La tarea configurada en `.vscode/tasks.json` compila los tres archivos fuente y genera `main.exe` dentro de `src`.

## Estructura del proyecto

```text
SBALL/
|-- README.md
|-- src/
|   |-- principal.c
|   |-- .vscode/
|   |   |-- tasks.json
|   |   `-- c_cpp_properties.json
|   |-- assets/
|   |   |-- articles/
|   |   |-- audio/
|   |   |-- sprites/
|   |   `-- ui/
|   |       |-- animaciones.c
|   |       |-- animaciones.h
|   |       |-- menu.c
|   |       |-- menu.h
|   |       |-- fondo.c
|   |       `-- fondo.h
|   `-- class/
|       `-- animaciones.h
`-- testing/
    `-- prueba.c
```

### Punto de entrada

- **`src/principal.c`** contiene `main`, punto de entrada del programa. Llama a `iniciar_interfaz()` para abrir el menu.

### Interfaz del menu

- **`src/assets/ui/menu.h`** declara `iniciar_interfaz(void)`, la funcion de entrada a la interfaz.
- **`src/assets/ui/menu.c`** inicializa la ventana y el audio de Raylib, carga los botones y la musica, y ejecuta el ciclo de entrada, actualizacion y dibujo.
  - El estado `pantalla == 0` muestra los botones del menu.
  - **Play** abre la pantalla de partida, inicia la musica correspondiente y muestra aves animadas.
  - **Options** abre una pantalla que aun esta vacia.
  - `Escape` regresa al menu y muestra su logo.
  - **Exit** termina el ciclo del programa.
  - Al salir, libera las texturas de botones y fondo, y cierra audio y ventana.

### Fondo animado

- **`src/assets/ui/fondo.h`** declara la interfaz publica del modulo de fondo. Incluye `<stdbool.h>` para compartir el tipo `bool` de C.
- **`src/assets/ui/fondo.c`** carga y dibuja el suelo, arboles, montanas, sol, nubes y logo. Tambien actualiza el desplazamiento del paisaje, la posicion de las nubes y la rotacion del sol.
  - `inicializar_fondo()` carga las texturas y asigna posiciones y velocidades aleatorias a 15 nubes.
  - `actualizar_fondo(float velocidad)` actualiza las posiciones segun el tiempo de cuadro de Raylib.
  - `dibujar_fondo()` dibuja las capas del paisaje y los elementos del fondo.
  - `mostrar_logo(bool visible)` controla la visibilidad del logo usando `true` o `false`.
  - `liberar_fondo()` libera las texturas del fondo.

### Animaciones

- **`src/assets/ui/animaciones.h`** declara las funciones para inicializar, actualizar, dibujar y liberar las animaciones.
- **`src/assets/ui/animaciones.c`** carga la hoja de sprites de aves, recorta el margen transparente y anima dos aves que cruzan la pantalla de derecha a izquierda durante la partida.

Los encabezados (`.h`) declaran las funciones que otros modulos pueden utilizar; las implementaciones estan en los archivos `.c`. GCC compila y enlaza esos modulos para crear el ejecutable.

### Recursos

- **`src/assets/sprites/background/`** contiene las imagenes del paisaje y del fondo. `mrcloudy.png` esta disponible, pero actualmente no se utiliza.
- **`src/assets/sprites/buttons/`** contiene las imagenes de Play, Options y Exit.
- **`src/assets/sprites/objects/planesprites.png`** contiene sprites del avion; aun no se utilizan en una pantalla de juego.
- **`src/assets/sprites/objects/birds.png`** es la hoja de sprites usada por la animacion de aves.
- **`src/assets/audio/soundtrack.mp3`** es la musica del menu.
- **`src/assets/audio/forest.mp3`** es la musica que se reproduce durante la pantalla de partida.
- **`src/assets/articles/Black_colour.jpg`** es un recurso de imagen que actualmente no se referencia desde el codigo.

### Animaciones, pruebas y configuracion

- **`src/class/animaciones.h`** esta reservado para futuras funciones de animacion; actualmente solo incluye Raylib.
- **`testing/prueba.c`** esta vacio y todavia no contiene pruebas ejecutables.
- **`src/.vscode/tasks.json`** define la tarea de compilacion con GCC, C17 y las bibliotecas de Raylib para Windows.
- **`src/.vscode/c_cpp_properties.json`** configura el compilador, las rutas de inclusion y el estandar C para IntelliSense.

## Estado actual

El menu, el fondo animado y las aves en movimiento estan implementados. Aun faltan el control del avion, las colisiones, la logica completa de la partida y el guardado del progreso.
