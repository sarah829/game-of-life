//
// Created by Sarah Youngquist on 6/2/21.
//

#include "FrameGraphics.h"
#include <wx/wxprec.h>
#include <wx/tglbtn.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <iostream>

GameOfLifeFrame::GameOfLifeFrame(int rows, int cols) : wxFrame(nullptr, wxID_ANY, "Game of Life", wxDefaultPosition, wxSize(1200, 800)), gs(new wxGridSizer(rows, cols, 0, 0)), speed(500) {
  game = new GraphicsArrayGame(rows, cols, this);
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  timer = new GameTimer(this);

  game->InitializeGrid();
  game->AddPanels(gs);
  sizer->Add(gs, 1, wxEXPAND);

  // create menu at the bottom
  wxBoxSizer* menu_sizer = new wxBoxSizer(wxHORIZONTAL);
  play_button = new wxButton(this, wxID_ANY, "Play");
  pause_button = new wxButton(this, wxID_ANY, "Pause");
  reset_button = new wxButton(this, wxID_ANY, "Reset");
  choose_squares = new wxToggleButton(this, wxID_ANY, "Choose Squares");
  slow_button = new wxButton(this, wxID_ANY, "Slower");
  fast_button = new wxButton(this, wxID_ANY, "Faster");
  menu_sizer ->AddStretchSpacer();
  menu_sizer -> Add(play_button);
  menu_sizer ->AddStretchSpacer();
  menu_sizer -> Add(pause_button);
  menu_sizer ->AddStretchSpacer();
  menu_sizer -> Add(fast_button);
  menu_sizer ->AddStretchSpacer();
  menu_sizer -> Add(slow_button);
  menu_sizer ->AddStretchSpacer();
  menu_sizer -> Add(choose_squares);
  menu_sizer ->AddStretchSpacer();
  menu_sizer -> Add(reset_button);
  menu_sizer ->AddStretchSpacer();
  sizer->Add(menu_sizer, 0, wxEXPAND, 10);

  SetSizer(sizer);
  Centre();

  // connect buttons
  Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(GameOfLifeFrame::OnClose));
  Connect(play_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GameOfLifeFrame::OnPlay));
  Connect(pause_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GameOfLifeFrame::OnPause));
  Connect(choose_squares->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(GameOfLifeFrame::OnToggle));
  Connect(reset_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GameOfLifeFrame::OnReset));
  Connect(slow_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GameOfLifeFrame::OnSlow));
  Connect(fast_button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GameOfLifeFrame::OnFast));
}

GameOfLifeFrame::~GameOfLifeFrame() {
}

void GameOfLifeFrame::OnClose(wxCloseEvent &event) {
  delete timer;
  delete game;
  event.Skip(true);
}

void GameOfLifeFrame::OnPlay(wxCommandEvent &event) {
  game->SetModify(false);
  choose_squares->SetValue(false);
  timer->Start(speed);
}
void GameOfLifeFrame::OnPause(wxCommandEvent &event) {
  game->SetModify(false);
  choose_squares->SetValue(false);
  timer->Stop();
}

// pauses if currently going, then will start again if it was.
void GameOfLifeFrame::OnToggle(wxCommandEvent &event) {
  game->SetModify(!(game->IsModify()));
  if (game->IsModify())
  {
    timer->SetGoing(timer->IsRunning());
    timer->Stop();
  }
  if (!(game->IsModify()))
  {
    if (timer->WasGoing())
      timer->Start();
  }
}

void GameOfLifeFrame::OnReset(wxCommandEvent &event) {
  game->Clear();
  Refresh();
  Update();
}

void GameOfLifeFrame::OnSlow(wxCommandEvent &event)
{
  game->SetModify(false);
  choose_squares->SetValue(false);
  timer->Start(((timer->GetInterval()) * 5) / 4);
}

void GameOfLifeFrame::OnFast(wxCommandEvent &event)
{
  game->SetModify(false);
  choose_squares->SetValue(false);
  timer->Stop();
  timer->Start(((timer->GetInterval()) * 4) / 5);
}


GameTimer::GameTimer(GameOfLifeFrame* game_frame) : wxTimer(), game_of_life_frame_(game_frame), was_going(false) { }

GameTimer::~GameTimer() {
}

void GameTimer::Notify() {
  if (game_of_life_frame_->game->GetNumFilled() > 0)
  {
    game_of_life_frame_->game->AdvanceState();
    game_of_life_frame_->Refresh();
    game_of_life_frame_->Update();
  }
}

bool GameTimer::WasGoing() {
  return was_going;
}

void GameTimer::SetGoing(bool going)
{
  was_going = going;
}