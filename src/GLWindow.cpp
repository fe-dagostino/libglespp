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


#include "../include/GLWindow.h"
#include "../include/GLApplication.h"
#include "../include/GLMessage.h"

GENERATE_CLASSINFO( GLWindow, GLObject )

/**
 * Specialized message class intended to be used for showing window if hidden.
 */
class GLWShow : public GLMessage
{
public:
  GLWShow( GLWindow* pWindow )
   : GLMessage( pWindow )
  {
  }
  
  virtual ~GLWShow()
  {}
  
  BOOL OnExecute()
  {
    return m_pWindow->show( GLWindow::epfCalling );
  }
};

/**
 * Specialized message class intended to be used for hidding the window.
 */
class GLWHide : public GLMessage
{
public:
  GLWHide( GLWindow* pWindow )
   : GLMessage( pWindow )
  {
  }
  
  virtual ~GLWHide()
  {}
  
  BOOL OnExecute()
  {
    return m_pWindow->hide( GLWindow::epfCalling );
  }
};


/**
 * Specialized message class intended to be used for creating a new window.
 */
class GLWCreate : public GLMessage
{
public:
  GLWCreate( GLWindow* pWindow, GLWindowOptions* pOptions )
    : GLMessage( pWindow ), m_ptrWinOptions( pOptions )
  {
    
  }
  
  virtual ~GLWCreate()
  {}
  
  BOOL OnExecute()
  {
    return m_pWindow->create( m_ptrWinOptions, GLWindow::epfCalling );
  }
  
private:
  GLAutoPtr<GLWindowOptions> m_ptrWinOptions;

};

/**
 * Specialized message class intended to be used for updating window title.
 */
class GLWSetTitle : public GLMessage
{
public:
  GLWSetTitle( GLWindow* pWindow, const FString& sTitle )
   : GLMessage( pWindow ), m_sTitle( sTitle )
  {
  }
  
  virtual ~GLWSetTitle()
  {}
  
  virtual BOOL OnExecute()
  {
    return m_pWindow->setTitle( m_sTitle, GLWindow::epfCalling );
  }
  
private:
  const FString  m_sTitle;
  
};

/**
 * Specialized message class intended to be used for updating window position.
 */
class GLWSetPosition : public GLMessage
{
public:
  GLWSetPosition( GLWindow* pWindow, int xpos, int ypos )
   : GLMessage( pWindow ), m_xpos(xpos), m_ypos(ypos)
  {
  }
  
  virtual ~GLWSetPosition()
  {}
  
  virtual BOOL OnExecute()
  {
    return m_pWindow->setPosition( m_xpos, m_ypos, GLWindow::epfCalling );
  }
  
private:
  int m_xpos;
  int m_ypos;
};

/**
 * Specialized message class intended to be used for updating window size.
 */
class GLWSetSize : public GLMessage
{
public:
  GLWSetSize( GLWindow* pWindow, int width, int height )
   : GLMessage( pWindow ), m_width(width), m_height(height)
  {
  }
  
  virtual ~GLWSetSize()
  {}
  
  virtual BOOL OnExecute()
  {
    return m_pWindow->setSize( m_width, m_height, GLWindow::epfCalling );
  }
  
private:
  int m_width;
  int m_height;
};

/**
 * Specialized message class intended to be used to restore window.
 */
class GLWShowNormal : public GLMessage
{
public:
  GLWShowNormal( GLWindow* pWindow )
   : GLMessage( pWindow )
  {
  }
  
  virtual ~GLWShowNormal()
  {}
  
  virtual BOOL OnExecute()
  {
    return m_pWindow->showNormal( GLWindow::epfCalling );
  }
  
};

/**
 * Specialized message class intended to be used to iconify window.
 */
class GLWShowMinimized : public GLMessage
{
public:
  GLWShowMinimized( GLWindow* pWindow )
   : GLMessage( pWindow )
  {
  }
  
  virtual ~GLWShowMinimized()
  {}
  
  BOOL OnExecute()
  {
    return m_pWindow->showMinimized( GLWindow::epfCalling );
  }
  
};

/**
 * Specialized message class intended to be destroy window.
 */
class GLWDestroy : public GLMessage
{
public:
  GLWDestroy( GLWindow* pWindow )
   : GLMessage( pWindow )
  {
  }
  
  virtual ~GLWDestroy()
  {}
  
  BOOL OnExecute()
  {
    return m_pWindow->destroy( GLWindow::epfCalling );
  }
  
};

