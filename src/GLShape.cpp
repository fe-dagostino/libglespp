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


#include "../include/GLShape.h"

GLShape::GLShape( const FString& sName )
  : m_sName( sName )
{
}

GLShape::~GLShape()
{
  
}

const FString&  GLShape::getName() const
{
  return m_sName;
}

BOOL  GLShape::load( const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource )
{
  GLVertexShader   _glVertexShader;
  GLFragmentShader _glFragmentShader;
  
  if ( _glVertexShader.load( vertexShaderSource ) == FALSE )
    return FALSE;
    
  if ( _glFragmentShader.load( fragmentShaderSource ) == FALSE )
    return FALSE;
  
  if ( m_glProgram.attachShaders( &_glVertexShader, &_glFragmentShader ) == FALSE )
    return FALSE;
  
  // Set up  identity matrix
  u_matModelView = glm::mat4(1.0);
  
  return m_glProgram.link();
}

BOOL  GLShape::load( const FString& sVertexFilename, const FString& sFragmentFilename )
{
  GLVertexShader   _glVertexShader;
  GLFragmentShader _glFragmentShader;
  
  if ( _glVertexShader.load( sVertexFilename ) == FALSE )
    return FALSE;
    
  if ( _glFragmentShader.load( sFragmentFilename ) == FALSE )
    return FALSE;
  
  if ( m_glProgram.attachShaders( &_glVertexShader, &_glFragmentShader ) == FALSE )
    return FALSE;
  
  return TRUE;
}

VOID  GLShape::scale( double xs, double ys, double zs )
{
  u_matModelView = glm::scale( u_matModelView, glm::vec3(xs,ys,zs) );
}

VOID  GLShape::translate( double x, double y, double z )
{
  u_matModelView = glm::translate( u_matModelView, glm::vec3(x,y,z) );
}

VOID  GLShape::rotateX( float angle )
{
  u_matModelView = glm::rotate( u_matModelView, angle, glm::vec3(1.0f,0.0f,0.0f) );
}

VOID  GLShape::rotateY( float angle )
{
  u_matModelView = glm::rotate( u_matModelView, angle, glm::vec3(0.0f,1.0f,0.0f) );
}

VOID  GLShape::rotateZ( float angle )
{
  u_matModelView = glm::rotate( u_matModelView, angle, glm::vec3(0.0f,0.0f,1.0f) );
}

GLProgram& GLShape::getProgram()
{
  return m_glProgram;
}

VOID    GLShape::render()
{
  GLint locModelView  = glGetUniformLocation( getProgram().getId(), "u_matModelView" );
  //GLint locProjection = glGetUniformLocation( getProgram().getId(), "u_matProjection");
  
  glUniformMatrix4fv( locModelView , 1, GL_FALSE, glm::value_ptr(u_matModelView) );

  OnRender();
  
}
