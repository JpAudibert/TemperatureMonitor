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

int printGraph(int temperatures[10], int length)
{
    setlinestyle(SOLID_LINE, 0, 2);
    int TIME_START_X = 25, TIME_END_X = 600, TIME_Y = 450;
    int TEMP_X = 25, TEMP_START_Y = 50, TEMP_END_Y = 450;
    int ZERO_POINT_X = TIME_START_X - 15, ZERO_POINT_Y = TIME_Y - 5;

    // graph lines
    line(TEMP_X, TEMP_START_Y, TEMP_X, TEMP_END_Y);
    line(TIME_START_X, TIME_Y, TIME_END_X, TIME_Y);

    // chevron temp
    line(TIME_START_X - 10, 70, TIME_START_X, 50);
    line(TIME_START_X + 10, 70, TIME_START_X, 50);

    // chevron time
    line(TIME_END_X - 10, 440, TIME_END_X, TIME_Y);
    line(TIME_END_X - 10, 460, TIME_END_X, TIME_Y);

    outtextxy(ZERO_POINT_X, 35, "100");
    outtextxy(TIME_END_X + 10, ZERO_POINT_Y, "10");
    outtextxy(ZERO_POINT_X, ZERO_POINT_Y, "0");

    int BAR_START = TEMP_X;
    int BAR_WIDTH = 32;
    int BAR_GAP = 15;
    for (int i = 0; i < length; i++)
    {
        int barCount = i + 1;
        int barStart = (BAR_START * barCount) + (BAR_WIDTH * i) + BAR_GAP;
        int temperatureInScale = (int)(temperatures[i] * 400) / 100;

        bar(barStart, TIME_Y - temperatureInScale, barStart + BAR_WIDTH, TIME_Y);
    }

    return 0;
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int temperatures[10];
    for (int i = 0; i < 10; i++)
    {
        temperatures[i] = 0;
    }

    int counter = 0;
    while (counter <= 15)
    {
        int temperature = rand() % 100;
        char printableTemperature[3];
        sprintf(printableTemperature, "%d", temperature);

        // if(temperature > 80)
        //     settextstyle(0, 10, 5);

        for (int i = 10; i >= 1; i--)
        {
            if (i == 0)
                continue;

            temperatures[i] = temperatures[i - 1];
        }

        temperatures[0] = temperature;

        printGraph(temperatures, 10);

        outtextxy(225, 25, "Temperature");
        outtextxy(325, 25, printableTemperature);

        sleep(1);
        cleardevice();
        counter++;
        logTemperature(temperature);
    }

    getch();
    closegraph();
    return 0;
}