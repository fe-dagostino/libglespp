libgles++
=========

This library is a work in progress and based on own needs but already working and stable for the little things it does.
I'll intend to bring this library up to a fully working 3D engine and any help will be appreciated.
libgles++ has been build on the above of many other libraries and many others will be introduced, but each library used until now:
 - is open source and under a license that allow commercial use
 - is portable through OSs and at least linux and windows are supported
 - supports Opengl ES as well OpenGL
 - supports x86,x86_64 and ARM architectures 

Here a list with all dependecies and their use

 - [**FEDLibrary**](http://fedlibrary.sourceforge.net/) used to keep code portable between linux and windows OSs
 - [**GLFW**](http://www.glfw.org/)       multi-platform library for creating windows with OpenGL contexts and receiving input and events. 
 - [**GLM**](http://glm.g-truc.net/)        OpenGL Mathematics (GLM)
 - [**FreeImage**](http://freeimage.sourceforge.net/)  Add supports for popular graphics image formats like PNG, BMP, JPEG. 
 - [**libav++**](https://github.com/fe-dagostino/libavcpp)    Add supports for many graphics image formats and also to multimedia files.
 - [**DevIL**](http://openil.sourceforge.net/about.php)      Add supports DevIL loading image library. 
 - [**libsigc++**](https://wiki.linuxfromscratch.org/blfs/wiki/libsigc++)  implements a typesafe callback system for standard C++. It allows you to define signals
                  and to connect those signals to any callback function, either global or a member function, 
                  regardless of whether it is static or virtual. 

# Build instructions

Please refer to the Building pages in the [wiki](https://github.com/fe-dagostino/libglespp/wiki).

