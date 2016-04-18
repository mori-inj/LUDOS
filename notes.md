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
* asm.bat: ipl.nas를 ipl.bin으로 바꿈. ipl.lst를 추가적으로 생성함.
* makeimg.bat: ipl.bin을 토대로 img파일(1440KB) 생성. edimg.exe라는 프로그램을 사용하며, 이 프로그램이 제거된 뒷 부분을 추가해주는 것으로 추정.
  
  
  
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

