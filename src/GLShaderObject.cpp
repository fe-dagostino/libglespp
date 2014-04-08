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


#include "../include/GLShaderObject.h"
#include "FFile.h"

USING_NAMESPACE_FED

GLShaderObject::GLShaderObject( ShaderType eType )
{
  setId( glCreateShader( eType ) );
}

GLShaderObject::~GLShaderObject()
{
  glDeleteShader( getId() );
}

BOOL GLShaderObject::load( const GLchar *shaderSource )
{
  if ( isValid() == FALSE )
    return FALSE;
  
  // Load the shader source
  glShaderSource(getId(), 1, &shaderSource, NULL);
  
  // Compile the shader
  glCompileShader(getId());
    
  if(isCompiled())
    return TRUE;
  
  return FALSE;
}

BOOL GLShaderObject::loadFromFile( const FString& sFilename )
{
  FFile  _shaderFile( nullptr, sFilename );
  
  _shaderFile.Open( FREAD_OPEN, 0, FOPEN_EXISTING, 0 );
  
  DWORD _size     = 0;
  DWORD _filesize = (DWORD)_shaderFile.GetSize();
  if (_filesize == 0 )
    return FALSE;
  
  GLchar* pBuffer = (GLchar*)calloc( sizeof(GLchar), (_filesize+1) );
  
  _shaderFile.Read( pBuffer, _filesize, &_size );
  
  _shaderFile.Close();
  
  BOOL  _bRetVal = load( pBuffer );

  // Release buffer
  free(pBuffer);
  
  return _bRetVal;
}

GLuint GLShaderObject::query( GLenum e ) const
{
  GLint iValue;
  
  // Check the compile status
  glGetShaderiv(getId(), e, &iValue);
  
  return iValue;
}

GLShaderObject::ShaderType GLShaderObject::getType() const
{
  return (GLShaderObject::ShaderType)query(GL_SHADER_TYPE);
}

BOOL GLShaderObject::isCompiled() const
{
  // Check the compile status
  return (query(GL_COMPILE_STATUS)>0);
}

GLint GLShaderObject::getSourceLength() const
{
  return query(GL_SHADER_SOURCE_LENGTH);
}

BOOL GLShaderObject::getLog( FString& sLog )
{
  GLint iInfoLength = query(GL_INFO_LOG_LENGTH);
  if (iInfoLength <= 0)
    return FALSE;
  
  char* pInfoLog = (char *)malloc(sizeof(char) * iInfoLength);
  
  glGetShaderInfoLog(getId(), iInfoLength, NULL, pInfoLog);
  
  sLog.Set( pInfoLog, iInfoLength );
  
  free(pInfoLog);
  
  return TRUE;
}



