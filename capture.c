#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

#include "capture.h"

struct camera_data start_camera( char * filename)
{
    int fd;
    struct camera_data camera;
    struct v4l2_buffer bufferinfo;
    struct v4l2_requestbuffers bufrequest;
    struct v4l2_capability cap;
    struct v4l2_format format;
    void *buffer_start;

    if((fd = open(filename, O_RDWR)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if(ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0)
    {
        perror("VIDIOC_QUERYCAP");
        exit(EXIT_FAILURE);
    }
    if (strcmp("e-con's 1MP Bayer RGB Camera", (const char *) cap.card)!= 0)
    {
        fprintf(stderr, "The file passed is not e-con's 1MP Bayer RGB Camera\n");
        exit(EXIT_FAILURE);           
    }
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        fprintf(stderr, "The device does not handle single-planar video capture.\n");
        exit(EXIT_FAILURE);
    }
    
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8; // Bayer format BA81, 1 byte per sample.
    format.fmt.pix.width = 640;
    format.fmt.pix.height = 480;
    if(ioctl(fd, VIDIOC_S_FMT, &format) < 0)
    {
        perror("VIDIOC_S_FMT");
        exit(1);
    }

    bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufrequest.memory = V4L2_MEMORY_MMAP;
    bufrequest.count = 1;
    if(ioctl(fd, VIDIOC_REQBUFS, &bufrequest) < 0)
    {
        perror("VIDIOC_REQBUFS");
        exit(1);
    }

    
    memset(&bufferinfo, 0, sizeof(bufferinfo));
    bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufferinfo.memory = V4L2_MEMORY_MMAP;
    bufferinfo.index = 0;
    bufferinfo.flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC | V4L2_BUF_FLAG_TSTAMP_SRC_SOE;
    
    if(ioctl(fd, VIDIOC_QUERYBUF, &bufferinfo) < 0)
    {
        perror("VIDIOC_QUERYBUF");
        exit(1);
    }

    buffer_start = mmap(NULL, bufferinfo.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, bufferinfo.m.offset);
    if(buffer_start == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    memset(buffer_start, 0, bufferinfo.length);
    
    if(ioctl(fd, VIDIOC_STREAMON, &(bufferinfo.type)) < 0)
    {
        perror("VIDIOC_STREAMON");
        exit(1);
    }

    camera.fd = fd;
    camera.buffer_start = buffer_start;
    camera.bufferinfo = bufferinfo;
    camera.width = format.fmt.pix.width;
    camera.height = format.fmt.pix.height;
    return camera;
}

void get_frame( struct camera_data camera)
{
    unsigned long buffer_time, process_time;
    struct timespec now;
    // Put the buffer in the incoming queue.
    if(ioctl(camera.fd, VIDIOC_QBUF, &camera.bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }
    // Retrieve the buffer
    if(ioctl(camera.fd, VIDIOC_DQBUF, &camera.bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }
    if(clock_gettime(CLOCK_MONOTONIC, &now)){
        perror("Get System time");
        exit(1);        
    }
    process_time = now.tv_sec *1000000 + now.tv_nsec/1000;
    buffer_time = camera.bufferinfo.timestamp.tv_sec *1000000 + camera.bufferinfo.timestamp.tv_usec;
    printf("processing time is %lu us\n", process_time-buffer_time );
}

int close_camera( struct camera_data camera)
{
    return close(camera.fd);
}