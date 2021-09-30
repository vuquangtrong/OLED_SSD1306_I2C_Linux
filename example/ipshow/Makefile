all: ipshow.cpp
	g++ ipshow.cpp -lssd1306 -o ipshow

install:
	sudo cp ipshow /usr/bin
	sudo cp ipshow.service /etc/systemd/system
	sudo systemctl enable ipshow.service
