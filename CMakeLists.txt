
cmake_minimum_required (VERSION 2.6)
project(libgles++)

include_directories( ./include/ )
include_directories( /usr/include/freetype2/  )
include_directories( ${CMAKE_INSTALL_PREFIX}/include/ )
include_directories( ${CMAKE_INSTALL_PREFIX}/include/sigc++-2.0/ )
include_directories( ${CMAKE_INSTALL_PREFIX}/include/fedlibrary/include )
include_directories( ${CMAKE_INSTALL_PREFIX}/include/fedlibrary/template_include )

link_directories( ${CMAKE_FIND_ROOT_PATH}/lib )
link_directories( ${CMAKE_FIND_ROOT_PATH}/usr/lib )

IF(NOT CMAKE_BUILD_TYPE )
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
ENDIF()

IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
  set(  LIBGLES++_VERSION
	-0.2.0-debug
    )
  set(  FEDLIB_VER
        -3.1.1-debug
     )
  set(  LIBAVC++_VERSION
        -1.0.0-debug
     )
ELSE()
  set(  LIBGLES++_VERSION
	-0.2.0
    )
  set(  FEDLIB_VER
        -3.1.1
     )
  set(  LIBAVC++_VERSION
        -1.0.0
     )
ENDIF()

option (HAVE_NEON          "NEON technology"             OFF) 
option (HAVE_HARD_FLOAT    "Hard Float Support"          OFF) 
option (FORCE_PIC          "Force -fPIC option"           ON)
option (HAVE_OPENGL_ES_API "OPENGL ES API"               OFF)
option (TARGET_NV_CARD     "Target NV Card"              OFF)
option (USE_FREEIMAGE      "Build FreeImage loader"       ON)
option (USE_AVCPP          "Build avc++ loader"          OFF)
option (USE_DEVIL          "Build DevIL loader"          OFF)
option (BUILD_GLPLAYER     "Build gles++ libav player"   OFF)
option (BUILD_GLES_GUI     "Build gles++ gui test"        ON)


if (HAVE_NEON)
  add_definitions( -mfpu=neon )
endif (HAVE_NEON)

if (HAVE_HARD_FLOAT)
  add_definitions( -mfloat-abi=hard )
endif (HAVE_HARD_FLOAT)

if (FORCE_PIC)
  # This option is available since cmake  (VERSION 2.8.9)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif (FORCE_PIC)

if (HAVE_OPENGL_ES_API)
  add_definitions( -DOPENGL_ES_API )
endif (HAVE_OPENGL_ES_API)

if (TARGET_NV_CARD)
  add_definitions( -D_NV_CARD_ )
endif (TARGET_NV_CARD)


set(  LIBGLES++_INCLUDE 
        ./include/GLApplication.h
        ./include/GLAutoPtr.h
        ./include/GLAnimation.h
        ./include/GLCamera.h
        ./include/GLCanvas.h
        ./include/GLCommonDefs.h
        ./include/GLObject.h
        ./include/GLHandleObject.h
        ./include/GLShaderObject.h
        ./include/GLVertexShader.h 
        ./include/GLFragmentShader.h
        ./include/GLFont.h
        ./include/GLFontLoader.h
        ./include/GLFontLoaderException.h
        ./include/GLFpsSync.h
        ./include/GLImage.h
        ./include/GLMessage.h
        ./include/GLModel.h
        ./include/GLPosition.h
        ./include/GLProgram.h
        ./include/GLProgramsCollector.h
        ./include/GLResourcesCollector.h
        ./include/GLRect.h 
        ./include/GLReference.h
        ./include/GLSceneCameraNode.h
        ./include/GLSceneGraph.h
        ./include/GLSceneLayerNode.h
        ./include/GLSceneModelNode.h
        ./include/GLSceneNode.h
        ./include/GLSceneNodeBase.h
        ./include/GLSceneTextNode.h
        ./include/GLShape.h
        ./include/GLSize.h
        ./include/GLText.h
        ./include/GLTexture.h
        ./include/GLTransformationsMatrix.h
        ./include/GLViewPort.h
        ./include/GLWindow.h
        ./include/GLWindowEvents.h
        ./include/GLVertex.h  
        ./include/GLVertex.inl
        ./include/GLVertices.h 
        ./include/GLVertices.inl
        ./include/GLMonitor.h
)

