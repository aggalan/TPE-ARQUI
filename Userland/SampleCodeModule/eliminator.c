#include "colors.h"
#include "utils.h"
#include "eliminator.h"
#include "userSyscalls.h"
#include <stdint.h>
#include <stdbool.h>

// Constantes del juego
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 760
#define PLAYER_SIZE 10
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

uint32_t MENU_X = 100;
uint32_t MENU_Y = 20;

uint32_t START_X = 100;
uint32_t START_Y = 20;


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
uint64_t board[SCREEN_WIDTH][SCREEN_HEIGHT];
bool quit = false;


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

void eliminator(){
    call_size_up();
    print_start();
    getCh();
    menu();
    call_size_down();
    }


void print_start(){
    call_paint_screen(DEFAULT_BCOLOR);
    call_drawWordColorAt("ELIMINATOR\n", DEFAULT_FCOLOR, START_X, START_Y);
    call_drawWordColorAt("Press any key to start\n", DEFAULT_FCOLOR , START_X, START_Y + 64);
}

void print_menu(){
    call_paint_screen(BLACK);
    call_drawWordColorAt("PLAYERS: ", DEFAULT_FCOLOR, MENU_X, MENU_Y);
    call_drawWordColorAt("SPEED: ", DEFAULT_FCOLOR, MENU_X, MENU_Y + 64);
    call_drawWordColorAt("LEVEL: ", DEFAULT_FCOLOR, MENU_X, MENU_Y + 128);
    call_drawWordColorAt("[SPACE] to begin game\n", DEFAULT_FCOLOR, MENU_X, MENU_Y + 256);
    call_drawWordColorAt("[ENTER] to change settings\n", DEFAULT_FCOLOR, MENU_X, MENU_Y + 320);
}

void menu(){
    while(1){
    call_paint_screen(BLACK);
    print_menu();
    char option = getCh();
    switch (option){
    case 'q':
        return;
    case ' ':
        start_game();
    }
    }
}

void start_game(){

    if(quit){
        return;
    }

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
    for(int i = 0; i < PLAYER_SIZE; i++){
        for(int j = 0; j < PLAYER_SIZE; j++){
            board[seg.x + i][seg.y + j] = color;
        }
    }
}



void handleInput(char key) {
    switch (key) {
        case 'w':  // Mover jugador 1 hacia arriba
            player1.direction = UP;
            break;
        case 's':  // Mover jugador 1 hacia abajo
            player1.direction = DOWN;
            break;
        case 'a':  // Mover jugador 1 hacia la izquierda
            player1.direction = LEFT;
            break;
        case 'd':  // Mover jugador 1 hacia la derecha
            player1.direction = RIGHT;
            break;
        case 'i':  // Mover jugador 2 hacia arriba
            player2.direction = UP;
            break;
        case 'k':  // Mover jugador 2 hacia abajo
            player2.direction = DOWN;
            break;
        case 'j':  // Mover jugador 2 hacia la izquierda
            player2.direction = LEFT;
            break;
        case 'l':  // Mover jugador 2 hacia la derecha
            player2.direction = RIGHT;
            break;
    }
}

void initializeGame() {

    for(int i = 0; i < SCREEN_WIDTH; i++){
        for(int j = 0; j < SCREEN_HEIGHT; j++){
            board[i][j] = 0;
        }
    }

    player1.direction = UP;
    player1.color = RED;
    player1.head.x = SCREEN_WIDTH / 2;
    player1.head.y = SCREEN_HEIGHT - 25;

    player2.direction = DOWN;
    player2.color = GREEN;
    player2.head.x = SCREEN_WIDTH / 2;
    player2.head.y = 25;

    call_paint_screen(BLACK);

     drawMargins();

    drawSegment(player1.head, player1.color);
    drawSegment(player2.head, player2.color);
}

bool updateSnake(Snake *snake) {

    bool collision = false;

    switch (snake->direction){
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


    for(int i = 0; i < PLAYER_SIZE; i++){
        for(int j = 0; j < PLAYER_SIZE; j++){
            if(board[snake->head.x + i][snake->head.y + j] != 0){
                collision = true;
            }
        }
    }
    drawSegment(snake->head, snake->color);
    return collision;
}


void updateGame() {

    if (updateSnake(&player1)|| updateSnake(&player2)) {
       game_over();
    }
}

void drawMargins(){
    for(int i = 20; i < SCREEN_WIDTH; i++){
        for(int j = 10; j < SCREEN_HEIGHT; j++){
            if(i == 20 && j >= 10 && j <= SCREEN_HEIGHT - 10 || i == SCREEN_WIDTH - 20 && j >= 10 && j <= SCREEN_HEIGHT - 10 || j == 10  && i >= 20 && i <= SCREEN_WIDTH - 20 || j == SCREEN_HEIGHT - 10 && i >= 20 && i <= SCREEN_WIDTH - 20){
                board[i][j] = RED;
                call_put_square(i, j, 5, RED);
            }
        }
    }
}

void game_over(){
    call_paint_screen(BLACK);
    call_drawWordColorAt("GAME OVER\n", DEFAULT_FCOLOR, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2);
    call_drawWordColorAt("Press q to exit, other to continue\n", DEFAULT_FCOLOR, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 40);
    if(getCh() == 'q'){
        quit = true;
    }
    start_game();
}
