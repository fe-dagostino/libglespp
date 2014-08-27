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


#include "../include/widgets/GLButton.h"

GENERATE_CLASSINFO( GLButton, GLWidget )

GLButton::GLButton( GLWidget* pParent )
 : GLLabel( pParent )
{
}

GLButton::~GLButton()
{

}

BOOL      GLButton::setCaption( GLFont* pFont, const FWString& sCaption, const glm::vec4& fgColor, WidgetTextAligment align )
{
  return setLabel( pFont, sCaption, fgColor, align  );
}
  
VOID      GLButton::setFocus( GLTexture* texture )
{
  m_imFocus.attach(texture);
}

BOOL      GLButton::OnDrawBackground( const GLRecti& rect )
{
  if ( hasFocus() == TRUE )
  {
    if ( m_imFocus != nullptr )
    {
      drawRect( m_bkVertices, m_bkTexCoord, m_imFocus, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
    }
  }

  return TRUE;
}

BOOL      GLButton::OnDraw( const GLRecti& rect )
{
  return GLLabel::OnDraw( rect );
}

  
VOID      GLButton::OnPositionChanged( const GLPosition2D& pos )
{
  GLLabel::OnPositionChanged( pos );
}

VOID      GLButton::OnSizeChanged( const GLSize& size )
{
  GLLabel::OnSizeChanged( size );
}
  