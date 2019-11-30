

set CC=C:\compilers\gbdk\bin\lcc

%CC% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o output/loadMem.o loadMem.c
%CC% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o output/world.o world.c

%CC% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o output/gameSprites.o gameSprites.c

%CC% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o output/main.o main.c
%CC% -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o output/main.gb output/main.o output/gameSprites.o output/world.o output/loadMem.o
