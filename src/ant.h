#pragma once
#include "common.h"
#include <cstddef>

class Ant {
public:
  Ant(size_t x, size_t y);
  size_t m_x, m_y;
  enum Direction { North, East, South, West };
  Direction m_current_dir;
  void updateDirection(Colour current_colour);

private:
  void turnClockwise();
  void turnCounterClockwise();
};
