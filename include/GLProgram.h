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


#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include "GLCommonDefs.h"
#include "FString.h"
#include "GLFW/glfw3.h"
#include <functional>
#include "GLReference.h"
#include "GLHandleObject.h"


USING_NAMESPACE_FED


class GLVertexShader;
class GLFragmentShader;


class GLProgram : public GLHandleObject, public GLReference
{
public:
  
  /***/
  GLProgram();

  /***/
  ~GLProgram();

  /***/
  using GLHandleObject::getId;
  
  /**
   * Loading shader from memory string and compile it.
   * return FALSE if compile operation has failed.
   */
  BOOL 		attachShaders( GLVertexShader* pVertexShader, GLFragmentShader* pFragmentShader );

  /**
   */
  VOID 		bindAttribLocation( GLuint index, const GLchar *name );
  
  /**
   */
  BOOL 		link();
  
  /**
   * Must be called on each render.
   * Mainly this function is called in the main gl loop.
   */
  VOID 		use();
  
  /**
   * Return TRUE if link process has been done successfully.
   */
  BOOL 		isLinked() const;

  /**
   * This function should be used only for debug; validation process 
   * will be slower. If validation will fails, detailed information will 
   * be available using the getLog() method.
   */
  BOOL 		validate() const;
  
  
  GLint getActiveAttributes() const;

  GLint getActiveAttributeMaxLength() const;

  GLint getActiveUniforms() const;

  GLint getActiveUniformMaxLength() const;

  GLint getAttachedShaders() const;
  
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
  
};

#endif // GLPROGRAM_H
