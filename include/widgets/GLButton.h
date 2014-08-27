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
  virtual VOID        OnPositionChanged( const GLPosition2D& pos );
  /***/
  virtual VOID        OnSizeChanged( const GLSize& size );

private:
  GLAutoRef<GLTexture>      m_imFocus;
  
  std::vector<glm::vec2>    m_vVertices;
  std::vector<glm::vec2>    m_vTexCoord;    
};

#endif // GLBUTTON_H
