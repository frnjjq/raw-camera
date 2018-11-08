#pragma once

#include <linux/videodev2.h>

struct camera_data{
    int fd;
    int width;
    int height;
    void *buffer_start;
    struct v4l2_buffer bufferinfo;
}; 
struct camera_data start_camera( char * filename);
void get_frame( struct camera_data camera);
int close_camera( struct camera_data camera);