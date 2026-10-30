# PLANE CRAZY - GAME

¡Eres el piloto más frenético que ha visto los cielos! 
--------------------------------------------------------


## Autores

- [@juanchairez](https://www.github.com/juanchairez)
- [@adrianhumberto](https://www.github.com/adev-hash)
- [@Leo-sbl](https://www.github.com/Leo-sbl)
- [@jisuscries428](https://www.github.com/jisuscries428)
- [@ICaballero07](https://www.github.com/ICaballero07)
## Ejecución

Clona el proyecto
```bash
  git clone https://github.com/adev-hash/SBALL.git
```
Abre la siguiente dirección 

```bash
  cd C:\Users\Name\OneDrive\Documentos\GitHub\SBALL\src
```
Para ejecutar el juego, presiona directamente

```bash
    main.exe
```

## Actualizaciónes 
Para actualizar el juego, haga los cambios en sus respectivos archivos.
Y al final ejecute lo siguiente en la terminal para actualizar.

```bash
    g++ main.cpp assets/ui/menu.cpp -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

## Dependencias:
```bash
    - MSYS2 UCRT64; V: 16.1.0
    - Raylib: pacman -S mingw-w64-ucrt-x86_64-raylib (Abrelo en la terminal de MSYS2 UCRT64) 
```

## Documentación
Menu Principal 

- 1.1 - Logica del Menu y Funcionamiento.

- 1.2 - Modulado de Funciones a nivel del Main. 

- 1.3 - Texturizado y posicionamiento visual. 

- 1.4 - Capturas del código.

## 1.1 - Lógica del Menu y Funcionamiento

La estructura del proyecto esta definida de la siguiente forma: 

- src : Codigo fuente.
- class: Clases de manejo de código. Aqui se separaran las modalidades de cada escenario o funcionamiento de los objetos de forma individual. 
- assets: Contiene los archivos gráficos del proyecto (Sprites, Sonidos, Audio, Animación, etc).
- testing: Se usa para actualizaciones temporales. O para probar scripts o medidas de nuevas ventanas. 

El menu funciona de la siguiente forma: 

Main manda a llamar a clases.h el cual contiene las funciones de ejecución del menu, que estan definidas en el archivo, bg.cpp.






