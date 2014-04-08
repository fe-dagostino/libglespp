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


#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "GLCommonDefs.h"
#include "GLFW/glfw3.h"
#include "GLSize.h"
#include "GLHandleObject.h"
#include "GLReference.h"

#include <glm/glm.hpp>

#include <vector>


USING_NAMESPACE_FED

/***
 * 
 */
class GLTexture : public GLReference, public GLHandleObject
{
public:
  /***/
  GLTexture();
  
  /**
   * @param format GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, and GL_LUMINANCE_ALPHA.
   * @param type   GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, and GL_UNSIGNED_SHORT_5_5_5_1
   */
  GLTexture( GLsizei width, GLsizei height, GLenum format, GLenum type );
  
  /***/
  ~GLTexture();
  
  /***/
  inline GLenum           getFormat() const
  { return m_format; }
  /***/
  inline GLenum           getType() const
  { return m_type; }
  
  /**
   * Return size in pixels.
   */
  inline const GLSize&    getSize() const
  { return m_size; }
  /***/
  inline GLvoid*          getPixels()
  { return m_pixels; }
  /**
   * @return pixels buffer length in bytes
   */
  inline GLuint           getLength() const 
  { return m_length; }
  
  /***/
  VOID                    setPacking( GLint param );
  /***/
  VOID                    setUnpacking( GLint param );

  /***/
  inline VOID             setParameterf( GLenum target, GLenum pname, GLfloat param )
  { glTexParameterf( target, pname, param ); }
  /***/
  inline VOID             setParameteri( GLenum target, GLenum pname, GLint param )
  { glTexParameteri( target, pname, param ); }
  
  /**
   * Push image data, vertex coordinates and texture coordinates then draw it.
   * At current time all data will be sent to GPU each time render will be called.
   * 
   * @param target     Specifies the target texture of the active texture unit. 
   *                   Must be GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
   *                   GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 
   *                   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
   *                   or GL_TEXTURE_CUBE_MAP_NEGATIVE_Z.
   * @param level      Specifies the level-of-detail number. Level 0 is the base image 
   *                   level. Level n is the nth mipmap reduction image.
   */
  VOID                    render( const std::vector<glm::vec2>& vertices, 
				  const std::vector<glm::vec2>& texCoord,
				  bool blend,
				  GLenum target, GLint level, GLint uLocation, GLuint aVertices, GLuint aTexCoord,
				  GLint  tws, GLint twt );

#ifdef _USE_FREEIMAGE
  /***/
  BOOL                    fiLoad( const FString& sFilename );
#endif

private:
  GLSize                   m_size;
  GLenum                   m_format;
  GLenum                   m_type;
  GLuint                   m_length;
  GLvoid*                  m_pixels;
};

#endif // GLTEXTURE_H
