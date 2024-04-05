# Computacao-Grafica

1. Instalar o GCC e o G++
Para instalar o GCC e o G++ no Ubuntu, que são os compiladores para C e C++, você pode usar o seguinte comando:


```sh
sudo apt update
sudo apt install build-essential
```

2. Instalar o GLFW
O GLFW é uma biblioteca que permite criar janelas e contextos OpenGL de maneira portável. Instale-a com o seguinte comando:

```sh
sudo apt install libglfw3 libglfw3-dev
```
3. Instalar o GLEW
O GLEW (OpenGL Extension Wrangler Library) ajuda na gestão de extensões OpenGL. Instale-a com:

```sh
sudo apt install libglew-dev
```
4. Instalar o GLM
O GLM (OpenGL Mathematics) é uma biblioteca de matemática para OpenGL. É opcional, mas é útil para a manipulação de vetores e matrizes:

```sh
sudo apt install libglm-dev
```
5. Instalar o SOIL
O SOIL (Simple OpenGL Image Library) é uma biblioteca para carregar imagens como texturas em OpenGL. É opcional, mas útil para trabalhar com texturas:

```sh
sudo apt install libsoil-dev
```
6. Instalar um Editor de Texto ou IDE
Para escrever seu código, você pode usar um editor de texto simples como o gedit ou uma IDE como o Code::Blocks ou Eclipse:

```sh
sudo apt install codeblocks
```
7. Verificar se o Mesa está instalado
Mesa é uma implementação open-source do OpenGL. Normalmente, está instalada por padrão, mas você pode verificar e instalar com:

```sh
sudo apt install mesa-common-dev
```
8. Build and Run code

```sh
gcc programa.c -o programa -lglfw -lGLEW -lGL -lm
./programa
```

# Referrence:
[Transformations](https://learnopengl.com/Getting-started/Transformations)