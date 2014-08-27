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


#include "../include/GLTexture.h"

#ifdef _USE_FREEIMAGE
extern "C"
{
# include "images/images.h"
}
#endif

#include "LOGGING/FLogger.h"


GLTexture::GLTexture()
 : m_size( 0, 0 ), m_format( 0 ), m_type( 0 ), m_length( 0 ), m_pixels( nullptr )
{
  
}

GLTexture::GLTexture( GLsizei width, GLsizei height, GLenum format, GLenum type )
 : m_size( 0, 0 ), m_format( 0 ), m_type( 0 ), m_length( 0 ), m_pixels( nullptr )
{
  init( width, height, format, type, nullptr );
}

GLTexture::~GLTexture()
{
  if ( m_pixels != nullptr )
  {
    free( m_pixels );
    m_pixels = nullptr;
  }
}

BOOL                    GLTexture::init(  GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels )
{
  if ( type != GL_UNSIGNED_BYTE )
  {
    return FALSE;
  }
  
  if (
       ( getSize().width  != width   ) || 
       ( getSize().height != height  ) ||
       ( getFormat()      != format  ) ||
       ( getType()        != type    ) 
     )
  {
    if ( m_pixels != nullptr )
    {
      free( m_pixels );
      m_pixels = nullptr;
    }
    
    m_size.width  = width;
    m_size.height = height;
    m_format      = format;
    m_type        = type;
    
    // Accepted values
    int bpp = 4;
    switch ( format )
    {
      case GL_RGBA: bpp = 4; break;
      case GL_RGB : bpp = 3; break;
    }
    
    m_length      = width*height*bpp;
    m_pixels      = calloc( m_length, 1 );
    if ( m_pixels == nullptr )
    {
      return FALSE;
    }
  }  
  
  if ( (m_pixels != nullptr) && (pixels != nullptr) )
  {
    memcpy( m_pixels, pixels, m_length );
  }
  
  return TRUE;
}

VOID                    GLTexture::setPacking( GLint param )
{
  glPixelStorei(GL_PACK_ALIGNMENT, param );
}

VOID                    GLTexture::setUnpacking( GLint param )
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, param );
}


BOOL                    GLTexture::load( TextureLoader tl, const FString& sFilename )
{
  int width  = 0;
  int height = 0;
  
  if ( tl == etlFreeImage )
  {
#ifdef _USE_FREEIMAGE
    m_pixels = fi_load( sFilename.GetBuffer(), &m_length, &width, &height );
    if (m_pixels==nullptr)
    {
      ERROR_INFO( FString( 0, "Failed to load Texture [%s]", sFilename.GetBuffer() ), load() );
    
      return FALSE;
    }
  
    m_size.width  = width;
    m_size.height = height;
  
    m_format = GL_RGBA;
    m_type   = GL_UNSIGNED_BYTE;
    
    LOG_INFO( FString( 0, "Loaded Texture [%s] MEM BYTES [%d] W:[%d] Pixel x H:[%d] D:[32] Bits", sFilename.GetBuffer(), m_length, m_size.width, m_size.height ), load() );
    return TRUE;
#else  //_USE_FREEIMAGE
    ERROR_INFO( "Use: cmake -DUSE_FREEIMAGE=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_FREEIMAGE   
  }
  
  if ( tl == etlLibAV )
  {
#ifdef _USE_AVCPP

#else  //_USE_AVCPP
    ERROR_INFO( "Use: cmake -DUSE_AVCPP=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_AVCPP    
  }
  
  return FALSE;
}

VOID                    GLTexture::render(  const std::vector<glm::vec2>& vertices, 
                                            const std::vector<glm::vec2>& texCoord, 
					    bool blend,
                                            GLenum target, GLint level, GLint uLocation, GLuint aVertices, GLuint aTexCoord,
					    GLint  tws, GLint twt
 					)
{
  glEnable(GL_TEXTURE_2D);
  if ( blend )
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  
  // Disable default 4 byte alignment
  setUnpacking( 1 );
    
  // Create Textures	    
  GLuint   _textureID;
  glGenTextures(1, &_textureID);
  setId( _textureID );
  
  glActiveTexture( GL_TEXTURE0 );

  // texture 1 (poor quality scaling)
  glBindTexture(GL_TEXTURE_2D, getId());   // 2d texture (x and y size)

  // Set the base map sampler to texture unit 0
  glUniform1i(uLocation, 0);
  
  // Set 2D texture rendering options
  setParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // cheap scaling when image bigger than texture
  setParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // cheap scaling when image smalled than texture
  setParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tws );
  setParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, twt );  
 
  // Send texture data to graphics card
  glTexImage2D(target, level, getFormat(), m_size.width, m_size.height, 0, getFormat(), getType(), m_pixels );

  glEnableVertexAttribArray(aTexCoord);
  glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, texCoord.data() );
    
  glEnableVertexAttribArray(aVertices);
  glVertexAttribPointer(aVertices, 2, GL_FLOAT, GL_FALSE, 0, vertices.data() );
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() ); 
  
  glDisable(GL_TEXTURE_2D);
  if ( blend )
  {
    glDisable(GL_BLEND);
  }
  
  glDeleteTextures(1, &_textureID);
  setId( _textureID );
  
  glDisableVertexAttribArray(aTexCoord);
  glDisableVertexAttribArray(aVertices);
}
