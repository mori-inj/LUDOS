TOOLPATH = ../z_tools/
MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del

# 디폴트 동작

default :
	$(MAKE) img

# 파일 생성 규칙

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst

LUDOS.sys : LUDOS.nas Makefile
	$(NASK) LUDOS.nas LUDOS.sys LUDOS.lst

LUDOS.img : ipl10.bin LUDOS.sys Makefile
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:LUDOS.sys to:@: \
		imgout:LUDOS.img

# 커맨드

asm :
	$(MAKE) ipl10.bin

img :
	$(MAKE) LUDOS.img

run :
	$(MAKE) img
	$(COPY) LUDOS.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

install :
	$(MAKE) img
	$(IMGTOL) w a: LDUOS.img

clear :
	-$(DEL) ipl10.bin
	-$(DEL) ipl10.lst
	-$(DEL) LUDOS.img
	-$(DEL) LUDOS.sys
	-$(DEL) LUDOS.lst

src_only :
	$(MAKE) clean
	-$(DEL) LUDOS.img
