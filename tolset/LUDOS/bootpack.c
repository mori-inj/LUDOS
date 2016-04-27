void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void line(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);



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

void LUDOSMain(void)
{
	char *vram;
	int xsize, ysize;

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
	boxfill8(vram, xsize, WHITE,		1,	ysize - 20,          xsize -  2, ysize - 2);
	boxfill8(vram, xsize, BLACK,		2,	ysize - 19,          xsize -  3, ysize - 3);

	boxfill8(vram, xsize, WHITE,		4,	ysize - 17,          40, ysize - 5);
	boxfill8(vram, xsize, BLACK,		5,	ysize - 16,          39, ysize - 6);

	

	for (;;) 
	{
		io_hlt();
	}
}

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:�� */
		0xff, 0x00, 0x00,	/*  1:���� ���� */
		0x00, 0xff, 0x00,	/*  2:���� �ʷ� */
		0xff, 0xff, 0x00,	/*  3:���� Ȳ�� */
		0x00, 0x00, 0xff,	/*  4:���� �Ķ� */
		0xff, 0x00, 0xff,	/*  5:���� ����� */
		0x00, 0xff, 0xff,	/*  6:���� ���� */
		0xff, 0xff, 0xff,	/*  7:��� */
		0xc6, 0xc6, 0xc6,	/*  8:���� ȸ�� */
		0x84, 0x00, 0x00,	/*  9:��ο� ���� */
		0x00, 0x84, 0x00,	/* 10:��ο� �ʷ� */
		0x84, 0x84, 0x00,	/* 11:��ο� Ȳ�� */
		0x00, 0x00, 0x84,	/* 12:��ο� �Ķ� */
		0x84, 0x00, 0x84,	/* 13:��ο� ����� */
		0x00, 0x84, 0x84,	/* 14:��ο� ���� */
		0x84, 0x84, 0x84	/* 15:��ο� ȸ�� */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char ����� ������ �ۿ� ����� �� ������ DB��ɿ� ��� */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* ���ͷ�Ʈ �㰡 �÷����� ���� ����Ѵ� */
	io_cli(); 			/* �㰡 �÷��׸� 0���� �Ͽ� ���ͷ�Ʈ ������ �Ѵ� */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* ���ͷ�Ʈ �㰡 �÷��׸� ������� �ǵ����� */
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
