/*
  File name: GameOfLifeApp.h
  @author: Sarah Youngquist
  Purpose: The app, the "main" class
  Classes:
    GameOfLifeWindowApp (extends public wxApp)
  History:
  Date             Action
  2021-06-02       Creation
  2021-11-28       Moved to separate header file
 */

#ifndef GAMEOFLIFE__GAMEOFLIFEAPP_H_
#define GAMEOFLIFE__GAMEOFLIFEAPP_H_

#include <wx/wxprec.h>
#include <wx/tglbtn.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class GameOfLifeWindowApp : public wxApp {
 public:
  virtual bool OnInit();
};

#endif //GAMEOFLIFE__GAMEOFLIFEAPP_H_
