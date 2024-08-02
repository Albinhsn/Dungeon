#include "game.h"

extern "C" void
update(game_renderer GameRenderer, platform_renderer Renderer, game_memory* Memory, game_input* Input, f32 dt)
{
  if (!Memory->Initialized)
  {
  }

  if (IsKeyPressed(Input, InputKey_W))
  {
    GameRenderer.STA_DRAW_RECTANGLE(Renderer, 0, 100, 0, 100, 0x0000FFFF);
  }
  if (IsKeyPressed(Input, InputKey_A))
  {
    GameRenderer.STA_DRAW_RECTANGLE(Renderer, 0, 100, 0, 100, 0x00FFFFFF);
  }
  if (IsKeyPressed(Input, InputKey_S))
  {
    GameRenderer.STA_DRAW_RECTANGLE(Renderer, 0, 100, 0, 100, 0xFFFFFFFF);
  }
  if (IsKeyPressed(Input, InputKey_D))
  {
    GameRenderer.STA_DRAW_RECTANGLE(Renderer, 0, 100, 0, 100, 0xFFFF00FF);
  }
  if (IsKeyPressed(Input, InputKey_Q))
  {
    GameRenderer.STA_DRAW_RECTANGLE(Renderer, 0, 100, 0, 100, 0x00FF00FF);
  }
  if (IsKeyPressed(Input, InputKey_E))
  {
    GameRenderer.STA_DRAW_RECTANGLE(Renderer, 0, 100, 0, 100, 0xFF0000FF);
  }
}