set(  LIBGLES++_INCLUDE_FONT
        ./include/font/GLFreeTypeFont.h
        ./include/font/GLFreeTypeFontLoader.h
)

set(  LIBGLES++_INCLUDE_WIDGETS
        ./include/widgets/GLButton.h
        ./include/widgets/GLLabel.h
        ./include/widgets/GLLayer.h
        ./include/widgets/GLWidget.h
)

set(  LIBGLES++_SRC 
        ./src/GLApplication.cpp
        ./src/GLAnimation.cpp
        ./src/GLCamera.cpp
        ./src/GLCanvas.cpp
        ./src/GLObject.cpp
        ./src/GLHandleObject.cpp
        ./src/GLShaderObject.cpp 
        ./src/GLVertexShader.cpp 
        ./src/GLFragmentShader.cpp
        ./src/GLFont.cpp
        ./src/GLFontLoader.cpp
        ./src/GLFontLoaderException.cpp
        ./src/GLFpsSync.cpp
        ./src/GLImage.cpp
        ./src/GLMessage.cpp
        ./src/GLModel.cpp
        ./src/GLPosition.cpp
        ./src/GLProgram.cpp
        ./src/GLProgramsCollector.cpp
        ./src/GLResourcesCollector.cpp
        ./src/GLRect.cpp 
        ./src/GLReference.cpp
        ./src/GLSceneCameraNode.cpp
        ./src/GLSceneGraph.cpp
        ./src/GLSceneLayerNode.cpp
        ./src/GLSceneModelNode.cpp
        ./src/GLSceneNode.cpp
        ./src/GLSceneNodeBase.cpp
        ./src/GLSceneTextNode.cpp
        ./src/GLShape.cpp
        ./src/GLSize.cpp
        ./src/GLText.cpp
        ./src/GLTexture.cpp
        ./src/GLTransformationsMatrix.cpp
        ./src/GLViewPort.cpp
        ./src/GLWindow.cpp
        ./src/GLWindowEvents.cpp
        ./src/GLMonitor.cpp
)

if (USE_FREEIMAGE)
set(  LIBGLES++_SRC_FREEIMAGE   
        ./src/images/freeimage.c
)
endif (USE_FREEIMAGE)

if (USE_DEVIL)
set(  LIBGLES++_SRC_DEVIL
        ./src/images/devil.c
)
endif (USE_DEVIL)


set(  LIBGLES++_SRC_FONT   
        ./src/font/GLFreeTypeFont.cpp
        ./src/font/GLFreeTypeFontLoader.cpp
)

set(  LIBGLES++_SRC_WIDGETS 
        ./src/widgets/GLButton.cpp
        ./src/widgets/GLWidget.cpp
        ./src/widgets/GLLabel.cpp
        ./src/widgets/GLLayer.cpp
)

set(  LIBGLES++_LIBRARIES
      pthread
      fedlibrary${FEDLIB_VER}
      freetype
      sigc-2.0
)

if (USE_FREEIMAGE)
set(  LIBGLES++_FI_LIBRARIES
      freeimage
)
else()
set(  LIBGLES++_FI_LIBRARIES
)
endif (USE_FREEIMAGE)

if (USE_DEVIL)
set(  LIBGLES++_LI_LIBRARIES
      IL
)
else()
set(  LIBGLES++_LI_LIBRARIES
)
endif (USE_DEVIL)


