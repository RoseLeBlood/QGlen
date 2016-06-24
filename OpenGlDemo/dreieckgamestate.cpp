
#include "dreieckgamestate.h"
#include "camera.h"



DreieckGameState::DreieckGameState(GameWindow *wnd) : GameState(wnd)
{
      AddObjectToScene(new DreieckObject(wnd));
      AddObjectToScene(new Camera("Came", wnd));
}
bool DreieckGameState::Initialize()
{
    return GameState::Initialize();
}
