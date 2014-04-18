import Image
import math
a=0;
b=0;
img = Image.new("RGB",(2440,1080),(0,0,0))
pix = img.load();
w,h = img.size;

tlx = -2.5
tly = -1.5
vw = 4.0
vh = 3.0;

for x in range(w):
	for y in range(h):
		a=0;
		b=0;
		c = tlx+vw/w*x
		d = tly+vh/h*y
		for i in range(127):

			t = a
			a=a**2-b**2+c
			b=2*t*b+d
			if(a**2+b**2>10):
				break;

		pix[x,y]=0,i*2,i**2;


img.save("output.png");

