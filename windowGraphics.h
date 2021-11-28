//
// Created by Sarah Youngquist on 6/2/21.
//

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

class GameOfLifeWindowApp : public wxApp {
 public:
  virtual bool OnInit();
  int GetMoves();
  void SetMoves(int moves);
 private:
  int moves_;
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
