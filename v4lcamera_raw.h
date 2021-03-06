#ifndef V4LCAMERA_RAW_H
#define V4LCAMERA_RAW_H

extern "C" {
int init_camera(const char*);
void terminate_camera();
void camera_main_iteration(void);
extern int CAMERA_WIDTH;
extern int CAMERA_HEIGHT;
extern void set_saturation(int saturation);
extern void set_hue(int hue);
void set_auto_exposure(short exposure);
}

#endif // V4LCAMERA_RAW_H
