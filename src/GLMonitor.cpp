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


#include "GLMonitor.h"


GLMonitor::GLMonitor( const GLFWmonitor* pMonitor )
 : m_pGlfwMonitor( pMonitor ), m_iPosition{ 0, 0 }, m_iSize{ 0, 0 } 
{
  m_sName         = glfwGetMonitorName( (GLFWmonitor*)pMonitor );
  m_glfwVideoMode = *glfwGetVideoMode ( (GLFWmonitor*)pMonitor );
  
  glfwGetMonitorPos( (GLFWmonitor*)pMonitor, &m_iPosition[0], &m_iPosition[1] );
  glfwGetMonitorPhysicalSize((GLFWmonitor*)pMonitor, &m_iSize[0], &m_iSize[1] );
}

GLMonitor::GLMonitor( const GLMonitor& rMonitor )
 : m_pGlfwMonitor( rMonitor.m_pGlfwMonitor ),
   m_sName( rMonitor.m_sName ) 
{
  m_iPosition[0] = rMonitor.m_iPosition[0];
  m_iPosition[1] = rMonitor.m_iPosition[1];
  m_iSize[0]     = rMonitor.m_iSize[0];
  m_iSize[1]     = rMonitor.m_iSize[1];
}

GLMonitor::~GLMonitor()
{
  
}

const FString&      GLMonitor::getName() const
{
  return m_sName;
}

const GLFWvidmode&  GLMonitor::getVideoMode() const
{
  return m_glfwVideoMode;
}

std::vector<GLFWvidmode* >* GLMonitor::getVideoModes() const
{
  std::vector<GLFWvidmode* >*  lstModes = new std::vector<GLFWvidmode* >();
  
  int iCount = 0;
  const GLFWvidmode* pVideoModes = glfwGetVideoModes( (GLFWmonitor*)m_pGlfwMonitor, &iCount );
  while ( iCount > 0 )
  {
    // Create item
    GLFWvidmode* pVideoMode = new GLFWvidmode(); 
    // initialize item
    *pVideoMode = *pVideoModes;
    
    lstModes->push_back( pVideoMode );
    
    pVideoModes++;
    iCount--;
  }
  
  return lstModes;
}
  
INT                 GLMonitor::getPositionX() const
{
  return m_iPosition[0];
}

INT                 GLMonitor::getPositionY() const
{
  return m_iPosition[1];
}

INT                 GLMonitor::getWidth() const
{
  return m_iSize[0];
}

INT                 GLMonitor::getHeight() const
{
  return m_iSize[1];
}

