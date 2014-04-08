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


#ifndef GLSHADEROBJECT_H
#define GLSHADEROBJECT_H

#include "GLCommonDefs.h"
#include "fedlibrary/include/FString.h"
#include "GLFW/glfw3.h"
#include "GLHandleObject.h"


USING_NAMESPACE_FED

class GLShaderObject : public GLHandleObject
{
public:

  enum ShaderType {
    eFragmentShader = GL_FRAGMENT_SHADER,
    eVertexShader   = GL_VERTEX_SHADER
  };
  /***/
  GLShaderObject( ShaderType eType );

  /***/
  virtual ~GLShaderObject();

  /**
   * Loading shader from memory string and compile it.
   * return FALSE if compile operation has failed.
   */
  BOOL 		load( const GLchar *shaderSource );
  /**
   * Loading shader from specified file and compile it.
   * return FALSE if compile operation has failed.
   */
  BOOL 		loadFromFile( const FString& sFilename ) FTHROW(FFileSystemException);
  
  /**
   * Return shader type vertex or fragment.
   */
  ShaderType	getType() const;
  /**
   * Return shader source code length.
   */
  GLint 	getSourceLength() const;

  /**
   * Can be used to check compile status.
   */
  BOOL 		isCompiled() const;
  
  /**
   * Can be used to retrieve log informations generated at 
   * load time.
   * Both in case of success or failure log could contains 
   * details for the reason of failure or just a confirmation message.
   * This function can be used at debug time in order to better understad
   * if there are errors and how to fix it. 
   */
  BOOL 		getLog( FString& sLog );
  
protected:
  
  /**
   * Query object values.
   */
  GLuint 	query( GLenum e ) const;  
  
private:
  
  friend class GLProgram;
};

#endif // GLSHADEROBJECT_H
