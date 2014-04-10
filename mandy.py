import Image
import math
a=0;
b=0;
img = Image.new("RGB",(1280,800),(0,0,0))
pix = img.load();

for x in range(1280):
	for y in range(800):
		a=0;
		b=0;
		c = -2.5+1.0/320*x
		d = -2+1.0/200*y
		for i in range(127):

			t = a
			a=a**2-b**2+c
			b=2*t*b+d
			if(a**2+b**2>10):
				break;

		pix[x,y]=0,i*2,i**2;


img.save("output.png");