///////////////////////////////////////////////////////////////

void GLWindow::pos_callback(GLFWwindow* window, int xpos, int ypos )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnPositionChanged( pWindow, xpos, ypos );
    }
  }  
}

void GLWindow::size_callback(GLFWwindow* window, int width, int height )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnSizeChanged( pWindow, width, height );
    }
  }  
}
 
void GLWindow::close_callback(GLFWwindow* window )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnClose( pWindow );
    }    
  }  
}

void GLWindow::refresh_callback(GLFWwindow* window )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnRefresh( pWindow );
    }    
  }  
}
 
void GLWindow::focus_callback(GLFWwindow* window, int focus )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      if ( focus == GL_TRUE )
        e->OnGotFocus( pWindow );
      else
        e->OnLostFocus( pWindow );
    }    
  }  
}

void GLWindow::iconify_callback(GLFWwindow* window, int iconified )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      if ( iconified == GL_TRUE )
        e->OnIconified( pWindow );
      else
        e->OnRestored( pWindow );
    }
  }  
}

void GLWindow::fbsize_callback(GLFWwindow* window, int width, int height )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnFbSizeChanged( pWindow, width, height );
    }
  }  
}

void GLWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      switch ( action )
      {
        case GLFW_PRESS:
	  e->OnMouseButtonPressed( pWindow, button, mods );
        break;
        case GLFW_RELEASE:
	  e->OnMouseButtonReleased( pWindow, button, mods );
        break;
      }
    }
  }  
}

void GLWindow::mouse_pos_callback (GLFWwindow* window, double xpos, double ypos )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnMouseMove( pWindow, xpos, ypos );
    }
  }  
}

void GLWindow::mouse_enter_callback (GLFWwindow* window, int entered )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      if ( entered == GL_TRUE )
        e->OnMouseEnter( pWindow );
      else
        e->OnMouseLeave( pWindow );
    }
  }  
}

void GLWindow::mouse_scroll_callback (GLFWwindow* window, double xoffset, double yoffset )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnMouseScroll( pWindow, xoffset, yoffset );
    }
  }  
}


void GLWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      switch( action )
      {
        case GLFW_RELEASE:
	  e->OnKeyReleased( pWindow, key, scancode, mods );
        break;
        case GLFW_PRESS:
	  e->OnKeyPressed( pWindow, key, scancode, mods );
        break;
        case GLFW_REPEAT:
	  e->OnKeyRepeated( pWindow, key, scancode, mods );
        break;
      }
    }
  }
}

void GLWindow::char_callback(GLFWwindow* window, unsigned int codepoint )
{
  GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer( window );
  
  if ( pWindow != nullptr )
  {
    for ( auto e : pWindow->getConnections() )
    {
      e->OnUnicodeChar( pWindow, codepoint );
    }
  }
}


GLWindow::GLWindow()
 : m_hWindow( nullptr ), m_mbxMessages( "GLWindow Mailbox", nullptr ) 
{
  
}

GLWindow::~GLWindow()
{
  destroy();
}

BOOL  GLWindow::connect( GLWindowEvents* pEvents )
{
  for ( auto e : m_vEvents )
  {
    if ( e == pEvents )
      return FALSE;
  }
  
  m_vEvents.push_back( pEvents );
  
  return TRUE;
}

const std::vector<GLWindowEvents*>&   GLWindow::getConnections() const
{
  return m_vEvents;
}

