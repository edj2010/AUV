#include "bitmap_image.hpp"
#include "Camera.h"
#include <iostream>
#include <cmath>
using namespace std;

int diff(int x, int y){
  if(x>y){
    return x-y;
  }
  return y-x;
}

double findCentroids(int row, bitmap_image line, const int lineColour[3], const int colourError, const int COLUMNS){
  int div = 0;
  int total = 0;
  for(int i = 0; i < COLUMNS; i++){
    unsigned char red, green, blue;
    line.get_pixel(i,row,red,green,blue);
    if(diff(red, lineColour[0]) < colourError and diff(green, lineColour[1]) < colourError and diff(blue, lineColour[2]) < colourError){
      int weight = (colourError-diff(red,lineColour[0]))+(colourError-diff(green,lineColour[1]))+(colourError-diff(blue,lineColour[2]));
      div += weight;
      total += weight*i;
    }
  }
  return ((double)total)/div;
}

int main(){
  // Camera c;
  // bitmap_image line(c.getFrame());
  // line.save_image("temp.bmp");
  bitmap_image line("temp.bmp");
  const int ROWS = 60;
  const int COLUMNS = 80;
  const int PRECISION = 10;//number of line skips
  const int LINECOLOUR[3] = {0,0,0};
  const int COLOURERROR = 100;
  double centroids[ROWS/PRECISION];
  for(int r = 0; r < ROWS; r+=PRECISION){
    centroids[r/PRECISION] = findCentroids(r, line, LINECOLOUR, COLOURERROR, COLUMNS);
  }
  double avg=0;
  int count=0;
  for(int i = 1; i < ROWS/PRECISION; i++){
    if(!isnan(centroids[i]) and !isnan(centroids[i-1])){
      avg += centroids[i-1]-centroids[i];
      count++;
    }
  }
  cout << avg/count/PRECISION << endl;
}
