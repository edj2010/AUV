#include "Eyes.h"

Eyes::Eyes(){
  //Camera c;
  //this->c = c;
}

Eyes::Eyes(Camera c){
  this->c = c;
}
void Eyes::saveFrame(){
  bitmap_image frame = c.getFrame();
  frame.save_image("eyes.bmp");
}
int Eyes::diff(int x, int y){
  if(x>y){
    return x-y;
  }
  return y-x;
}

double Eyes::findCentroids(int row, bitmap_image line, const int lineColour[3], const int colourError, const int COLUMNS){
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

double Eyes::getErrorLine(int r, int g, int b, int pres, int error){
  bitmap_image line(c.getFrame());
  //bitmap_image line("line.bmp");
  const int ROWS = 60;
  const int COLUMNS = 80;
  const int PRECISION = pres;//number of line skips
  const int LINECOLOUR[3] = {r,g,b};
  const int COLOURERROR = error;
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
  return avg/count;
}

double Eyes::getErrorCenter(int r, int g, int b, int pres, int error){return 0;}//to be implemented