set(  GLES_GUI_LIBRARIES
      glfw3
      rt
      Xcursor
      Xrandr
      Xi
      Xxf86vm
#	m
#	Xrender
      Xext
      X11
#	xcb
#	Xau
#	Xdmcp
      
)

if (HAVE_OPENGL_ES_API)
set( GL_LIBRARIES 
     EGL
     GLESv2
   )
else()
set( GL_LIBRARIES 
     GL 
   )
endif (HAVE_OPENGL_ES_API)


IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
add_definitions(
                -ggdb3
)
ENDIF()

add_definitions(
                -Wall
                -std=c++11
                -D__STDC_CONSTANT_MACROS
                -D_NO_FED_NAMESPACE
                -D_TRACING_EXCEPTION_RAISE
                -D_TRACING_EXCEPTION_CATCH
                -D_ENABLE_ERROR_INFO
                -D_ENABLE_LOG_INFO
                -D_ENABLE_RAW_INFO
                -D_ENABLE_METHOD_TRACING
                -D_ENABLE_VERBOSE_INFO 
                -D_ENABLE_ASSERTION_TRACING
		-DGLFW_INCLUDE_ES2
               )

# Enable using of FreeImage library in GLImage
IF(USE_FREEIMAGE)
add_definitions(
                -D_USE_FREEIMAGE
)
ENDIF(USE_FREEIMAGE)

IF(USE_AVCPP)
add_definitions(
                -D_USE_AVCPP
)
ENDIF(USE_AVCPP)

IF(USE_DEVIL)
add_definitions(
                -D_USE_DEVIL
)
ENDIF(USE_DEVIL)

add_library   ( gles++${LIBGLES++_VERSION}  SHARED  ${LIBGLES++_SRC} ${LIBGLES++_SRC_FREEIMAGE} ${LIBGLES++_SRC_DEVIL} ${LIBGLES++_SRC_FONT} ${LIBGLES++_SRC_WIDGETS} )

if (BUILD_GLPLAYER)
add_executable( glplayer                     ${LIBGLES++_SRC} ${LIBGLES++_SRC_FREEIMAGE} ${LIBGLES++_SRC_DEVIL} ${LIBGLES++_SRC_FONT} ${LIBGLES++_SRC_WIDGETS} glplayer.cpp )
endif()
if (BUILD_GLES_GUI)
add_executable( gles-gui                     ${LIBGLES++_SRC} ${LIBGLES++_SRC_FREEIMAGE} ${LIBGLES++_SRC_DEVIL} ${LIBGLES++_SRC_FONT} ${LIBGLES++_SRC_WIDGETS} gles-gui.cpp )
endif()

target_link_libraries( gles++${LIBGLES++_VERSION}  ${LIBGLES++_LIBRARIES} ${LIBGLES++_FI_LIBRARIES} ${LIBGLES++_LI_LIBRARIES} )

if (BUILD_GLPLAYER)
target_link_libraries( glplayer                    ${LIBGLES++_LIBRARIES} ${LIBGLES++_FI_LIBRARIES} ${LIBGLES++_LI_LIBRARIES} ${GLPLAYER_LIBRARIES} ${GL_LIBRARIES}  )
endif()
if (BUILD_GLES_GUI)
target_link_libraries( gles-gui                    ${LIBGLES++_LIBRARIES} ${LIBGLES++_FI_LIBRARIES} ${LIBGLES++_LI_LIBRARIES} ${GLES_GUI_LIBRARIES} ${GL_LIBRARIES}  )
endif()

install( TARGETS gles++${LIBGLES++_VERSION}  LIBRARY DESTINATION lib                       )
install( FILES   ${LIBGLES++_INCLUDE}                DESTINATION include/libgles++         )
install( FILES   ${LIBGLES++_INCLUDE_FONT}           DESTINATION include/libgles++/font    )
install( FILES   ${LIBGLES++_INCLUDE_WIDGETS}        DESTINATION include/libgles++/widgets )



