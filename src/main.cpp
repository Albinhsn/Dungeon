#include "platform.h"
#include "platform.cpp"
#include "platform_sdl.h"

void (*update)();
void* Handle;

void
get_game_functions_from_library(long& LibraryLastChanged)
{
  // check if newer version exist
  const char* LibraryName    = "./libgame.so";
  const char* LibraryTmpName = "./libgame_tmp.so";
  if (Sta_FileHasChanged(LibraryLastChanged, LibraryName))
  {
    if (!Sta_FileCopy(LibraryName, LibraryTmpName))
    {
      LibraryLastChanged = 0;
      return;
    }
    void* TmpHandle = Sta_LibraryLoad(LibraryTmpName);
    update          = (void (*)())Sta_GetProcAddress(TmpHandle, "update");
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
  WindowsInitWindowData init_data = {};
  init_data.Instance              = Instance;
  init_data.PrevInstance          = PrevInstance;
  init_data.CommandLine           = CommandLine;
  init_data.ShowCode              = ShowCode;
  PlatformWindow window           = sta_window_create(window_name, screen_width, screen_height, (void*)&init_data);
#else
  WindowCreationData.WindowName   = WindowName;
  WindowCreationData.WindowWidth  = ScreenWidth;
  WindowCreationData.WindowHeight = ScreenHeight;
#endif
  platform_window_creation_result WindowCreationResult = Sta_WindowCreate(WindowCreationData);
  platform_window                 Window               = WindowCreationResult.Window;
  platform_renderer               Renderer             = WindowCreationResult.Renderer;
  platform_input                  Input                = Sta_InputInit(&Window);

  // long           Timer = 0;

  uint32_t Color = 0xFF00FFFF;
  while (true)
  {
    if (Sta_InputReadEvents(&Input))
    {
      return 1;
    }
    uint64_t Start = Sta_GetTicks();

    Sta_RendererClearBuffer(Renderer, Color);
    Sta_RendererSwapBuffer(Window, Renderer);
    uint64_t End = Sta_GetTicks();
    // ToDo sleep? :)
    while (Start + 60 > End)
    {
      End = Sta_GetTicks();
    }
  }
  return 0;
}
