
# Hangman Game 🎮

## 📝 Hangman Game License

Um jogo clássico da forca implementado em C, onde você adivinha letras para descobrir a palavra oculta antes que o boneco da forca seja completado!

---

## ✨ Features

- 🎲 Seleção aleatória de palavras a partir de um banco de dados (`words.txt`)
- 🎨 Arte ASCII que representa a forca e atualiza a cada erro
- 📝 Controle de letras já tentadas
- 🏆 Condições de vitória e derrota com arte ASCII comemorativa ou de consolo
- ➕ Opção de adicionar novas palavras ao banco de dados
- 🖥️ Limpeza de tela compatível com Windows, Linux e macOS

---

## 🕹️ Como Jogar

1. O jogo escolhe uma palavra aleatória do arquivo `words.txt`
2. Você deve adivinhar letras uma por vez
3. Letras corretas revelam sua posição na palavra
4. Letras erradas adicionam partes ao desenho da forca
5. Você vence se adivinhar todas as letras antes de cometer 5 erros

---

## ⚙️ Instalação

Clone o repositório:

```bash
git clone https://github.com/oliveeiralucas/hangman-game.git
```

Compile o programa:

```bash
gcc hangman.c -o hangman
```

Execute o jogo:

```bash
./hangman
```

---

## 📚 Banco de Palavras

O jogo lê palavras do arquivo `words.txt`, que deve estar formatado da seguinte forma:

```
N
PALAVRA1
PALAVRA2
...
PALAVRAN
```

Onde `N` é o número total de palavras no arquivo.

---

## 🏗️ Estrutura do Código

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define WORD_SIZE 20
#define MAX_GUESSES 26
#define MAX_ERRORS 5

/* Variáveis globais */
static char secretWord[WORD_SIZE + 1];
static char guesses[MAX_GUESSES];
static int guessCount = 0;

/* Protótipos das funções */
int letterExists(char letter);
int wrongGuesses();
int isHanged();
int hasWon();
void showHeader();
void makeGuess();
int alreadyGuessed(char letter);
void clearScreen();
void drawHangman();
void chooseWord();
void addWord();
```

---

## 📋 Visão Geral das Funções

- `letterExists()`: Verifica se a letra está na palavra secreta
- `wrongGuesses()`: Conta os erros cometidos
- `isHanged()`: Verifica se o jogador perdeu
- `hasWon()`: Verifica se o jogador venceu
- `drawHangman()`: Mostra a forca e o progresso da palavra
- `chooseWord()`: Escolhe uma palavra aleatória do banco
- `addWord()`: Permite adicionar novas palavras ao banco

---

## 📸 Capturas de Tela

**Início do Jogo:**

```
/****************/
/* Hangman Game */
/****************/

  _______
 |/      |
 |
 |
 |
 |
 |
_|___

_ _ _ _ _

Letras tentadas:
```

**Vitória:**

```
Parabéns! Você venceu!

       ___________
      '._==_==_=_.'  
      .-\:      /-.
     | (|:.     |) |
      '-|:.     |-'
        \::.    /
         '::. .'
           ) (
         _.' '._
        '-------'
```

---

Aproveite o jogo! Se tiver dúvidas ou sugestões, sinta-se à vontade para abrir uma *issue*. 😊
