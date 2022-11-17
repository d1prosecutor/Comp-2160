//-----------------------------------------
// NAME: Chukwunaza Chukwuocha
// STUDENT NUMBER: 7928676
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// ASSIGNMENT: assignment 2
//
// REMARKS: Implements The backtracking algorithm and Linked list (using Structs) to make
// a simple maze game
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

#define MAX_DIMENSION 20

// constant definitions for the different cell states
const char WALL = '1';
const char SPACE = '0';
const char VISITED = '.';
const char MOUSE = 'm';
const char EXIT = 'e';

typedef enum BOOL
{
  false,
  true
} Boolean;

struct CELL
{
  int row;
  int column;
};
typedef struct CELL Cell;

typedef struct CELL_NODE CellNode;
struct CELL_NODE
{
  Cell cell;
  CellNode *next;
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

CellNode *top = NULL;

// a 2D array used to store the maze
char maze[MAX_DIMENSION][MAX_DIMENSION];
int mazeRows;
int mazeCols;

// holds the location of the mouse and escape hatch
Cell mouse;
Cell escape;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// basic cell manipulation

// returns true if the cells are at the same position in our maze
Boolean equalCells(const Cell cell1, const Cell cell2);
// returns a new cell object
Cell makeCell(const int row, const int col);
// returns true if the cell is within our maze
Boolean validCell(const Cell theCell);

// routines for managing our backtracking

// returns true if there are no more cells to try
Boolean noMoreCells();
// returns the next cell to try for a path out of the maze
Cell nextCell();
// introduces a new cell to try
void addCell(const Cell cell);

void printMaze();
void loadMaze();

// returns true if there's a solution to the maze
Boolean solveMaze();

// our invariant checker
void checkState();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  loadMaze();

  if (solveMaze())
    printf("The mouse is free!!!!\n");
  else
    printf("The mouse is trapped!!!!\n");

  printf("\nEnd of processing\n");

  return EXIT_SUCCESS;
}

//////////////////////////////////////////////
// Cell routines
//////////////////////////////////////////////

//------------------------------------------------------
// equalCells
//
// PURPOSE: Checks if two cells are equal
// INPUT PARAMETERS:
// cell1: The first cell to be compared
// cell2: The second cell to be compared
// OUTPUT PARAMETERS:
// boolFlag: The boolean which states if the cells are equal or not
//------------------------------------------------------
Boolean equalCells(const Cell cell1, const Cell cell2)
{
  // Verify that the 2 cells are valid
  assert(validCell(cell1) && validCell(cell2));

  //........................

  Boolean boolFlag = false;

  if ((cell1.row == cell2.row) && (cell1.column == cell2.column))
  {
    boolFlag = true;
  }

  return boolFlag;
}

//------------------------------------------------------
// makeCell
//
// PURPOSE: Creates and initialzes a new cell with the given row and column values
// INPUT PARAMETERS:
// row: The row to be assigned to the cell
// col: The column to be assigned to the cell
// OUTPUT PARAMETERS:
// newCell: The newly created cell
//------------------------------------------------------
Cell makeCell(const int row, const int col)
{
  // assert that the coordinates are valid
  assert((row >= 0 && row < mazeRows) && (col >= 0 && col < mazeCols));

  Cell newCell;
  newCell.row = row;
  newCell.column = col;

  // Check that a new cell was successfully made and correctly initialized
  assert(newCell.row == row && newCell.column == col);
  assert(validCell(newCell));

  return newCell;
}

//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////

//------------------------------------------------------
// addCell
//
// PURPOSE: adds a given cell to the stack(implented as a linked list)
// INPUT PARAMETERS:
// cell: The cell to be added to the list
//------------------------------------------------------
void addCell(const Cell cell)
{
  // Verify that the cell to be added is valid
  assert(validCell(cell));

  CellNode *temp = top;

  // Check if the cell is not already in the list
  Boolean isInList = false;

  while (temp != NULL && isInList != true)
  {
    if (equalCells(cell, temp->cell))
    {
      isInList = true;
    }
    temp = temp->next;
  }

  // add the cell to the list if it is not already in the list
  if (isInList == false)
  {
    CellNode *newCell = malloc(sizeof(CellNode));

    if (newCell != NULL)
    {
      newCell->cell = cell;
      newCell->next = top;

      top = newCell;
    }
  }

  // The stack(list) must be non-empty once a cell is added
  assert(false == noMoreCells());

  // The top must also be the same as the cell which was just added
  if (isInList == false)
  {
    assert(equalCells(top->cell, cell));
  }
}

