import Image
import sys
import math


def main():
	if len(sys.argv) < 2:
		print "Please name a file to rotate."
		sys.exit(0);

	img = Image.open(sys.argv[1]);
	pix = img.load();
	w,h = img.size;

	r = float(sys.argv[3]);
	g = float(sys.argv[4]);
	b = float(sys.argv[5]);


	for i in xrange(w):
		for j in xrange(h):
			r1 = dist(0,0,i,0)/1000.0 * r;
			g1 = dist(0,0,i,0)/1000.0 * g;
			b1 = dist(0,0,i,0)/1000.0 * b;
			p = pix[i,j];
			pix[i,j] = rot(p,r1,g1,b1);
	img.save(sys.argv[2]);

def dist(a,b,c,d):
	return math.sqrt((a-c)**2+(b-d)**2);

def rotx(p,x):
	r1,g1,b1=p;
	r = r1;
	g = math.cos(x)*g1 - math.sin(x)*b1;
	b = math.sin(x)*g1 + math.cos(x) *b1;
	r = abs(r);
	g = abs(g);
	b = abs(b);
	p = r,g,b;
	return p;

def rotz(p,z):
	r1,g1,b1=p;
	r = r1*math.cos(z) + math.sin(z) *g1;
	g = -math.sin(z)*r1 + math.cos(z) *g1;
	b = b1;
	r = abs(r);
	g = abs(g);
	b = abs(b);
	p = r,g,b;
	return p;

def roty(p,y):
	r1,g1,b1=p;
	r = r1*math.cos(y) + math.sin(y) * b1;
	g = g1;
	b = -math.sin(y)*r1 + math.cos(y) *b1;
	r = abs(r);
	g = abs(g);
	b = abs(b);
	p = r,g,b;
	return p;

def rot(p,x,y,z):
	p = rotx(p,x);
	p = roty(p,y);
	p = rotz(p,z);
	r,g,b = p;
	r = int(r);
	g = int(g);
	b = int(b);
	p = r,g,b;
	return p;

main();	
