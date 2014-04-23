/*
    gles plus plus
    Copyright (C) 2013 <fedagostino@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "../include/GLWindowEvents.h"
#include "../include/GLWindow.h"

GLWindowEvents::GLWindowEvents()
{
  
}

GLWindowEvents::~GLWindowEvents()
{
}

VOID     GLWindowEvents::OnCreating( GLWindow* pGlWindow )
{
#if defined(OPENGL_ES_API)  
  glfwWindowHint( GLFW_CLIENT_API           , GLFW_OPENGL_ES_API );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2                  );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0                  );
#endif
}

VOID     GLWindowEvents::OnPositionChanged( GLWindow* pGlWindow, INT iPosX, INT iPosY )
{ 
  
}

VOID     GLWindowEvents::OnSizeChanged( GLWindow* pGlWindow, INT iWidth, INT iHeight )
{ 
  
}

VOID     GLWindowEvents::OnFbSizeChanged( GLWindow* pGlWindow, INT iWidth, INT iHeight )
{ 
  
}

VOID     GLWindowEvents::OnClose( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnRefresh( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnGotFocus( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnLostFocus( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnIconified( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnRestored( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnMouseButtonPressed( GLWindow* pGlWindow, int iButton, int iMods )
{ 
  
}

VOID     GLWindowEvents::OnMouseButtonReleased( GLWindow* pGlWindow, int iButton, int iMods )
{ 
  
}

VOID     GLWindowEvents::OnMouseMove( GLWindow* pGlWindow, double dPosX, double dPosY )
{ 
  
}

VOID     GLWindowEvents::OnMouseEnter( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnMouseLeave( GLWindow* pGlWindow )
{ 
  
}

VOID     GLWindowEvents::OnMouseScroll( GLWindow* pGlWindow, double dOffsetX, double dOffsetY )
{ 
  
}

VOID     GLWindowEvents::OnKeyReleased( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
{ 
  
}

VOID     GLWindowEvents::OnKeyPressed( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods ) 
{
  if ( iKey == GLFW_KEY_ESCAPE )
    pGlWindow->close();
}

VOID     GLWindowEvents::OnKeyRepeated( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
{
  
}

VOID     GLWindowEvents::OnUnicodeChar( GLWindow* pGlWindow, UINT iCodePoint )
{
  
}

  
  