# rawcam
Demonstation of the minimum lag from glass to glass using a bayer raw camera(See3CAM_10CUG_CH). 

## Dependencies
* SDL 2
* OpenMP
* v4l2

## Compiling Ubuntu
1. Install libraries. In Ubuntu `sudo apt-get install libv4l-dev libsdl2-dev libomp-dev`
2. Get to the directory and run `make`
3. The binary is located in the same folder. The name is rawcam.

## Usage
```
./rawcam
```

## Credits
[This blog shows perfectly how to use the v4l api](http://jwhsmith.net/2014/12/capturing-a-webcam-stream-using-v4l2/)
