/*
    This file is part of lib gles plus plus.

    libgles++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libgles++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libgles++.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "GLCommonDefs.h"
#include "FString.h"
#include "FTMailbox.tlh"
#include "GLObject.h"
#include "GLWindowEvents.h"
#include "GLMessage.h"

#include "GLFW/glfw3.h"

#include <vector>
#include <functional>

#include <sigc++/sigc++.h>

USING_NAMESPACE_FED


class GLWindow : public GLObject
{
public:
  enum GLFlags
  {
    eWindowShouldClose = 0x00000001
  };
  
  enum GLProcessingFlags
  {
    epfCalling = 0x0000,    // Call will be executed by calling thread.    
    epfEnqueue = 0x0001,    // Call will be enqueued in order to be processed by @processMessage method
    epfWait    = 0x0002     // If specified it will wait for the message to be processed. This must be 
                            // used together with epfEnqueue
  };
  
  /***/
  GLWindow();

  /***/
  ~GLWindow();
  
  /**
   * Initialize events interface in order to raise window events.
   * This function should be called before create in order to handle 
   * also creation related events.
   */
  BOOL                                  connect( GLWindowEvents* pEvents );
  /***/
  const std::vector<GLWindowEvents*>&   getConnections() const;
  
  /***/
  BOOL             create( const FString& sTitle, INT iPosX, INT iPosY, INT iWidth, INT iHeight, WORD wFlags = epfCalling );
  /***/
  BOOL             createFullScreen( const FString& sMonitor, const FString& sTitle, INT iWidth, INT iHeight, WORD wFlags = epfCalling );
  /***/
  BOOL             show( WORD wFlags = epfCalling );
  /***/
  BOOL             hide( WORD wFlags = epfCalling );
  /**
   * Return TRUE if windows is in windowed mode or FALSE if window is in full screen mode. 
   */
  BOOL             isWindowed();
  /***/
  BOOL             setTitle( const FString& sTitle, WORD wFlags = epfCalling );
  /***/
  BOOL             setPosition( INT iPosX, INT iPosY, WORD wFlags = epfCalling );
  /***/
  BOOL             setSize( INT iWidth, INT iHeight, WORD wFlags = epfCalling );
  /***/
  BOOL             getFramebufferSize( INT & iWidth, INT & iHeight );
  /***/
  BOOL             showNormal( WORD wFlags = epfCalling );
  /***/
  BOOL             showMinimized( WORD wFlags = epfCalling );
  /**
   *  It is possible to select the minimum number of monitor refreshes the driver should wait 
   *  before swapping the buffers:
   */
  BOOL             setSwapInterval( int iRefresh );
  /***/
  BOOL             swapBuffers();
  /***/
  BOOL             close();
  /***/
  BOOL             destroy( WORD wFlags = epfCalling );
  /***/
  INT              getInputMode( int iMode );
  /***/
  BOOL             setInputMode( int iMode, int iValue );
  
  /***/
  BOOL             getCursorPosition( double* dPosX, double* dPosY );
  /***/
  BOOL             setCursorPosition( double dPosX, double dPosY );
  
  /**
   */
  BOOL             check( DWORD dwFlags );
  
  /**
   * Return TRUE if a message has been processed, FALSE if message queue was empty.
   */
  BOOL             processMessage();
  
  /**
   */  
  BOOL             sendMessage( GLMessage* pMessage );
  /**
   */
  BOOL             postMessage( GLMessage* pMessage );
  
protected:
  /***/
  VOID             setWindowHint( int iTarget, int iHint );
  
private:
  /***/
  static void pos_callback (GLFWwindow* window, int xpos, int ypos );
  /***/
  static void size_callback(GLFWwindow* window, int width, int height );
  /***/
  static void close_callback(GLFWwindow* window );
  /***/
  static void refresh_callback(GLFWwindow* window );
  /***/
  static void focus_callback(GLFWwindow* window, int focus );
  /***/
  static void iconify_callback(GLFWwindow* window, int iconified );
  /***/
  static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
  /***/
  static void char_callback(GLFWwindow* window, unsigned int codepoint );
  /***/
  static void fbsize_callback(GLFWwindow* window, int width, int height );
  /***/
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods );
  /***/
  static void mouse_pos_callback (GLFWwindow* window, double xpos, double ypos );
  /***/
  static void mouse_enter_callback (GLFWwindow* window, int entered );
  /***/
  static void mouse_scroll_callback (GLFWwindow* window, double xoffset, double yoffset );

private:
  /***/
  void            setCallbacks( bool bRegister );
  
protected:
  std::vector<GLWindowEvents*>   m_vEvents;
  
private:
  GLFWwindow*               m_hWindow;
  FTMailbox<GLMessage*>     m_mbxMessages;
  FString                   m_sTitle;
};

#endif // GLWINDOW_H
