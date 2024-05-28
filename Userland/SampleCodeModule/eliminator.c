#include "colors.h"
#include "utils.h"
#include "eliminator.h"
#include "userSyscalls.h"
#include <stdint.h>
#include <stdbool.h>

// Constantes del juego
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 760
#define PLAYER_SIZE 15
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define DEFAULT_LEVEL 1
#define DEFAULT_SPEED 2
#define DEFAULT_PLAYERS 1

uint64_t DEFAULT_BCOLOR = BLACK;
uint64_t DEFAULT_FCOLOR = RED;

uint64_t DEFAULT_PLAYER1_COLOR = RED;
uint64_t DEFAULT_PLAYER2_COLOR = GREEN;

uint32_t MENU_X;
uint32_t MENU_Y;

uint32_t START_X;
uint32_t START_Y;


uint32_t CONFIG_X;
uint32_t CONFIG_Y;
unsigned int players = DEFAULT_PLAYERS;
unsigned int speed = DEFAULT_SPEED;
unsigned int level = DEFAULT_LEVEL;


typedef struct {
    uint64_t x, y;
} Segment;

typedef struct {
    Segment head;
    int direction;
    uint64_t color;
} Snake;

Snake player1;
Snake player2;


//
// char * get_players(){
//     char * str = "PLAYERS: ";
//     char * str2 = malloc(10);
//     intToStr(players, str2, 10);
//     strcat(str, str2);
//     return str;
// }
//
// char * get_speed(){
//     char * str = "SPEED: ";
//     char * str2 = malloc(10);
//     intToStr(speed, str2, 10);
//     strcat(str, str2);
//     return str;
// }
//
// char * get_level(){
//     char * str = "LEVEL: ";
//     char * str2 = malloc(10);
//     intToStr(level, str2, 10);
//     strcat(str, str2);
//     return str;
// }
//
//
//
// void eliminator(){
//     print_start();
//     getCh();
//     menu();
//     }
//
// void reset_menu(){
//     ccall_paint_screen(DEFAULT_BCOLOR);
//         print_menu();
//         option = getCh();
// }
//
// void print_start(){
//     call_paint_screen(DEFAULT_BCOLOR);
//     call_drawWordColorAt("ELIMINATOR\n", DEFAULT_FCOLOR, START_X, START_Y);
//     call_drawWordColorAt("Press any key to start\n", DEFAULT_FCOLOR , START_X, START_Y + 64);
// }
//
// void print_menu(){
//     call_paint_screen(BLACK);
//     call_drawWordColorAt(get_players(), DEFAULT_FCOLOR, MENU_X, MENU_Y);
//     call_drawWordColorAt(get_speed(), DEFAULT_FCOLOR, MENU_X, MENU_Y + 64);
//     call_drawWordColorAt(get_level(), DEFAULT_FCOLOR, MENU_X, MENU_Y + 128);
//     call_drawWordColorAt("[SPACE] to begin game\n", DEFAULT_FCOLOR, MENU_X, MENU_Y + 256);
//     call_drawWordColorAt("[ENTER] to change settings\n", DEFAULT_FCOLOR, MENU_X, MENU_Y + 320);
// }
//
// void menu(){
//     print_menu();
//     char option = getCh();
//     while(option != ' ' && option != '\n'){
//         reset_menu();
//     }
//     switch (option){
//     case ' ':
//         start_game();
//     case '\n':
//         change_settings();
//     }
// }
//
void start_game(){
    initializeGame();

    while (1) {
        char key = getCh();  // Obtener entrada del teclado (bloqueante)
        handleInput(key);
        updateGame();
    }

    return 0;
}

void drawSegment(Segment seg, uint64_t color) {
    call_put_square(seg.x, seg.y, PLAYER_SIZE, color);
}



void handleInput(char key) {
    switch (key) {
        case 'W':  // Mover jugador 1 hacia arriba
            player1.direction = UP;
            break;
        case 'S':  // Mover jugador 1 hacia abajo
            player1.direction = DOWN;
            break;
        case 'A':  // Mover jugador 1 hacia la izquierda
            player1.direction = LEFT;
            break;
        case 'D':  // Mover jugador 1 hacia la derecha
            player1.direction = RIGHT;
            break;
        case 'I':  // Mover jugador 2 hacia arriba
            player2.direction = UP;
            break;
        case 'K':  // Mover jugador 2 hacia abajo
            player2.direction = DOWN;
            break;
        case 'J':  // Mover jugador 2 hacia la izquierda
            player2.direction = LEFT;
            break;
        case 'L':  // Mover jugador 2 hacia la derecha
            player2.direction = RIGHT;
            break;
    }
}

void initializeGame() {

    player1.direction = UP;
    player1.color = RED;
    player1.head.x = SCREEN_WIDTH / 2;
    player1.head.y = SCREEN_HEIGHT - 10;

    player2.direction = DOWN;
    player2.color = GREEN;
    player2.head.x = SCREEN_WIDTH / 2;
    player2.head.y = 10;

    call_paint_screen(BLACK);
    drawSegment(player1.head, player1.color);
    drawSegment(player2.head, player2.color);
}

bool updateSnake(Snake *snake) {

    bool collision = false;


    switch (snake->direction) {
        case UP:
            snake->head.y -= PLAYER_SIZE + 1;
            break;
        case DOWN:
            snake->head.y += PLAYER_SIZE + 1;
            break;
        case LEFT:
            snake->head.x -= PLAYER_SIZE + 1;
            break;
        case RIGHT:
            snake->head.x += PLAYER_SIZE + 1;
            break;
    }

    uint64_t color = call_pixelColorAt(snake->head.x, snake->head.y);

    if(color != 0x00000000){
        collision = true;
    }

    drawSegment(snake->head, snake->color);
    return collision;
}


void updateGame() {

    if (updateSnake(&player1)|| updateSnake(&player2)) {
        print("GAME OVER\n");
        initializeGame();
    }
}
