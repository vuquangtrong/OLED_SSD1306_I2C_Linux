all: ipshow.o

ipshow.o:
	g++ ipshow.cpp -lssd1306 -o ipshow

install:
	sudo systemctl stop ipshow.service
	sudo cp ipshow /usr/bin
	sudo cp ipshow.service /etc/systemd/system
	sudo systemctl enable ipshow.service
