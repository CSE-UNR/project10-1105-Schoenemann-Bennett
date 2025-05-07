// Bennett Schoenemann
// 04/22/2025
// Project 10

#include <stdio.h>

#define max 6
#define len 5

void load(char word[]);
int valid(char guess[]);
void lower(char text[]);
void check(char guess[], char word[], char show[], char hint[]);
int same(char a[], char b[]);
void print(char show[], char hint[]);

int main() {
    char word[len + 1];
    char guess[max][len + 1];
    char show[max][len + 1];
    char hint[max][len + 1];
    int turn = 0;

    load(word);

    while (turn < max) {
        char try[100];
        printf("Try #%d: ", turn + 1);
        scanf("%s", try);

        if (!valid(try)) {
            printf("Nope. Use 5 letters.\n");
            continue;
        }

        lower(try);

        for (int i = 0; i < len; i++)
            guess[turn][i] = try[i];
        guess[turn][len] = '\0';

        check(try, word, show[turn], hint[turn]);
        print(show[turn], hint[turn]);

        if (same(try, word)) {
            printf("YAYYYY! You got it!\n");
            return 0;
        }

        turn++;
    }

    printf("Out of tries. Word was: %s\n", word);
    return 0;
}

void load(char word[]) {
    FILE *file = fopen("mystery.txt", "r");
    if (!file) {
        printf("Can't open file.\n");
        word[0] = '\0';
        return;
    }
    fscanf(file, "%5s", word);
    fclose(file);
}

int valid(char guess[]) {
    int i;
    for (i = 0; guess[i]; i++) {
        if (!((guess[i] >= 'A' && guess[i] <= 'Z') || (guess[i] >= 'a' && guess[i] <= 'z')))
            return 0;
    }
    return i == len;
}

void lower(char text[]) {
    for (int i = 0; text[i]; i++)
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] += 'a' - 'A';
}

void check(char guess[], char word[], char show[], char hint[]) {
    int used[len] = {0};

    for (int i = 0; i < len; i++) {
        if (guess[i] == word[i]) {
            show[i] = guess[i] - ('a' - 'A');
            hint[i] = ' ';
            used[i] = 1;
        } else {
            show[i] = guess[i];
            hint[i] = ' ';
        }
    }

    for (int i = 0; i < len; i++) {
        if (guess[i] == word[i]) continue;
        for (int j = 0; j < len; j++) {
            if (!used[j] && guess[i] == word[j]) {
                hint[i] = '^';
                used[j] = 1;
                break;
            }
        }
    }

    show[len] = '\0';
    hint[len] = '\0';
}

int same(char a[], char b[]) {
    for (int i = 0; i < len; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void print(char show[], char hint[]) {
    printf("%s\n%s\n", show, hint);
}
