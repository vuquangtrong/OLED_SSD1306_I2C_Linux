#include <string.h>
#include <unistd.h>
#include <SSD1306/ssd1306.h>

int main() {
    char counter = 0;
    char buffer[4];
    SSD1306_Init("/dev/i2c-1");
    while(1) {
        sprintf(buffer, "%d", counter++);
        SSD1306_Clear();
        SSD1306_WriteString(0,0, "counter:", &Font_7x10, SSD1306_WHITE, SSD1306_OVERRIDE);
        SSD1306_WriteString(0,10, buffer, &Font_11x18, SSD1306_WHITE, SSD1306_OVERRIDE);
        SSD1306_DrawRectangle(0,28,128,4,SSD1306_WHITE);
        SSD1306_DrawFilledRectangle(0,28,counter/2,4,SSD1306_WHITE);
        SSD1306_Screen_Update();
        sleep(0.2);
    }
    return 0;
}
