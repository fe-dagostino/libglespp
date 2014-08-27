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

class GLLayer : public GLReference, public GLWidget, public GLWindowEvents
{
  ENABLE_FRTTI( GLLayer )
public:
 
  /***/
  GLLayer( GLViewPort& rViewPort );
  /***/
  virtual ~GLLayer();
    
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
  virtual VOID     OnKeyReleased( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods ); 
  /**
   * Default implementation will close widows when ESCAPE key went pressed.
   */
  virtual VOID     OnKeyPressed( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods ); 
  /***/
  virtual VOID     OnKeyRepeated( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods ); 
  /***/
  virtual VOID     OnUnicodeChar( GLWindow* pGlWindow, UINT iCodePoint ); 
  
private:
  
};

#endif // GLLAYER_H
