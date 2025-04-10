#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define WORD_SIZE 20
#define MAX_GUESSES 26
#define MAX_ERRORS 5

static char secretWord[WORD_SIZE + 1];
static char guesses[MAX_GUESSES];
static int guessCount = 0;

int letterExists(char letter) {
	for (size_t j = 0; j < strlen(secretWord); j++) {
		if (letter == secretWord[j]) {
			return 1;
		}
	}
	return 0;
}

int wrongGuesses() {
	int errors = 0;
	for (int i = 0; i < guessCount; i++) {
		if (!letterExists(guesses[i])) {
			errors++;
		}
	}
	return errors;
}

int isHanged() {
	return wrongGuesses() >= MAX_ERRORS;
}

int hasWon() {
	for (size_t i = 0; i < strlen(secretWord); i++) {
		if (!alreadyGuessed(secretWord[i])) {
			return 0;
		}
	}
	return 1;
}

void showHeader() {
	printf("/****************/\n");
	printf("/ Hangman Game */\n");
	printf("/****************/\n\n");
}

void makeGuess() {
	char guess;
	printf("Enter a letter: ");

	// Clear input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

	if (scanf_s(" %c", &guess, 1) != 1) {
		printf("Invalid input.\n");
		return;
	}

	guess = toupper(guess);

	if (!isalpha(guess)) {
		printf("Please enter a valid letter.\n");
		return;
	}

	if (alreadyGuessed(guess)) {
		printf("You already tried letter %c.\n\n", guess);
		return;
	}

	if (guessCount < MAX_GUESSES) {
		guesses[guessCount] = guess;
		guessCount++;

		if (letterExists(guess)) {
			printf("Correct! The word contains letter %c\n\n", guess);
		}
		else {
			printf("\nWrong! The word doesn't contain letter %c\n\n", guess);
		}
	}
	else {
		printf("Maximum number of guesses reached.\n");
	}
}

int alreadyGuessed(char letter) {
	for (int j = 0; j < guessCount; j++) {
		if (guesses[j] == letter) {
			return 1;
		}
	}
	return 0;
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void drawHangman() {
	clearScreen();
	int errors = wrongGuesses();

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (errors >= 1 ? '(' : ' '), (errors >= 1 ? '_' : ' '), (errors >= 1 ? ')' : ' '));
	printf(" |      %c%c%c  \n", (errors >= 3 ? '\\' : ' '), (errors >= 2 ? '|' : ' '), (errors >= 3 ? '/' : ' '));
	printf(" |       %c     \n", (errors >= 2 ? '|' : ' '));
	printf(" |      %c %c   \n", (errors >= 4 ? '/' : ' '), (errors >= 4 ? '\\' : ' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	for (size_t i = 0; i < strlen(secretWord); i++) {
		if (alreadyGuessed(secretWord[i])) {
			printf("%c ", secretWord[i]);
		}
		else {
			printf("_ ");
		}
	}
	printf("\n");
	printf("\nLetters tried: ");
	for (int i = 0; i < guessCount; i++) {
		printf("%c ", guesses[i]);
	}
	printf("\n\n");
}

void chooseWord() {
	FILE* f;
	if (fopen_s(&f, "words.txt", "r") != 0) {
		printf("Word database not available\n\n");
		exit(1);
	}

	int wordCount;
	if (fscanf_s(f, "%d", &wordCount) != 1) {
		printf("Error reading word count\n");
		fclose(f);
		exit(1);
	}

	srand((unsigned int)time(NULL));
	int random = rand() % wordCount;

	for (int i = 0; i <= random; i++) {
		if (fscanf_s(f, "%20s", secretWord, (unsigned)_countof(secretWord)) != 1) {
			printf("Error reading word\n");
			fclose(f);
			exit(1);
		}
	}

	fclose(f);
}

void addWord() {
	char choice;
	printf("Do you want to add a new word to the game (Y/N)? ");

	if (scanf_s(" %c", &choice, 1) != 1) {
		printf("Invalid input.\n");
		return;
	}

	choice = toupper(choice);

	if (choice != 'Y') {
		return;
	}

	// Clear input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

	char newWord[WORD_SIZE + 1];
	printf("Enter the new word in uppercase (max %d letters): ", WORD_SIZE);

	if (scanf_s("%20s", newWord, (unsigned)_countof(newWord)) != 1) {
		printf("Invalid input.\n");
		return;
	}

	// Validate word contains only letters
	for (size_t i = 0; i < strlen(newWord); i++) {
		if (!isalpha(newWord[i])) {
			printf("The word must contain only letters.\n");
			return;
		}
		newWord[i] = toupper(newWord[i]);
	}

	FILE* f;
	if (fopen_s(&f, "words.txt", "r+") != 0) {
		printf("Word database not available\n\n");
		exit(1);
	}

	int count;
	if (fscanf_s(f, "%d", &count) != 1) {
		printf("Error reading word count\n");
		fclose(f);
		exit(1);
	}

	count++;
	fseek(f, 0, SEEK_SET);
	fprintf_s(f, "%d", count);

	fseek(f, 0, SEEK_END);
	fprintf_s(f, "\n%s", newWord);

	fclose(f);
	printf("Word added successfully!\n");
}

int main() {
	showHeader();
	chooseWord();

	do {
		drawHangman();
		makeGuess();
	} while (!hasWon() && !isHanged());

	if (hasWon()) {
		printf("\nCongratulations! You won!\n\n");
		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");
	}
	else {
		printf("\nSorry, you were hanged!\n");
		printf("The word was **%s**\n\n", secretWord);
		printf("    _______________         \n");
		printf("   /               \\       \n");
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
	}

	addWord();
	return 0;
}