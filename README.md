Kromophone
==========

http://kromophone.com

This program is licesned under the GPL v. 3. See LICENSE for more info.


Installation and Setup
----------------------

### Dependencies

The required dependencies are:

 * Qt 5.0
 * OpenCV

### Compiling

#### Windows, Linux, or Mac

*If you are on Windows*, edit Kromophone.pro and change the OPENCV variable to point to your installation of OpenCV, or pass OPENCV=C:/PATH/TO/OPENCV as a qmake argument.

*All desktop platforms:*

	    qmake -r Kromophone.pro
	    make

or use QtCreator to build it.

#### Android

Compiling for Android is a little tricky. The dependencies are Qt 5.2.1 for Android and OpenCV-2.4.6-android-sdk. 

Using Qt Creator to build:

 1) Open Kromophone.pro
 2) Add the Android for armeabi-v7 kit
 3) In the qmake build step, add OPENCV=/path/to/OpenCV-2.4.6-android-sdk as an additional argument (replacing /path/to with whereever you unpackaged the openCV sdk)
 4) Click Run and cross your fingers.

### Running

Unix:

	./Kromophone
	
Windows: Double click Kromophone.exe


Issues
------

**THIS IS ALPHA SOFTWARE.** This is pretty much just a demo release. There's a lot of features missing, and a lot left to do. If it doesn't work, you can let us know by submitting an issue at: https://github.com/zach-capalbo/Kromophone/issues
    
