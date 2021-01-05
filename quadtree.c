#include<stdio.h>
#include<stdlib.h>

typedef struct _quadTree * Position;


//Struct point represents point in the space, it has x and y coordinates
typedef struct _point{
  int x;
  int y;
}Point;


/*Struct quadtree represents space, and its subdivisions. It has array of points in space, start and end which define boundaries of the space, 
capacity, and first, second, etc. which are subdivisions. If tree has more points that capacity it creates 4 subdivisions.*/
typedef struct _quadTree{
  Point * points;
  Point start;
  Point end;
  int capacity;
  Position first;
  Position second;
  Position third;
  Position fourth;
}QuadTree;


int main(){
  return 0;
}