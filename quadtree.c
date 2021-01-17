#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _quadTree * Position;

//Struct point represents point in the space, it has x and y coordinates
typedef struct _point{
  float x;
  float y;
}Point;

/*Struct quadtree represents space, and its subdivisions. It has array of points in space, start and end which define boundaries of the space, 
capacity, and first, second, etc. which are subdivisions. If tree has more points that capacity it creates 4 subdivisions.*/
typedef struct _quadTree{
  Point * points;
  Point start;
  Point end;
  int capacity;
  int counter;
  Position first;
  Position second;
  Position third;
  Position fourth;
  int divided;
}QuadTree;

Position createTree(int capacity, Point start, Point end);
int insert(Position point, float x, float y);
int printTree(Position point);
int divide(Position point);
int findPoint(Position point, float x, float y);

int main(){
  Point start, end;
  start.x = 0; start.y = 0; end.x = 100; end.y = 100;
  Position tree = createTree(5, start, end);
  
  srand(time(0));

  int i = 0;
  float a, b;

  for(i = 0; i < 30; i++){
    int upper = 100;
    int lower = 0;
    int tempX = (rand() % (upper-lower+1))+ lower;
    int tempY= (rand() % (upper-lower+1))+ lower;
    insert(tree, tempX, tempY);
  }

  printTree(tree);

  printf("Unesite trazenu tocku:\n");
  scanf(" %f %f", &a, &b);
  findPoint(tree, a, b);
  
  return 0;
}

//Creates tree node, initialize points list, sets all subdivision to null
Position createTree(int capacity, Point start, Point end){
  Position temp = (Position)malloc(sizeof(QuadTree));
  if(temp == NULL){
    return NULL;
  }

  temp->start = start;
  temp->end = end;
  temp->capacity = capacity;
  temp->counter = 0;
  temp->divided = 0;
  temp->points = (Point *)malloc(capacity * sizeof(Point));

  temp->first = NULL;
  temp->second = NULL;
  temp->third = NULL;
  temp->fourth = NULL;

  return temp;
}

//Inserts points into tree
int insert(Position point, float x, float y){
  if(x >= point->end.x || x < point->start.x || y >= point->end.y || y < point->start.y)
    return 1;
  
  if(point->counter < point->capacity && point->divided == 0){
    Point temp;
    temp.x = x; temp.y = y;
    point->points[point->counter] = temp;
    point->counter++;
    return 0;
  }

  if(!point->divided)
    divide(point);

  insert(point->first, x, y);
  insert(point->second, x, y);
  insert(point->third, x, y);
  insert(point->fourth, x, y);
  
  return 0;
}

//Creates subdivisions of a tree and inserts all points into its quadrant
int divide(Position tree){
  float width = tree->end.x - tree->start.x;
  float height = tree->end.y - tree->start.y;
  
  //Points that will help create subdivisions of a tree
  Point middleLeft, center, middleBottom, middleTop, middleRight;
  middleLeft.x = tree->start.x; middleLeft.y = height / 2;
  center.x = width / 2; center.y = height / 2;
  middleBottom.x = width /2; middleBottom.y = tree->start.y;
  middleTop.x = width / 2; middleTop.y = tree->end.y;
  middleRight.x = tree->end.x; middleRight.y = height / 2;

  tree->first = createTree(tree->capacity, center, tree->end);
  tree->second = createTree(tree->capacity, middleLeft, middleTop);
  tree->third = createTree(tree->capacity, tree->start, center);
  tree->fourth = createTree(tree->capacity, middleBottom, middleRight);

  int i = 0;

  for(i = 0; i < tree->capacity; i++){
    insert(tree->first, tree->points[i].x, tree->points[i].y);
    insert(tree->second, tree->points[i].x, tree->points[i].y);
    insert(tree->third, tree->points[i].x, tree->points[i].y);
    insert(tree->fourth, tree->points[i].x, tree->points[i].y);
  }

  free(tree->points);

  tree->divided = 1;

  return 0;
}

//Prints tree
int printTree(Position point){
  int i = 0;
  if(point == NULL){
    return 1;
  }

  if(point->divided == 0){
    printf("\n");
    for(i = 0; i < point->counter; i++){
      printf("%.0f %.0f\n", point->points[i].x, point->points[i].y);
    }
  }

  else{
    printTree(point->first);
    printTree(point->second);
    printTree(point->third);
    printTree(point->fourth);
  }

  return 0;
}

int findPoint(Position point, float x, float y){
  if(point == NULL){
    return 1;
  }

  int width = point->end.x - point->start.x;
  int height = point->end.y - point->start.y;
  int i = 0;
  
  if(point->divided == 1){
    if(x < width / 2){
      if(y < width / 2)
        findPoint(point->third, x, y);
      else
        findPoint(point->second, x, y); 
    }
    else{
      if(y < width / 2)
        findPoint(point->fourth, x, y);
      else
        findPoint(point->first, x, y);
    }
  }

  else{
    printf("\nNajblize tocke su:\n");
    for(i = 0; i < point->counter; i++){
      if(point->points[i].x == x && point->points[i].y == y)
        continue;
      else
        printf("%.0f %.0f\n", point->points[i].x, point->points[i].y);
    }
  }

  return 0;
}

