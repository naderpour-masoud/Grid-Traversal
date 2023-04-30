#include "grid.h"

void Grid::valid_next_step(coordination *cut, valid_movement *movs, cell_state *cstate)
{

  // cell *neighbor_cell=&grid_cell[cut->co_x][cut->co_y];
  init_movs(movs);
  // validate the right movement
  //  neighbor_cell->co_x=cut->co_x+1;
  //  neighbor_cell->co_y=cut->co_y;
  //  printf(" Right =%d Left =%d Up= %d Down =%d \n", movs->right, movs->left, movs->up, movs->down);
  if (cut->co_x <= grid_rows - 1)
  {
    if (!grid_cell[cut->co_x + 1][cut->co_y].blocked && !grid_cell[cut->co_x + 1][cut->co_y].visited)
    {
      // if(cstate->end()== cstate->find(cut->co_y*(grid_cols+1)+ cut->co_x+1))

      movs->right = true;
    }
  }

  //  printf(" Right =%d Left =%d Up= %d Down =%d \n", movs->right, movs->left, movs->up, movs->down);
  // validate the left movement
  // neighbor_cell->co_x=cut->co_x-1;
  // neighbor_cell->co_y=cut->co_y;
  // printf("Here 100 %d\n", cut->co_x - 1);
  if (cut->co_x >= 1)
  {
    if (!grid_cell[cut->co_x - 1][cut->co_y].blocked && !grid_cell[cut->co_x - 1][cut->co_y].visited)
    {
      movs->left = true;
    }
  }

  //  printf(" Right =%d Left =%d Up= %d Down =%d \n", movs->right, movs->left, movs->up, movs->down);
  // validate the up movement
  if (cut->co_y >= 1)
  {
    if (!grid_cell[cut->co_x][cut->co_y - 1].blocked && !grid_cell[cut->co_x][cut->co_y - 1].visited)
    {
      movs->up = true;
    }
  }
  //  printf(" Right =%d Left =%d Up= %d Down =%d \n", movs->right, movs->left, movs->up, movs->down);
  // validate the down movement
  // neighbor_cell->co_x=cut->co_x;
  // neighbor_cell->co_y=cut->co_y+1;
  if (cut->co_y <= grid_cols - 1)
  {
    if (!grid_cell[cut->co_x][cut->co_y + 1].blocked && !grid_cell[cut->co_x][cut->co_y + 1].visited)
    {
      movs->down = true;
    }
    //  printf(" Right =%d Left =%d Up= %d Down =%d \n", movs->right, movs->left, movs->up, movs->down);
  }
}
void Grid::find_path(coordination *grid, path *pth, cell_state *cstate, int credit)
{
  coordination *cut = grid; //(coordination*)malloc(sizeof(coordination));
  // cut->co_x = grid->co_x;
  // cut->co_y = grid->co_y;
  // grid_cell[0][0].visited=true;
  valid_movement movs; //=(valid_movement*)malloc(sizeof(valid_movement));
  update_profile(cstate);
  // init_movs(&movs);

  //  printf("Nof = %d",nof_movment);
  nof_movment = 0;
  // printf(" The CREDIT is =%d ",credit);
  backward_offset = 1;
  MAX_MOVS = credit;
  while (nof_movment < MAX_MOVS)
  {

    //  printf(" Right =%d Left =%d Up= %d Down =%d \n", movs.right, movs.left, movs.up, movs.down);
    valid_next_step(cut, &movs, cstate);

    //  printf("Th X CORDINATE IS =%d \n",cut.co_x);
    //  std::vector<direction>::iterator it =pth->end();
    //  printf("The Path Value is %d ", *it);
    if (movs.right)
    {
      nof_movment++;
      //   printf("Here 1 \n");
      backward_offset = 1;
      forward_right(grid, pth, &movs, cstate);
      // cut->co_x = cut->co_x + 1;
      // printf("Here 2 \n");
    }
    if (movs.down)
    {
      backward_offset = 1;
      nof_movment++;
      forward_down(grid, pth, &movs, cstate);
      // cut->co_y = cut->co_y + 1;
    }
    if (movs.left)
    {
      backward_offset = 1;
      nof_movment++;
      forward_left(grid, pth, &movs, cstate);
      // cut->co_x = cut->co_x - 1;
    }

    if (movs.up)
    {
      backward_offset = 1;
      nof_movment++;
      // printf("The X Before Forward Up =%d",grid->co_x);
      forward_up(grid, pth, &movs, cstate);
      // cut->co_y = cut->co_y - 1;
    }

    if (!movs.up && !movs.down && !movs.right && !movs.left)
    {
      // printf("Backword\n");
      nof_movment++;
      bakward(cut, pth);
    }
  }
}
void Grid::bakward(coordination *cut, path *pth)
{
  std::vector<direction>::iterator it = pth->end() - backward_offset;
  // printf("The Path Value is %d ", *it);
  if (*it == direction::RIGHT)
  {
    // printf("Backword Direction is LEFT\n");
    pth->push_back(direction::LEFT);
    cut->co_x = cut->co_x - 1;
  }
  if (*it == direction::LEFT)
  {
    // printf("Backword Direction is RIGHT\n");
    pth->push_back(direction::RIGHT);
    //  printf("RIGHT BACKWARD ::: The x= %d, y=%d,\n",cut->co_x,cut->co_y);
    cut->co_x = cut->co_x + 1;
    //  printf("RIGHT BACKWARD ::: The x= %d, y=%d,\n",cut->co_x,cut->co_y);
  }
  if (*it == direction::UP)
  {
    // printf("Backword Direction is Down\n");
    pth->push_back(direction::DOWN);
    cut->co_y = cut->co_y + 1;
  }

  if (*it == direction::DOWN)
  {
    // printf("Backword Direction is UP\n");
    pth->push_back(direction::UP);
    cut->co_y = cut->co_y - 1;
  }
  backward_offset = backward_offset + 2;
}
void Grid::forward_right(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae)
{
  // printf("Forward Right \n");
  path pth_aux;
  {
    pth->push_back(direction::RIGHT);

    // printf("Pushed Backed RIGHT \n");
    grid_cell[cut->co_x][cut->co_y].visited = true;
    //  printf("The x= %d, y=%d, visited=%d",cut->co_x,cut->co_y,grid_cell[cut->co_x][cut->co_y].visited );
    // cstae->insert(cut->co_y*(grid_cols+1)+cut->co_x);
    cstae->insert(std::make_pair(cut->co_x, cut->co_y));

    cut->co_x = cut->co_x + 1;
    grid_cell[cut->co_x][cut->co_y].visited = true;
    //  printf("The x= %d, y=%d, visited=%d",cut->co_x,cut->co_y,grid_cell[cut->co_x][cut->co_y].visited );
    // cstae->insert(std::pair<int,bool>(cut->co_y*grid_cols+cut->co_x,true));

    // std::copy(pth->begin(),pth->end()-1,pth_aux.begin());
    std::vector<direction>::iterator it;
    std::vector<direction>::iterator it_m = pth->begin();
    int count = 0;
    for (it = pth->begin(); it < pth->end() - 1; it++)
    {
      pth_aux.push_back(*(it_m + count));
      count++;
      // printf("The Number of Count is =%d\n", count);
    }

    // printf("Copied Aux Path \n");
    if (movs->left)
    {
      cstae->insert(std::make_pair(cut->co_x - 2, cut->co_y));
      // cstae->insert((cut->co_y)*(grid_cols+1)+cut->co_x-2);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x - 2, cut->co_y));
      cstae->erase(std::pair<int, int>(cut->co_x - 2, cut->co_y));
      // printf("Stacked Left\n");
      pth_aux.push_back(direction::LEFT);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->left = false;
    }
    if (movs->up)
    {
      cstae->insert(std::make_pair(cut->co_x - 1, cut->co_y - 1));
      // cstae->insert((cut->co_y-1)*(grid_cols+1)+cut->co_x-1);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x - 1, cut->co_y - 1));
      cstae->erase(std::pair<int, int>(cut->co_x - 1, cut->co_y - 1));
      ;
      // printf("Stacked UP\n");
      pth_aux.push_back(direction::UP);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->up = false;
    }
    if (movs->down)
    {
      cstae->insert(std::make_pair(cut->co_x - 1, cut->co_y + 1));
      // cstae->insert((cut->co_y+1)*(grid_cols+1)+cut->co_x-1);
      // printf("Stacked DOWN\n");
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x - 1, cut->co_y + 1));
      std::set<std::pair<int, int>>::iterator it3;

      // = std::pair<int,int> (*it3);

      // for (it3 = cstae->begin(); it3 != cstae->end(); it3++)
      // {
      //   std::pair<int, int> foo = std::pair<int, int>(*it3);
      //   printf(" The First is =(%d ,%d)", foo.first, foo.second);
      // }

      // printf("The size is =%d\n", cstae->size());
      cstae->erase(std::pair<int, int>(cut->co_x - 1, cut->co_y + 1));
      // printf("The size is =%d\n", cstae->size());

      // for (it3 = cstae->begin(); it3 != cstae->end(); it3++)
      // {
      //   std::pair<int, int> foo = std::pair<int, int>(*it3);
      //   printf(" The First is =(%d ,%d)", foo.first, foo.second);
      // }

      pth_aux.push_back(direction::DOWN);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->down = false;
    }
  }
  // printf("End of Forward Right \n \n");
}

