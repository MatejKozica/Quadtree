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
}QuadTree;

Position createTree(int capacity, Point start, Point end);
int insert(Position tree, int x, int y);
int push(NodePosition node, int x, int y);
int printList(NodePosition node);
int listSize(NodePosition node);

int main(){
/*   Point start, end;
  start.x = 0; start.y = 0; end.x = 100; end.y = 100;
  Position tree = createTree(5, start, end);
  insert(tree, 1, 1);
  insert(tree, 2, 2);
  insert(tree, 3, 3);
  printList(tree->points->next); */

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
  temp->points = (NodePosition)malloc(sizeof(Node));
  temp->points->next = NULL;

  temp->first = NULL;
  temp->second = NULL;
  temp->third = NULL;
  temp->fourth = NULL;

  return temp;
}

int insert(Position tree, int x, int y){
  if(listSize(tree->points) < tree->capacity){
    push(tree->points, x, y);
  }
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

