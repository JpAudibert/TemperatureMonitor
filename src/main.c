#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

int logTemperature(int temperature)
{
    FILE *fp;

    if ((fp = fopen("temperatureLog.txt", "a+")) == NULL)
        return 1;

    fprintf(fp, "Temperature: %d \n", temperature);
    fclose(fp);
    return 0;
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int counter = 0;
    while (counter <= 3)
    {
        int temperature = rand() % 100;
        char printableTemperature[3];
        sprintf(printableTemperature, "%d", temperature);

        setlinestyle(3, 0, 5);
        outtextxy(25, 240, "Temperature");
        outtextxy(255, 240, printableTemperature);

        sleep(1);
        cleardevice();
        counter++;
        logTemperature(temperature);
    }

    // getch();
    closegraph();
    return 0;
}