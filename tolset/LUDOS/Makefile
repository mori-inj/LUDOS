TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/LUDOS/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
BIM2lds  = $(TOOLPATH)bim2lds.exe
RULEFILE = $(TOOLPATH)LUDOS/haribote.rul
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

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

bootpack.gas : bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.nas : bootpack.gas Makefile
	$(GAS2NASK) bootpack.gas bootpack.nas

bootpack.obj : bootpack.nas Makefile
	$(NASK) bootpack.nas bootpack.obj bootpack.lst

bootpack.bim : bootpack.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj
# 3MB+64KB=3136KB

bootpack.lds : bootpack.bim Makefile
	$(BIM2lds) bootpack.bim bootpack.lds 0

LUDOS.sys : asmhead.bin bootpack.lds Makefile
	copy /B asmhead.bin+bootpack.lds LUDOS.sys

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
	-$(DEL) *.bin
	-$(DEL) *.lst
	-$(DEL) *.gas
	-$(DEL) *.obj
	-$(DEL) bootpack.nas
	-$(DEL) bootpack.map
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.lds
	-$(DEL) LUDOS.img
	-$(DEL) LUDOS.sys
	-$(DEL) LUDOS.lst

src_only :
	$(MAKE) clean
	-$(DEL) LUDOS.img
