#include "game.h"
#include "platform.cpp"

extern "C" void
update(platform_renderer Renderer, game_memory* Memory, game_input* Input, f32 dt)
{
  if (!Memory->Initialized)
  {
  }

  if (IsKeyPressed(Input, InputKey_W))
  {
    Sta_DrawRectangle(Renderer, 0, 100, 0, 100, 0x0000FFFF);
  }
  if (IsKeyPressed(Input, InputKey_A))
  {
    Sta_DrawRectangle(Renderer, 0, 100, 0, 100, 0x00FFFFFF);
  }
  if (IsKeyPressed(Input, InputKey_S))
  {
    Sta_DrawRectangle(Renderer, 0, 100, 0, 100, 0xFFFFFFFF);
  }
  if (IsKeyPressed(Input, InputKey_D))
  {
    Sta_DrawRectangle(Renderer, 0, 100, 0, 100, 0xFFFF00FF);
  }
  if (IsKeyPressed(Input, InputKey_Q))
  {
    Sta_DrawRectangle(Renderer, 0, 100, 0, 100, 0x00FF00FF);
  }
  if (IsKeyPressed(Input, InputKey_E))
  {
    Sta_DrawRectangle(Renderer, 0, 100, 0, 100, 0xFF0000FF);
  }
}
