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


#include "../include/GLProgram.h"
#include "../include/GLVertexShader.h"
#include "../include/GLFragmentShader.h"


GLProgram::GLProgram( )
{
  setId( glCreateProgram( ) );
}

GLProgram::~GLProgram()
{
  glDeleteProgram( getId() );
}


BOOL	GLProgram::attachShaders( GLVertexShader* pVertexShader, GLFragmentShader* pFragmentShader )
{
  if (( pVertexShader == NULL ) || ( pFragmentShader == NULL ))
    return FALSE;
  
  if ( pVertexShader->getType() != GLShaderObject::eVertexShader )
    return FALSE;
  
  if ( pFragmentShader->getType() != GLShaderObject::eFragmentShader )
    return FALSE;
  
  glAttachShader( getId(), pVertexShader->getId() );

  glAttachShader( getId(), pFragmentShader->getId() );
  
  return TRUE;
}

  
void 	GLProgram::bindAttribLocation( GLuint index, const GLchar *name )
{
  glBindAttribLocation( getId(), index, name );
}

BOOL    GLProgram::link()
{
  // Link the program
  glLinkProgram( getId() );

  if (isLinked())
    return TRUE;
  
  return FALSE;
}

void 	GLProgram::use()
{
  glUseProgram( getId() );
}

BOOL GLProgram::isLinked() const
{
  // Check the link status
  return (query(GL_LINK_STATUS)>0);
}

BOOL GLProgram::validate() const
{
  glValidateProgram( getId() );

  return (query(GL_VALIDATE_STATUS)>0);
}

GLint GLProgram::getActiveAttributes() const
{
  return query(GL_ACTIVE_ATTRIBUTES);
}

GLint GLProgram::getActiveAttributeMaxLength() const
{
  return query(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
}

GLint GLProgram::getActiveUniforms() const
{
  return query(GL_ACTIVE_UNIFORMS);
}

GLint GLProgram::getActiveUniformMaxLength() const
{
  return query(GL_ACTIVE_UNIFORM_MAX_LENGTH);
}

GLint GLProgram::getAttachedShaders() const
{
  return query(GL_ATTACHED_SHADERS);
}

GLuint GLProgram::query( GLenum e ) const
{
  GLint iValue;
  
  // Check the compile status
  glGetProgramiv(getId(), e, &iValue);
  
  return iValue;
}


BOOL GLProgram::getLog( FString& sLog )
{
  GLint iInfoLength = query(GL_INFO_LOG_LENGTH);
  if (iInfoLength <= 0)
    return FALSE;
  
  char* pInfoLog = (char *)malloc(sizeof(char) * iInfoLength);
  
  glGetProgramInfoLog(getId(), iInfoLength, NULL, pInfoLog);
  
  sLog.Set( pInfoLog, iInfoLength );
  
  free(pInfoLog);
  
  return TRUE;
}



