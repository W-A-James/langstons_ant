#include "ant.h"

Ant::Ant(size_t x, size_t y)
    : m_x(x), m_y(y), m_current_dir(Direction::North) {}

void Ant::updateDirection(Colour current_colour) {
  switch (current_colour) {
  case Colour::WHITE:
    turnClockwise();
    break;
  case Colour::BLACK:
    turnCounterClockwise();
    break;
  }
}


void Ant::turnClockwise() {
  switch (m_current_dir) {
  case Ant::Direction::North:
    m_current_dir = Direction::East;
    break;
  case Ant::Direction::East:
    m_current_dir = Direction::South;
    break;
  case Ant::Direction::South:
    m_current_dir = Direction::West;
    break;
  case Ant::Direction::West:
    m_current_dir = Direction::North;
    break;
  }
}

void Ant::turnCounterClockwise() {
  switch (m_current_dir) {
  case Ant::Direction::North:
    m_current_dir = Direction::West;
    break;
  case Ant::Direction::East:
    m_current_dir = Direction::North;
    break;
  case Ant::Direction::South:
    m_current_dir = Direction::East;
    break;
  case Ant::Direction::West:
    m_current_dir = Direction::South;
    break;
  }
}
