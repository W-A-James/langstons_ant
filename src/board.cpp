#include "board.h"
#include "ant.h"
#include "common.h"
#include <vector>

Board::Board(size_t w, size_t h) : m_width(w), m_height(h) {
  m_board.reserve(m_width * m_height);
  for (int i = 0; i < m_board.size(); i++)
    m_board[i] = Colour::WHITE;
}
Board::~Board() {
  for (auto ant : m_ants) {
    delete ant;
  }

  m_ants.clear();
  m_board.clear();
}

void Board::step() {
  for (auto ant : m_ants) {
    auto colour = this->get(ant->m_x, ant->m_y);
    switch (colour) {
    case Colour::WHITE:
      this->set(ant->m_x, ant->m_y, Colour::BLACK);
      break;
    case Colour::BLACK:
      this->set(ant->m_x, ant->m_y, Colour::WHITE);
      break;
    }
    ant->updateDirection(colour);
    switch (ant->m_current_dir) {
    case Ant::Direction::North:
      ant->m_y = ant->m_y == 0 ? this->m_height - 1 : ant->m_y - 1;
      break;
    case Ant::Direction::East:
      ant->m_x = (ant->m_x + 1) % this->m_width;
      break;
    case Ant::Direction::South:
      ant->m_y = (ant->m_y + 1) % this->m_height;
      break;
    case Ant::Direction::West:
      ant->m_x = ant->m_x == 0 ? this->m_width - 1 : ant->m_x - 1;
      break;
    }
  }
}

void Board::add_ant(size_t x, size_t y) { m_ants.push_back(new Ant(x, y)); }

Colour Board::get(size_t x, size_t y) { return m_board[y * m_width + x]; }
void Board::set(size_t x, size_t y, Colour c) { m_board[y * m_width + x] = c; }
