#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "quadtree.h"

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
int insert(Position node, float x, float y, float radius){
  if(x >= node->end.x || x < node->start.x || y >= node->end.y || y < node->start.y)
    return 1;
  
  if(node->counter < node->capacity && node->divided == 0){
    Point temp;
    temp.x = x; temp.y = y; temp.radius = radius;
    node->points[node->counter] = temp;
    node->counter++;
    return 0;
  }

  if(!node->divided)
    divide(node);

  insert(node->first, x, y, radius);
  insert(node->second, x, y, radius);
  insert(node->third, x, y, radius);
  insert(node->fourth, x, y, radius);
  
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
    insert(tree->first, tree->points[i].x, tree->points[i].y, tree->points[i].radius);
    insert(tree->second, tree->points[i].x, tree->points[i].y, tree->points[i].radius);
    insert(tree->third, tree->points[i].x, tree->points[i].y, tree->points[i].radius);
    insert(tree->fourth, tree->points[i].x, tree->points[i].y, tree->points[i].radius);
  }

  free(tree->points);

  tree->divided = 1;

  return 0;
}

//Prints tree
int printTree(Position node){
  int i = 0;
  if(node == NULL){
    return 1;
  }

  if(node->divided == 0){
    printf("\n");
    for(i = 0; i < node->counter; i++){
      printf("%.0f %.0f\n", node->points[i].x, node->points[i].y);
    }
  }

  else{
    printTree(node->first);
    printTree(node->second);
    printTree(node->third);
    printTree(node->fourth);
  }

  return 0;
}

//Find nearest points and prints them out
Position findNearestPoints(Position node, float x, float y){
  if(node == NULL){
    return NULL;
  }

  int width = node->end.x - node->start.x;
  int height = node->end.y - node->start.y;
  int i = 0;
  
  if(node->divided == 1){
    if(x < width / 2){
      if(y < width / 2)
        return findNearestPoints(node->third, x, y);
      else
        return findNearestPoints(node->second, x, y); 
    }
    else{
      if(y < width / 2)
        return findNearestPoints(node->fourth, x, y);
      else
        return findNearestPoints(node->first, x, y);
    }
  }

  else{
    for(i = 0; i < node->counter; i++){
      if(node->points[i].x == x && node->points[i].y == y)
        return node;
    }
  }

  return NULL;
}

//Calculates distance between 2 points
float distanceBetweenPoints(Point a, Point b){
  return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

//Check for collision of 2 objects
int checkCollisions(Position node, float x, float y){
  if(node == NULL)
    return 1;

  Point temp; temp.x = x; temp.y = y;
  int i = 0;

  for(i = 0; i < node->counter; i++){
    if(distanceBetweenPoints(temp, node->points[i]) <= (temp.radius + node->points[i].radius) && distanceBetweenPoints(temp, node->points[i]) != 0)
      printf("%.0f %0.f is in collision with %.0f %0.f\n", temp.x, temp.y, node->points[i].x, node->points[i].y);
  }

  return 0;
}