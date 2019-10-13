all: SocketVic.o SocketServer.o
	gcc -o tcpClient SocketVic.o
	gcc -o tcpServer SocketServer.o
	rm *.o

SocketVic.o: SocketVic.c
	gcc -c SocketVic.c 
	
SocketServer.o: SocketServer.c
	gcc -c SocketServer.c
