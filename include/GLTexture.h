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
  /**
   * Note: Both etlFreeImage and etlDevIL load the image in the same order 
   *       it has been stored, so if file format store the image from top
   *       to bottom or from bottom to top these two libraries don't take 
   *       care of it and image should be adjusted in rendering.
   *       etlLibAV will load the image from top to bottom as for and 
   *       image viewer even the file format store the image in a different 
   *       manner. 
   *       This so etlLibAV will be the best option if you don't knwo what
   *       kind of image will be loaded.
   */
  enum TextureLoader
  {
    etlFreeImage,
    etlLibAV,
    etlDevIL
  };
  
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
  BOOL                    init(  GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels );
  
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

  /**
   */
  BOOL                    load( TextureLoader tl, const FString& sFilename );

private:
  GLSize                   m_size;
  GLenum                   m_format;
  GLenum                   m_type;
  GLuint                   m_length;
  GLvoid*                  m_pixels;
};

#endif // GLTEXTURE_H
