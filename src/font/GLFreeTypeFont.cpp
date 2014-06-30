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


#include "../include/font/GLFreeTypeFont.h"
#include "../include/GLText.h"
#include "../include/GLSize.h"
#include "../include/GLTexture.h"

GENERATE_CLASSINFO( GLFreeTypeFont, GLFont )


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include FT_GLYPH_H



GLFreeTypeFont::GLFreeTypeFont( FT_Face face, const GLSize& size )
 : GLFont(), m_face( face ),
   m_left(0), m_top(0), m_right(0), m_bottom(0)
{
  setSize( size );
}

GLFreeTypeFont::~GLFreeTypeFont()
{
  FT_Done_Face( m_face );
}

const GLSize&      GLFreeTypeFont::getSize() const
{
  return m_size;
}

VOID      GLFreeTypeFont::setSize( const GLSize& size )
{
  m_size = size;
  
  FT_Set_Pixel_Sizes( m_face, m_size.width, m_size.height );
  
  if ( m_size.width  == 0 )
    m_size.width  = m_size.height;

  if ( m_size.height == 0 )
    m_size.height = m_size.width;
}

VOID      GLFreeTypeFont::getMargins( GLsizei& left, GLsizei& top, GLsizei& right, GLsizei& bottom ) const
{
   left   = m_left;
   top    = m_top;
   right  = m_right;
   bottom = m_bottom;
}

VOID      GLFreeTypeFont::setMargins( GLsizei  left, GLsizei  top, GLsizei  right, GLsizei  bottom )
{
   m_left   = left;
   m_top    = top;
   m_right  = right;
   m_bottom = bottom;
}

GLText*   GLFreeTypeFont::getText( const FWString& sText, const glm::vec4& frColor )
{
  if ( sText.IsEmpty() == TRUE )
    return nullptr;
  
  std::vector<FT_Glyph>   glyphs;
  const wchar_t *         pBuffer = sText.GetBuffer();
  size_t                  iChars  = sText.GetLen();
  FT_Error                error   = 0;
  GLSize                  size(0,0) ;
  
  while ( iChars-- )
  {
    FT_Glyph pGlyph = nullptr;
    
    error = FT_Load_Char ( m_face, *pBuffer++, FT_LOAD_RENDER );
    if ( error == 0 )
    {
      error = FT_Get_Glyph( m_face->glyph, &pGlyph );
      if ( error == 0 )
      {
        // convert to a bitmap (default render mode + destroying old)  
        if ( pGlyph->format != FT_GLYPH_FORMAT_BITMAP )                 
        {
          error = FT_Glyph_To_Bitmap( &pGlyph, FT_RENDER_MODE_NORMAL, 0, 1 );                          
	}
	      
	// access bitmap content by typecasting                        
        FT_BitmapGlyph bmpGlyph = (FT_BitmapGlyph)pGlyph;  
	
        ///////////
        // Update bounding rect
	size.width  += (pGlyph->advance.x >> 16);
        size.height = std::max( size.height, bmpGlyph->bitmap.rows );
      
        glyphs.push_back( pGlyph );
      }
    }     
  } //while ( iChars-- )
  
  ///////////////////
  // Create new texture in order to store all characters
  GLTexture* pTexture = new GLTexture( size.width + m_left + m_right, size.height + m_top  + m_bottom, GL_ALPHA, GL_UNSIGNED_BYTE );
  
  BYTE*   pTextureData = (BYTE*)pTexture->getPixels();  
  
  GLsizei  width = pTexture->getSize().width;  
  GLsizei  xPos  = m_left;
  for ( auto g : glyphs )
  {
    // access bitmap content by typecasting                        
    FT_BitmapGlyph bmpGlyph = (FT_BitmapGlyph)g;
    FT_Bitmap&     bmp      = (bmpGlyph->bitmap);
    
    int yOffset = (size.height - bmpGlyph->top) + m_top;

    for ( register int y = 0; y < bmp.rows; y++ )
    {
      memcpy( &(pTextureData[((y+yOffset)*width)+(xPos+bmpGlyph->left)]), &(bmp.buffer[y*bmp.width]), bmp.width );
    }
    
    xPos += (g->advance.x >> 16);
    
    // Release glyph data
    FT_Done_Glyph( g );
  }
  
  GLText* pText = new GLText( pTexture );
  
  // Set text foreground color
  pText->setColor( frColor );
  
  return pText;
}

FT_Face   GLFreeTypeFont::getFace() const
{
  return m_face;
}

