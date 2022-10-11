#include "bmp.h"
#include <math.h>
#include <string.h>
#define width 400
#define height 400
#define image_size 3*width*height

unsigned char image[image_size];
float color[4] = {0., 1., 1., 1.}; // cyan
int gamma_correction = 0, transparent = 0.5;
int triangles[7][3] = {
		{0, 1, 2},   // ABC
		{0, 3, 1},   // ADB
		{1, 4, 2},   // BEC
		{0, 2, 5},   // ACF
		{0, 3, 6},   // ADG
		{7, 8, 9},   // HIJ
		{10, 11, 12} // KLM
		};
double vertices[14][3] = {
		{60.5, 175.5, 1.},  // A 0
		{224.5, 325.5, 2.}, // B 1
		{374.5, 190.5, 5.}, // C 2
		{74.5, 285.5, 4.},  // D 3
		{350.5, 300.5, 6.}, // E 3
		{150., 100., 3.},   // F 5
		{ 25., 125., 8.},   // G 6
		{450., 120., -2.},  // H 7
		{445., 350., -2.},  // I 8
		{100., 260., 9.},   // J 9
		{20., 90., 10.},    // K 10
		{189., 95., 10.},   // L 11
		{102., 350., 1.},   // M 12
		{0., 0., 0.}        // Q 13, the other vertex on the horizontal cutting line
		};

double colors[14][4] = {
	{1., 0., 0., 1.}, // A 0
	{1., .7, 0., 1.}, // B 1
	{.7, 1., 0., 1.}, // C 2
	{.4, .4, .4, 1.}, // D 3
	{0., 1., 0., 1.}, // E 4
	{0., .7, 1., 1.}, // F 5
	{0., .2, 1., 1.}, // G 6
	{0., 1., 1., 1.}, // H 7
	{0., .7, .7, 1.}, // I 8
	{0., 1., 1., 1.}, // J 9
	{1., 0., 1., .5}, // K 10
	{1., 0., 1., .5}, // L 11
	{1., 0., 1., .5}, // M 12
	{0., 0., 0., 1.}, // Q 13
	};

double ZBuffer[width][height];

