#pragma once

#include "../defines.h"

typedef struct KeyState
{
    u8 *current;
    u8 *prev;
}KeyState;

#define DEFINE_KEY(name, code) KEY_##name = code

typedef enum keys
{
    // SDL_scancode values here.
    // https://sdl2referencejp.osdn.jp/SDLScancodeLookup.html
    
    DEFINE_KEY(BACKSPACE, 42),
    DEFINE_KEY(RETURN, 40),
    DEFINE_KEY(LSHIFT, 225),
    DEFINE_KEY(RSHIFT, 229),
    DEFINE_KEY(LCONTROL, 224),
    DEFINE_KEY(RCONTROL, 228),
    DEFINE_KEY(ESCAPE, 41),
    DEFINE_KEY(SPACE, 44),
  
    DEFINE_KEY(LEFT, 80),
    DEFINE_KEY(UP, 82),
    DEFINE_KEY(RIGHT, 79),
    DEFINE_KEY(DOWN, 81),

    DEFINE_KEY(A, 4),
    DEFINE_KEY(B, 5),
    DEFINE_KEY(C, 6),
    DEFINE_KEY(D, 7),
    DEFINE_KEY(E, 8),
    DEFINE_KEY(F, 9),
    DEFINE_KEY(G, 10),
    DEFINE_KEY(H, 11),
    DEFINE_KEY(I, 12),
    DEFINE_KEY(J, 13),
    DEFINE_KEY(K, 14),
    DEFINE_KEY(L, 15),
    DEFINE_KEY(M, 16),
    DEFINE_KEY(N, 17),
    DEFINE_KEY(O, 18),
    DEFINE_KEY(P, 19),
    DEFINE_KEY(Q, 20),
    DEFINE_KEY(R, 21),
    DEFINE_KEY(S, 22),
    DEFINE_KEY(T, 23),
    DEFINE_KEY(U, 24),
    DEFINE_KEY(V, 25),
    DEFINE_KEY(W, 26),
    DEFINE_KEY(X, 27),
    DEFINE_KEY(Y, 28),
    DEFINE_KEY(Z, 29),


    DEFINE_KEY(NUM0, 39),
    DEFINE_KEY(NUM1, 30),
    DEFINE_KEY(NUM2, 31),
    DEFINE_KEY(NUM3, 32),
    DEFINE_KEY(NUM4, 33),
    DEFINE_KEY(NUM5, 34),
    DEFINE_KEY(NUM6, 35),
    DEFINE_KEY(NUM7, 36),
    DEFINE_KEY(NUM8, 37),
    DEFINE_KEY(NUM9, 38),
 
    DEFINE_KEY(F1, 58),
    DEFINE_KEY(F2, 59),
    DEFINE_KEY(F3, 60),
    DEFINE_KEY(F4, 61),
    DEFINE_KEY(F5, 62),
    DEFINE_KEY(F6, 63),
    DEFINE_KEY(F7, 64),
    DEFINE_KEY(F8, 65),
    DEFINE_KEY(F9, 66),
    DEFINE_KEY(F10, 67),
    DEFINE_KEY(F11, 68),
    DEFINE_KEY(F12, 69),
}Keys;

b8 input_initialize(void);
void input_update(void);

POAPI b8 key_held(Keys key);
POAPI b8 key_pressed(Keys key);
POAPI b8 key_released(Keys key);