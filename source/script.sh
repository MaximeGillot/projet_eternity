g++ main.cpp piece.cpp plateau.cpp instance.cpp -o appli.exe -std=c++11 -Ofast -s -msse -msse2 -mfpmath=sse -mtune=native -mpc64 -mno-abm -mcx16 -msahf -mrecip -mpush-args  -mno-push-args  -maccumulate-outgoing-args -fno-pic -fomit-frame-pointer -ffunction-sections -msse3 -mssse3 -msse4.1 -fopenmp -m64 

./appli.exe ../instances_puzzles/pieces_02x02_vrai.txt 