//------------------------------------------------------
// nextCell
//
// PURPOSE: Returns the first Cell from the list of cells and removes it from the list
// OUTPUT PARAMETERS:
// tempCell: A copy of the first cell in the list which has been removed from the list
//------------------------------------------------------
Cell nextCell()
{
  // The list has to be non-empty
  assert(false == noMoreCells());

  // Chekcs that the cell to be returned is part of the maze
  assert(validCell(top->cell));

  CellNode *garbagePointer = top; // Using this to free the garbage in memory no longer being used

  Cell tempCell = top->cell;
  top = top->next;

  // free the memory allocated to the node which was just detached from the list
  free(garbagePointer);

  // Verify that the first cell was indeed removed from the list and it
  // does not equal the next cell in the list (inherently verifying that there are no duplicates)
  if (top != NULL)
  { // If the list is not empty
    assert(!equalCells(top->cell, tempCell));
  }

  // averufy that the cell that was copied out is still valid
  assert(validCell(tempCell));

  return tempCell;
}

//------------------------------------------------------
// noMoreCells
//
// PURPOSE: checks if the list containing the cells is empty
// INPUT PARAMETERS:
// OUTPUT PARAMETERS:
// boolFlag : A boolean stating if the list is empty or not
//------------------------------------------------------
Boolean noMoreCells()
{
  Boolean boolFlag = false;

  if (top == NULL)
  {
    boolFlag = true;
  }

  return boolFlag;
}

//////////////////////////////////////////////
// Maze routines
//////////////////////////////////////////////

//------------------------------------------------------
// validCell
//
// PURPOSE: Checks if a given cell is within the maze, ie, has dimensions which are
// non-negative and not more than the mazeRows and mazeCols
// INPUT PARAMETERS:
// theCell : The cell to be checked
// OUTPUT PARAMETERS:
// boolFlag: A boolean stating if the given cell is within the maze or not
//------------------------------------------------------
Boolean validCell(const Cell theCell)
{
  Boolean boolFlag = false;

  if ((theCell.row > 0 && theCell.row < mazeRows) && (theCell.column > 0 && theCell.column < mazeCols))
  {
    boolFlag = true;
  }

  return boolFlag;
}

//------------------------------------------------------
// loadMaze
//
// PURPOSE: Reads input from standard input and uses the input read to create the maze
// and initialize all its required cells(Walls, spaces, starting postion and the exit).
//------------------------------------------------------
void loadMaze()
{
  // Reads the first line(Containing two integers- the row and column sizes of the maze)
  scanf("%d %d", &mazeRows, &mazeCols);

  // Makes sure that the given size(dimensions) of the maze is non negative
  assert((mazeRows >= 0 && mazeRows <= MAX_DIMENSION) && (mazeCols >= 0 && mazeCols <= MAX_DIMENSION));

  // consumes the newLine (and possibly carriage return line feed for windows)
  // character which is left in the buffer by scanf
  char garbageChars[MAX_DIMENSION];
  fgets(garbageChars, MAX_DIMENSION, stdin);

  // Variables for the current position while filling up the maze
  int rowIndex = 0;
  int columnIndex = 0;

  // giving enough buffer space for the situation where the input file has max number of maze characters in a column
  //  plus the spaces inbetween each column character
  //(also accounting for the \n char at the end of each line (with the +1))
  int lineLength = (MAX_DIMENSION * 2) + 1;

  // New temp char array used to read each line of the input file and fill up the maze
  char tempChar[lineLength];

  while ((rowIndex < mazeRows) && fgets(tempChar, lineLength, stdin) != NULL)
  {
    int newCharIndex = 0; // index of each character in the new Line being read
    columnIndex = 0;      // index of the next column in the maze

    while (tempChar[newCharIndex] != '\n' && columnIndex < mazeCols)
    {
      if (tempChar[newCharIndex] == SPACE || tempChar[newCharIndex] == EXIT ||
          tempChar[newCharIndex] == MOUSE || tempChar[newCharIndex] == WALL)
      {
        maze[rowIndex][columnIndex] = tempChar[newCharIndex];

        // Initialize the start and escape cells for the maze
        if (tempChar[newCharIndex] == MOUSE)
        {
          mouse.row = rowIndex;
          mouse.column = columnIndex;
        }
        else if (tempChar[newCharIndex] == EXIT)
        {
          escape.row = rowIndex;
          escape.column = columnIndex;
        }

        // increase the number of characters added in each column
        columnIndex++;
      }

      // go to the next charcter in the current string line being read
      newCharIndex++;
    }

    // Move to the next row
    rowIndex++;
  }

  // Verify that the whole maze is valid after loading it
  checkState();

  // Print the maze in its original state
  printMaze();
}

