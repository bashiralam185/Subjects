#include "bmp.h"
#include <math.h>
#include <string.h>
#define width 400
#define height 400
#define image_size 3*width*height

unsigned char image[image_size];
float color[4] = {0., 1., 1., 1.}; // cyan
int gamma_correction = 0, transparent = 1;
int triangles[5][3] = {
		{0, 1, 2},  // ABC
		{0, 3, 1},  // ADB
		{1, 4, 2},  // BEC
		{0, 2, 5},  // ACF
		{0, 3, 6}   // ADG
		};
double vertices[8][2] = {
      {60.5, 175.5},  // A 0
      {224.5, 325.5}, // B 1
      {374.5, 190.5}, // C 2
      {74.5, 285.5},  // D 3
      {350.5, 300.5}, // E 3
      {150., 100.},   // F 5
      { 25., 125.},   // G 6
      {0., 0.}        // Q 7, the other vertex on the horizontal cutting line
      };

void set_pixel(int x, int y, double r, double g, double b) {
   int index;
   if (x >= 0 && x < width && y >= 0 && y < height) {
      index = 3*(x + width*y);
      if (gamma_correction) {
         image[index  ] = (unsigned char) 255.*sqrt(r);
         image[index+1] = (unsigned char) 255.*sqrt(g);
         image[index+2] = (unsigned char) 255.*sqrt(b);
         }
      else {
         image[index  ] = (unsigned char) 255.*r;
         image[index+1] = (unsigned char) 255.*g;
         image[index+2] = (unsigned char) 255.*b;
         }
      }
   }

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

void get_line_equation(double y1, double y2, double v1, double v2, double *m, double *b) {
   *m = (v2 - v1)/(y2 - y1);
   *b = v1 - *m*y1;
   }

void draw_horizontal_edge_triangle(int i1, int i2, int i3, int kind) {
	double m_left, b_left, m_right, b_right, x, y, top_y, bottom_y, xleft, xright;
	double x1, x2, x3, y1, y2, y3;
	int i_top, i_left, db_horizontal = 0;

   x1 = vertices[i1][0];
   x2 = vertices[i2][0];
   x3 = vertices[i3][0];
   y1 = vertices[i1][1];
   y2 = vertices[i2][1];
   y3 = vertices[i3][1];

   if (kind) { // top vertex i1 belongs to both non-horizontal edges
      if (vertices[i2][0] < vertices[i3][0]) { // vertex i2 is on the left
         get_line_equation(y1, y2, x1, x2, &m_left, &b_left);
         get_line_equation(y1, y3, x1, x3, &m_right, &b_right);
         }
      else { // vertex i3 is on the left
         get_line_equation(y1, y3, x1, x3, &m_left, &b_left);
         get_line_equation(y1, y2, x1, x2, &m_right, &b_right);
         }
      }
   else { // bottom vertex i3 is on both both non-horizontal edges
      if (vertices[i1][0] < vertices[i2][0]) { // vertex i1 is on the left
         get_line_equation(y1, y3, x1, x3, &m_left, &b_left);
         get_line_equation(y2, y3, x2, x3, &m_right, &b_right);
         }
     else { // vertex i2 is on the left
         get_line_equation(y2, y3, x2, x3, &m_left, &b_left);
         get_line_equation(y1, y3, x1, x3, &m_right, &b_right);
         }
	  }
	// now do scan conversion loops in slide 43 of lecture 3
	top_y = vertices[i1][1];
	bottom_y = vertices[i3][1];
	i_top = floor(top_y - .5);
	if (i_top > height - 1)
		i_top = height - 1;
	if (bottom_y < 0)
		bottom_y = 0;
	for (y = i_top + .5; y > bottom_y; y -= 1) {
		xleft = m_left*y + b_left;
		xright = m_right*y + b_right;
		i_left = ceil(xleft - .5);
		if (i_left < 0)
			i_left = 0;
		if (xright > width)
			xright = width;
		for (x = i_left + .5; x < xright; x += 1) {
			set_pixel_alpha((int)floor(x), (int)floor(y), color[0], color[1], color[2], color[3]);
		}
	}
}

