#include "ant.h"
#include "board.h"
#include "common.h"

#ifdef WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include <chrono>
#include <cstdlib>
#include <ncurses.h>
#include <signal.h>

static void end(int sig);

using namespace std::chrono_literals;
int main(int argc, char **argv) {
  signal(SIGINT, end);
  size_t terminal_columns, terminal_rows;
#ifdef WIN32
  CONSOLE_SCREEN_BUFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
  winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  terminal_columns = w.ws_col;
  terminal_rows = w.ws_row;
#endif
  bool running{true};
  size_t generation = 0;
  auto frame_time_ms = 1ms;

  /* Initialize ncurses window */
  initscr();
  keypad(stdscr, TRUE);
  nonl();
  cbreak();
  nodelay(stdscr, TRUE);

  if (has_colors()) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
  }

  auto board = new Board(terminal_columns, terminal_rows);
  board->add_ant(board->m_width / 4, board->m_height / 4);
  board->add_ant(board->m_width / 2, board->m_height / 2);
  board->add_ant(3 * board->m_width / 4, 3 * board->m_height / 4);

  auto now = std::chrono::steady_clock::now();
  auto previous = std::chrono::steady_clock::now();
  for (;;) {
    auto time_since_previous_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - previous);

    if (running && (time_since_previous_ms >= frame_time_ms)) {
      move(0, 0);
      for (size_t i = 0; i < board->m_width * board->m_height; i++) {
        switch (board->m_board[i]) {
        case Colour::BLACK:
          attrset(COLOR_PAIR(2));
          break;
        case Colour::WHITE:
          attrset(COLOR_PAIR(1));
          break;
        }
        addch(' ');
      }
      board->step();
      for (auto ant : board->m_ants) {
        move((int)ant->m_y, (int)ant->m_x);
        attrset(COLOR_PAIR(3));
        addch('0');
      }
      previous = now;
      move(0, 0);
      attrset(COLOR_PAIR(0));
      printw("generation: %lu", generation++);

      refresh();
    }
    now = std::chrono::steady_clock::now();
  }
  end(0);
  return 0;
}
static void end(int sig) {
  endwin();
  exit(0);
}
