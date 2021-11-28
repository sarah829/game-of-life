//
// Created by Sarah Youngquist on 5/28/21.
//

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
