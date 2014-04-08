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


#ifndef GLSHAPE_H
#define GLSHAPE_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "GLProgram.h"
#include "GLVertexShader.h"
#include "GLFragmentShader.h"
#include "GLFW/glfw3.h"
#include "glm/mat4x4.hpp"

USING_NAMESPACE_FED


class GLShape : public GLObject
{
public:
  
  /**
   * @param sName
   */
  GLShape( const FString& sName );

  /***/
  virtual ~GLShape();

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
  const FString     m_sName;
  GLProgram         m_glProgram;
  
};

#endif // GLSHAPE_H
