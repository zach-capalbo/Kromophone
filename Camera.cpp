#include "Camera.h"

/*
 *  V4L2 video capture example
 *
 *  This program can be used and distributed without restrictions.
 */

/* This program has been modified from the original by Zachary Capalbo, June 2009 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>          /* for videodev2.h */

#include <linux/videodev2.h>


#define CLEAR(x) memset (&(x), 0, sizeof (x))

#ifndef V4L2_CID_EXPOSURE_AUTO
#define V4L2_CID_EXPOSURE_AUTO			(V4L2_CID_PRIVATE_BASE+10)
#define V4L2_CID_SHARPNESS			(V4L2_CID_PRIVATE_BASE+2)
#define AUTO_EXPOSURE_ON	8
#else
#define AUTO_EXPOSURE_ON	3
#endif

typedef enum {
	IO_METHOD_READ,
	IO_METHOD_MMAP,
	IO_METHOD_USERPTR,
} io_method;

Camera::Camera(QObject *parent)
{
	
}

int Camera::xioctl (int fd, int request, void * arg)
{
        int r;

        do r = ioctl (fd, request, arg);
        while (-1 == r && EINTR == errno);

        return r;
}
