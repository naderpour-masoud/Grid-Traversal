#include "stdio.h"
#include "grid.h"
int main()
{
  Grid g(3, 3, 8);// First :Number Of Column, Second: Number of Rows [0,1,2]
                  ///////////////////////////////////////////////////[*,4,5]
                  ///////////////////////////////////////////////////[6,7,8]                                                    
  g.set_block(1, 0);//// ////////////////////////////////////////////The Third Cell is Blocked.
  coordination co;
  path final_path;
  int start_position;
  g.find_largest_path(&final_path, &start_position);
  printf("The largest  direction for this grid is athe starting cell:%d, The order of movements are: ", start_position);
  std::vector<direction>::iterator it;
  for (it = final_path.begin(); it < final_path.end(); it++)
  {
    printf("%c,", *it);
  }
  printf("\n");
  return 0;
}