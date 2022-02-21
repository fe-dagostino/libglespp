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


#ifndef GLFPSSYNC_H
#define GLFPSSYNC_H

#include "GLCommonDefs.h"
#include "FString.h"

USING_NAMESPACE_FED

class GLFpsSync : public FObject
{
public:
  /***/
  GLFpsSync();

  /***/
  virtual ~GLFpsSync();
  
  /**
   */
  VOID    setFps( double dRequestedFps );
  /**
   * Return time in seconds to wait.
   * A positive value means you have to wait, a negative 
   * value instead means that requested FPS is too high, so 
   * you must reduce FPS or try to reduce process time in order to 
   * have a positive value or ZERO.
   */
  DOUBLE  sync();
  
protected:


private:
  DOUBLE   m_dRequestedFps;
  DOUBLE   m_dFpsInterval;
  DOUBLE   m_dLastUpdate;
  
};

#endif // GLFPSSYNC_H
