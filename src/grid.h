using namespace std;
#include "common.h"
class Grid
{
    // Access specifier
public:
    cell **grid_cell;
    //cell **grid_cell2;
    Grid(int m, int n, int max_movs)
    {
        grid_rows = m-1;
        grid_cols = n-1;
        MAX_MOVS = max_movs;
        grid_cell=(cell**)malloc(m*sizeof(cell *));
        for (int idx = 0; idx < m; idx++)
        {
            grid_cell[idx]=(cell*)malloc(n*sizeof(cell));
        }
     
         //grid_cell[0][0].blocked = true;
        // grid_cell[1][0].blocked = true;
         //grid_cell[0][1].blocked = true;
            
    }
    Grid()
    {
        grid_rows = 2;
        grid_cols = 2;
        MAX_MOVS = 8;
        // grid_cell[0][2].blocked = true;

        grid_cell[0][0].blocked = true;
         grid_cell[1][0].blocked = true;
         grid_cell[0][1].blocked = true;
    }

    void find_path(coordination *grid, path *pth, cell_state *cstae, int credit);
    void find_largest_path(path *best_path, int *selected_start_position);
    void forward_right(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae);
    void forward_left(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae);
    void forward_up(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae);
    void forward_down(coordination *cut, path *pth, valid_movement *movs, cell_state *cstae);
    void update_profile(cell_state *cstate);
    void set_block(int co_x,int co_y);

    std::stack<path> path_pool;
    std::stack<cell_state> grid_state; // std::map<int,cell_state> grid_state; Should be changed to map;
    std::stack<std::pair<int, int>> cell_start_point;
    std::stack<int> res_credit;

    typedef struct cell_profile
    {
        path saved_path;
        // cell_state cst;
        position visited_positions;
        std::pair<int, int> cur_position;
        int res_credit;
    } cell_profile;
    int get_num_visited();
    int grid_rows, grid_cols;
      int MAX_MOVS;
private:
    
  
    uint nof_movment = 0;
    int backward_offset=1;
    // std::stack<int> path_pool;

    void init_movs(valid_movement *movs)
    {
        movs->right = false;
        movs->left = false;
        movs->down = false;
        movs->up = false;
    }
    void valid_next_step(coordination *cut, valid_movement *movs, cell_state *cstate);
    void bakward(coordination *cut, path *pth);
};
