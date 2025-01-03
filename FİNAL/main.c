#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <ncurses.h>
#include <unistd.h>
#endif

#define WIDTH 20
#define HEIGHT 10

void draw(char gameBoard[HEIGHT][WIDTH], int score) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("Catch the Falling Stars\n");
    printf("Score: %d\n\n", score);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", gameBoard[i][j]);
        }
        printf("\n");
    }
#ifdef __linux__
    refresh();
#endif
}

int main() {
    char gameBoard[HEIGHT][WIDTH];
    int playerPos = WIDTH / 2; // Oyuncunun baþlangýç pozisyonu
    int starX = rand() % WIDTH; // Yýldýzýn baþlangýç pozisyonu
    int starY = 0;
    int score = 0;

    srand(time(NULL)); // Rastgele sayý üreteci için tohumlama

#ifndef _WIN32
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
#endif

    while (1) {
        // Oyun tahtasýný temizle
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                gameBoard[i][j] = ' ';
            }
        }

        // Yýldýzý ve oyuncuyu yerleþtir
        if (starY < HEIGHT) {
            gameBoard[starY][starX] = '*';
        }
        gameBoard[HEIGHT - 1][playerPos] = 'O';

        draw(gameBoard, score);

        // Yýldýzýn düþüþü
        starY++;
        if (starY == HEIGHT - 1) {
            if (abs(starX - playerPos) <= 1) { // Yýldýzýn oyuncuya yakýn olmasý
                score++;
            } else {
                printf("Game Over! Final Score: %d\n", score);
                break;
            }
            starX = rand() % WIDTH; // Yýldýzýn yeni pozisyonu
            starY = 0;
        }

        // Kullanýcý girdisi
#ifdef _WIN32
        if (_kbhit()) {
            char input = _getch();
            if (input == 'a' && playerPos > 1) { // Sola hareket (2 blok)
                playerPos -= 2;
            } else if (input == 'd' && playerPos < WIDTH - 2) { // Saða hareket (2 blok)
                playerPos += 2;
            }
        }
        Sleep(500); // Windows için
#else
        int input = getch();
        if (input == 'a' && playerPos > 1) { // Sola hareket (2 blok)
            playerPos -= 2;
        } else if (input == 'd' && playerPos < WIDTH - 2) { // Saða hareket (2 blok)
            playerPos += 2;
        }
        usleep(500000); // Linux için 500ms
#endif
    }

#ifndef _WIN32
    endwin();
#endif
    return 0;
}