BOOL             GLWindow::create( GLWindowOptions* pOpts, WORD wFlags )
{
  if ((m_hWindow != nullptr) || (pOpts == nullptr))
    return FALSE;
  
  m_ptrWinOptions = pOpts;
  
  if ( wFlags & epfEnqueue )
  {
    BOOL bResult = TRUE;
    
    GLWCreate* pMessage  = new GLWCreate( this, pOpts );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
    
    return bResult;
  }

  m_glRenderer = new GLRenderer();
  if ( m_glRenderer == nullptr )
    return FALSE;
  
  // Full Screen monitor
  GLFWmonitor* pFsMonitor = nullptr;
  
  if ( ! m_ptrWinOptions->getMonitor().IsEmpty() )
  {
    pFsMonitor                = glfwGetPrimaryMonitor(); // Set Default
    const GLMonitor* pMonitor = GLApplication::GetInstance().getMonitorByName( m_ptrWinOptions->getMonitor() );
    if ( pMonitor != nullptr )
    {
      pFsMonitor = (GLFWmonitor*)pMonitor->m_pGlfwMonitor;
    }
   
    // Set Refresh rate accordingly with video mode max refresh rate
    glfwWindowHint( GLFW_REFRESH_RATE, 0 );
  }
  else
  {
    // For windowed mode initial state will be not visible.
    glfwWindowHint( GLFW_VISIBLE              , GL_FALSE           );
  }
  
  // Raise event for custom settings
  for ( auto e : getConnections() )
  {
    e->OnCreating( this );
  }

  m_hWindow = glfwCreateWindow( 
                                m_ptrWinOptions->getWidth(), m_ptrWinOptions->getHeight(),
			        m_ptrWinOptions->getTitle().GetBuffer(),
			        pFsMonitor, 
			        nullptr
			      );

  if (!m_hWindow)
  {
    delete m_glRenderer;
    m_glRenderer = nullptr;
    
    glfwTerminate();
    return FALSE;
  }

  // Only in windowed mode it is necessary to move window
  // and to make it visible after move.
  if ( pFsMonitor == nullptr )
  {
    glfwSetWindowPos( m_hWindow, m_ptrWinOptions->getPosX(), m_ptrWinOptions->getPosY() );
    
    glfwShowWindow( m_hWindow );
  }
  
  glfwMakeContextCurrent( m_hWindow );
  
  glfwSetWindowUserPointer( m_hWindow, this );
  
  setCallbacks(true);
  
  return TRUE;
  
}

GLRenderer*      GLWindow::getRenderer()
{ return m_glRenderer; }

BOOL             GLWindow::show( WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwShowWindow( m_hWindow );
    return TRUE;
  }

  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWShow( this );
    
    if (wFlags & epfWait)
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;
}

BOOL             GLWindow::hide( WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwHideWindow( m_hWindow );
    return TRUE;
  }

  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWHide( this );
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;
}

BOOL             GLWindow::isWindowed()
{
  if ( m_hWindow == nullptr )
    return FALSE;

  return ( glfwGetWindowMonitor( m_hWindow ) == nullptr );
}

BOOL             GLWindow::setTitle( const FString& sTitle, WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwSetWindowTitle( m_hWindow, sTitle.GetBuffer() );
    return TRUE;
  }

  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWSetTitle( this, sTitle );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;
}

BOOL             GLWindow::setPosition( INT iPosX, INT iPosY, WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwSetWindowPos( m_hWindow, iPosX, iPosY );
    return TRUE;
  }
  
  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWSetPosition( this, iPosX, iPosY );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;  
}

BOOL             GLWindow::setSize( INT iWidth, INT iHeight, WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwSetWindowSize( m_hWindow, iWidth, iHeight );
    return TRUE;
  }

  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWSetSize( this, iWidth, iHeight );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;  
}

BOOL             GLWindow::getFramebufferSize( INT & iWidth, INT & iHeight )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  glfwGetFramebufferSize( m_hWindow, &iWidth, &iHeight );
  
  return TRUE;
}

BOOL             GLWindow::showNormal( WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwRestoreWindow( m_hWindow );
    return TRUE;
  }

  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWShowNormal( this );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;
}

BOOL             GLWindow::showMinimized( WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  if ( wFlags == epfCalling )
  {
    glfwIconifyWindow( m_hWindow );
    return TRUE;
  }
  
  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWShowMinimized( this );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;
}

BOOL             GLWindow::setSwapInterval( int iRefresh )
{
  if ( m_hWindow == nullptr )
    return FALSE;
  
  glfwSwapInterval(iRefresh);
  
  return TRUE;
}

BOOL             GLWindow::swapBuffers()
{
  if ( m_hWindow == nullptr )
    return FALSE;
  
  glfwSwapBuffers(m_hWindow);
  
  return TRUE;
}

BOOL             GLWindow::close()
{
  if ( m_hWindow == nullptr )
    return FALSE;

  glfwSetWindowShouldClose( m_hWindow, GL_TRUE );
    
  return TRUE;
}

BOOL             GLWindow::destroy( WORD wFlags )
{
  if ( m_hWindow == nullptr )
    return FALSE;
  
  if ( wFlags == epfCalling )
  {
    delete m_glRenderer;
    m_glRenderer = nullptr;
  
    setCallbacks( false );
    
    glfwDestroyWindow(m_hWindow);
    m_hWindow = nullptr;
    
    return TRUE;
  }

  BOOL bResult = FALSE;
  if ( wFlags & epfEnqueue )
  {
    GLMessage* pMessage  = new GLWDestroy( this );
    
    if ( wFlags & epfWait )
      bResult = sendMessage( pMessage );
    else
      bResult = postMessage( pMessage );
  }
  
  return bResult;
}

