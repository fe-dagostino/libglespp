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


#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "GLCommonDefs.h"
#include "GLExtensions.h"
#include "FString.h"

class GLRenderer
{
private:
  /***/
  GLRenderer();
  /***/
  virtual ~GLRenderer();

public:
  /**
   * Returns the company responsible for this GL implementation. This name does not 
   * change from release to release.
   * Return TRUE if function succeeded, FALSE otherwise
   */
  BOOL          getVendor  ( FString& sVendor   );
  /**
   * Returns the name of the renderer. This name is typically specific to a particular 
   * configuration of a hardware platform. It does not change from release to release.
   * Return TRUE if function succeeded, FALSE otherwise
   */
  BOOL          getRenderer( FString& sRenderer );

  /**
   * Returns a version or release number of the form 
   * OpenGL<space>ES<space><version number><space><vendor-specific information>.
   * Return TRUE if function succeeded, FALSE otherwise
   */
  BOOL          getVersion( FString& sVersion );
  /**
   * Returns a version or release number for the shading language of the form 
   * OpenGL<space>ES<space>GLSL<space>ES<space><version number><space><vendor-specific information>.
   * Return TRUE if function succeeded, FALSE otherwise
   */
  BOOL          getShaderVersion( FString& sShaderVersion );
  /***/
  GLExtensions* getExtensions();
  
private:
  GLExtensions*    m_glExtensions;
  
  friend class GLWindow;
};

#endif // GLRENDERER_H
