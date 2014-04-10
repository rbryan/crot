#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <gsl/gsl_matrix.h>
#include <Imlib2.h>


#define VWIDTH 4.0
#define VHEIGHT 3.0
#define VX -2.5
#define VY -1.5

typedef unsigned int uint;

struct matrix
{
	int width, height;
	int **vals;
};


struct image
{
	int width, height;


	struct matrix *red;
	struct matrix *green;
	struct matrix *blue;
};

typedef struct image image;


struct matrix *newMatrix(int width, int height)
{
	int i;
	struct matrix *mat = (struct matrix *)calloc(1, sizeof(struct matrix));


	mat->vals = (int **)calloc(width, sizeof(int *));
	mat->width = width;
	mat->height = height;


	for(i = 0; i < width; i++)
	{
		mat->vals[i] = (int*)calloc(height, sizeof(int));
	}
	return mat;
}


image *loadImage(const char *filename)
{
	Imlib_Image img;
	int i, j, width, height;


	struct image *result = (struct image*)calloc(1, sizeof(struct image));


	img = imlib_load_image(filename);
	imlib_context_set_image(img);


	width = imlib_image_get_width();
	height = imlib_image_get_height();


	result->width = width;
	result->height = height;


	result->red = newMatrix(width, height);
	result->green = newMatrix(width, height);
	result->blue = newMatrix(width, height);


	for(i = 0; i < width; i++)
	{
		for(j = 0; j < height; j++)
		{
			Imlib_Color col;
			imlib_image_query_pixel(i, j, &col);


			result->red->vals[i][j] = (int)col.red;
			result->green->vals[i][j] = (int)col.green;
			result->blue->vals[i][j] = (int)col.blue;
		}
	}


	return result;
}


void saveImage(struct image *img, const char *filename)
{
	Imlib_Image out;
	int i, j;


	out = imlib_create_image(img->width, img->height);
	imlib_context_set_image(out);


	for(i = 0; i < img->width; i++)
	{
		for(j = 0; j < img->height; j++)
		{
			int red = (int)img->red->vals[i][j];
			int green = (int)img->green->vals[i][j];
			int blue = (int)img->blue->vals[i][j];


			red = red <= 255 ? red : 255;
			green = green <= 255 ? green : 255;
			blue = blue <= 255 ? blue : 255;


			imlib_context_set_color(red, green, blue, 255);
			imlib_image_draw_line(i, j, i, j, 0);
		}
	}


	imlib_save_image(filename);
}

uint mand(uint w, uint h, uint x, uint y){
	uint i;
	double complex z;
	double complex c;

	z = 0 + 0 * I;
	c = VX + VWIDTH/w * x + (VY+VHEIGHT/h * y) * I;

	for(i=0; i<256; i++){
		z = z*z+c;
		if(creal(z*conj(z)) > 20) break;
	}
	return i;
}

void rotx(image *img, float t,int x ,int y){
	int r,g,b;
	int r1,g1,b1;
	
	r1 = img->red->vals[x][y];
	g1 = img->green->vals[x][y];
	b1 = img->blue->vals[x][y];

	r = r1;
	g = cos(t)*g1 - sin(t)*b1;
	b = sin(t)*g1 + cos(t)*b1;
	
	img->red->vals[x][y] = abs(r);
	img->green->vals[x][y] = abs(g);
	img->blue->vals[x][y] = abs(b);
}


void rotz(image *img, float t,int x ,int y){
	int r,g,b;
	int r1,g1,b1;
	
	r1 = img->red->vals[x][y];
	g1 = img->green->vals[x][y];
	b1 = img->blue->vals[x][y];

	r = r1*cos(t) + sin(t) *g1;
	g = cos(t)*g1 - sin(t)*r1;
	b = b1;
	
	img->red->vals[x][y] = abs(r);
	img->green->vals[x][y] = abs(g);
	img->blue->vals[x][y] = abs(b);
}

void roty(image *img, float t,int x ,int y){
	int r,g,b;
	int r1,g1,b1;
	
	r1 = img->red->vals[x][y];
	g1 = img->green->vals[x][y];
	b1 = img->blue->vals[x][y];

	r = r1*cos(t) - sin(t) *b1;
	g = g1;
	b = b1*sin(t) + cos(t) * r1;
	
	img->red->vals[x][y] = abs(r);
	img->green->vals[x][y] = abs(g);
	img->blue->vals[x][y] = abs(b);
}

void rot(image *img, int x,int y,float r,float g,float b)
{
	rotx(img,r,x,y);
	roty(img,g,x,y);
	rotz(img,b,x,y);
}

int main(int argc, char**argv){

	int i,j;
	image *img;

	if(argc < 6){
		fprintf(stderr,"Usage: <input> <output> <mfr> <mfg> <mfb>\n");
		exit(0);
	}

	img = loadImage(argv[1]);

	float r,g,b;
	r = atof(argv[3]);
	g = atof(argv[4]);
	b = atof(argv[5]);
	
	for(i=0; i< img->width; i++){
		for(j=0; j<img->height; j++){
			uint m;
			m = mand(img->width,img->height,i,j);
			rot(img,i,j,m*r,m*g,m*b);
		}
	}
	saveImage(img,argv[2]);
	
}


