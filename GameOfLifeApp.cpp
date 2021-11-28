//
// Created by Sarah Youngquist on 11/28/21.
//

#include "GameOfLifeApp.h"
#include "FrameGraphics.h"

IMPLEMENT_APP(GameOfLifeWindowApp)

bool GameOfLifeWindowApp::OnInit()
{
  GameOfLifeFrame* game_of_life_frame = new GameOfLifeFrame(30, 30);

  // arbitar
  game_of_life_frame->game->ToggleElement(9, 9);
  game_of_life_frame->game->ToggleElement(10, 10);
  game_of_life_frame->game->ToggleElement(12, 10);
  game_of_life_frame->game->ToggleElement(9, 11);
  game_of_life_frame->game->ToggleElement(10, 12);
  game_of_life_frame->game->ToggleElement(15, 5);
  game_of_life_frame->game->ToggleElement(15, 4);
  game_of_life_frame->game->ToggleElement(16, 3);
  game_of_life_frame->game->ToggleElement(16, 4);
  game_of_life_frame->game->ToggleElement(17, 2);
  game_of_life_frame->game->ToggleElement(18, 2);
  game_of_life_frame->game->ToggleElement(14, 5);
  game_of_life_frame->game->ToggleElement(15, 3);
  game_of_life_frame->game->ToggleElement(14, 2);
  game_of_life_frame->game->ToggleElement(16, 17);
  game_of_life_frame->game->ToggleElement(16, 16);
  game_of_life_frame->game->ToggleElement(2, 6);
  game_of_life_frame->game->ToggleElement(3, 4);
  game_of_life_frame->game->ToggleElement(3, 6);
  game_of_life_frame->game->ToggleElement(4, 5);
  game_of_life_frame->game->ToggleElement(4, 6);
  game_of_life_frame->Show(true);

  return true;
}