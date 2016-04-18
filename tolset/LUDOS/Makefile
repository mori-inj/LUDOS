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

ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst

LUDOS.img : ipl.bin Makefile
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek wbinimg src:ipl.bin len:512 from:0 to:0   imgout:LUDOS.img

# 커맨드

asm :
	$(MAKE) ipl.bin

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
	-$(DEL) ipl.bin
	-$(DEL) ipl.lst
	-$(DEL) LUDOS.img

src_only :
	$(MAKE) clean
	-$(DEL) LUDOS.img
