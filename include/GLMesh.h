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


#ifndef GLMESH_H
#define GLMESH_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "GLProgram.h"
#include "GLVertexShader.h"
#include "GLFragmentShader.h"
#include "GLFW/glfw3.h"
#include "glm/mat4x4.hpp"

USING_NAMESPACE_FED


class GLMesh : public GLObject
{
public:
  
  /**
   */
  GLMesh( );

  /***/
  virtual ~GLMesh();

  /***/
  const FString&  getName() const;
  
  /***/
  BOOL  load( const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource );
  /***/
  BOOL  load( const FString& sVertexFilename, const FString& sFragmentFilename );
  /***/
  VOID  scale( double xs, double ys, double zs );
  /***/
  VOID  translate( double x, double y, double z );
  /***/
  VOID  rotateX( float angle );
  /***/
  VOID  rotateY( float angle );
  /***/
  VOID  rotateZ( float angle );
  
  /***/
  GLProgram& getProgram();

  /***/
  VOID    render();

protected:
  /***/
  virtual VOID    OnRender() = 0;
  
protected:
  glm::mat4         u_matModelView;
  
private:  
  GLProgram         m_glProgram;
  
};

#endif // GLMESH_H
