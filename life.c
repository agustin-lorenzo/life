#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int rows;
int cols;
bool **grid;

int getNumNeighbors(int i, int j) {
  int count = 0;

  int deltaCol[] = {-1,-1,-1,0,0,1,1,1};
  int deltaRow[] = {-1,0,1,-1,1,-1,0,1};

  for (int i = 0; i < 8; i++) {
    int x = i + deltaCol[i];
    int y = j + deltaRow[i];

    if (x >= 0 && x < cols && y >= 0 && y < rows
    && grid[y][x] == true) {
      count++;
    }
  }

  return count;
	    
} // getNumNeighbors()

void updateGrid() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // Check cell color
      if(grid[i][j] == true) { // Cell is alive
	// Count the number of neighbors
	int numAliveNeighbors = getNumNeighbors(i, j);

	// Cell dies from lonliness/overpopulation
	if (numAliveNeighbors < 2 || numAliveNeighbors > 3) {
	  grid[i][j] = false;
	}

      } else { // Cell is dead
	// Count the number of neighbors
	int numAliveNeighbors = getNumNeighbors(i, j);

	if (numAliveNeighbors == 3) {
	  grid[i][j] = true;
	}
      }
      
    }
  }
  
} // updateGrid()

void renderGrid() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j]) {
	mvaddch(i, j, 'O');
      } else {
	start_color();
	init_color(1, 100, 100, 100);
	init_pair(2, 1, COLOR_BLACK);
	attron(COLOR_PAIR(2) | A_DIM);
	mvaddch(i, j, 'X');
	attroff(COLOR_PAIR(2) | A_DIM);
      }
    }
  }
}

int main() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  curs_set(0);
  getmaxyx(stdscr, rows, cols);
  srand(time(NULL));

  grid = (bool **)malloc(rows * sizeof(bool *));
  for (int i = 0; i < rows; i++) {
    grid[i] = (bool *)malloc(cols * sizeof(bool));
    for (int j = 0; j < cols; j++) {
      double randomValue = (double)rand() / RAND_MAX;
      if (randomValue > 0.5) {
	grid[i][j] = true; // Initialize all cells randomly
      } else {
	grid[i][j] = false;
      }
    }
  }

  // Render the grid for each new step
  while (true) {
    renderGrid();
    updateGrid();
    //addstr(win, "Hello world", 0, 0);
    //mvaddstr(0, strlen("Hello world"), "Hello world");
    init_color(1, 200, 200, 200);
    init_pair(1, 1, COLOR_WHITE);
    attron(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE);
    mvaddstr(0, (cols/2 - strlen("Conway's Game of Life")/2), "Conway's Game of Life");
    attroff(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE);
    refresh();
    getch();
  }
  

  // Free allocated memory when you're done
  for (int i = 0; i < rows; i++) {
    free(grid[i]);
  }
  free(grid);
  printf("\n\n");
  
  endwin();
  return 0;
  
} // main
