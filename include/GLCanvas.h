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


#ifndef GLCANVAS_H
#define GLCANVAS_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "GLText.h"
#include "GLTexture.h"
#include "GLImage.h"

#include "FString.h"

#include "glm/glm.hpp"

#include <vector>
#include <string>

USING_NAMESPACE_FED

class GLProgram;

class GLCanvas : public GLObject
{
  ENABLE_FRTTI( GLCanvas )
public:
  /***/
  GLCanvas();
  /***/
  virtual ~GLCanvas();
  
  /***/
  inline void         setMVP( const glm::mat4& mvp )
  { m_mvp = mvp;  }
  /***/
  inline glm::mat4&   getMVP()
  { return m_mvp; }
  
  /***/
  void   drawPoints( const std::vector<glm::vec2>& points, const glm::vec4& color, GLfloat fThickness = 1.0f );
  /***/
  void   drawLines( const std::vector<glm::vec2>& points, const glm::vec4& color, GLfloat fThickness = 1.0f );
  /***/
  void   drawRect( const std::vector<glm::vec2>& points, const glm::vec4& color );
  /***/
  void   drawRect( const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& texCoord, GLTexture* texture, GLint tws, GLint twt );
  
  /***/
  void   drawText( const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& texCoord, GLText* text, GLint tws, GLint twt );
  
private:
  /***/
  void          draw( GLenum mode, const std::vector<glm::vec2>& points, const glm::vec4& color, GLfloat fThickness );
  /***/
  void          draw( const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& texCoord, GLText* text, GLint tws, GLint twt );
 
private:  
  glm::mat4     m_mvp;
  
};

#endif // GLCANVAS_H
