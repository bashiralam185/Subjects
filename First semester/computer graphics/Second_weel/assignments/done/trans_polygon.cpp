#include "bmp.h"
// #include <math.h>
#include <cmath>
#include <iostream>
using namespace std;

#define width 400
#define height 400
#define image_size 3*width*height

unsigned char image[image_size];

int gamma_correction = 1;

void set_pixel_alpha(int x, int y, double r, double g, double b, double a) {
   int index;
   float transparency = 1 - a;
   float transp = (1 - a)/255.;
   if (x >= 0 && x < width && y >= 0 && y < height) {
      index = 3*(x + width*y);
      if (gamma_correction) {
      	image[index  ] = (unsigned char) (255*sqrt(a*r + transp*(float) image[index  ]));
      	image[index+1] = (unsigned char) (255*sqrt(a*g + transp*(float) image[index+1]));
      	image[index+2] = (unsigned char) (255*sqrt(a*b + transp*(float) image[index+2]));
         }
      else {
      	image[index  ] = (unsigned char) (255*a*r + transparency*(float) image[index  ]);
      	image[index+1] = (unsigned char) (255*a*g + transparency*(float) image[index+1]);
      	image[index+2] = (unsigned char) (255*a*b + transparency*(float) image[index+2]);
         }
      }
   }





void draw_traingle(double x1, double y1, double x2, double y2, double x3, double y3){
    double y_top = max(y1,max(y2,y3));
    double y_bottom = min(y1,min(y2,y3));
    int i,j, n = 40;
    double m_left, m_right, b_left, b_right, x_left, x_right;



    m_left = (y2 - y1) / (x2 - x1);
    
    m_right = (y3-y2) / (x3-x2);
    

    b_left = y2-x2*m_left;
    b_right = y2-x2*m_right;
    for(int y = floor(y_top);y>floor(y_bottom);y--){
        if(x2==x1){
            x_left=x2;
        }else{
            x_left = (y - b_left)/m_left;
        }

        if(x3==x2){
            x_right=x3;
        }else{
            x_right = (y-b_right)/m_right;
        }
        
        
        for(float x = x_left;x<floor(x_right);x++){
            set_pixel_alpha(floor(x), floor(y), 0, 0, 225, 0.5);
        }
    }
}




 int main(int argc, char** argv) {  
   
//    double x1 = 74.5, y1 = 175.5, x2 = 224.5, y2 = 325.5, x3 = 374.5, y3 = 175.5; ABC
//    double x1 = 74.5, y1 = 175.5, x2 = 74.5, y2 = 325.5, x3 = 224.5, y3 = 325.5; //ADB
    
    int i;
	
	// set image to black background
    for (i = 0; i < image_size; ++i)
		image[i] = 0;

    draw_traingle(74.5, 175.5, 224.5, 325.5, 374.5, 175.5);
    draw_traingle(74.5, 325.5, 74.5, 175.5, 224.5, 325.5);
    draw_traingle(224.5, 325.5, 374.5, 175.5, 374.5, 325.5);
    draw_traingle(74.5, 175.5, 150.0, 100.0, 374.5, 175.5);
    draw_traingle(37.5, 175.5, 74.5, 325.5, 74.5, 175.5);
    draw_traingle(37.5, 175.5, 25.0, 125.0, 74.5, 175.5);


	
   

	write_bmp((char*) "triangle_transparent.bmp", (char*) image, image_size, width);
	return 1;
}