void Grid::forward_left(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae)
{
  path pth_aux;
  {
    // printf("Forward LEFT \n");
    pth->push_back(direction::LEFT);
    // printf("Pushed Backed LEFT \n");

    int count = 0;

    grid_cell[cut->co_x][cut->co_y].visited = true;
    // cstae->insert(cut->co_y*(grid_cols+1)+cut->co_x);
    cstae->insert(std::make_pair(cut->co_x, cut->co_y));
    cut->co_x = cut->co_x - 1;
    grid_cell[cut->co_x][cut->co_y].visited = true;
    std::vector<direction>::iterator it;
    std::vector<direction>::iterator it_m = pth->begin();
    for (it = pth->begin(); it < pth->end() - 1; it++)
    {
      pth_aux.push_back(*(it_m + count));
      count++;
      // printf("The Number of Count is =%d\n", count);
    }

    // printf("Copied Aux Path \n");
    if (movs->right)
    {
      cstae->insert(std::make_pair(cut->co_x + 2, cut->co_y));
      //  cstae->insert((cut->co_y)*(grid_cols+1)+cut->co_x+2);
      // printf("Stacked Right\n");
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x + 2, cut->co_y));
      cstae->erase(std::pair<int, int>(cut->co_x + 2, cut->co_y));
      pth_aux.push_back(direction::RIGHT);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->right = false;
    }
    if (movs->up)
    {
      // printf("Stacked UP\n");
      cstae->insert(std::make_pair(cut->co_x + 1, cut->co_y - 1));
      // cstae->insert((cut->co_y-1)*(grid_cols+1)+cut->co_x+1);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x + 1, cut->co_y - 1));
      cstae->erase(std::pair<int, int>(cut->co_x + 1, cut->co_y - 1));
      pth_aux.push_back(direction::UP);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->up = false;
    }
    if (movs->down)
    {
      // printf("Stacked Down\n");
      cstae->insert(std::make_pair(cut->co_x + 1, cut->co_y + 1));
      // cstae->insert((cut->co_y+1)*(grid_cols+1)+cut->co_x+1);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x + 1, cut->co_y + 1));
      cstae->erase(std::pair<int, int>(cut->co_x + 1, cut->co_y + 1));
      pth_aux.push_back(direction::DOWN);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->down = false;
    }
  }
  // printf("End of Forward Left \n \n");
}

