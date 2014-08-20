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


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "GLCommonDefs.h"
#include "GLSize.h"
#include "GLRect.h"
#include "GLCanvas.h"
#include "GLPosition.h"
#include "GLWindow.h"
#include "GLImage.h"

#include "FObject.h"

#include <vector>

#include <sigc++/sigc++.h>

USING_NAMESPACE_FED


class GLLayer;
class GLViewPort;

class GLWidget : public GLCanvas, public sigc::trackable
{
  ENABLE_FRTTI( GLWidget )
public:
  /***/
  enum BackgroundType
  {
    NoBackground,
    SolidColor,
    ImageBrush
  };
  /***/
  enum BackgroundOptions
  {
    eboUndefined,
    eboOriginal,
    eboFlipHorizontal,
    eboFlipVertical,
    eboFlipBoth
  };
  
  /**
   */
  GLWidget( GLWidget* pParent );
  /**
   */
  virtual ~GLWidget();
  
  /***/
  inline GLWidget*               getParent()
  { return m_pParent; }
    
  /***/
  BOOL                           addChild( GLWidget* widget );
  
  /***/
  inline std::vector<GLWidget*>& getChildren()
  { return m_vChildren; }
  
  /**
   * @return TRUE if layer is visible.
   */
  inline BOOL                    isVisible() const
  { return m_bVisible;     }
  /**
   * Set if layer is visible or not. When not visible render is disabled.
   */
  inline VOID                    setVisible( BOOL bVisible )
  { m_bVisible = bVisible; }  
  
  /**
   * @return TRUE if widget is enabled, so it will be receive envents
   *         like keys, mouse and so on.
   */
  inline BOOL                    isEnabled() const
  { return m_bEnabled;     }
  /***/
  inline VOID                    setEnabled( BOOL bEnabled )
  { m_bEnabled = bEnabled;     }
  
  /**
   * @return TRUE if it is referred by parent window as current focused.
   * @return FALSE if the widget has no parent or focus is on an other widget.
   */
  BOOL                           hasFocus() const;
  /**
   * Must be reimplemented at specialized class in order to
   * return a value that differs from defalut FALSE.
   * Return value should be TRUE if current widget or its children
   * can take the focus.
   */
  virtual BOOL                   isFocusable() const
  { return FALSE; }
  
  /***/
  VOID                           setPosition( const GLPosition& pos );  
  /***/
  VOID                           setPosition( GLint x, GLint y );
  /***/
  inline const GLPosition&       getPosition() const
  { return m_pos; }
  
  /***/
  VOID                           setSize( const GLSize& size );
  /***/
  VOID                           setSize( GLsizei width, GLsizei height );  
  /***/
  inline const GLSize&           getSize()
  { return m_size; }
  
  /**
   */
  VOID                           getClientArea( GLRecti& rect );
  
  /***/    
  inline BOOL                    hasBackground() const
  { return (m_eBackground!=NoBackground); }
  
  /***/
  VOID                           setBackground( const glm::vec4& cr );

  /**
   * @bo  usually image loaded from files needs a vertival flip in order to be shown as original.
   *      The reason is related to format type used to store image where images are store starting
   *      from the bottom line in the image.
   */
  VOID                           setBackground( GLTexture* texture, BackgroundOptions bo );
  
  inline const glm::vec4&        getBkColor() const
  { return m_crBackground;   }
  inline const GLTexture*        getBkImage() const
  { return m_imBackground;   }
  
  /***/
  BOOL                           draw( const glm::mat4& mvp, const GLRecti& rect );
  
public:
  typedef sigc::signal<VOID, GLWidget*>  SignalOnClick;
  
  
  SignalOnClick               OnClick;
  
protected:
  /**
   * Default implementation will check if current widget has th focus and then will 
   * propagate the event to all child widgets.
   * Usual implementation propagate event only to focused child, that can be done
   * exending the class with a specialized event.
   */
  virtual VOID     OnKeyReleased( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode, WORD wMods );
  /**
   * Default implementation will check if current widget has th focus and then will 
   * propagate the event to all child widgets.
   * Usual implementation propagate event only to focused child, that can be done
   * exending the class with a specialized event.
   */
  virtual VOID     OnKeyPressed ( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode, WORD wMods );
  /**
   * Default implementation will check if current widget has th focus and then will 
   * propagate the event to all child widgets.
   * Usual implementation propagate event only to focused child, that can be done
   * exending the class with a specialized event.
   */
  virtual VOID     OnKeyRepeated( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode, WORD wMods );
  
protected:
  virtual VOID                   OnBeginDrawing( const GLRecti& rect );
  /**
   * Called before drawing background. To hinibit defalut drawing return FALSE.
   */
  virtual BOOL                   OnDrawBackground( const GLRecti& rect );
  /***/
  virtual BOOL                   OnDraw( const GLRecti& rect );
  /***/
  virtual VOID                   OnEndDrawing( const GLRecti& rect );
  /***/
  virtual VOID                   OnPositionChanged( const GLPosition& pos );
  /***/
  virtual VOID                   OnSizeChanged( const GLSize& size );

protected:
  
protected:
  /**
   * Just set client area without to invoke OnSizeChanged
   */
  VOID   clientResize( const GLSize& size );
  /***/
  BOOL   stepFocus();
  /***/
  BOOL   hasFocusable();
  /**
   * NOTE: this method should be called only when current 
   *       widget is both visible and enabled.
   */
  VOID   handleDefaultKeys( INT iKey, INT iScanCode );
  
private:

  /***/
  VOID      _updateBkVertices();

protected:
  typedef sigc::signal<VOID, GLWindow*, GLLayer*, INT, INT, WORD>  KeySignal;
  
  KeySignal  signalKeyReleased;
  KeySignal  signalKeyPressed;
  KeySignal  signalKeyRepeated;
  
  /***/
  VOID       setParent( GLWidget* pParent );

private:
  KeySignal::iterator   slotKeyReleased;
  KeySignal::iterator   slotKeyPressed;
  KeySignal::iterator   slotKeyRepeated;
  
  
private:
  typedef std::vector< GLWidget* >   WIDGETS;
  
  BackgroundOptions         m_ebo;
  GLPosition                m_pos;
  GLSize                    m_size;
  BOOL                      m_bVisible;
  BOOL                      m_bEnabled;
  GLWidget*                 m_pParent;
  WIDGETS                   m_vChildren;
  WIDGETS::iterator         m_Focused;
  BackgroundType            m_eBackground;
  glm::vec4                 m_crBackground;
  GLAutoRef<GLTexture>      m_imBackground;
  
protected:
  std::vector<glm::vec2>    m_bkVertices;
  std::vector<glm::vec2>    m_bkTexCoord;  
};

#endif // GLWIDGET_H
