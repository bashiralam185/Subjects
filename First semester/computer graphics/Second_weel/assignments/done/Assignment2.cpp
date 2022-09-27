// importing the required moudules for the drawing
#include "bmp.h"
#include <cmath>
#include <iostream>
using namespace std;

// defining the width and height
#define width 400
#define height 400

// defining the size of the image
#define image_size 3*width*height
unsigned char image[image_size];
int g_correction = 1;


// This function will set the pixels values 
// I took this function from the previous examples / source code of assignemt 1 and modify a little bit
void set_pixel_alpha(int x, int y, double r, double g, double b, double a) {
   int index_value;
   float trns = 1 - a;
   float transp = (1 - a)/255.;
   if (x >= 0 && x < width && y >= 0 && y < height) {
      index_value = 3*(x + width*y);
      if (g_correction) {
      	image[index_value  ] = (unsigned char) (255*sqrt(a*r + transp*(float) image[index_value  ]));
      	image[index_value+1] = (unsigned char) (255*sqrt(a*g + transp*(float) image[index_value+1]));
      	image[index_value+2] = (unsigned char) (255*sqrt(a*b + transp*(float) image[index_value+2]));
         }
      else {
      	image[index_value  ] = (unsigned char) (255*a*r + trns*(float) image[index_value  ]);
      	image[index_value+1] = (unsigned char) (255*a*g + trns*(float) image[index_value+1]);
      	image[index_value+2] = (unsigned char) (255*a*b + trns*(float) image[index_value+2]);
         }
      }
   }



// This function will draw the triangle 
void triangle_drawing(double x1, double y1, double x2, double y2, double x3, double y3){
    
// This is to create opque and transparent objects. 
// if color ==1, create opque image
// if color ==0, create transparent image
    double color = 0;


    // defining the top and bottom values
    double y_top = max(y1,max(y2,y3));
    double y_bottom = min(y1,min(y2,y3));
    int i,j, n = 60;
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


        // Here we have given condition to check if the color is 1, we will create
        //  solid or opque image
        if(color==1){
            for(float x = x_left;x<floor(x_right);x++){
            set_pixel_alpha(floor(x), floor(y), 0, 0, 225, 1);
        }
        }
        // if the color is equal to 0, then we need to create transparant image 
        if(color==0){
            for(float x = x_left;x<floor(x_right);x++){
            set_pixel_alpha(floor(x), floor(y), 0, 0, 225, 0.5);
        }
        } 
    }
}

// the main function
 int main(int argc, char** argv) {  
    int i;
    for (i = 0; i < image_size; ++i)
		image[i] = 0;

// using the given coordinates of the triangles to draw 
    triangle_drawing(74.5, 175.5, 224.5, 325.5, 374.5, 175.5);
    triangle_drawing(74.5, 325.5, 74.5, 175.5, 224.5, 325.5);
    triangle_drawing(224.5, 325.5, 374.5, 175.5, 374.5, 325.5);
    triangle_drawing(74.5, 175.5, 150.0, 100.0, 374.5, 175.5);
    triangle_drawing(37.5, 175.5, 74.5, 325.5, 74.5, 175.5);
    triangle_drawing(37.5, 175.5, 25.0, 125.0, 74.5, 175.5);
	write_bmp((char*) "Required_triangle_trans.bmp", (char*) image, image_size, width);
	return 1;
}
