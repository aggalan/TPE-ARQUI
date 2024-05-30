#include "colors.h"
#include "utils.h"
#include "eliminator.h"
#include "userSyscalls.h"
#include <stdint.h>
#include <stdbool.h>
#include "sounds.h"

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
#define DEFAULT_PLAYERS 2

uint64_t DEFAULT_BCOLOR = BLACK;
uint64_t DEFAULT_FCOLOR = RED;

uint64_t DEFAULT_PLAYER1_COLOR = RED;
uint64_t DEFAULT_PLAYER2_COLOR = GREEN;

uint32_t MENU_X = 100;
uint32_t MENU_Y = 20;

uint32_t START_X = 100;
uint32_t START_Y = 20;


uint64_t player1Up = 0x11;
uint64_t player1Down = 0x1F;
uint64_t player1Left = 0x1E;
uint64_t player1Right = 0x20;

uint64_t player2Up = 0x17;
uint64_t player2Down = 0x25;
uint64_t player2Left = 0x24;
uint64_t player2Right = 0x26;

uint32_t CONFIG_X;
uint32_t CONFIG_Y;
unsigned int players = DEFAULT_PLAYERS;
unsigned int speed = DEFAULT_SPEED;
unsigned int level = DEFAULT_LEVEL;
unsigned int player1Deaths = 0;
unsigned int player2Deaths = 0;



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
    call_drawWordColorAt("[Q] to return to the shell\n", DEFAULT_FCOLOR, MENU_X, MENU_Y + 384);
}

void menu(){
    while(1){
        quit = false;
        call_paint_screen(BLACK);
        print_menu();
        char option = getCh();
        switch (option){
        case 'q':
            return;
        case ' ':
            start_game();
        // case '\n':
        //     change_settings();
        // }
        }
    }
}

void start_game(){
    if(players == 1){
        initializeGame();
    }
    else{
        initializeGameTwoPlayers();
    }
    
    int pos = call_get_pos();
    char key;

    while (1) {
        key = call_get_charAt(pos-1);  // Obtener entrada del teclado (bloqueante)
        if(key != 0){
            pos++;
        }
        handleInput(key);
        updateGame();
        if(quit){
            return;
        }
        
        call_sleepms(speed);

        


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
        if(key == player1Up){
            if(player1.direction != DOWN){
                player1.direction = UP;
                return;
            }
        }
        else if(key == player1Down){
            if(player1.direction != UP){
               player1.direction = DOWN; 
               return;
            }
        }
        else if(key == player1Left){
            if(player1.direction != RIGHT){
                player1.direction = LEFT;
                return;
            }
            }
        else if(key == player1Right){
            if(player1.direction != LEFT){
                player1.direction = RIGHT;
                return;
            }

        }
        else if(key == player2Up){
            if(player2.direction != DOWN){
                player2.direction = UP;
                return;
            }

        }
        else if(key == player2Down){
                if(player2.direction != UP){
                player2.direction = DOWN;
                return;
            }
        }
        else if(key == player2Left){
            if(player2.direction != RIGHT){
                player2.direction = LEFT;
                return;
            }
        }
        else if(key == player2Right){
            if(player2.direction != LEFT){
                player2.direction = RIGHT;
                return;
            }
        }
}

void initializeGame(){
    for(int i = 0; i < SCREEN_WIDTH; i++){
        for(int j = 0; j < SCREEN_HEIGHT; j++){
            board[i][j] = 0;
        }
    }

    player1.direction = UP;
    player1.color = RED;
    player1.head.x = SCREEN_WIDTH / 2;
    player1.head.y = SCREEN_HEIGHT - 25;

    call_paint_screen(BLACK);

    drawMargins();
    drawSegment(player1.head, player1.color);

}

void initializeGameTwoPlayers() {

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
    bool player1Status = updateSnake(&player1);
    bool player2Status = updateSnake(&player2);
    if(player1Status && player2Status){
        game_over();
        player1Deaths++;
        player2Deaths++;
        if(quit){
            return;
        }
    }else{
        if(player1Status){
            game_over();
            player1Deaths++;
            if(quit){
                return;
            }
        }
        if(player2Status){
            game_over();
            player2Deaths++;
            if(quit){
                return;
            }
        }
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
    collision();
    call_paint_screen(BLACK);
    call_drawWordColorAt("GAME OVER\n", DEFAULT_FCOLOR, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100);
    call_drawWordColorAt("Press [Q] to return to menu\n", DEFAULT_FCOLOR, SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 50);
    call_drawWordColorAt("Press any other key to continue\n", DEFAULT_FCOLOR, SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 10);
     if(getCh() == 'q'){
         quit = true;
     }
    
    call_clear_buff();
    start_game();
}
