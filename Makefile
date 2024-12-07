#
# /usr/bin/g++ -fdiagnostics-color=always
# -I /home/andrus/learn/tts/3/test-task3/common
# -o /home/andrus/learn/tts/3/test-task3/main.exe
# -g 
# /home/andrus/learn/tts/3/test-task3/main.cpp /home/andrus/learn/tts/3/test-task3/common/*.cpp
#

build: main.exe

clean:
	-rm -f *.exe *.log

all:
	$(MAKE) -j3 main.exe server.exe client.exe

INC = -I common
CMN = common/common_udp.cpp common/rnd.cpp

main.exe: main.cpp
	g++ $(INC) -o main.exe   -g main.cpp   common/*.cpp

client.exe:
	g++ $(INC) -o client.exe -g client.cpp $(CMN) common/client_udp.cpp common/state_mashine.cpp

server.exe:
	g++ $(INC) -o server.exe -g server.cpp $(CMN) common/server_udp.cpp

run: main.exe
	./main.exe
