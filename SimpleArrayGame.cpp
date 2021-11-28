
//
// Created by Sarah Youngquist on 5/28/21.
//

#include <iostream>
#include <vector>
#include "SimpleArrayGame.h"

const int SimpleArrayGame::DEFAULT_DIMENSION = 10;

// constructors DO NOT initialize the grid
SimpleArrayGame::SimpleArrayGame() : height_(SimpleArrayGame::DEFAULT_DIMENSION), width_(SimpleArrayGame::DEFAULT_DIMENSION), num_filled_(0) {
}

SimpleArrayGame::SimpleArrayGame(int height, int width) : height_(height), width_(width), num_filled_(0) {
}

SimpleArrayGame::SimpleArrayGame(int height,
                                 int width,
                                 int initial_condition[][2],
                                 int num_elements) {
  SimpleArrayGame(height, width);
  SetElements(initial_condition, num_elements);
}

SimpleArrayGame::~SimpleArrayGame() {
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + height_ * width_; ++pp_element)
  {
    delete (*pp_element);
  }
  delete[] pp_grid_;
}
int SimpleArrayGame::GetHeight() const {
  return height_;
}
void SimpleArrayGame::SetHeight(int height) {
  height_ = height;
}
int SimpleArrayGame::GetWidth() const {
  return width_;
}
void SimpleArrayGame::SetWidth(int width) {
  width_ = width;
}

GridElement* SimpleArrayGame::GetElement(int row, int col)
{
  return pp_grid_[row * width_ + col];
}

GridElement* SimpleArrayGame::GetElement(int index)
{
  return pp_grid_[index];
}

int SimpleArrayGame::GetNumFilled() {
  return num_filled_;
}
bool SimpleArrayGame::SetPosition(int condition[][2], int num_elements) {
  Clear();
  return SetElements(condition, num_elements);
}
bool SimpleArrayGame::IsEmpty() const {
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + height_ * width_; ++pp_element)
  {
    if (**pp_element)
      return false;
  }
  return true;
}

void SimpleArrayGame::AdvanceState() {
  ChangeOn();
  UpdateNeighborCount();
}

void SimpleArrayGame::ToggleElement(int row, int col) {
  GridElement* p_element = pp_grid_[GetIndexFromCoordinates(row, col)];
  if (*p_element)
  {
    p_element->SetOn(false);
    num_filled_--;
  }
  else
  {
    p_element->SetOn(true);
    num_filled_++;
  }
  ZeroNeighborCount();
  UpdateNeighborCount();
}

void SimpleArrayGame::ToggleElement(int index)
{
  ToggleElement(index / width_, index % width_);
}

std::ostream &operator<<(std::ostream &os, const SimpleArrayGame &game) {
  GridElement** pp_element = nullptr;
  for (pp_element = game.pp_grid_; pp_element < game.pp_grid_ + game.height_ * game.width_; ++pp_element)
  {
    if (**pp_element)
      os << "*";
    else
      os << "-";
    os << " ";
    if ((pp_element - game.pp_grid_) % game.width_ == game.width_ - 1)
      os << std:: endl;
  }
  os << std::endl;

  return os;
}

void SimpleArrayGame::InitializeGrid() {
  pp_grid_ = new GridElement*[height_ * width_];
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + height_ * width_; ++pp_element)
  {
    *pp_element = new GridElement();
  }
}
bool SimpleArrayGame::SetElements(int condition[][2], int num_elements) {
  bool successful = true;
  for (int elem = 0; elem < num_elements; ++elem)
  {
    if (condition[elem][0] < height_ && condition[elem][1] < width_)
    {
      pp_grid_[GetIndexFromCoordinates(condition[elem][0], condition[elem][1])]->SetOn(true);
      ++num_filled_;
    }
    else
      successful = false;
  }
  UpdateNeighborCount();
  return successful;
}

void SimpleArrayGame::Clear() {
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + width_ * height_; ++pp_element)
  {
    delete *pp_element;
    *pp_element = new GridElement();
  }
  num_filled_ = 0;
}
void SimpleArrayGame::ChangeOn() {
  GridElement** pp_element = nullptr;
  int neighbors = 0;

  for (pp_element = pp_grid_; pp_element < pp_grid_ + width_ * height_; ++pp_element)
  {
    neighbors = (*pp_element)->GetNumNeighbors();
    if (!(**pp_element))
    {
      if (neighbors == 3)
      {
        (*pp_element)->SetOn(true);
        ++num_filled_;
      }
    }
    else
    {
      if (neighbors != 2 && neighbors != 3)
      {
        (*pp_element)->SetOn(false);
        --num_filled_;
      }
    }

    (*pp_element)->SetNumNeighbors(0); // will change later
  }
}

void SimpleArrayGame::UpdateNeighborCount() {
  // locations of the neighbors (when added to the coordinate)
  int squares[8][2] = {
      {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
  };
  for (int row = 0; row < height_; ++row)
  {
    for (int col = 0; col < width_; ++ col)
    {
      if (pp_grid_[row * width_ + col]) {
        // add 1 to the number of neighbors if neighboring square
        for (auto &square : squares) {
          int r = row + square[0];
          int c = col + square[1];
          if (r >= 0 && r < height_ && c >= 0 && c < width_)
          {
            if (*pp_grid_[r * width_ + c])
              pp_grid_[row * width_ + col]->IncrementNumNeighbors();
          }
        }
      }
    }
  }
}

void SimpleArrayGame::ZeroNeighborCount()
{
  GridElement** pp_element = nullptr;
  for (pp_element = pp_grid_; pp_element < pp_grid_ + width_ * height_; ++pp_element)
  {
    (*pp_element)->SetNumNeighbors(0);
  }
}

int SimpleArrayGame::GetIndexFromCoordinates(int row, int col) {
  return width_ * row + col;
}

std::vector<int> SimpleArrayGame::GetCoordinatesFromIndex(int index) {
  std::vector<int> ret;
  ret.push_back(index / width_);
  ret.push_back(index % width_);
  return ret;
}




GridElement::GridElement() : on_(false), num_neighbors_(0) {}

GridElement::GridElement(bool on, int num_neighbors) : on_(on), num_neighbors_(num_neighbors) {}

GridElement::GridElement(bool on) : on_(on), num_neighbors_(0) {}

GridElement::~GridElement() = default;

bool GridElement::IsOn() const {
  return on_;
}
void GridElement::SetOn(bool on) {
  on_ = on;
}
int GridElement::GetNumNeighbors() const {
  return num_neighbors_;
}
void GridElement::SetNumNeighbors(int num_neighbors) {
  num_neighbors_ = num_neighbors;
}

void GridElement::IncrementNumNeighbors() {
  ++num_neighbors_;
}

std::ostream &operator<<(std::ostream &os, const GridElement &element) {
  os << "on_: " << element.on_ << " num_neighbors_: " << element.num_neighbors_;
  return os;
}
bool GridElement::operator==(const GridElement &rhs) const {
  return on_ == rhs.on_ &&
      num_neighbors_ == rhs.num_neighbors_;
}
bool GridElement::operator!=(const GridElement &rhs) const {
  return !(rhs == *this);
}
GridElement::operator bool() const {
  return on_;
}

