//
// Created by Sarah Youngquist on 6/2/21.
//
#include "SimpleArrayGame.h"
#include "windowGraphics.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "GraphicsGameClasses.h"

const wxColour *GraphicsGridElement::ON_COLOUR = wxStockGDI::GetColour(wxStockGDI::COLOUR_BLUE);
const wxColour *GraphicsGridElement::OFF_COLOUR = wxStockGDI::GetColour(wxStockGDI::COLOUR_CYAN);
const int GraphicsGridElement::BASE_ID = 100;

GraphicsGridElement::GraphicsGridElement(GraphicsArrayGame *game, wxWindow* grid_window) : GridElement(), parent_game(game), p_panel(new GraphicsElementPanel(game, grid_window, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)) {
  SetColor();
}

GraphicsGridElement::GraphicsGridElement(GraphicsArrayGame *game, wxWindow *grid_window, int id) : GridElement(), parent_game(game), p_panel(new GraphicsElementPanel(game, grid_window, id, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)) {
  SetColor();
}

GraphicsGridElement::GraphicsGridElement(GraphicsArrayGame *game, GraphicsElementPanel *p_panel) : GridElement(), parent_game(game), p_panel(p_panel){
  SetColor();
}

GraphicsGridElement::GraphicsGridElement(GraphicsArrayGame *game, bool on, GraphicsElementPanel *p_panel)
    : GridElement(on), parent_game(game), p_panel(p_panel) {
  SetColor();
}

GraphicsGridElement::GraphicsGridElement(GraphicsArrayGame *game, bool on, int num_neighbors, GraphicsElementPanel *p_panel)
    : GridElement(on, num_neighbors), p_panel(p_panel) {
  SetColor();
}

GraphicsElementPanel *GraphicsGridElement::GetPanel() const {
  return p_panel;
}

GraphicsGridElement::~GraphicsGridElement() {
  p_panel->Destroy();
}

void GraphicsGridElement::SetOn(bool on) {
  GridElement::SetOn(on);
  if (on)
    p_color = GraphicsGridElement::ON_COLOUR;
  else
    p_color = GraphicsGridElement::OFF_COLOUR;
  p_panel->SetBackgroundColour(p_color->GetAsString());
}

void GraphicsGridElement::SetColor()
{
  if (on_)
    p_color = GraphicsGridElement::ON_COLOUR;
  else
    p_color = GraphicsGridElement::OFF_COLOUR;
  p_panel->SetBackgroundColour(p_color->GetAsString());
  p_panel->Refresh();
  p_panel->Update();
}

void GraphicsGridElement::DeletePanel() {
  p_panel->Destroy();
  p_panel = nullptr;
}

// GraphicsArrayGame ------------------------------------------------------------------------------
GraphicsArrayGame::GraphicsArrayGame() : SimpleArrayGame()
{
  p_grid_window = new wxWindow();
  modify = false;
}

GraphicsArrayGame::GraphicsArrayGame(int height, int width) : SimpleArrayGame(height, width)
{
  p_grid_window = new wxWindow();
  modify = false;
}

GraphicsArrayGame::GraphicsArrayGame(int height,
                int width,
                int initial_condition[][2],
                int num_elements) : SimpleArrayGame(height, width, initial_condition, num_elements)
{
  p_grid_window = new wxWindow();
  modify = false;
}

GraphicsArrayGame::GraphicsArrayGame(wxWindow *window) : SimpleArrayGame(), p_grid_window(window){
  modify = false;
}
GraphicsArrayGame::GraphicsArrayGame(int height, int width, wxWindow *window) : SimpleArrayGame(height, width), p_grid_window(window) {
  modify = false;
}

GraphicsArrayGame::GraphicsArrayGame(int height,
                                     int width,
                                     int (*initial_condition)[2],
                                     int num_elements,
                                     wxWindow *window) : SimpleArrayGame(height, width, initial_condition, num_elements), p_grid_window(window) {
  modify = false;
}

GraphicsArrayGame::~GraphicsArrayGame()
{
}

void GraphicsArrayGame::InitializeGrid() {
  pp_grid_ = new GridElement*[width_ * height_];
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + height_ * width_; ++pp_element)
  {
    *pp_element = new GraphicsGridElement(this, p_grid_window, GraphicsGridElement::BASE_ID + pp_element - pp_grid_);
  }
}

void GraphicsArrayGame::Clear() {
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + width_ * height_; ++pp_element)
  {
    (*pp_element)->SetOn(false);
    (*pp_element)->SetNumNeighbors(0);
  }
  num_filled_ = 0;
}

void GraphicsArrayGame::AddPanels(wxGridSizer* gs)
{
  GridElement** pp_element = nullptr;
  GraphicsGridElement* p_grid_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + width_ * height_; ++pp_element)
  {
    p_grid_element = dynamic_cast<GraphicsGridElement*>(*pp_element);
    gs->Add(p_grid_element->GetPanel(), 1, wxEXPAND);
  }
}

wxWindow *GraphicsArrayGame::GetGridWindow() const {
  return p_grid_window;
}

void GraphicsArrayGame::SetGridWindow(wxWindow *grid_window) {
  p_grid_window = grid_window;
}

bool GraphicsArrayGame::IsModify()
{
  return modify;
}

void GraphicsArrayGame::SetModify(bool mod)
{
  modify = mod;
};


GraphicsElementPanel::GraphicsElementPanel(GraphicsArrayGame* game, wxWindow *parent,
                                           wxWindowID winid,
                                           const wxPoint &pos,
                                           const wxSize &size,
                                           long style,
                                           const wxString &name) : p_game(game), wxPanel(parent, winid, pos, size, style, name) {
  Connect(GetId(), wxEVT_LEFT_DOWN, wxMouseEventHandler(GraphicsElementPanel::OnClicked));
}

void GraphicsElementPanel::OnClicked(wxMouseEvent &event) {
  if (p_game->IsModify())
  {
    p_game->ToggleElement(GetId() - GraphicsGridElement::BASE_ID);
    Refresh();
    Update();
  }
  event.Skip();
}

