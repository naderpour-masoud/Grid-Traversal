#include "stdio.h"
#include <bits/stdc++.h>
typedef struct cell // A Type for Storing cells state and spec
{
  bool blocked = false;
  bool visited = false;
  int co_x, co_y;
} cell;
enum direction
{
  RIGHT = 'R',
  LEFT = 'L',
  UP = 'U',
  DOWN = 'D',
  null = 'N'
};
typedef std::vector<direction> path;
typedef std::set<std::pair<int, int>> cell_state;
typedef std::set<std::pair<int, int>> position;

#define ROW_MAX 100
#define COL_MAX 100
typedef struct valid_movement
{
  bool right = false;
  bool left = false;
  bool up = false;
  bool down = false;
} valid_movement;
typedef struct coordination // A Type for Storing cells state and spec
{
  int co_x = 0;
  int co_y = 0;

} coordination;
