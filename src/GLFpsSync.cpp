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


#include "GLFpsSync.h"

GLFpsSync::GLFpsSync()
 :   m_dRequestedFps( 0.0f ), m_dFpsInterval( 0.0f ), m_dLastUpdate( 0.0f )
{
}

GLFpsSync::~GLFpsSync()
{
}

VOID    GLFpsSync::setFps( double dRequestedFps )
{
  m_dRequestedFps  = dRequestedFps;
  m_dFpsInterval   = 1 / m_dRequestedFps;
  m_dLastUpdate    = glfwGetTime();
}

DOUBLE  GLFpsSync::sync()
{
  // Time elapsed between current call to sync() and the previous call to the same method.
  DOUBLE  dElapsedTime = glfwGetTime() - m_dLastUpdate;
  
  // Update member variable to current time
  m_dLastUpdate = glfwGetTime();
  
  // Return time to wait
  return  m_dFpsInterval - dElapsedTime;
}
  
  





