Kromophone
==========

http://kromophone.com

This program is licesned under the GPL v. 3. See LICENSE for more info.


Installation and Setup
----------------------

### Dependencies

The required dependencies are:

 * [Qt 5.6][qt]

### Compiling

#### Windows, Linux, or Mac
Just like any other Qt project, run

```
qmake -r Kromophone.pro
make
```

or use QtCreator to build it.

#### Android

 1. Make sure you have [Qt for Android][qt] installed
 2. Open `Kromophone.pro` with QtCreator, and configure the project for the Android target.
 
Alternatively, you can find a prebuilt version on the [Google Play Store][play].

#### Raspberry Pi

Building everything for the raspberry pi is a little tricky, but can be done!

 1. Start with a [Raspbian Jesse Lite image][raspbian]
 2. Follow the guide [RaspberryPi2EGLFS guide][wikiguide] on the Qt Wiki for cross compiling Qt for raspberry pi
 3. Also build and deploy the following QT submodules: `qtmultimedia, qtquickcontrols2, qtdeclarative,  qtquickcontrols,  qtwebsockets`
 4. Use the qmake from step 2 to build Kromophone.pro
 
**Caveats for Raspberry Pi:**

 - The Kromophone on Raspberry pi uses a hacky V4L capture module, which only supports USB UVC cameras. YMMV
 - The Kromophone sounds awful with the on board sound card. Get a USB sound card and use the `--audioDevice plughw:CARD=Device,DEV=0` option.
 
If you are interested in purchasing a made Raspberry Pi sdcard pre-loaded with the Kromophone software, please contact us.

### Running

#### Unix:

	./Kromophone
	
#### Windows: 

Double click Kromophone.exe


Issues
------

**THIS IS ALPHA SOFTWARE.**  

If it doesn't work, you can let us know by submitting an issue at: https://github.com/zach-capalbo/Kromophone/issues
    
[qt]: https://www.qt.io/download-open-source/
[play]: https://play.google.com/store/apps/details?id=com.zachcapalbo.kromophones
[wikiguide]: https://wiki.qt.io/RaspberryPi2EGLFS
[raspbian]: https://www.raspberrypi.org/downloads/raspbian/