void set_pixel_alpha_z(int x, int y, double r, double g, double b, double a, double z) {
   int index;
   float transparency = 1 - a;
   float transp = (1 - a)/255.;
   if (x >= 0 && x < width && y >= 0 && y < height && z >= ZBuffer[x][y]) {
		ZBuffer[x][y] = z;
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
	*b = v1 - *m * y1;
	}

void draw_horizontal_edge_triangle(int i1, int i2, int i3, int kind,
		int side, double m, double bb, int triangle) {
	double m_x_left, b_x_left, m_x_right, b_x_right, x, y, top_y, bottom_y, xleft, xright;
	double zleft, zright, rleft, rright, gleft, gright, bleft, bright, aleft, aright;
	double m_z, m_r, m_g, m_b, m_a;
	int i_top, i_left, db_horizontal = 0, db_line_eq = 0, db_blue = 1;
	double x1, x2, x3, y1, y2, y3, z1, z2, z3, r1, r2, r3, g1, g2, g3, b1, b2, b3, a1, a2, a3;
	double b_z_left, b_z_right, b_r_left, b_r_right, b_g_left, b_g_right, b_b_left, b_b_right,
		b_a_left, b_a_right, m_z_left, m_z_right, m_r_left, m_r_right, m_g_left, m_g_right,
		m_b_left, m_b_right, m_a_left, m_a_right, z, r, g, b, a;

   x1 = vertices[i1][0];
   x2 = vertices[i2][0];
   x3 = vertices[i3][0];
	y1 = vertices[i1][1];
	y2 = vertices[i2][1];
	y3 = vertices[i3][1];
	z1 = vertices[i1][2];
	z2 = vertices[i2][2];
	z3 = vertices[i3][2];
	r = colors[triangle][0];
	g = colors[triangle][1];
	b = colors[triangle][2];
	a = colors[triangle][3];

	if (kind) { // top vertex i1 belongs to both non-horizontal edges
		if (vertices[i2][0] < vertices[i3][0]) { // vertex i2 is on the left
			get_line_equation(y1, y2, x1, x2, &m_x_left, &b_x_left);
			get_line_equation(y1, y3, x1, x3, &m_x_right, &b_x_right);
			get_line_equation(y1, y2, z1, z2, &m_z_left, &b_z_left);
			get_line_equation(y1, y3, z1, z3, &m_z_right, &b_z_right);
			}
		else { // vertex i3 is on the left
			get_line_equation(y1, y3, x1, x3, &m_x_left, &b_x_left);
			get_line_equation(y1, y2, x1, x2, &m_x_right, &b_x_right);
			get_line_equation(y1, y3, z1, z3, &m_z_left, &b_z_left);
			get_line_equation(y1, y2, z1, z2, &m_z_right, &b_z_right);
			}
		}
	else { // bottom vertex i3 is on both both non-horizontal edges
		if (vertices[i1][0] < vertices[i2][0]) { // vertex i1 is on the left
			get_line_equation(y1, y3, x1, x3, &m_x_left, &b_x_left);
			get_line_equation(y2, y3, x2, x3, &m_x_right, &b_x_right);
			get_line_equation(y1, y3, z1, z3, &m_z_left, &b_z_left);
			get_line_equation(y2, y3, z2, z3, &m_z_right, &b_z_right);
			}
		else { // vertex i2 is on the left
			get_line_equation(y2, y3, x2, x3, &m_x_left, &b_x_left);
			get_line_equation(y1, y3, x1, x3, &m_x_right, &b_x_right);
			get_line_equation(y2, y3, z2, z3, &m_z_left, &b_z_left);
			get_line_equation(y1, y3, z1, z3, &m_z_right, &b_z_right);
			}
		}
	if (side == 1) {
		m_x_left = m;
		b_x_left = bb;
		}
	else if (side == 2) {
		m_x_right = m;
		b_x_right = bb;
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
		xleft = m_x_left*y + b_x_left;
		xright = m_x_right*y + b_x_right;
		i_left = ceil(xleft - .5);
		zleft = m_z_left*y + b_z_left;
		zright = m_z_right*y + b_z_right;
		m_z = (zright - zleft) / (xright - xleft);
		if (i_left < 0)
			i_left = 0;
		if (xright > width)
			xright = width;
		z = zleft + m_z * (i_left + .5 - xleft);
		for (x = i_left + .5; x < xright; x += 1) {
			set_pixel_alpha_z((int)floor(x), (int)floor(y), r, g, b, a, z);
			z += m_z;
		}
	}
}

void draw_triangle(int i) {
	int j, k, top_index, middle_index, bottom_index, dbpr_draw = 0, index[3], side;
	double vertex[3][3], color[3][4], m_x, b_x, xmiddle, ymiddle, y0, y1, y2;
	double m_z, b_z, m_r, b_r, m_g, b_g, m_b, b_b, m_a, b_a;
	char alphabet[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'Q'};
	for (j = 0; j < 3; ++j) {
		index[j] = triangles[i][j];
		for (k = 0; k < 3; ++k) 
			vertex[j][k] = vertices[index[j]][k];
		for (k = 0; k < 4; ++k) 
			color[j][k] = colors[index[j]][k];
		}
	y0 = vertex[0][1];
	y1 = vertex[1][1];
	y2 = vertex[2][1];

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
	if (vertex[top_index][1] == vertex[bottom_index][1]) // zero height triangle
		return;
	if (vertex[middle_index][1] == vertex[top_index][1]) {
		draw_horizontal_edge_triangle(index[top_index], index[middle_index],
			index[bottom_index], 0, 0, 0, 0, i);
		return;
		}
	else if (vertex[middle_index][1] == vertex[bottom_index][1]) {
		draw_horizontal_edge_triangle(index[top_index], index[middle_index], index[bottom_index],
			1, 0, 0, 0, i);
		return;
		}
	
	// We need to cut the triangle in two with a horizontal line.
	// First find the line equation for the line between the top and bottom vertices.
	get_line_equation(vertex[top_index][1], vertex[bottom_index][1],
	                  vertex[top_index][0], vertex[bottom_index][0], &m_x, &b_x);
	get_line_equation(vertex[top_index][1], vertex[bottom_index][1],
	                  vertex[top_index][2], vertex[bottom_index][2], &m_z, &b_z);
	xmiddle = vertices[index[middle_index]][0];
	ymiddle = vertices[index[middle_index]][1];
	if (xmiddle > m_x*ymiddle + b_x)
		side = 1;
	else
		side = 2;
	vertices[13][0] = m_x*ymiddle + b_x;
	vertices[13][1] = ymiddle;
	vertices[13][2] = m_z*ymiddle + b_z;
	draw_horizontal_edge_triangle(index[top_index], index[middle_index], 13, 1, side, m_x, b_x, i);
	draw_horizontal_edge_triangle(index[middle_index], 13, index[bottom_index], 0, side, m_x, b_x, i);
	}

int main(int argc, char** argv) {  
   int i, x, y, start = 0, stop = 6, n = 4, dbpr_main = 0;
   double x1, y1, x2, y2;
	char name[100];
	strcpy (name, "ZbufferTriangles");
	
	strcat(name, ".bmp");

	// set image to black background
	for (i = 0; i < image_size; ++i)
		image[i] = 0;
	
	// set ZBuffer to very far away
	for (x = 0; x < width; ++x)
		for (y = 0; y < height; ++y)
			ZBuffer[x][y] = -1000000;

   for (i = start; i <= stop; ++i)
		draw_triangle(i);

	write_bmp(name, (char*) image, image_size, width);
	return 1;
}
