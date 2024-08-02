#include "platform.h"
#include "platform.cpp"
#include "game.h"

void (*update)(game_renderer, platform_renderer*, game_memory*, game_input*, f32 dt);
void* Handle;

void
LoadGameLibrary(long& LibraryLastChanged)
{
// check if newer version exist
#if PLATFORM_WINDOWS
  const char* LibraryName    = "./libgame.dll";
  const char* LibraryTmpName = "./libgame_tmp.dll";
#else
  const char* LibraryName    = "./libgame.so";
  const char* LibraryTmpName = "./libgame_tmp.so";
#endif
  if (Sta_FileHasChanged(LibraryLastChanged, LibraryName))

  {
    if (!Sta_FileCopy(LibraryName, LibraryTmpName))
    {
      LibraryLastChanged = 0;
      return;
    }
    void* TmpHandle = Sta_LibraryLoad(LibraryTmpName);
    update          = (void (*)(game_renderer, platform_renderer*, game_memory*, game_input*, f32 dt))Sta_GetProcAddress(TmpHandle, "update");
    if (update == 0)
    {
      LibraryLastChanged = 0;
      return;
    }
    if (Handle)
    {
      Sta_LibraryFree(Handle);
    }
    Handle = TmpHandle;
  }
}

void
TransferInput(game_input* GameInput, platform_input PlatformInput)
{
  SetKeyPressed(GameInput, InputKey_W, Sta_InputIsKeyPressed(PlatformInput, 'W'));
  SetKeyPressed(GameInput, InputKey_A, Sta_InputIsKeyPressed(PlatformInput, 'A'));
  SetKeyPressed(GameInput, InputKey_S, Sta_InputIsKeyPressed(PlatformInput, 'S'));
  SetKeyPressed(GameInput, InputKey_D, Sta_InputIsKeyPressed(PlatformInput, 'D'));
  SetKeyPressed(GameInput, InputKey_E, Sta_InputIsKeyPressed(PlatformInput, 'E'));
  SetKeyPressed(GameInput, InputKey_Q, Sta_InputIsKeyPressed(PlatformInput, 'Q'));
}

#if PLATFORM_WINDOWS
int CALLBACK
WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
#else
int
main()
#endif
{
  LoadPlatformFunctions();
  int                           ScreenWidth        = 640;
  int                           ScreenHeight       = 480;
  const char*                   WindowName         = "hello";

  platform_window_creation_data WindowCreationData = {};
#if PLATFORM_WINDOWS
  WindowCreationData.Instance     = Instance;
  WindowCreationData.PrevInstance = PrevInstance;
  WindowCreationData.CommandLine  = CommandLine;
  WindowCreationData.ShowCode     = ShowCode;
  WindowCreationData.WindowName   = WindowName;
  WindowCreationData.WindowWidth  = ScreenWidth;
  WindowCreationData.WindowHeight = ScreenHeight;
#else
  WindowCreationData.WindowName   = WindowName;
  WindowCreationData.WindowWidth  = ScreenWidth;
  WindowCreationData.WindowHeight = ScreenHeight;
#endif
  platform_window_creation_result WindowCreationResult = Sta_WindowCreate(WindowCreationData);
  platform_window                 Window               = WindowCreationResult.Window;
  platform_renderer               Renderer             = WindowCreationResult.Renderer;
  platform_input                  PlatformInput        = Sta_InputInit(&Window);

  game_memory                     Memory               = {};
  game_input                      GameInput            = {};
  game_renderer                   GameRenderer         = {};
  GameRenderer.STA_DRAW_RECTANGLE                      = Sta_DrawRectangle;

  // uint32_t                        Color                = 0xFF00FFFF;
  uint64_t End = Sta_GetTicks(), Start;
  long     GameLibraryLastChanged;
  while (true)
  {
    Start = Sta_GetTicks();
    LoadGameLibrary(GameLibraryLastChanged);
    if (Sta_InputReadEvents(&PlatformInput))
    {
      return 0;
    }
    TransferInput(&GameInput, PlatformInput);

    // Sta_RendererClearBuffer(Renderer, Color);
    f32 dt = (End - Start) * 1000.0f;
    if (update)
    {
      update(GameRenderer, &Renderer, &Memory, &GameInput, dt);
    }

    Sta_RendererSwapBuffer(Window, Renderer);
    End = Sta_GetTicks();
    // ToDo sleep? :)
    while (Start + 60 > End)
    {
      End = Sta_GetTicks();
    }
  }
  return 0;
}