void draw_triangle(int i) {
	int j, k, top_index, middle_index, bottom_index, dbpr_draw = 0, index[3];
	double vertex[3][2], m, b, ymiddle, y0, y1, y2;
	char alphabet[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'Q'};
	for (j = 0; j < 3; ++j) {
		index[j] = triangles[i][j];
		for (k = 0; k < 2; ++k) 
			vertex[j][k] = vertices[index[j]][k];
		if (dbpr_draw)
			printf("i %d j %d index %d %c vertex %f %f\n", i, j, triangles[i][j],
			   alphabet[triangles[i][j]], vertices[triangles[i][j]][0], vertices[triangles[i][j]][1]);
		}
	y0 = vertex[0][1];
	y1 = vertex[1][1];
	y2 = vertex[2][1];
	if (dbpr_draw)
		printf("y0 %f y1 %g y2 %f\n", y0, y1, y2);

	// find top and bottom y values, and the vertex indices
	if (y0 > y1) {
		if (y0 > y2) {  // y0 is highest
			if (y1 > y2) { // y1 is second highest
				top_index = 0;
				middle_index = 1;
				bottom_index = 2;
				}
			else { // y2 is second highest
				top_index = 0;
				middle_index = 2;
				bottom_index = 1;
				}
			}
		else if (y2 > y0) {  // y2 is highest and y0 is second highest
			top_index = 2;
			middle_index = 0;
			bottom_index = 1;
			}
		}
	else {
		if (y1 > y2) { // y1 is highest
			if (y0 > y2) { // y0 is second_higest
				top_index = 1;
				middle_index = 0;
				bottom_index = 2;
				}
			else { // y2 is second highest
				top_index = 1;
				middle_index = 2;
				bottom_index = 0;
				}
			}
		else { // y2 is highest and y1 is second highest
			top_index = 2;
			middle_index = 1;
			bottom_index = 0;
			}
		}
	if (dbpr_draw)
		printf("indices %d %d %d ytop %f ymiddle %g ybottom %f\n", 
			index[top_index], index[middle_index], index[bottom_index],
			vertex[top_index][1], vertex[middle_index][1], vertex[bottom_index][1]); 
	if (vertex[top_index][1] == vertex[bottom_index][1]) // zero height triangle
		return;
	if (vertex[middle_index][1] == vertex[top_index][1]) {
		draw_horizontal_edge_triangle(index[top_index], index[middle_index], index[bottom_index], 0);
		return;
		}
	else if (vertex[middle_index][1] == vertex[bottom_index][1]) {
		draw_horizontal_edge_triangle(index[top_index], index[middle_index], index[bottom_index], 1);
		return;
		}
	
	// We need to cut the triangle in two with a horizontal line.
	// First find the line equation for the line between the top and bottom vertices.
   get_line_equation(vertex[top_index][1], vertex[bottom_index][1],
                     vertex[top_index][0], vertex[bottom_index][0], &m, &b);
	ymiddle = vertices[index[middle_index]][1];
	vertices[7][0] = m*ymiddle + b;
	vertices[7][1] = ymiddle;
	if (dbpr_draw)
		printf("q is %f %f m %f b %f\n", vertices[7][0], vertices[7][1], m, b);
	draw_horizontal_edge_triangle(index[top_index], index[middle_index], 7, 1);
	draw_horizontal_edge_triangle(index[middle_index], 7, index[bottom_index], 0);
	}

int main(int argc, char** argv) {  
   int i, start = 0, n = 4, dbpr_main = 0;
   double x1, y1, x2, y2;
	char name[100];
	strcpy (name, "Triangles");
	
	if (argc > 1)
		gamma_correction = atoi(argv[1]);
	if (argc > 2)
		transparent = atoi(argv[2]);
	if (argc > 3) {
		n = atoi(argv[3]);
		strcat(name, argv[3]);
		}
	if (argc > 4) {
		start = n;
		n = atoi(argv[4]);
		strcat(name, argv[4]);
		}
	strcat(name, ".bmp");
	for (i = 0; i < argc; ++i)
		printf("%s ", argv[i]);
	if (dbpr_main)
		printf("name %s\n", name);
	if (transparent)
		color[3] = .5;

	// set image to black background
	for (i = 0; i < image_size; ++i)
		image[i] = 0;

   for (i = start; i <= n; ++i)
		draw_triangle(i);

	write_bmp(name, (char*) image, image_size, width);
	return 1;
}
