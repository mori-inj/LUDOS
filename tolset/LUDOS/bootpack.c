void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void boxline8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void line(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void pixel(unsigned char *vram, int xsize, unsigned char c, int x, int y);
double sqrt(double x);

typedef struct p2
{
	double x;
	double y;
} Point2;

typedef struct p3
{
	double x;
	double y;
	double z;
} Point3;

void cube(unsigned char *vram, int xsize, unsigned char c, double x, double y, double z, double size);
Point2 transform(double Px, double Py, double Pz);

#define WIDTH 320
#define HEIGHT 200


#define BLACK		COL8_000000
#define RED		COL8_FF0000
#define GREEN		COL8_00FF00
#define YELLOW		COL8_FFFF00
#define BLUE		COL8_0000FF
#define MAGENTA		COL8_FF00FF
#define CYAN		COL8_00FFFF
#define WHITE		COL8_FFFFFF
#define GRAY		COL8_C6C6C6
#define DRED		COL8_840000
#define DGREEN		COL8_008400
#define DYELLOW		COL8_848400
#define DBLUE		COL8_000084
#define DMAGENTA	COL8_840084
#define DCYAN		COL8_008484
#define DGRAY		COL8_848484


#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15


#define D 350
double ox=1,oy=0,oz=0;
double origin_x = -100, origin_y = 0, origin_z = 0;

void LUDOSMain(void)
{
	char *vram;
	int xsize, ysize;
	int temp;

	init_palette();
	vram = (char *) 0xa0000;
	xsize = 320;
	ysize = 200;

	/*
	boxfill8(vram, xsize, BLACK,		0,	0,          xsize -  1, ysize - 27); //background color

	boxfill8(vram, xsize, GRAY,		0,	ysize - 24, xsize -  1, ysize - 24); //gray row of taskbar
	boxfill8(vram, xsize, WHITE,		0,	ysize - 23, xsize -  1, ysize - 23); //white row of taskbar
	boxfill8(vram, xsize, GRAY,		0,	ysize - 22, xsize -  1, ysize -  1); //gray row of taskbar

	boxfill8(vram, xsize, WHITE,		3,	ysize - 20, 49,         ysize - 20); //white column of start button
	boxfill8(vram, xsize, WHITE,		2,	ysize - 20,  2,         ysize -  4); //white row of start button
	boxfill8(vram, xsize, DGRAY,		3,	ysize -  4, 49,         ysize -  4); //gray column of start button
	boxfill8(vram, xsize, DGRAY,		49,	ysize - 19, 49,         ysize -  5); //gray row of start button
	boxfill8(vram, xsize, BLACK,		2,	ysize -  3, 49,         ysize -  3); //black column of start button
	boxfill8(vram, xsize, BLACK,		50,	ysize - 20, 50,         ysize -  3); //black row of start button

	boxfill8(vram, xsize, DGRAY,		xsize - 37, ysize - 20, xsize -  4, ysize - 20); //gray column of tool box
	boxfill8(vram, xsize, DGRAY,		xsize - 37, ysize - 19, xsize - 37, ysize -  4); //gray row of tool box
	boxfill8(vram, xsize, WHITE,		xsize - 37, ysize -  3, xsize -  4, ysize -  3); //white column of tool box
	boxfill8(vram, xsize, WHITE,		xsize -  3, ysize - 20, xsize -  3, ysize -  3); //white row of tool box
	*/

	boxfill8(vram, xsize, BLACK,		0,	0,          xsize -  1, ysize - 1);
	boxline8(vram, xsize, WHITE,		0,	ysize - 20,          xsize -  1, ysize - 1);
	
	boxline8(vram, xsize, WHITE,		2,	ysize - 18,          40, ysize - 3);
	boxline8(vram, xsize, WHITE,		xsize-30,	ysize - 17,     xsize - 5, ysize - 4);
	
	//cube(vram, xsize, WHITE, 0, 0, 0, 20);
	
	for (;;) 
	{
		io_hlt();
	}
}

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:흑 */
		0xff, 0x00, 0x00,	/*  1:밝은 빨강 */
		0x00, 0xff, 0x00,	/*  2:밝은 초록 */
		0xff, 0xff, 0x00,	/*  3:밝은 황색 */
		0x00, 0x00, 0xff,	/*  4:밝은 파랑 */
		0xff, 0x00, 0xff,	/*  5:밝은 보라색 */
		0x00, 0xff, 0xff,	/*  6:밝은 물색 */
		0xff, 0xff, 0xff,	/*  7:흰색 */
		0xc6, 0xc6, 0xc6,	/*  8:밝은 회색 */
		0x84, 0x00, 0x00,	/*  9:어두운 빨강 */
		0x00, 0x84, 0x00,	/* 10:어두운 초록 */
		0x84, 0x84, 0x00,	/* 11:어두운 황색 */
		0x00, 0x00, 0x84,	/* 12:어두운 파랑 */
		0x84, 0x00, 0x84,	/* 13:어두운 보라색 */
		0x00, 0x84, 0x84,	/* 14:어두운 물색 */
		0x84, 0x84, 0x84	/* 15:어두운 회색 */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char 명령은 데이터 밖에 사용할 수 없지만 DB명령에 상당 */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* 인터럽트 허가 플래그의 값을 기록한다 */
	io_cli(); 			/* 허가 플래그를 0으로 하여 인터럽트 금지로 한다 */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* 인터럽트 허가 플래그를 원래대로 되돌린다 */
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y;
	for (y = y0; y <= y1; y++) 
	{
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}

void boxline8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x,y;
	for(x = x0; x <= x1; x++)
	{
		vram[y1 * xsize + x] = c;
		vram[y0 * xsize + x] = c;
	}
	for(y = y0 + 1; (y1 >= y0)? (y < y1) : (y > y1); y+=((y1 >= y0)? 1 : -1))
	{
		vram[y * xsize + x1] = c;
		vram[y * xsize + x0] = c;
	}
}