INT              GLWindow::getInputMode( int iMode )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  return glfwGetInputMode( m_hWindow, iMode );
}

BOOL             GLWindow::setInputMode( int iMode, int iValue )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  glfwSetInputMode( m_hWindow, iMode, iValue );
  
  return TRUE;
}

BOOL             GLWindow::getCursorPosition( double* dPosX, double* dPosY )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  glfwGetCursorPos( m_hWindow, dPosX, dPosY );

  return TRUE;
}

BOOL             GLWindow::setCursorPosition( double dPosX, double dPosY )
{
  if ( m_hWindow == nullptr )
    return FALSE;

  glfwSetCursorPos( m_hWindow, dPosX, dPosY );
  
  return TRUE;
}
  
VOID             GLWindow::setWindowHint(int iTarget, int iHint)
{
  glfwWindowHint( iTarget, iHint );
}
 
void           GLWindow::setCallbacks( bool bRegister )
{
  if ( bRegister )
  {
    glfwSetWindowPosCallback      ( m_hWindow, pos_callback          );
    glfwSetWindowSizeCallback     ( m_hWindow, size_callback         );
    glfwSetWindowCloseCallback    ( m_hWindow, close_callback        );
    glfwSetWindowRefreshCallback  ( m_hWindow, refresh_callback      );
    glfwSetWindowFocusCallback    ( m_hWindow, focus_callback        );
    glfwSetWindowIconifyCallback  ( m_hWindow, iconify_callback      );
    glfwSetFramebufferSizeCallback( m_hWindow, fbsize_callback       );
    glfwSetMouseButtonCallback    ( m_hWindow, mouse_button_callback );
    glfwSetCursorPosCallback      ( m_hWindow, mouse_pos_callback    );
    glfwSetCursorEnterCallback    ( m_hWindow, mouse_enter_callback  );
    glfwSetScrollCallback         ( m_hWindow, mouse_scroll_callback );
    glfwSetKeyCallback            ( m_hWindow, key_callback          );
    glfwSetCharCallback           ( m_hWindow, char_callback         );
  } 
  else
  {
    glfwSetWindowPosCallback      ( m_hWindow, nullptr );
    glfwSetWindowSizeCallback     ( m_hWindow, nullptr );
    glfwSetWindowCloseCallback    ( m_hWindow, nullptr );
    glfwSetWindowRefreshCallback  ( m_hWindow, nullptr );
    glfwSetWindowFocusCallback    ( m_hWindow, nullptr );
    glfwSetWindowIconifyCallback  ( m_hWindow, nullptr );
    glfwSetFramebufferSizeCallback( m_hWindow, nullptr );
    glfwSetMouseButtonCallback    ( m_hWindow, nullptr );
    glfwSetCursorPosCallback      ( m_hWindow, nullptr );
    glfwSetCursorEnterCallback    ( m_hWindow, nullptr );
    glfwSetScrollCallback         ( m_hWindow, nullptr );
    glfwSetKeyCallback            ( m_hWindow, nullptr );
    glfwSetCharCallback           ( m_hWindow, nullptr );
  }
}

BOOL           GLWindow::check( DWORD dwFlags )
{
  if (dwFlags & eWindowShouldClose)    
    return glfwWindowShouldClose( m_hWindow );
  
  return FALSE;
}

BOOL           GLWindow::processMessage()
{
  GLMessage* pMessage = m_mbxMessages.Read(0);
  if (pMessage == nullptr )
    return FALSE;
    
  BOOL bResult = pMessage->execute();
  if ( pMessage->release() )
    delete pMessage;
  
  return bResult;
}

BOOL             GLWindow::sendMessage( GLMessage* pMessage )
{
  if ( pMessage == nullptr )
    return FALSE;

  pMessage->event();
  
  m_mbxMessages.Write( pMessage );
  
  // Wait until event will be processed.
  pMessage->wait();
  
  delete pMessage;
  
  return TRUE;
}

BOOL             GLWindow::postMessage( GLMessage* pMessage )
{
  if ( pMessage == nullptr )
    return FALSE;
  
  m_mbxMessages.Write( pMessage );
  
  return TRUE;
}


  
  