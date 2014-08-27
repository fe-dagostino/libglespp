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


#include "../include/widgets/GLLabel.h"

GENERATE_CLASSINFO( GLLabel, GLWidget )


GLLabel::GLLabel( GLWidget* pParent )
 : GLWidget( pParent ), m_fgColor( 0.0f, 0.0f, 0.0f, 1.0f ), 
   m_eAlignment(wtaAutoResize), m_pText( nullptr )
{
}

GLLabel::~GLLabel()
{

}

BOOL      GLLabel::setLabel( GLFont* pFont, const FWString& sLabel, const glm::vec4& fgColor, WidgetTextAligment align )
{
  if ( pFont == nullptr )
    return FALSE;
  
  if  ( m_pText != nullptr )
  {
    delete m_pText;
    m_pText = nullptr;
  }
  
  m_pText = pFont->getText( sLabel, fgColor );
  if ( m_pText == nullptr )
    return FALSE;
  
  // Default Texture coordinates
  m_vTexCoord.clear();
  m_vTexCoord.reserve(4);
  m_vTexCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
  m_vTexCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
  m_vTexCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
  m_vTexCoord.push_back( glm::vec2( 1.0f, 1.0f )  );  
  
  _updateVertices( align );
  
  return TRUE;
}

BOOL      GLLabel::OnDraw( const GLRecti& rect )
{
  if ( m_pText != nullptr )
  {
    drawText( m_vVertices, m_vTexCoord, m_pText, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
  }
  
  return TRUE;
}

  
VOID      GLLabel::OnPositionChanged( const GLPosition2D& pos )
{
  _updateVertices( getAlignment() );
}

VOID      GLLabel::OnSizeChanged( const GLSize& size )
{
  _updateVertices( getAlignment() );
}
  
BOOL      GLLabel::OnUpdateBackgroundVertices()
{
  _updateVertices( getAlignment() );
  return FALSE;  
} 

VOID      GLLabel::_updateVertices( WidgetTextAligment align )
{
  m_eAlignment = align;
  
  if (m_pText == nullptr )
    return;
    
  // Remove all vertices
  m_vVertices.clear();
  
  // Default Vertices coordinates 
  GLPosition2D pos = getPosition();
  GLSize       size(0,0);
  
  if (getParent()!=nullptr)
  {
    pos += getParent()->getPosition();
  }
  
  switch ( getAlignment() )
  {
    case wtaAutoResize :
    {
      size = m_pText->getTexture()->getSize();
      
      // Resize client area without notifications
      setSize( size.width, size.height, FALSE );
    }; break;
    case wtaFillClientArea :
    {
      size = getSize();
    }; break; 
    case wtaCentered:
    {
      GLSize  cSize = getSize();
      size = m_pText->getTexture()->getSize();
      
      GLfloat x = (GLfloat)pos.x + ((GLfloat)cSize.width  / (GLfloat)2) - ( (GLfloat)size.width  / (GLfloat)2);  
      GLfloat y = (GLfloat)pos.y + ((GLfloat)cSize.height / (GLfloat)2) - ( (GLfloat)size.height / (GLfloat)2);
      
      pos.x = (GLint)x;
      pos.y = (GLint)y;
    }; break; 
      
  }
  
  m_vVertices.push_back( glm::vec2( pos.x             , pos.y               ) );
  m_vVertices.push_back( glm::vec2( pos.x + size.width, pos.y               ) );
  m_vVertices.push_back( glm::vec2( pos.x             , pos.y + size.height ) );
  m_vVertices.push_back( glm::vec2( pos.x + size.width, pos.y + size.height ) );
}