void pixel(unsigned char *vram, int xsize, unsigned char c, int x, int y)
{
	vram[y * xsize + x] = c;
}

void line(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y, d_x = x1 - x0, d_y = (y1 >= y0)? y1 - y0 : y0 - y1;
	vram[y0 * xsize + x0] = c;
	if(d_x >= d_y)
		for(x = x0 + 1; x < x1; x++)
		{
			y = (int)((double) (y1 - y0) / (x1 - x0) * (x - x0) + y0 + 0.5);
			vram[y * xsize + x] = c;
		}
	else
		for(y = y0 + 1; (y1 >= y0)? (y < y1) : (y > y1); y+=((y1 >= y0)? 1 : -1))
		{
			x =  (int)((double)(x1 - x0) / (y1 - y0) * (y - y0) + x0 + 0.5);
			vram[y * xsize + x] = c;
		}
	vram[y1 * xsize + x1] = c;
	return; 
}

double sqrt(double x)
{
	double ret = x;
	int i;
	for(i=0; i<20; i++)
		ret = (ret + (x/ret)) / 2;
	return ret;
}

Point2 transform(double Px, double Py, double Pz)
{
	Point2 ret;
	double A,n,m;
	Px -= origin_x;
	Py -= origin_y;
	Pz -= origin_z;

	A = ox * Px + oy * Py+ oz * Pz;
	n = D * (oz - Pz / A) / sqrt(ox * ox + oy * oy);
	m = D * (Px * oy - Py * ox) / (A * sqrt(ox * ox + oy * oy));
	
	ret.x = m+WIDTH/2;
	ret.y = n+HEIGHT/2;
	return ret;
}

void cube(unsigned char *vram, int xsize, unsigned char c, double x, double y, double z, double size)
{
	Point3 p;
	int i;
	Point3 points[8];

	p.x = x;
	p.y = y;
	p.z = z;

	int connect1[12]={0,0,1,2,4,4,6,5,0,1,2,3};
	int connect2[12]={1,2,3,3,5,6,7,7,4,5,6,7};

	double m,n,m1,n1,m2,n2;

	for(i=0; i<8; i++)
	{
		points[i].x = p.x+(i%2==0)? size/2 : -size/2;
		points[i].y = p.y+(i/2%2==0)? size/2 : -size/2;
		points[i].z = p.z+(i/4%2==0)? size/2 : -size/2;
	}

	for(i=0; i<8; i++)
	{
		m = transform(points[i].x,points[i].y,points[i].z).x;
		n = transform(points[i].x,points[i].y,points[i].z).y;
		
		pixel(vram, xsize, c, m, n);
	}
	for(i=0; i<12; i++)
	{
		m1 = transform(points[connect1[i]].x, points[connect1[i]].y, points[connect1[i]].z).x;
		n1 = transform(points[connect1[i]].x, points[connect1[i]].y, points[connect1[i]].z).y;

		m2 = transform(points[connect2[i]].x, points[connect2[i]].y, points[connect2[i]].z).x;
		n2 = transform(points[connect2[i]].x, points[connect2[i]].y, points[connect2[i]].z).y;

		line(vram, xsize, c, m1, n1, m2, n2);
	}
}
