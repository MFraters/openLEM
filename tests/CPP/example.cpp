#define SHAREDSP
#include "openlem.cpp"
#include <stdio.h>

int main(int argc, char *argv[]) {


 if (argc != 3) {
      printf("Two arguments expected.\n");
      return 1;
   }

  Grid<> g(2261,1390);
  g.read("/home/m/programming/openLEM/openLEM/data/lapalma.flt", "H4");//argv[1],argv[2]);

for ( int i = 0; i < g.m; ++i )
    for ( int j = 0; j < g.n; ++j )  g[i][j].b = g[i][j].h <= 0;

	g.fillLakes();
double dt = 1e-3;
  for ( int i = 0; i < 5; ++i )
  {
    int nc = g.computeFlowDirection();
    printf("Changes in flow direction: %i\n",nc);  
    double ch = g.erode(dt);
    printf("Maximum elevation change: %e\n",ch);
  }

  return 0;
}
