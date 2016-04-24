void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

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
	char *p; /* p라고 하는 변수는 BYTE [...]용 번지 */

	init_palette(); /* 팔레트를 설정 */

	p = (char *) 0xa0000; /* 번지를 대입 */

	int ys = 130;

	boxfill8(p, 320, WHITE,  	0,  0, 45-1, ys-1);
	boxfill8(p, 320, YELLOW,  	45,  0, 90-1, ys-1);
	boxfill8(p, 320, CYAN,		90,  0, 135-1, ys-1);
	boxfill8(p, 320, GREEN,  	135,  0, 180-1, ys-1);
	boxfill8(p, 320, MAGENTA,  	180,  0, 225-1, ys-1);
	boxfill8(p, 320, RED, 	 	225,  0, 270-1, ys-1);
	boxfill8(p, 320, BLUE,  	270,  0, 320-1, ys-1);
	
	boxfill8(p, 320, BLUE,  	0,  ys, 45-1, ys+20-1);
	boxfill8(p, 320, BLACK,  	45,  ys, 90-1, ys+20-1);
	boxfill8(p, 320, MAGENTA,	90,  ys, 135-1, ys+20-1);
	boxfill8(p, 320, BLACK,  	135,  ys, 180-1, ys+20-1);
	boxfill8(p, 320, CYAN,  	180,  ys, 225-1, ys+20-1);
	boxfill8(p, 320, BLACK, 	 225,  ys, 270-1, ys+20-1);
	boxfill8(p, 320, WHITE,  	270,  ys, 320-1, ys+20-1);

	boxfill8(p, 320, DBLUE,  	0,  ys+20, 56-1, 200-1);
	boxfill8(p, 320, WHITE,  	56,  ys+20, 113-1, 200-1);
	boxfill8(p, 320, DMAGENTA,	113,  ys+20, 169-1, 200-1);
	boxfill8(p, 320, BLACK,  	169,  ys+20, 225-1, 200-1);
	boxfill8(p, 320, DGRAY,  	225,  ys+20, 270-1, 200-1);
	boxfill8(p, 320, BLACK,  	270,  ys+20, 320-1, 200-1);
	
	for (;;) {
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
	for (y = y0; y <= y1; y++) {
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}