void Grid::forward_up(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae)
{
  path pth_aux;
  {
    // printf("Forward UP \n");
    pth->push_back(direction::UP);
    // printf("Pushed Backed UP \n");

    grid_cell[cut->co_x][cut->co_y].visited = true;
    //  printf("The x= %d, y=%d, visited=%d",cut->co_x,cut->co_y,grid_cell[cut->co_x][cut->co_y].visited );
    cstae->insert(std::make_pair(cut->co_x, cut->co_y));
    // cstae->insert(cut->co_y*(grid_cols+1)+cut->co_x);
    cut->co_y = cut->co_y - 1;
    grid_cell[cut->co_x][cut->co_y].visited = true;
    //  printf("The x= %d, y=%d, visited=%d",cut->co_x,cut->co_y,grid_cell[cut->co_x][cut->co_y].visited );
    int count = 0;
    std::vector<direction>::iterator it;
    std::vector<direction>::iterator it_m = pth->begin();
    for (it = pth->begin(); it < pth->end() - 1; it++)
    {
      pth_aux.push_back(*(it_m + count));
      count++;
      // printf("The Number of Count is =%d\n", count);
    }

    // printf("Copied Aux Path \n");
    if (movs->right)
    {
      cstae->insert(std::make_pair(cut->co_x + 1, cut->co_y + 1));
      //  cstae->insert((cut->co_y+1)*(grid_cols+1)+cut->co_x+1);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x + 1, cut->co_y + 1));
      cstae->erase(std::pair<int, int>(cut->co_x + 1, cut->co_y + 1));

      // printf("Stacked Right\n");
      pth_aux.push_back(direction::RIGHT);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->right = false;
    }
    if (movs->left)
    {
      cstae->insert(std::make_pair(cut->co_x - 1, cut->co_y + 1));
      //  cstae->insert((cut->co_y+1)*(grid_cols+1)+cut->co_x-1);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x - 1, cut->co_y + 1));
      cstae->erase(std::pair<int, int>(cut->co_x - 1, cut->co_y + 1));
      // printf("Stacked LEFT\n");
      pth_aux.push_back(direction::LEFT);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->left = false;
    }
    if (movs->down)
    {
      cstae->insert(std::make_pair(cut->co_x, cut->co_y + 2));
      //  cstae->insert((cut->co_y+2)*(grid_cols+1)+cut->co_x);
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x, cut->co_y + 2));
      cstae->erase(std::pair<int, int>(cut->co_x, cut->co_y + 2));
      // printf("Stacked Down\n");
      pth_aux.push_back(direction::DOWN);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->down = false;
    }
  }
  // printf("End of Forward UP \n \n");
}

