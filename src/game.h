#ifndef GAME_H
#define GAME_H

#include "common.h"

struct game_memory
{
  arena PermanentStorage;
  arena TransientStorage;
  bool Initialized;
};

enum input_keys
{
  InputKey_W = 1,
  InputKey_A = 2,
  InputKey_S = 3,
  InputKey_D = 4,
  InputKey_E = 5,
  InputKey_Q = 6,
};


struct game_input
{
   
  // W, A, S, D, E, Q
  u8 KeysPressed;
  // Mouse pos
};
inline bool IsKeyPressed(game_input* Input, input_keys Key){
  return (Input->KeysPressed >> Key) & 1;
}

inline void SetKeyPressed(game_input* Input, input_keys Key, bool IsPressed){
  u8 Mask = 0xFF | (IsPressed << Key);
  Input->KeysPressed &= Mask;
}

#endif
