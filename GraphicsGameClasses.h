/*
  File name: GraphicsGameClasses.h
  @author: Sarah Youngquist
  Purpose: Defines graphical versions of the classes needed for the game
  Classes:
    GraphicsGridElement (extends GridElement):
      Attaches a color, a panel, and a parent game to GameElement
    GraphicsArrayGame (extends SimpleArrayGame):
      Adds a window to SimpleArrayGame to methods to initialize the grid
    GraphicsElementPanel (extends wxPanel):
      Controls the OnClick behavior of grid elements
  History:
  Date             Action
  2021-06-02/3/4   Initial coding
  2021-11-28       Added additional documentation
 */

#include "SimpleArrayGame.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifndef GAMEOFLIFE__GRAPHICSGAMECLASSES_H_
#define GAMEOFLIFE__GRAPHICSGAMECLASSES_H_
class GraphicsArrayGame;
class GraphicsElementPanel;

class GraphicsGridElement : public GridElement {
 public:
  GraphicsGridElement(GraphicsArrayGame* game, wxWindow* grid_window);
  GraphicsGridElement(GraphicsArrayGame* game, wxWindow* grid_window, int id);
  GraphicsGridElement(GraphicsArrayGame* game, bool on, GraphicsElementPanel *p_panel);
  explicit GraphicsGridElement(GraphicsArrayGame* game, GraphicsElementPanel *p_panel);
  GraphicsGridElement(GraphicsArrayGame* game, bool on, int num_neighbors, GraphicsElementPanel *p_panel);
  virtual ~GraphicsGridElement();
  GraphicsElementPanel *GetPanel() const;
  void DeletePanel();
  virtual void SetOn(bool on);
 public:
  static const wxColour* ON_COLOUR;
  static const wxColour* OFF_COLOUR;
  static const int BASE_ID;
 private:
  GraphicsArrayGame* parent_game;
  GraphicsElementPanel* p_panel;
  const wxColour* p_color;
  void SetColor();
};

// must use GraphicsGridElements, not GridElements
class GraphicsArrayGame : public SimpleArrayGame {
 public:
  GraphicsArrayGame();
  GraphicsArrayGame(int height, int width);
  GraphicsArrayGame(int height,
                    int width,
                    int initial_condition[][2],
                    int num_elements);
  GraphicsArrayGame(wxWindow* window);
  GraphicsArrayGame(int height, int width, wxWindow* window);
  GraphicsArrayGame(int height,
                    int width,
                    int initial_condition[][2],
                    int num_elements, wxWindow* window);
  virtual ~GraphicsArrayGame();
  wxWindow *GetGridWindow() const;
  void SetGridWindow(wxWindow *p_grid_window);
  void AddPanels(wxGridSizer* gs);
  virtual void InitializeGrid();
  virtual void Clear();
  bool IsModify() const;
  void SetModify(bool mod);
 private:
  bool modify;
 protected:
  wxWindow* p_grid_window;
};

class GraphicsElementPanel : public wxPanel
{
 public:
  GraphicsElementPanel(GraphicsArrayGame* game, wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0x00080000 | wxBORDER_NONE, const wxString &name = wxString::FromAscii(wxPanelNameStr));
  void OnClicked(wxMouseEvent &event);
 private:
  GraphicsArrayGame* p_game;
};
#endif //GAMEOFLIFE__GRAPHICSGAMECLASSES_H_
