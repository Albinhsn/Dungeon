#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "platform.h"

struct game_memory
{
  arena PermanentStorage;
  arena TransientStorage;
  bool  Initialized;
};

struct game_renderer
{
  void (*STA_DRAW_RECTANGLE)(platform_renderer Renderer, int MinX, int MaxX, int MinY, int MaxY, uint32_t Color);
};

enum input_keys
{
  InputKey_W = (1 << 1),
  InputKey_A = (1 << 2),
  InputKey_S = (1 << 3),
  InputKey_D = (1 << 4),
  InputKey_E = (1 << 5),
  InputKey_Q = (1 << 6),
};

struct game_input
{

  // W, A, S, D, E, Q
  u8 KeysPressed;
  // Mouse pos
};
inline bool
IsKeyPressed(game_input* Input, input_keys Key)
{
  return (Input->KeysPressed & Key) != 0;
}

inline void
SetKeyPressed(game_input* Input, input_keys Key, bool IsPressed)
{
  if (IsPressed)
  {
    Input->KeysPressed |= Key;
  }
  else
  {
    Input->KeysPressed &= ~Key;
  }
}

#endif
