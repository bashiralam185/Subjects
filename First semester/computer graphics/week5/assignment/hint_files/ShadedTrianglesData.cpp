#include "bmp.h"
#include <math.h>
#include <string.h>
#define width 400
#define height 400
#define image_size 3*width*height

unsigned char image[image_size];
float color[4] = {0., 1., 1., 1.}; // cyan
int gamma_correction = 0, transparent = 1;
int triangles[8][3] = {
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

void set_pixel_alpha(int x, int y, double r, double g, double b, double a, double z) {
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