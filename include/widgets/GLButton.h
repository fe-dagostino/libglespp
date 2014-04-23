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


#ifndef GLBUTTON_H
#define GLBUTTON_H

#include "GLCommonDefs.h"
#include "GLLabel.h"
#include "GLFont.h"
#include "GLText.h"

#include "FWString.h"

USING_NAMESPACE_FED

/**
 */
class GLButton : public GLLabel
{
  ENABLE_FRTTI( GLButton ) 
public:

  /***/
  GLButton( GLWidget* pParent );
  /***/
  virtual ~GLButton();  
  
  /***/
  inline const FWString&     getCaption() const
  { return getLabel();  }
  /***/
  inline const glm::vec4&    getForeground() const
  { return getForeground(); }
  
  /***/
  BOOL                setCaption( GLFont* pFont, const FWString& sCaption, const glm::vec4& fgColor, WidgetTextAligment align );
  
  /***/
  VOID                setFocus( GLTexture* texture );
  
  virtual BOOL        isFocusable() const
  { return TRUE; }

  
protected:
  /***/
  virtual BOOL        OnDrawBackground( const GLRecti& rect );
  /***/
  virtual BOOL        OnDraw( const GLRecti& rect );
  /***/
  virtual VOID        OnPositionChanged( const GLPosition& pos );
  /***/
  virtual VOID        OnSizeChanged( const GLSize& size );

private:
  GLAutoRef<GLTexture>      m_imFocus;
  
  std::vector<glm::vec2>    m_vVertices;
  std::vector<glm::vec2>    m_vTexCoord;    
};

#endif // GLBUTTON_H