//------------------------------------------------------
// solveMaze
//
// PURPOSE: Guides the mouse from its starting position to the exit position if there
// exists a path (hence trying to solve the maze).
// OUTPUT PARAMETERS:
// mazeSolved: A boolean that states if there exists a path from the mouse's starting position
// to the exit position or not
//------------------------------------------------------
Boolean solveMaze()
{
  // check that the maze to be solved is still valid
  checkState();

  // The flag to check if there is a solution or not
  Boolean mazeSolved = true;

  // Starting Point
  Cell currentCell = mouse;

  // Verify that startCell was successfully copied into escape cell
  assert((currentCell.row == mouse.row) && (currentCell.column == mouse.column));

  while ((!equalCells(currentCell, escape)) && mazeSolved == true)
  {
    // Verify that the all the cells in the stack are still valid
    checkState();

    maze[currentCell.row][currentCell.column] = VISITED;
    printMaze();

    //!!!Remember to check for array out of bounds here
    //---This is where you add to the list the unvisited open neighbours of currentCell or some shit like that
    // You also need to check how to set mazeSolved to true or false depending on if the loop exited due to the escape
    // cell being found or because there are no more cells;

    // Check the Right Cell for a space or the exit
    if ((maze[currentCell.row][currentCell.column + 1] == SPACE) ||
        (maze[currentCell.row][currentCell.column + 1] == EXIT))
    {
      addCell(makeCell(currentCell.row, currentCell.column + 1));
    }

    // Check the Left Cell for a space or the exit
    if ((maze[currentCell.row][currentCell.column - 1] == SPACE) ||
        (maze[currentCell.row][currentCell.column - 1] == EXIT))
    {
      addCell(makeCell(currentCell.row, currentCell.column - 1));
    }

    // Check the UP Cell for a space or the exit
    if ((maze[currentCell.row - 1][currentCell.column] == SPACE) ||
        (maze[currentCell.row - 1][currentCell.column] == EXIT))
    {
      addCell(makeCell(currentCell.row - 1, currentCell.column));
    }

    // Check the Down Cell for a space or the exit
    if ((maze[currentCell.row + 1][currentCell.column] == SPACE) ||
        (maze[currentCell.row + 1][currentCell.column] == EXIT))
    {
      addCell(makeCell(currentCell.row + 1, currentCell.column));
    }

    // if there are no more possible cells to try then the mouse is trapped
    if (noMoreCells())
    {
      // Verifies that the stack of cells is indeed empty
      assert(NULL == top);

      mazeSolved = false;
    }
    else
    {
      // Verifies that the stack of cells is indeed not empty
      assert(NULL != top);

      // gets the next possible cell path for the mouse to try
      currentCell = nextCell();
    }
  }

  // check that the maze structure remained valid till the end
  checkState();

  return mazeSolved;
}

//------------------------------------------------------
// printMaze
//
// PURPOSE: Prints the maze
//------------------------------------------------------
void printMaze()
{
  // Checks that the maze to be printed is still valid
  checkState();

  for (int i = 0; i < mazeRows; i++)
  {
    for (int j = 0; j < mazeCols; j++)
    {
      printf("%c ", maze[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  // Checks that the maze remains intact after printing
  checkState();
}

//------------------------------------------------------
// checkState
//
// PURPOSE: Invariant checke for the maze. Checks that the dimensions and cells of the maze are valid,
// there is an exit position in the maze and the mouse is within the maze
//------------------------------------------------------
void checkState()
{
  // Verifying that the maze only contains Walls, Spaces, Visited cells, mouse or escape
  //  positions at any given time
  for (int i = 0; i < mazeRows; i++)
  {
    for (int j = 0; j < mazeCols; j++)
    {
      assert(maze[i][j] == WALL || maze[i][j] == SPACE || maze[i][j] == VISITED ||
             maze[i][j] == MOUSE || maze[i][j] == EXIT);
    }
  }

  // Verify that the mouse is still within the maze and there is still an escape cell in the maze
  // and the dimensions are still intact.
  assert(validCell(mouse));
  assert(validCell(escape));
  assert((mazeRows >= 0 && mazeRows <= MAX_DIMENSION) && (mazeCols >= 0 && mazeCols <= MAX_DIMENSION));
}
