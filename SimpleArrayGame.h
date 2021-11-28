/*
  File name: GraphicsGameClasses.h
  @author: Sarah Youngquist
  Purpose: Contains the main logic of the game. This header has the functionalities required to have a non-interactive
    version run through the console.
  Classes:
    SimpleArrayGame:
      This is the class that contains a grid for the game and defines all game logic. It has methods to advance
      between states in the game.
    GridElement:
      Each element has a bool for on/off keeps track of how many neighbors are on.
  History:
  Date               Action
  2021-05-28/29/30   Initial coding
  2021-11-28         Added additional documentation
 */

#ifndef GAMEOFLIFE__SIMPLEARRAYGAME_H_
#define GAMEOFLIFE__SIMPLEARRAYGAME_H_

#include <ostream>

class GridElement;

class SimpleArrayGame {
 protected:
  int height_;
  int width_;
  int num_filled_;
  GridElement** pp_grid_;
 public:
  static const int DEFAULT_DIMENSION;
 public:
  SimpleArrayGame();
  SimpleArrayGame(int height, int width);
  SimpleArrayGame(int height,
                  int width,
                  int initial_condition[][2],
                  int num_elements);
  virtual ~SimpleArrayGame();
  int GetHeight() const;
  void SetHeight(int height);
  int GetWidth() const;
  void SetWidth(int width);
  GridElement* GetElement(int row, int col);
  GridElement *GetElement(int index);
  int GetNumFilled();
  virtual bool SetPosition(int condition[][2], int num_elements);
  bool IsEmpty() const;
  virtual void AdvanceState();
  void ToggleElement(int row, int col);
  void ToggleElement(int index);
  virtual void InitializeGrid();
  virtual void Clear();
  friend std::ostream &operator<<(std::ostream &os, const SimpleArrayGame &game);
 protected:
  bool SetElements(int condition[][2], int num_elements);
  void UpdateNeighborCount();
  void ZeroNeighborCount();
  void ChangeOn();
  int GetIndexFromCoordinates(int row, int col);
  std::vector<int> GetCoordinatesFromIndex(int index);
};

class GridElement {
 protected:
  bool on_;
  int num_neighbors_;
  SimpleArrayGame* parent_game;
 public:
  GridElement();
  explicit GridElement(bool on);
  GridElement(bool on, int num_neighbors);
  virtual ~GridElement();
  bool IsOn() const;
  virtual void SetOn(bool on);
  int GetNumNeighbors() const;
  void SetNumNeighbors(int num_neighbors);
  void IncrementNumNeighbors();
  bool operator==(const GridElement &rhs) const;
  bool operator!=(const GridElement &rhs) const;
  operator bool() const;
  friend std::ostream &operator<<(std::ostream &os, const GridElement &element);
};
#endif //GAMEOFLIFE__SIMPLEARRAYGAME_H_
