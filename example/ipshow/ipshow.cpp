#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <SSD1306/ssd1306.h>

using namespace std;
char i2c_dev[] = "/dev/i2c-1";
char noIP[] = "No IP";

void showIP(int line, char type, char* ip) {
    char buffer[32] = {0};
    sprintf(buffer, "%c:%s", type, ip);
    SSD1306_WriteString(0,line*10, buffer, &Font_7x10, SSD1306_WHITE, SSD1306_OVERRIDE);
}

void getIPAddresses() {
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    int found = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if(strcmp(temp_addr->ifa_name, "wlan0")==0){
                    showIP(found++, 'W',
                        inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr)
                    );
                }
                if(strcmp(temp_addr->ifa_name, "eth0")==0){
                    showIP(found++, 'E',
                        inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr)
                    );
                }

            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);

    if (!found) {
       showIP(found, '?', noIP);
    }
}


int main(int argc, char** argv) {
   SSD1306_Init(i2c_dev);
   while(1) {
      SSD1306_Clear();
      getIPAddresses();
      SSD1306_Screen_Update();
      sleep(10);
   }
}