void Grid::forward_down(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae)
{
  path pth_aux;
  {
    // printf("Forward DOWN \n");
    pth->push_back(direction::DOWN);
    // printf("Pushed Backed DOWN \n");
    grid_cell[cut->co_x][cut->co_y].visited = true;
    cstae->insert(std::make_pair(cut->co_x, cut->co_y));
    // cstae->insert(cut->co_y*(grid_cols+1)+cut->co_x);
    cut->co_y = cut->co_y + 1;
    grid_cell[cut->co_x][cut->co_y].visited = true;
    std::vector<direction>::iterator it;
    std::vector<direction>::iterator it_m = pth->begin();
    int count = 0;
    for (it = pth->begin(); it < pth->end() - 1; it++)
    {
      pth_aux.push_back(*(it_m + count));
      count++;
      // printf("The Number of Count is =%d\n", count);
    }

    if (movs->right)
    {
      cstae->insert(std::make_pair(cut->co_x + 1, cut->co_y - 1));
      cell_start_point.push(std::make_pair(cut->co_x + 1, cut->co_y - 1));
      //  cstae->insert((cut->co_y-1)*(grid_cols+1)+cut->co_x+1);
      // printf("Stacked Right\n");
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cstae->erase(std::pair<int, int>(cut->co_x + 1, cut->co_y - 1));
      pth_aux.push_back(direction::RIGHT);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->right = false;
    }
    if (movs->left)
    {
      std::set<std::pair<int, int>>::iterator it3;
      //   for (it3 = cstae->begin(); it3 != cstae->end(); it3++)
      // {
      //   std::pair<int, int> foo = std::pair<int, int>(*it3);
      //   printf(" The First is =(%d ,%d)", foo.first, foo.second);
      // }

      cstae->insert(std::make_pair(cut->co_x - 1, cut->co_y - 1));
      //  cstae->insert((cut->co_y-1)*(grid_cols+1)+cut->co_x-1);

      // printf("Stacked Left\n");

      // printf("The size is =%d\n", cstae->size());
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      //   for (it3 = cstae->begin(); it3 != cstae->end(); it3++)
      // {
      //   std::pair<int, int> foo = std::pair<int, int>(*it3);
      //   printf(" The First is =(%d ,%d)", foo.first, foo.second);
      // }
      cell_start_point.push(std::make_pair(cut->co_x - 1, cut->co_y - 1));
      // printf("The size is=%d\n", cstae->size());
      cstae->erase(std::pair<int, int>(cut->co_x - 1, cut->co_y - 1));

      //  for (it3 = cstae->begin(); it3 != cstae->end(); it3++)
      //     {
      //       std::pair<int, int> foo = std::pair<int, int>(*it3);
      //       printf(" The First is =(%d ,%d)", foo.first, foo.second);
      //     }

      pth_aux.push_back(direction::LEFT);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->left = false;
    }
    if (movs->up)
    {
      cstae->insert(std::make_pair(cut->co_x, cut->co_y - 2));
      //  cstae->insert((cut->co_y-2)*(grid_cols+1)+cut->co_x);
      // printf("Stacked UP\n");
      grid_state.push(*cstae);
      res_credit.push(MAX_MOVS - nof_movment - 1);
      cell_start_point.push(std::make_pair(cut->co_x, cut->co_y - 2));
      cstae->erase(std::pair<int, int>(cut->co_x, cut->co_y - 2));
      pth_aux.push_back(direction::UP);
      path_pool.push(pth_aux);
      pth_aux.pop_back();
      movs->up = false;
    }
  }
  // printf("End of Forward Down \n \n");
}
void Grid::update_profile(cell_state *cstate)
{
  for (size_t idx = 0; idx <= grid_rows; idx++)
  {
    for (size_t jdx = 0; jdx <= grid_cols; jdx++)
    {
      grid_cell[idx][jdx].visited = false;
    }
  }

  std::set<std::pair<int, int>>::iterator it;
  for (it = cstate->begin(); it != cstate->end(); it++)
  {
    std::pair<int, int> foo = std::pair<int, int>(*it);
    grid_cell[foo.first][foo.second].visited = true;
    // printf(" The First is=%d and Second is %d \n", foo.first, foo.second);
    // printf(" ::::::::::::::::;UPDATE PROFILING ::::::::::::::The First is=%d and Second is %d \n", foo.first, foo.second);
    // printf("The Current position is x= % d , y=%d, cur_cred=%d\n", cur_pos.first, cur_pos.second,cur_credit);
  }
}
int Grid::get_num_visited()
{
  int num_visited = 0;
  for (size_t idx = 0; idx <= grid_rows; idx++)
  {
    for (size_t jdx = 0; jdx <= grid_cols; jdx++)
    {
      if (grid_cell[idx][jdx].visited)
        num_visited++;
    }
  }
  return num_visited;
}
void Grid::set_block(int co_x, int co_y)
{
  grid_cell[co_x][co_y].blocked = true;
}

