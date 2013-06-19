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

*If you are on Windows*, edit Kromophone.pro and change the OPENCV variable to point to your installation of OpenCV.

*All platforms:*

	    qmake -r Kromophone.pro
	    make

or use QtCreator to build it.

### Running

Unix:

	./Kromophone
	
Windows: Double click Kromophone.exe


Issues
------

**THIS IS ALPHA SOFTWARE.** This is pretty much just a demo release. There's a lot of features missing, and a lot left to do. If it doesn't work, you can let us know by submitting an issue at: https://github.com/zach-capalbo/Kromophone/issues
