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


#ifndef GLLABEL_H
#define GLLABEL_H

#include "GLCommonDefs.h"
#include "GLWidget.h"
#include "GLFont.h"
#include "GLText.h"

#include "FWString.h"

USING_NAMESPACE_FED


/***/
enum WidgetTextAligment
{
  wtaAutoResize,              // Client Area will be resized as for text requirements 
  wtaFillClientArea,          // Fill Label Rectangle using to stretch/reduce text in both direction
  wtaCentered                 // Text will keep original aspect ratio and original dimensions and its
                              // position will be relative to client area center in client coordinates.
};
  
/**
 */
class GLLabel : public GLWidget
{
  ENABLE_FRTTI( GLLabel )
public:

  /***/
  GLLabel( GLWidget* pParent );
  /***/
  virtual ~GLLabel();
  
  /***/
  inline const FWString&     getLabel() const
  { return m_sLabel;  }
  /***/
  inline const glm::vec4&    getForeground() const
  { return m_fgColor; }
  
  /***/
  BOOL                setLabel( GLFont* pFont, const FWString& sLabel, const glm::vec4& fgColor, WidgetTextAligment align );
  
protected:
  /***/
  virtual BOOL        OnDraw( const GLRecti& rect );
  /***/
  virtual VOID        OnPositionChanged( const GLPosition& pos );
  /***/
  virtual VOID        OnSizeChanged( const GLSize& size );

private:
  /***/
  VOID       _updateVertices( WidgetTextAligment align );

private:
  FWString                  m_sLabel;
  glm::vec4                 m_fgColor;
  WidgetTextAligment        m_eAlignment;
  GLText*                   m_pText;
  
  std::vector<glm::vec2>    m_vVertices;
  std::vector<glm::vec2>    m_vTexCoord;    
};

#endif // GLLABEL_H
