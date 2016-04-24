#LUDOS

##Day1

* LUDOS_0.img: 디스크 이미지 파일을 바이너리 에디터를 이용해 일일이 기록. 편집이 불편하고 패딩을 위해 존재하는 0x00을 일일이 입력해야 한다는 불편함이 존재.  
* LUDOS_1.nas: LUDOS_0.img를 DB 명령어를 사용해 어셈블리 코드로 생성하고, 0x00를 RESB를 사용해 단축.  
* LUDOS_2.nas: LUDOS_1.nas에서 DB명령어로 작성된 코드 중, 앞부분의 FAT포맷을 위한 설정 부분과 화면에 출력할 메세지를 출력하는 부분을 좀 더 의미가 명확한 어셈블리 코드로 작성. [FAT설정 / 프로그램 본체 / 메세지 출력 / 부트섹터 이외의 부분]으로 구성. 
    * asm.bat: nask 어셈블러를 이용해 nas 파일을 img파일로 생성(img파일도 bin파일과 본질적으로 동일하지만 디스켓에 구울 수 있냐 여부가 다른듯)
    * run.bat: qemu 에뮬레이터를 이용해 img파일을 부팅
    * install.bat: A드라이브(디스켓)에 구움(안 씀).

###부트 섹터
플로피디스크에서 1섹터 = 512바이트.  
1440KB = 1474560B = 512 * 2880이므로 2880개의 섹터로 구성.  
이들 중 첫번째 섹터가 부트 섹터.  
부팅 시에 부트 섹터의 맨 끝 2바이트가 55 AA 인지 읽는다.  
(55 AA가 아니면 부팅할 수 없는 프로그램으로 판단)  

###IPL
부트 섹터 하나만으로는 당연하게도 OS를 다 담을 수 없다.  
부트 섹터에는 그 뒤에 나올 OS의 나머지 부분들을 읽게끔 하는 프로그램을 써 두는데 이를 Initial Program Loader(IPL)이라 한다.  
cf. 부트 섹터의 이름은 반드시 8바이트여야 한다.  

###어셈블리 정리
* ;: 주석
* DB: Data Byte의 약자로 파일에 1바이트 크기의 내용을 직접 쓴다. 대소문자 구분x  
* DW: Data Word의 약자로 2바이트(16비트)크기의 내용을 직접 쓴다.  
* DD: Data Double-word의 약자로 4바이트(32비트)크기의 내용을 직접 쓴다.  
* RESB: Reserve Byte의 약자로 지정한 크기만큼 띄어둔다는 의미. NASK에선 자동으로 0으로 초기화.  
* $: 특정 행이 선두로부터 몇 바이트인지 알려줌. 현재부터 0x1fe번지까지를 0으로 채우고 싶은 경우 RESB 0x1fe-$ 와 같은 형태로 사용가능.  

###NASK
NASM이라는 어셈블러(어셈블리 코드를 기계어로 바꿔줌)를 개량한 어셈블러.  
  
  
  
  
  
  
##Day2

[FAT설정 / 프로그램 본체 / 메세지 출력 / 부트섹터 이외의 부분]  
* LUDOS_3.nas: LUDOS_2.nas에서 FAT설정과 메세지 출력 부분을 명확히 했다면, 3.nas에서는 프로그램 본체 부분을 좀 더 의미가 잘 드러나는 어셈블리 코드로 작성. JMP명령어로 프로그램의 흐름은 프로그램 본체( entry: )로 바로 이동하고 FAT설정 부분은 그냥 그 자리에 존재함으로써 설정을 담당하는 것으로 추정.  
    * ipl.nas: LUDOS_3.nas에서 초기 512바이트(IPL)를 제외한 뒷부분을 제거. (이 뒷부분을 어떻게 만드는지 모르겠음...ㅂㄷㅂㄷ)
    * asm.bat: ipl.nas를 ipl.bin으로 바꿈. ipl.lst(objdump한 결과와 유사)를 추가적으로 생성함.
    * makeimg.bat: ipl.bin을 토대로 img파일(1440KB) 생성. edimg.exe라는 프로그램을 사용하며, 이 프로그램이 제거된 뒷 부분을 추가해주는 것으로 추정.
* Makefile: Windows에서도 make.exe(GNU에서 만듦)를 이용해 Makefile을 사용 가능. 기존 배치파일들(asm, run, install, makeimg 등)을 Makefile 하나로 관리할 수 있으며, 파일들의 일괄적인 삭제도 가능. (프로그램 이름을 argument형태로 전달 하고 싶었지만 아직 Makefile의 변수 사용에 익숙하지 않아 일단 넘어감.)
  
  
  
###레지스터 정리(16비트 기준) 

