/*
  File name: FrameGraphics.h
  @author: Sarah Youngquist
  Purpose: Defines the frame for the game which controls all interactive GUI components
  Classes:
    GameOfLifeFrame (extends wxFrame):
      Frame with all buttons and the grid. It has a corresponding game.
    GameTimer (extends wxTimer):
      Timer that keeps track of if the game is currently active and provides time intervals for changing state
  History:
  Date             Action
  2021-06-02/3/4   Initial coding
  2021-11-28       Added additional documentation
 */

#include "GraphicsGameClasses.h"
#include <wx/wxprec.h>
#include <wx/tglbtn.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifndef GAMEOFLIFE__WINDOWGRAPHICS_H_
#define GAMEOFLIFE__WINDOWGRAPHICS_H_

class GameOfLifeWindowApp;
class GameOfLifeFrame;
class GameTimer;

class GameOfLifeFrame : public wxFrame
{
 public:
  GameOfLifeFrame(int rows, int cols);
  virtual ~GameOfLifeFrame();
  void OnClose(wxCloseEvent& event);
  void OnPlay(wxCommandEvent& event);
  void OnPause(wxCommandEvent& event);
  void OnToggle(wxCommandEvent& event);
  void OnReset(wxCommandEvent& event);
  void OnSlow(wxCommandEvent& event);
  void OnFast(wxCommandEvent& event);
 friend class GameOfLifeWindowApp;
 friend class GameTimer;
 private:
  int speed;
  wxGridSizer *gs;
  GraphicsArrayGame* game;
  GameTimer* timer;
  wxButton* play_button;
  wxButton* pause_button;
  wxButton* reset_button;
  wxToggleButton* choose_squares;
  wxButton* slow_button;
  wxButton* fast_button;
};

class GameTimer : public wxTimer
{
 public:
  GameTimer(GameOfLifeFrame* game_frame);
  virtual ~GameTimer();
  virtual void Notify();
  bool WasGoing();
  void SetGoing(bool going);
 private:
  bool was_going; // keeps track of if the game was running when toggled
  GameOfLifeFrame* game_of_life_frame_;
};
#endif //GAMEOFLIFE__WINDOWGRAPHICS_H_
