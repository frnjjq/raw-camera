#include <stdbool.h>
#include <stdlib.h>

#include "capture.h"
#include "player.h"

void  raw_to_rgb(uint8_t *rgb_data, uint8_t *raw_data, int width, int height);

//int main( int argc, const char* argv[] )
int main()
{
    struct camera_data camera;
    char filename[80] = "/dev/video0";
    bool quit;
    uint8_t *rgb_data;
	camera = start_camera(filename);
    rgb_data = (uint8_t *) malloc (camera.width * camera.height *3 );
    init_player(camera.width, camera.height);
    
    while(!quit)
    {
        handle_window(&quit);
        get_frame( camera);
        raw_to_rgb(rgb_data, camera.buffer_start, camera.width, camera.height);
        play_frame((void *)rgb_data, camera.width*3);
    }
    close_player();
    return close_camera(camera);;
}

void  raw_to_rgb(uint8_t *rgb_data, uint8_t *raw_data, int width, int height)
{
    uint8_t r,g,b;
    for (int y = 0; y< height; y++)
    {
        for (int x = 0; x< width; x++)
        {
            if(y%2==0 && x%2==0) // Even column and even row
            {
                r = 0;
                g = 0;
                b = raw_data[y*width+x];
            }
            else if (y%2!=0 && x%2!=0) // Odd column and Odd row
            {
                r = raw_data[y*width+x];
                g = 0;
                b = 0;
            }
            else
            {
                r = 0;
                g = raw_data[y*width+x];
                b = 0;                
            }
            rgb_data[3*(y*width+x)] = r;
            rgb_data[3*(y*width+x)+1] = g;
            rgb_data[3*(y*width+x)+2] = b;
        }
    }
}