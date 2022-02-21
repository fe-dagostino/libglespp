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


#include "widgets/GLLayer.h"

GENERATE_CLASSINFO( GLLayer, GLWidget )


GLLayer::GLLayer( GLViewPort& rViewPort )
 : GLWidget(nullptr)
{
  GLint    x,y = 0;
  GLsizei  w,h = 0;
  
  rViewPort.getArea( x, y, w, h );
  
  setPosition( x, y, FALSE );
  setSize( w, h, FALSE );
}

GLLayer::~GLLayer()
{

}


BOOL    GLLayer::render( const glm::mat4& mvp )
{
  if ( isVisible() == FALSE )
    return FALSE;
  
  GLRecti cliRect( getPosition().x, getPosition().y, getSize().width, getSize().height );
  
  return draw( mvp, cliRect );
}

/// Implements GLWindowEvents
  
VOID   GLLayer::OnCreating( GLWindow* pGlWindow )
{
  
}

VOID   GLLayer::OnPositionChanged( GLWindow* pGlWindow, INT iPosX, INT iPosY )
{
  
}

VOID   GLLayer::OnSizeChanged( GLWindow* pGlWindow, INT iWidth, INT iHeight )
{
  
}

VOID   GLLayer::OnFbSizeChanged( GLWindow* pGlWindow, INT iWidth, INT iHeight )
{
  
}

VOID   GLLayer::OnClose( GLWindow* pGlWindow )
{
  
}

VOID   GLLayer::OnRefresh( GLWindow* pGlWindow )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnGotFocus( GLWindow* pGlWindow )
{
  
}

VOID   GLLayer::OnLostFocus( GLWindow* pGlWindow )
{
  
}

VOID   GLLayer::OnIconified( GLWindow* pGlWindow )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnRestored( GLWindow* pGlWindow )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnMouseButtonPressed( GLWindow* pGlWindow, int iButton, int iMods )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnMouseButtonReleased( GLWindow* pGlWindow, int iButton, int iMods )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnMouseMove( GLWindow* pGlWindow, double dPosX, double dPosY )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnMouseEnter( GLWindow* pGlWindow )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnMouseLeave( GLWindow* pGlWindow )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnMouseScroll( GLWindow* pGlWindow, double dOffsetX, double dOffsetY )
{
  if ( isEnabled() == FALSE )
    return;
  
}

VOID   GLLayer::OnKeyReleased( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
{
  if ( isEnabled() == FALSE )
    return;
 
  // Propagate event to all registered functions even 
  // there is no focus.
  signalKeyReleased.emit( pGlWindow, this, iKey, iScanCode, wMods );
}

VOID   GLLayer::OnKeyPressed( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
{
  if ( isEnabled() == FALSE )
    return;
  
  if ( iKey == GLFW_KEY_TAB )
  {
    stepFocus();
  }
  
  // Propagate event to all registered functions even 
  // there is no focus.
  signalKeyPressed.emit( pGlWindow, this, iKey, iScanCode, wMods );
}

VOID   GLLayer::OnKeyRepeated( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
{
  if ( isEnabled() == FALSE )
    return;
  
  if ( iKey == GLFW_KEY_TAB )
  {
    stepFocus();
  }
  
  // Propagate event to all registered functions even 
  // there is no focus.
  signalKeyRepeated.emit( pGlWindow, this, iKey, iScanCode, wMods );
}

VOID   GLLayer::OnUnicodeChar( GLWindow* pGlWindow, UINT iCodePoint )
{
  if ( isEnabled() == FALSE )
    return;
  
}

