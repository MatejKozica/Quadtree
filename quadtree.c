#include<stdio.h>
#include<stdlib.h>

typedef struct _quadTree * Position;
typedef struct _node * NodePosition;

//Struct point represents point in the space, it has x and y coordinates
typedef struct _point{
  int x;
  int y;
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

int push(NodePosition node, int x, int y);
int printList(NodePosition node);
int listSize(NodePosition node);
int freeList(NodePosition node);
Position createTree(int capacity, Point start, Point end);
int insert(Position point, int x, int y);
int printTree(Position point);
int divide(Position point);

int main(){
  Point start, end;
  start.x = 0; start.y = 0; end.x = 10; end.y = 10;
  Position tree = createTree(5, start, end);
  insert(tree, 6, 6);
  insert(tree, 7, 7);
  insert(tree, 2, 6);
  insert(tree, 1, 1);
  insert(tree, 6, 2);
  insert(tree, 2, 2);
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

int insert(Position point, int x, int y){
  if(listSize(point->points) < point->capacity && point->divided == 0){
    push(point->points, x, y);
  }
  
  else{
    int width = point->end.x - point->start.x;
    int height = point->end.y - point->start.y;
    divide(point);

    if(x <= width / 2){
      if(y <= height / 2)
        insert(point->third, x, y);
      else
        insert(point->second, x, y);
    }
    else{
      if(y <= height / 2)
        insert(point->fourth, x, y);
      else
        insert(point->first, x, y);
    }
  }
  
}

//Creates subdivisions of a tree and inserts all points into its quadrant
int divide(Position tree){
  int width = tree->end.x - tree->start.x;
  int height = tree->end.y - tree->start.y;
  
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
    int tempX = temp->point.x;
    int tempY = temp->point.y;
    if(tempX <= width / 2){
      if(tempY <= height / 2)
        insert(tree->third, tempX, tempY);
      else
        insert(tree->second, tempX, tempY);
    }
    else{
      if(tempY <= height / 2)
        insert(tree->fourth, tempX, tempY);
      else
        insert(tree->first, tempX, tempY);
    }
    temp = temp->next;
  }

  free(temp);
  freeList(tree->points);

  tree->divided = 1;

  return 0;
}

//Push a point into the list
int push(NodePosition node, int x, int y){
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
  while(node != NULL){
    printf("%d %d\n", node->point.x, node->point.y);
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

int freeList(NodePosition node){
  NodePosition temp = NULL;
  while(node != NULL){
    temp = node;
    node = node->next;
    free(temp);
  }
  return 0;
}

int printTree(Position point){
  if(point == NULL){
    return 1;
  }

  printf("\n");
  printList(point->points->next);

  printTree(point->first);
  printTree(point->second);
  printTree(point->third);
  printTree(point->fourth);

  return 0;
}