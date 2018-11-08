#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>


int start_camera()
{
    int fd;
    struct v4l2_capability cap;
    struct v4l2_format format;

    if((fd = open("/dev/video0", O_RDWR)) < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if(ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0)
    {
        perror("VIDIOC_QUERYCAP");
        exit(EXIT_FAILURE);
    }
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        fprintf(stderr, "The device does not handle single-planar video capture.\n");
        exit(EXIT_FAILURE);
    }
    
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_SGBRG8;
    format.fmt.pix.width = 800;
    format.fmt.pix.height = 600;
    
    if(ioctl(fd, VIDIOC_S_FMT, &format) < 0){
        perror("VIDIOC_S_FMT");
        exit(1);
    }
 

 
    close(fd);
    return EXIT_SUCCESS;
}