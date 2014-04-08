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


#ifndef GLLAYER_H
#define GLLAYER_H

#include "GLCommonDefs.h"
#include "GLViewPort.h"
#include "GLReference.h"
#include "GLProgram.h"
#include "GLCanvas.h"
#include "GLWidget.h"

#include "FObject.h"

USING_NAMESPACE_FED

class GLLayer : public GLReference, protected GLWidget, public GLWindowEvents
{
public:
 
  /***/
  GLLayer( GLViewPort& rViewPort );
  /***/
  virtual ~GLLayer();
  
  using GLWidget::getParent;
  
  using GLWidget::addChild;
  using GLWidget::getChildren;
  
  using GLWidget::isVisible;
  using GLWidget::setVisible;
  
  using GLWidget::setPosition;  
  using GLWidget::getPosition;
  
  using GLWidget::setSize;
  using GLWidget::getSize;
  
  using GLWidget::getClientArea;
  
  using GLWidget::hasBackground;
  
  using GLWidget::setBackground;
 
  using GLWidget::getBkColor;
  
  using GLWidget::getBkImage;
  
  /***/
  inline GLViewPort&    getViewPort()
  { return m_rViewPort; }
  
  /***/
  BOOL                  render( const glm::mat4& mvp );

  
/// Implements GLWindowEvents
protected:
  
  /**
   * Called in just before windows creation.
   * It will be a nice place to see own window hints
   */
  virtual VOID     OnCreating( GLWindow* pGlWindow );
  /**
   * Called to notify new window position.
   */
  virtual VOID     OnPositionChanged( GLWindow* pGlWindow, INT iPosX, INT iPosY );
  /**
   * Called to notify new window size.
   */
  virtual VOID     OnSizeChanged( GLWindow* pGlWindow, INT iWidth, INT iHeight );
  /**
   * Called to notify new window size.
   */
  virtual VOID     OnFbSizeChanged( GLWindow* pGlWindow, INT iWidth, INT iHeight );
  /**
   * Called when user attempt to close the window.
   */
  virtual VOID     OnClose( GLWindow* pGlWindow );
  /**
   * Called when the window whose content needs to be refreshed.
   */
  virtual VOID     OnRefresh( GLWindow* pGlWindow );
  /***/  
  virtual VOID     OnGotFocus( GLWindow* pGlWindow );
  /***/
  virtual VOID     OnLostFocus( GLWindow* pGlWindow );
  /***/  
  virtual VOID     OnIconified( GLWindow* pGlWindow );
  /***/
  virtual VOID     OnRestored( GLWindow* pGlWindow );
  /***/
  virtual VOID     OnMouseButtonPressed( GLWindow* pGlWindow, int iButton, int iMods );
  /***/
  virtual VOID     OnMouseButtonReleased( GLWindow* pGlWindow, int iButton, int iMods );
  /***/
  virtual VOID     OnMouseMove( GLWindow* pGlWindow, double dPosX, double dPosY );
  /***/
  virtual VOID     OnMouseEnter( GLWindow* pGlWindow );
  /***/
  virtual VOID     OnMouseLeave( GLWindow* pGlWindow );
  /***/
  virtual VOID     OnMouseScroll( GLWindow* pGlWindow, double dOffsetX, double dOffsetY );
  /***/
  virtual VOID     OnKeyReleased( GLWindow* pGlWindow, INT iKey, INT iScanCode ); 
  /**
   * Default implementation will close widows when ESCAPE key went pressed.
   */
  virtual VOID     OnKeyPressed( GLWindow* pGlWindow, INT iKey, INT iScanCode ); 
  /***/
  virtual VOID     OnKeyRepeated( GLWindow* pGlWindow, INT iKey, INT iScanCode ); 
  /***/
  virtual VOID     OnUnicodeChar( GLWindow* pGlWindow, UINT iCodePoint ); 
  
private:
  GLViewPort&       m_rViewPort;
  

  
};

#endif // GLLAYER_H
