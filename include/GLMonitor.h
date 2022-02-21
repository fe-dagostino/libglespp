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


#ifndef GLMONITORINFO_H
#define GLMONITORINFO_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include <vector>


USING_NAMESPACE_FED


class GLMonitor : public GLObject
{
public:
  
  /**
   * @param 
   */
  GLMonitor( const GLFWmonitor* pMonitor );
  /***/
  GLMonitor( const GLMonitor& rMonitor );

  /***/
  virtual ~GLMonitor();

  /***/
  const FString&              getName() const;
  
  /**
   * Return current video mode.
   */
  const GLFWvidmode&          getVideoMode() const;
  
  /**
   * Return the list with all available video modes supported by the monitor.
   * 
   * NOTE: Returned list pointer and its elements must be released by caller.
   */
  std::vector<GLFWvidmode* >* getVideoModes() const;  
  
  /***/
  INT                         getPositionX() const;
  /***/
  INT                         getPositionY() const;
  
  /***
   *  Returns the width, in millimetres, of display area.
   */
  INT                         getWidth() const;
  /***
   *  Returns the height, in millimetres, of display area.
   */
  INT                         getHeight() const;
  
protected:

private:
  const GLFWmonitor* m_pGlfwMonitor;
  FString            m_sName;
  GLFWvidmode        m_glfwVideoMode;
  INT                m_iPosition[2];
  INT                m_iSize[2];
  
  friend class GLWindow;
};

#endif // GLSHAPE_H
