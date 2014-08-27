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


#ifndef GLTRANSFORMATIONSMATRIX_H
#define GLTRANSFORMATIONSMATRIX_H

#include "GLCommonDefs.h"
#include "FObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

USING_NAMESPACE_FED


/**
 */
class GLTransformationsMatrix
{
public:
  /***/
  GLTransformationsMatrix();
  /***/
  virtual ~GLTransformationsMatrix();
  
  /***/
  inline glm::mat4&  get()
  { return m_matrix; }
  
  /***/
  inline VOID  scale( double xs, double ys, double zs )
  { m_matrix = glm::scale( m_matrix, glm::vec3(xs,ys,zs) );  }
  /***/
  inline VOID  translate( double x, double y, double z )
  { m_matrix = glm::translate( m_matrix, glm::vec3(x,y,z) ); }
  /***/
  inline VOID  rotateX( float angle )
  { m_matrix = glm::rotate( m_matrix, angle, glm::vec3(1.0f,0.0f,0.0f) ); }
  /***/
  inline VOID  rotateY( float angle )
  { m_matrix = glm::rotate( m_matrix, angle, glm::vec3(0.0f,1.0f,0.0f) ); }
  /***/
  inline VOID  rotateZ( float angle )
  { m_matrix = glm::rotate( m_matrix, angle, glm::vec3(0.0f,0.0f,1.0f) ); }  
  
private:
  glm::mat4         m_matrix;
};

#endif // GLTRANSFORMATIONSMATRIX_H
