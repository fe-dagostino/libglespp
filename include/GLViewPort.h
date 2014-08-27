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


#ifndef GLVIEW_PORT_H
#define GLVIEW_PORT_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "GLPosition.h"
#include "GLSize.h"
#include "FString.h"
#include "GLFW/glfw3.h"
#include <functional>
#include "GLTransformationsMatrix.h"

class GLSceneGraph;

USING_NAMESPACE_FED


class GLViewPort : public GLObject
{
public:
  
  /***/
  GLViewPort();
  /***/
  GLViewPort( GLSceneGraph* pSceneGraph, const glm::mat4& mProjection );

  /***/
  ~GLViewPort();

  /***/
  GLSceneGraph* setScene( GLSceneGraph* pSceneGraph );
  /***/
  GLSceneGraph* getScene() const;
  
  /***/
  VOID use();
  /***/
  VOID reset();
  /***/
  VOID setArea( GLint x, GLint y, GLsizei width, GLsizei height );
  /***/
  VOID getArea( GLint& x, GLint& y, GLsizei& width, GLsizei& height ) const;
 
  /**
   * eg.
   * Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   * glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
   */
  inline GLTransformationsMatrix&     getProjectionMatrix()
  { return m_matProjection; }
  
  /**
   * GL_COLOR_BUFFER_BIT     Indicates the buffers currently enabled for color writing.
   * GL_DEPTH_BUFFER_BIT     Indicates the depth buffer.
   * GL_STENCIL_BUFFER_BIT   Indicates the stencil buffer.
   */
  VOID clearBuffer( GLbitfield mask = GL_COLOR_BUFFER_BIT );

  /***/
  virtual BOOL render();
  
  
protected:
  

private:
  GLSceneGraph*              m_pSceneGraph;
  GLTransformationsMatrix    m_matProjection;
  GLPosition2D               m_pos;
  GLSize                     m_size;
  
};

#endif // GLVIEW_PORT_H
