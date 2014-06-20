#include "Camera.h"

using namespace std;

int main(){
  Camera c;
  bitmap_image image(c.getFrame());
  image.save_image("temp.bmp");
}
