#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _quadTree * Position;
typedef struct _node * NodePosition;

//Struct point represents point in the space, it has x and y coordinates
typedef struct _point{
  float x;
  float y;
}Point;

typedef struct _node{
  Point point;
  NodePosition next;
}Node;

/*Struct quadtree represents space, and its subdivisions. It has array of points in space, start and end which define boundaries of the space, 
capacity, and first, second, etc. which are subdivisions. If tree has more points that capacity it creates 4 subdivisions.*/
typedef struct _quadTree{
  NodePosition points;
  Point start;
  Point end;
  int capacity;
  Position first;
  Position second;
  Position third;
  Position fourth;
  int divided;
}QuadTree;

int push(NodePosition node, float x, float y);
int printList(NodePosition node);
int listSize(NodePosition node);
int freeList(NodePosition node);
Position createTree(int capacity, Point start, Point end);
int insert(Position point, float x, float y);
int printTree(Position point);
int divide(Position point);

int main(){
  Point start, end;
  start.x = 0; start.y = 0; end.x = 10; end.y = 10;
  Position tree = createTree(5, start, end);
  

  printTree(tree);

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
  temp->divided = 0;
  temp->points = (NodePosition)malloc(sizeof(Node));
  temp->points->next = NULL;

  temp->first = NULL;
  temp->second = NULL;
  temp->third = NULL;
  temp->fourth = NULL;

  return temp;
}

int insert(Position point, float x, float y){
  if(x >= point->end.x || x < point->start.x || y >= point->end.y || y < point->start.y)
    return 1;
  
  if(listSize(point->points) < point->capacity && point->divided == 0){
    push(point->points, x, y);
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
  middleTop.x = width / 2; middleBottom.y = tree->end.y;
  middleRight.x = tree->end.x; middleRight.y = height / 2;

  tree->first = createTree(tree->capacity, center, tree->end);
  tree->second = createTree(tree->capacity, middleLeft, middleTop);
  tree->third = createTree(tree->capacity, tree->start, center);
  tree->fourth = createTree(tree->capacity, middleBottom, middleRight);

  NodePosition temp = tree->points->next;

  while(temp != NULL){
    float tempX = temp->point.x;
    float tempY = temp->point.y;
    
    insert(tree->first, tempX, tempY);
    insert(tree->second, tempX, tempY);
    insert(tree->third, tempX, tempY);
    insert(tree->fourth, tempX, tempY);

    temp = temp->next;
  }

  free(temp);
  freeList(tree->points);

  tree->divided = 1;

  return 0;
}

//Push a point into the list
int push(NodePosition node, float x, float y){
  NodePosition temp = (NodePosition)malloc(sizeof(Node));
  if(temp == NULL){
    return 1;
  }

  temp->point.x = x;
  temp->point.y = y;

  while(node->next != NULL){
    node = node->next;
  }

  temp->next = node->next;
  node->next = temp;

  return 0;
}

//Print list of points
int printList(NodePosition node){
  if(node == NULL){
    return 1;
  }
  while(node != NULL){
    printf("%.0f %.0f\n", node->point.x, node->point.y);
    node = node->next;
  }
  return 0;
}

//Returns list's number of elements
int listSize(NodePosition node){
  int size = 0;
  while(node->next != NULL){
    size++;
    node = node->next;
  }
  return size;
}

//Deletes list
int freeList(NodePosition node){
  NodePosition temp = NULL;
  while(node != NULL){
    temp = node;
    node = node->next;
    free(temp);
  }
  return 0;
}


//Prints tree
int printTree(Position point){
  if(point == NULL){
    return 1;
  }

  if(point->divided == 0){
    printf("\n");
    printList(point->points->next);
  }

  else{
    printTree(point->first);
    printTree(point->second);
    printTree(point->third);
    printTree(point->fourth);
  }

  return 0;
}