void Grid::find_largest_path(path *largest_path, int *selected_start_position)
{
  int cur_credit = this->MAX_MOVS;
  int bigest_score;
  coordination co;

  std::vector<int> scores;
  std::map<int, path> found_path;
  std::vector<int> best_start_point;
  for (int kdx = 0; kdx <= grid_rows; kdx++)
  {
    for (int ndx = 0; ndx <= grid_cols; ndx++)
    {

      if (cur_credit > 0)
      {
        path p1;
        cell_state cs;
        cur_credit = MAX_MOVS;
        std::pair<int, int> cur_position;

        if (!grid_cell[kdx][ndx].blocked)

        {
          co.co_x = kdx;
          co.co_y = ndx;
          find_path(&co, &p1, &cs, cur_credit);
          std::vector<direction>::iterator it;
          int cur_score;
          cur_score = get_num_visited();

          found_path.insert(std::pair<int, path>(cur_score, p1));
          while (!path_pool.empty())
          {
            cur_credit = res_credit.top() + 1;
            p1 = path_pool.top();
            cs = grid_state.top();
            grid_state.pop();
            path_pool.pop();
            res_credit.pop();
            cur_position = cell_start_point.top();
            co.co_x = cur_position.first;
            co.co_y = cur_position.second;
            // printf("The New Start Position is = %d ,%d",co.co_x,co.co_y);
            cell_start_point.pop();
            if (cur_credit > 0)
              find_path(&co, &p1, &cs, cur_credit);
            cur_score = get_num_visited();
            // printf("The Number of Visited cells is =%d", cur_score);
            scores.push_back(cur_score);
            best_start_point.push_back((grid_cols + 1) * ndx + kdx);
            found_path.insert(std::pair<int, path>(cur_score, p1));
          }
        }
        else
          continue;
      }
    }
  }

  // bigest_score = *max_element(scores.begin(), scores.end());

  std::vector<int>::iterator it_temp;
  bigest_score = 0;
  // int max_el_pos=0;
  int count = 0;
  for (it_temp = scores.begin(); it_temp < scores.end(); it_temp++)
  {
    count++;
    if (*it_temp > bigest_score)
    {
      bigest_score = *it_temp;
      *selected_start_position = count;
    }
  }

  *largest_path = found_path.at(bigest_score);
  *selected_start_position = best_start_point.at(*selected_start_position);
}