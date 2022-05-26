#include <cstdio>
#include <poll.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <signal.h>
#include "schedulers/roundrobin.hh"

using namespace schedulers;

#define GOTO_POS(x, y) printf("\033[%u;%uH", y, x)
#define CLEAR() printf("\033[2J");
#define ERASE_LINE() printf("\033[2K");

constexpr int plot_height = 30;
constexpr int plot_height_origin = 40;
constexpr int plot_width = 144 * 2;
constexpr double PI = 3.1415926535;
constexpr double phase = 2*PI/144.0;

// This is volatile to make sure it does not get cached in the registers during a context switch
volatile unsigned int x = 0;

void sine()
{

    // render a sine wave canvas
    while(true)
    {
        CLEAR();
        for(int x = 0; x < plot_width; x++)
        {
            int plotted_y = plot_height_origin + plot_height * sin(x * phase);
            for(int y = 0; y < 100; y++)
            {
                GOTO_POS(x, y);
                if ((plotted_y >= plot_height_origin && y <= plotted_y && y >= plot_height_origin) || (plotted_y < plot_height_origin && y >= plotted_y && y <= plot_height_origin))
                    putchar('.');
                else
                    putchar(' ');
            }

        }
        poll(NULL, 0, 100);
    }
}

constexpr int BLOCK_PERIOD = 24;

void block()
{

    while(true)
    {
        CLEAR();
        for(int x = 0; x < plot_width; x++)
        {
            int plotted_y = plot_height_origin + plot_height * (x % BLOCK_PERIOD < 12 ? -1 : 1);

            for(int y = 0; y < 100; y++)
            {
                GOTO_POS(x, y);
                if ((plotted_y >= plot_height_origin && y <= plotted_y && y >= plot_height_origin) || (plotted_y < plot_height_origin && y >= plotted_y && y <= plot_height_origin))
                    putchar('.');
                else
                    putchar(' ');
            }

        }
        poll(NULL, 0, 100);
    }
}

constexpr int SAWTOOTH_PERIOD = 40;

void sawtooth()
{
    while(true)
    {
        CLEAR();
        for(int x = 0; x < SAWTOOTH_PERIOD * 4; x++) {
            int plotted_y = plot_height_origin +
                            plot_height * ((x % SAWTOOTH_PERIOD) - SAWTOOTH_PERIOD / 2.0) / SAWTOOTH_PERIOD;

            for (int y = 0; y < 100; y++) {
                GOTO_POS(x, y);
                if ((plotted_y >= plot_height_origin && y <= plotted_y && y >= plot_height_origin) ||
                    (plotted_y < plot_height_origin && y >= plotted_y && y <= plot_height_origin))
                    putchar('.');
                else
                    putchar(' ');
            }
        }
        poll(NULL, 0, 100);
    }
}
int main()
{
    roundrobin::setup(800);
    roundrobin::add_task(sine);
    roundrobin::add_task(block);
    roundrobin::add_task(sawtooth);
    roundrobin::start();
}
