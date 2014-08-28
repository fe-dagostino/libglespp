libgles++
=========

This library is a work in progress and based on own needs but already working and stable for the little things it does.
I'll intend to bring this library up to a fully working 3D engine and any help will be appreciated.
libgles++ has been build on the above of many other libraries and many others will be introduced, but each library used until now:
 - is open source and under a license that allow commercial use
 - is portable through OSs and at least linux and windows are supported
 - supports Opengl ES as well OpenGL
 - supports x86,x86_64 and ARM architectures 


Download and Install all dependencies
-------------------------------------

In the following opearaion we are supposing to work with an ARM device that supports **hard float** *https://wiki.debian.org/ArmHardFloatPort* and **neon** *http://www.arm.com/products/processors/technologies/neon.php* also supposing to have **EGL** and **OpenGL ES 2.0**.

 - **FEDLibrary** used to keep code portable between linux and windows OSs
 - **GLFW**       multi-platform library for creating windows with OpenGL contexts and receiving input and events. 
 - **GLM**        OpenGL Mathematics (GLM)
 - **FreeImage**  Add supports for popular graphics image formats like PNG, BMP, JPEG. 
 - **libav++**    Add supports for many graphics image formats and also to multimedia files.
 - **libsigc++**  implements a typesafe callback system for standard C++. It allows you to define signals 
                  and to connect those signals to any callback function, either global or a member function, 
                  regardless of whether it is static or virtual. 
 

**FEDLibrary** - *http://sourceforge.net/projects/fedlibrary/*
```
git clone git://git.code.sf.net/p/fedlibrary/git fedlibrary
cd fedlibrary 
mkdir build 
cd build
cmake ../ -DHAVE_NEON=ON -DHAVE_HARD_FLOAT=ON -DFORCE_PIC=ON 
make 
make install 
ldconfig 
cd ../../ 
```

**GLFW** - *http://www.glfw.org/*
```
git clone https://github.com/glfw/glfw.git glfw 
cd glfw 
git checkout 3.0.4
mkdir build 
cd build
cmake ../ -DGLFW_USE_EGL=ON -DGLFW_CLIENT_LIBRARY=glesv2 -DGLFW_BUILD_DOCS=OFF   -DCMAKE_C_FLAGS:STRING="-DLINUX=1 -mfpu=neon -mfloat-abi=hard -fPIC -O3 -DNDEBUG" 
make 
make install 
ldconfig 
cd ../../ 
```

**OpenGL Mathematics (GLM)** - *http://glm.g-truc.net/0.9.5/index.html*
```
wget http://softlayer-ams.dl.sourceforge.net/project/ogl-math/glm-0.9.5.4/glm-0.9.5.4.zip
unzip glm-0.9.5.4.zip 
cp -R glm/glm /usr/include/ 
```

**FreeImage** - *http://freeimage.sourceforge.net/*
```
You can optimize this library using -mfloat-abi=hard option, do not use neon or you will get link error.

wget http://garr.dl.sourceforge.net/project/freeimage/Source%20Distribution/3.16.0/FreeImage3160.zip 
unzip FreeImage3160.zip 
cd FreeImage 
make 
make install 
ldconfig
cd .. 
```

**libsigc++** - *http://libsigc.sourceforge.net/*
```
wget http://ftp.gnome.org/pub/GNOME/sources/libsigc++/2.3/libsigc++-2.3.1.tar.xz
unxz libsigc++-2.3.1.tar.xz
tar xvf  libsigc++-2.3.1.tar
cd libsigc++-2.3.1
./configure --disable-shared –-enable-static --with-pic –-with-gnu-ld --disable-documentation CXXFLAGS='-mfpu=neon -mfloat-abi=hard' 
make 
make install 
cp sigc++config.h /usr/local/include/sigc++-2.0/
ldconfig 
cd .. 
```

**libgles++** - *here you are*
```
git clone https://github.com/fe-dagostino/libglespp.git libgles++
cd libgles++ 
mkdir build 
cd build
cmake ../  -DHAVE_NEON=ON -DHAVE_HARD_FLOAT=ON -DFORCE_PIC=ON -DHAVE_OPENGL_ES_API=ON -DTARGET_NV_CARD=ON -DUSE_FREEIMAGE=ON -DUSE_AVCPP=OFF -DBUILD_GLPLAYER=OFF -DBUILD_GLES_GUI=ON 
make 
make install 
ldconfig 
cd ../../ 
```

