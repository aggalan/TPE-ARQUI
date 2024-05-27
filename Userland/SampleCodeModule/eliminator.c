// #include "colors.h"
// #include "utils.h"
// #include "eliminator.h"
// #include "userSyscalls.h"
// #include <stdint.h>
// #include <stdbool.h>
//
// // Definiciones abstractas de las syscalls
// extern void sys_clear_screen();
//
// // Constantes del juego
// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600
// #define PLAYER_SIZE 10
// #define UP 0
// #define DOWN 1
// #define LEFT 2
// #define RIGHT 3
// #define MAX_LENGTH 1000  // Máximo número de segmentos de la serpiente
// #define DEFAULT_LEVEL 1
// #define DEFAULT_SPEED 2
// #define DEFAULT_PLAYERS 1
//
// uint64_t DEFAULT_BCOLOR = BLACK;
// uint64_t DEFAULT_FCOLOR = RED;
//
// uint64_t DEFAULT_PLAYER1_COLOR = RED;
// uint64_t DEFAULT_PLAYER2_COLOR = GREEN;
//
// uint32_t MENU_X;
// uint32_t MENU_Y;
//
// uint32_t START_X;
// uint32_t START_Y;
//
//
// uint32_t CONFIG_X;
// uint32_t CONFIG_Y;
// unsigned int players = DEFAULT_PLAYERS;
// unsigned int speed = DEFAULT_SPEED;
// unsigned int level = DEFAULT_LEVEL;
//
//
// typedef struct {
//     int x, y;
// } Segment;
//
// typedef struct {
//     Segment segments[MAX_LENGTH];
//     int length;
//     int direction;
//     uint64_t color;
// } Snake;
//
// Snake player1;
// Snake player2;


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
// void start_game(){
//     initializeGame();
//
//     while (1) {
//         char key = getCh();  // Obtener entrada del teclado (bloqueante)
//         handleInput(key);
//         updateGame();
//     }
//
//     return 0;
// }
//
// void drawSegment(Segment seg, uint64_t color) {
//     call_put_square(seg.x, seg.y, PLAYER_SIZE, color);
// }
//
// void drawSnake(Snake *snake) {
//     for (int i = 0; i < snake->length; i++) {
//         drawSegment(snake->segments[i], snake->color);
//     }
// }
//
//
// void handleInput(char key) {
//     switch (key) {
//         case 'w':  // Mover jugador 1 hacia arriba
//             player1.direction = UP;
//             break;
//         case 's':  // Mover jugador 1 hacia abajo
//             player1.direction = DOWN;
//             break;
//         case 'a':  // Mover jugador 1 hacia la izquierda
//             player1.direction = LEFT;
//             break;
//         case 'd':  // Mover jugador 1 hacia la derecha
//             player1.direction = RIGHT;
//             break;
//         case 'i':  // Mover jugador 2 hacia arriba
//             player2.direction = UP;
//             break;
//         case 'k':  // Mover jugador 2 hacia abajo
//             player2.direction = DOWN;
//             break;
//         case 'j':  // Mover jugador 2 hacia la izquierda
//             player2.direction = LEFT;
//             break;
//         case 'l':  // Mover jugador 2 hacia la derecha
//             player2.direction = RIGHT;
//             break;
//     }
// }
//
// void initializeGame() {
//
//     player1.length = 1;
//     player1.direction = UP;
//     player1.color = RED;
//     player1.segments[0].x = SCREEN_WIDTH / 4;
//     player1.segments[0].y = SCREEN_HEIGHT / 2;
//
//     player2.length = 1;
//     player2.direction = DOWN;
//     player2.color = GREEN;
//     player2.segments[0].x = 3 * SCREEN_WIDTH / 4;
//     player2.segments[0].y = SCREEN_HEIGHT / 2;
//
//     sys_clear_screen();
//     drawSnake(&player1);
//     drawSnake(&player2);
// }
//
// void updateSnake(Snake *snake) {
//     Segment new_head = snake->segments[0];
//
//     switch (snake->direction) {
//         case UP:
//             new_head.y -= PLAYER_SIZE;
//             break;
//         case DOWN:
//             new_head.y += PLAYER_SIZE;
//             break;
//         case LEFT:
//             new_head.x -= PLAYER_SIZE;
//             break;
//         case RIGHT:
//             new_head.x += PLAYER_SIZE;
//             break;
//     }
//
//     // Mover segmentos
//     for (int i = snake->length - 1; i > 0; i--) {
//         snake->segments[i] = snake->segments[i - 1];
//     }
//     snake->segments[0] = new_head;
//
//     drawSegment(snake->segments[0], snake->color);
// }
//
// bool checkCollision(Snake *snake) {
//     Segment head = snake->segments[0];
//
//     // Colisión con los bordes
//     if (head.x < 0 || head.x >= SCREEN_WIDTH || head.y < 0 || head.y >= SCREEN_HEIGHT) {
//         return true;
//     }
//
//     // Colisión con el propio cuerpo
//     for (int i = 1; i < snake->length; i++) {
//         if (head.x == snake->segments[i].x && head.y == snake->segments[i].y) {
//             return true;
//         }
//     }
//
//     return false;
// }
//
// void updateGame() {
//
//     updateSnake(&player1);
//     updateSnake(&player2);
//
//     if (checkCollision(&player1) || checkCollision(&player2)) {
//         //chocaron
//         initializeGame();
//     }
// }
