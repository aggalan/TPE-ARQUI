#include "sounds.h"
#include "userSyscalls.h"


void collision(){

    call_sound(200, 261);
    call_sleepms(10);

    call_sound(200, 329);
    call_sleepms(10);

    call_sound(200, 392);
    call_sleepms(10);

    call_sound(200, 523);
    call_sleepms(10);
}

void game_start(){
    call_sound(500, 440); 
    call_sleepms(10);

    call_sound(500, 554); 
    call_sleepms(10);

    call_sound(500, 659);
    call_sleepms(10);
}

void game_pause(){
    call_sound(1000, 262); 
    call_sleepms(1000);
}

void snake_movement(){
    call_sound(50, 330); 
    call_sleepms(50);
}


