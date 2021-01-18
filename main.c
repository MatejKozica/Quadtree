#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "quadtree.h"

int main(){
  Point start, end;
  start.x = 0; start.y = 0; end.x = 50; end.y = 50;
  Position tree = createTree(5, start, end);
  
  srand(time(0));

  int i = 0;
  float a, b;

  for(i = 0; i < 20; i++){
    int upper = 50;
    int lower = 0;
    int tempX = (rand() % (upper-lower+1)) + lower;
    int tempY= (rand() % (upper-lower+1)) + lower;
    insert(tree, tempX, tempY, 1);
  }

  printTree(tree);

  printf("Enter wanted point:\n");
  scanf(" %f %f", &a, &b);
  
  Position wanted = findNearestPoints(tree, a, b);
  
  printf("Nearest points:\n");
  for(i = 0; i < wanted->counter; i++){
    if(wanted->points[i].x == a && wanted->points[i].y == b)
      continue;
    else
      printf("%.0f %.0f\n", wanted->points[i].x, wanted->points[i].y);
  }

  checkCollisions(wanted, a, b);

  return 0;
}