####범용 레지스터  
* AX: accumulator  
* CX: counter  
* DX: data  
* BX: base  
* SP: stack pointer  
* BP: base pointer  
* SI: source index  
* DI: destination index  

####세그먼트 레지스터  
* ES: extra  
* CS: code  
* SS: stack  
* DS: data  
* FS: extra2  
* GS: extra3  
  
  

###어셈블리 정리
* ORG: 기계어가 실행될 PC상의 메모리 위치를 지정.$의 의미도 ORG를 기준으로 재정의. ([0x7c00으로 설정하는 이유](https://github.com/mori-inj/LUDOS/blob/master/AT-MemoryMap.md))  
* MOV: 특정 레지스터나 메모리에 값을 쓰는 명령어. movl, movq 등과 달리 MOV BYTE, MOV WORD 형태로 쓰이니 주의. 메모리의 주소값을 지정할 수 있는 레지스터는 BX, BP, SI, DI 뿐.  
* INT: 인터럽트. (바이오스)함수를 호출하는 데에 사용. [사용 가능한 함수 목록](https://github.com/mori-inj/LUDOS/blob/master/AT-BIOS.md)  
* HLT: halt. 아무 것도 하지 않고 CPU를 대기상태에 두게 하는 명령어. (몹시 맘에 듦)  




###BIOS(Basic Input Output System)  
원래는 OS개발자를 위한 함수 모음. INT를 이용해 호출하며 INT 뒤의 숫자로 호출될 함수를 결정. 0x10 함수의 경우 [비디오카드 제어](https://github.com/mori-inj/LUDOS/blob/master/AT-BIOS.md#한-문자-출력) 관련. 

  
  
  
  
  
  
##Day3

* ipl_a.nas: 이제 본격적으로 ipl을 만들고 512바이트가 뒤의 내용을 읽어오게끔 하는 작업(부트로더, Day2에서 edimg.exe가 해주는 것으로 추정되던 작업)을 하기 시작. (디스크에서 내용을 읽어오는 법: [BIOS INT(0x13)](https://github.com/mori-inj/LUDOS/blob/master/AT-BIOS.md#int0x13--디스크-관련-함수)) ES:BX를 묶어서 버퍼 어드레스로 사용하는데, 읽어온 데이터를 저장할 메모리 상의 공간을 지정. 지정한 주소로부터 한 섹터의 크기인 512바이트까지 디스크로부터 읽어온 데이터가 write됨. 레지스터가 16비트(2바이트)라 2개를 묶어서 총 4바이트를 주소를 지정하는데 쓰...ㄹ 것 같지만 그렇지 않고, ES * 16 + BX 같은 변태 같은 꼴로 사용함. 따라서 접근 가능한 메모리는 약 1메가 바이트 남짓(1114095==0x10FFEF Byte). 당시에는 32비트를 고려하지 않았고, 1메가로도 충분할 것으로 생각했겠지... 다른 어셈블리 인스트럭션에서도 암묵적으로 [DS:]가 생략된 것으로 볼 수 있고, 명시적으로 DS를 쓰지 않는 경우, DS를 0으로 설정해줘야 함. 2번 섹터를 읽음에 주의. 1번 섹터는 부트로더 자기 자신이므로 굳이 읽을 필요 없음.  
* ipl_b.nas: 디스켓이 제대로 읽어오지 못할 경우 드라이브 리셋 후 다시 읽어오기 시도. 최대 5번.  
* ipl_c.nas: 18섹터까지 읽기 시도. 코드는 루프를 사용해서 한 섹터씩 읽어 오고 있지만 AL을 17(2부터 18)로 정해도 되지만, 연속된 섹터를 루프 없이 한번에 읽을 경우 제한 조건이 붙기 때문에 루프로 읽는 것을 연습.  
* ipl_d.nas: 10실린더까지 읽기 시도.  
* ipl_e.nas: ipl_d.nas와 동일.
* LUDOS_5.nas: 아무것도 하지 않고 그저 대기 상태에 있는 OS. 처음으로 나온 OS 본체(어셈파일).  
* LUDOS_5.sys: LUDOS_5.nas를 nask로 어셈블 한 것(바이너리 파일).  
* LUDOS_5.img: ipl_e.bin(바이너리 파일)과 LUDOS_5.sys(바이너리 파일)을 합쳐서(이 때 edimg.exe를 사용하는데, 여전히 edimg가 구체적으로 무슨 일을 하는지 알 수 없음) 하나의 디스크 이미지 파일을 생성. 생성해본 결과, ipl_e.bin은 지금까지처럼 파일의 맨 위(앞)에 존재하고, LUDOS_5.sys는 LUDOS_5.img안의 다른 곳에 포함되어 들어감. "LUDOS_5.sys"라는 파일 이름은 0x002600에 들어가고 파일의 내용은 0x004200에 들어가는 것으로 추정. 남은 일은 부트섹터가 읽어온 내용들 중에 저 위치로 프로그램의 흐름이 바로 이동하게끔 해주는 작업(JMP)이 필요.
* LUDOS_6.nas: LUDOS_5.img파일은 디스켓에 저장되고 0x2600이나 0x4200은 디스켓 상의 주소. 부트섹터는 메모리 상의 0x7c00 ~ 0x7dff (512바이트)에 로드되고, 아직 안 나왔지만 0x8000 ~ 0x81ff의 512 바이트에 부트 섹터의 내용을 넣을 예정이라 함. 부트 섹터는 디스켓으로부터 나머지 뒷 내용을 읽어와 0x8200번지부터 쓰기 시작하므로, 디스켓 상에서 0x4200번지에 있던 LUDOS_5.sys의 내용은 메모리의 0xc200번지에 올라오게 됨. 그러므로 LUDOS_6.nas에는 ORG 0xc200을 추가.  
* LUDOS_7.nas: LUDOS_6.nas에서는 OS자체가 하는 일이 없기 때문에 정상 작동 하는지 판단 불가. 화면 모드를 바꾸는 내용 추가. (부트로더가 디스켓으로부터 메모리로 내용을 다 읽어온 후에 OS가 실행되면 화면이 변화.) (화면 모드를 바꾸는 법: [BIOS INT(0x10) 비디오모드 설정](https://github.com/mori-inj/LUDOS/blob/master/AT-BIOS.md#비디오-모드-설정))  
* ipl_f.nas -> ipl10.nas: 마찬가지 이유로 JMP 0xc200 을 추가해서 부팅 작업이 끝난 이후에 바로 OS의 본체를 실행. 10실린더만 읽는다는 의미로 ipl10.nas로 이름 변경. JMP 직전에 메모리의 0x0ff0번지에 CYLS(현재로서는 10)를 기록해둠으로써 디스크를 어디까지 읽었는지 기억.  
* LUDOS_8.nas: 키보드 LED의 상태를 레지스터에 기록. 32비트 모드에서는 BIOS관련 함수를 사용할 수 없음(16비트용 기계어(BIOS 함수도 여기에 해당.)와 32비트용 기계어는 호환 불가). BIOS로 할 수 있는 작업들 중 키보드의 상태나 화면 모드에 관한 정보를 레지스터에 기록.  
* asmhead_0.nas: LUDOS_8.nas의 내용 + C언어로 쓰인 본체 호출을 위해 코드 추가(자세한 설명은 나중에). 원래 있던 HLT 부분만 뻬서 C언어로 작성함.  
* bootpack_0.c: C로 짠 OS 본체(HLT부분에 해당). 이 c언어를 잘 돌아가게 하기 위해 지금 매우 머리가 복잡함(왜 main이 HariMain인거야... 표준 좀 지켜 => 는 나도 안 지키고 이름만 LUDOSMain으로 바꿈).  
    * *.c --[cc1.exe(gcc를 개조)]--> *.gas //gcc도 내부적으로 gas라는 어셈블러를 통해 바이너리 파일을 생성  
    * *.gas --[gas2nask.exe]--> *.nas // gas확장자는 gas어셈블러용이므로 nask용 어셈블리인 nas로 변경(gas2nas라는 이름이 더 적합한 것 같으니 바꾸기로)  
    * *.nas --[nask.exe]--> *.obj // 바이너리 기계어 파일이지만 링커를 거치지 않아서 직접적으로 실행 불가.  
    * *.obj --[obj2bim]--> *.bim // 링킹 작업. bim은 binary image file의 약자로 이 책에서만 쓰임.  
    * *.bim --[bim2lsd]--> *.lds // 링킹 작업이 끝난 후에도 각 OS에 맞게 가공이 필요.  
   
   boot_pack.c를 최종적으로 boot_pack.lds로 바꾼 후에 이걸 asmhead.bin뒤에 붙여서 원래 LUDOS_8.sys같은 형태의 파일을 만듦. LUDOS_8.sys와 기존에 있던 ipl10.bin파일을 합쳐서 LUDOS.img파일을 생성.    
   hrb등 하리보테가 들어가는 것들을 전부 커스터마이징 예정. 이 작업에 상당한 시간이 소요되는 중. => hrb파일은 lds파일로 변경.  
   HariMain을 바꾸기 위해 꽤 고생중이었는데 [좋은 곳](http://hrb.osask.jp/wiki/?advance/NotHariMain)을 발견.  
   \tolset\z_tools\LUDOS의 *.rul과 *.lib을 바꿔줘야 함. *.rul은 직접 바꾸면 되고 *.lib은 \cd\omake\tolsrc\hrblib0a로 들어가서 startup.c파일을 수정한 후 makefile로 *.lib파일 취득 가능.  
* naskfunc_0.nas: HLT라는 어셈블리 명령어를 C언어 상에서 사용할 수 있게 해줌. 함수이름을 전역변수로 설정하고 링킹을 위한 옵션(WCOFF모드)와 32비트 설정, 소스파일 정보 등을 추가. 맨 아래 부분에 함수의 본체를 작성.  
* bootpack_1.c: 이제서야 hlt를 사용할 수 있음. HTL는 IO관련 함수이므로 함수명dl _io_hlt. 외부(naskfunc_0.nas)에 정의된 함수를 사용하므로 함수 선언만 명시해주고 바로 사용가능(당연하게도, 재정의 금지).  
* Makefile: 변수를 사용하는 형태로 좀 더 깔끔하게 작성. 생성해내는 파일의 이름을 변수로 설정하는 방법은 여전히 모르겠음... ipl_e.nas와 LUDOS_5.sys를 추가하는 부분에서 copy from:LUDOS.sys to :@: 라는 명령어 추가됨. bootpack_0.c가 등장하며 수많은 툴들을 위한 명령어가 잔뜩 추가됨. naskfunc의 함수를 위한 링커 옵션도 추가됨.    


###디스크 구조(소위 말하는 디스켓)
* 실린더: 디스크를 구성하는 동심원. 바깥쪽부터 안쪽까지 0에서 79, 총 80개가 존재.  
* 헤드: 디스크의 앞/뒤 구분. 0과 1로 표기.  
* 섹터: 원주를 따라 하나의 실린더를 18등분 한 조각(개당 20도의 중심각을 갖겠군). 1에서 18로 표기.  
* Cx-Hy-Sz의 형태로 표기함. (ex. C0-H0-S1) 80 * 2 * 18 * 512B = 1474560B = 1440KB. 어떤 섹터의 다음 섹터를 찾을땐, 진법처럼 섹터가 18을 넘으면 헤드가 증가, 헤드가 1을 넘으면 실린더가 증가하는 식.  

###어셈블리 정리
* EQU: C언어에서 #define과 같음. (ex. CYLS EQU 10 은 #define CYLS 10 과 동일.) EQU는 알다시피 equal의 약자.  





##Day4

* naskfunc_1.nas: 화면에 무언가를 출력하기 위해선 VRAM(비디오램)에 값을 써줘야함. VRAM의 각 번지는 화면의 각 화소에 대응. 사실 C언어로 특정 메모리에 값을 쓸 수는 있지만, ASM명령을 이용해 쓰기로 함. ESP 관련된 내용은 아니깐 패스. addr주소에 data값을 쓰는 함수가 추가됨. calling convention 신경써야 함(EAX와 ECX만 사용하는 걸로...). INSET명령으로 32bit레지스터의 이름을 인식할 수 있도록 486이상의 컴퓨터라는 걸 명시.  
* bootpack_2.c: for loop 돌려서 0xa0000번지부터 0x0afff번지까지 (VRAM 영역) 15(0xf) 흰색을 대입.
* bootpack_3.c: 줄무늬를 출력. 각 화소의 번지의 주소값의 하위 4비트가 색으로 쓰임.  
* bootpack_4.c: 포인터를 이용해 메모리에 직접 값을 씀. p를 추가적으로 선언할 필요 없이 캐스팅만 잘 해주면 되는데, "이렇게 쓰면 BYTE[i] = i & 0x0f와 조금 닮았다는 느낌이 들지 않습니까? 어셈블러를 너무 좋아하는 필자는 그런 것 같아서 저도 모르게 씩 웃게 됩니다."라고 표현한 필자의 의견에 전적으로 동의.  
* naskfunc_2.nas: write_mem8함수가 필요 없어졌으므로 제거.  

###[CGA(Color Graphics Adapter)](https://en.wikipedia.org/wiki/Color_Graphics_Adapter)
4bit로 16가지 색만 표현 가능
* 0x0: black         (#000000)  
* 0x1: blue          (#0000AA)  
* 0x2: green         (#00AA00)
* 0x3: cyan          (#00AAAA)
* 0x4: red           (#AA0000)
* 0x5: magenta       (#AA00AA)
* 0x6: brown         (#AA5500)
* 0x7: light gray    (#AAAAAA)
* 0x8: gray          (#555555)
* 0x9: light blue    (#5555FF)
* 0xa: light green   (#55FF55)
* 0xb: light cyan    (#55FFFF)
* 0xc: light red     (#FF5555)
* 0xd: light magenta (#FF55FF)
* 0xe: yellow        (#FFFF55)
* 0xf: white         (#FFFFFF)


