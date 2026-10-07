# Raylib — Instalação no Windows e Linux

Este guia apresenta como instalar e compilar projetos usando a biblioteca **Raylib** para desenvolvimento de jogos em **C** nos sistemas operacionais **Windows** e **Linux**.

A Raylib é uma biblioteca simples e multiplataforma para desenvolvimento de jogos e aplicações gráficas em C/C++.

---

## 📋 Pré-requisitos

Você precisará de:

* Compilador C (`gcc`)
* Git
* CMake
* Raylib

---

# 🪟 Windows

## Opção 1 — MSYS2

A maneira recomendada para trabalhar com C no Windows é utilizar o **MSYS2**.

### 1. Instalar o MSYS2

Baixe o MSYS2 em: [https://www.msys2.org/](https://www.msys2.org/)

Após a instalação, abra o terminal **MSYS2 UCRT64** e atualize os pacotes:

```bash
pacman -Syu
```

Se o terminal solicitar o fechamento, feche-o, abra novamente o **MSYS2 UCRT64** e execute:

```bash
pacman -Su
```

### 2. Instalar o compilador

No terminal **MSYS2 UCRT64**:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Verifique a instalação:

```bash
gcc --version
```

### 3. Instalar a Raylib

Execute:

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

Verifique:

```bash
pkg-config --modversion raylib
```

---

## # Como rodar o codigo no windowns

Para compilar o seu código em C com a Raylib diretamente pelo terminal no Windows (linkando as bibliotecas do sistema como OpenGL, GDI e Multimedia), utilize:

```bash
gcc NomedoArquivo.c -o exe.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Para executar o programa gerado:

```bash
./exe.exe
```

---

# 🐧 Linux

Os comandos abaixo são voltados principalmente para distribuições baseadas em Debian/Ubuntu.

## 1. Atualizar o sistema e instalar dependências

```bash
sudo apt update
sudo apt install build-essential git cmake pkg-config
```

Instale as dependências gráficas e de áudio:

```bash
sudo apt install \
libasound2-dev \
libx11-dev \
libxrandr-dev \
libxi-dev \
libxcursor-dev \
libxinerama-dev \
libgl1-mesa-dev \
libglu1-mesa-dev
```

---

## 2. Instalar a Raylib

Clone e compile a biblioteca:

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig
```

---

## # Como rodar o codigo no linux

Para compilar o seu arquivo em C no Linux linkando manualmente todas as dependências gráficas, de sistema e threads:

```bash
gcc NomedoArquivo.c -o exe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

Para executar o programa gerado:

```bash
./exe
```

---

# 🧪 Exemplo Básico (`main.c`)

Crie um arquivo chamado `main.c` com o conteúdo abaixo para testar sua instalação:

```c
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "Meu primeiro jogo");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "Raylib funcionando!",
            250,
            200,
            30,
            BLACK
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# 📁 Estrutura recomendada do projeto

```text
meu-jogo/
│
├── src/
│   └── main.c
│
├── assets/
│   ├── images/
│   ├── sounds/
│   └── fonts/
│
├── include/
├── build/
└── README.md
```

---

## 📚 Documentação e Recursos

* Documentação Oficial: [raylib.com](https://www.raylib.com/)
* Repositório no GitHub: [github.com/raysan5/raylib](https://github.com/raysan5/raylib)
* Exemplos Práticos: [raylib.com/examples.html](https://www.raylib.com/examples.html)