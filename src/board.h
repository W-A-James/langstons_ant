#pragma once
#include "ant.h"
#include "common.h"
#include <cstddef>
#include <vector>

class Board {
public:
  size_t m_width, m_height;
  std::vector<Colour> m_board;
  std::vector<Ant *> m_ants;

  Board(size_t w, size_t h);
  ~Board();

  void step();
  void add_ant(size_t x, size_t y);

  Colour get(size_t x, size_t y);
  void set(size_t x, size_t y, Colour c);
};
