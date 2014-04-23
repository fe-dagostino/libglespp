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
 : m_size( width, height ), m_format( format ), m_type( type ), m_length( 0 ), m_pixels( nullptr )
{
  if ( 
      ( type != GL_UNSIGNED_BYTE          ) &&
      ( type != GL_UNSIGNED_SHORT_5_6_5   ) &&
      ( type != GL_UNSIGNED_SHORT_4_4_4_4 ) &&
      ( type != GL_UNSIGNED_SHORT_5_5_5_1 )
     )
  {
    //@todo
  }
      
  if ( m_pixels == nullptr )
  {
    // Accepted values
    //GL_UNSIGNED_BYTE             1 byte
    //GL_UNSIGNED_SHORT_5_6_5      2 bytes
    //GL_UNSIGNED_SHORT_4_4_4_4    2 bytes
    //GL_UNSIGNED_SHORT_5_5_5_1    2 bytes
    
    m_length = width*height*((type==GL_UNSIGNED_BYTE)?1:2);
    m_pixels = calloc( m_length, 1 );
    if ( m_pixels == nullptr )
    {
      //@todo
    }
  }
}

GLTexture::~GLTexture()
{
  if ( m_pixels != nullptr )
  {
    free( m_pixels );
    m_pixels = nullptr;
  }
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
