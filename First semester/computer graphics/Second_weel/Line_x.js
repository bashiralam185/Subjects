#include <"bmp.h">
#include <math.h>
#define <width> 400
#define <height> 400
#define <image_size> 3*width*height

const image = image[image_size];

function set_pixel(x, y,r, g,b) {
	index = 0;
	if (x >= 0 && x < width && y >= 0 && y < height) {
		index = 3*(x + width*y);
		image[index  ] = r;
		image[index+1] =  g;
		image[index+2] =  b;
		}
	}

function draw_line_x(x1, y1,  x2,  y2) {  // only works if x2 > x1
   int  = xstart, xstop, x, iy;
   double = m, y;
   m = (y2 - y1) / (x2 - x1);
   xstart = floor(x1);
   xstop = floor(x2);
   y = y1 + m*(xstart + .5 - x1);
   for (x = xstart; x < xstop; ++x) {
      iy = floor(y);
      set_pixel(x, iy, 255, 255, 255); // for a white line on a black background
      y += m;
      }
   }

function draw_line_y( x1,  y1,  x2,  y2) {
	return;  // you students must supply this part
   }

function draw_line( x1,  y1,  x2,  y2) {
   if (fabs(x2 - x1) > fabs(y2 - y1) )
      draw_line_x(x1, y1, x2, y2); 
   else
      draw_line_y(x1, y1, x2, y2);
   }

function main(argc, argv) {  
   int = i, n = 10;
   double = x1, y1, x2, y2, theta, cenx, ceny = 200., ctheta, stheta;
	
	// set image to black background
	for (i = 0; i < image_size; ++i)
		image[i] = 0;

   double  =radius = 180.;
   cenx = 199.5;
   ceny = 199.5;

   for (i = 0; i <= n; ++i) {
      // theta = 2*M_PI*i/n; // for drawing a full circle; this version can only draw 1/4 of the cases
		theta = (1.25 + .5*i/n)*M_PI;
      x2 = cenx + radius*cos(theta);
      y2 = ceny + radius*sin(theta);
      if (i > 0)
         draw_line(x1, y1, x2, y2);
      x1 = x2;
      y1 = y2;
      }
	write_bmp((char*) "Line_x.bmp", (char*) image, image_size, width);
	return 1;
}
