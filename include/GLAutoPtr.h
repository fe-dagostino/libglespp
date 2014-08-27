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


#ifndef GLAUTOPTR_H
#define GLAUTOPTR_H

#include "GLCommonDefs.h"
#include "fedlibrary/include/FString.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale, glm::perspective
 

USING_NAMESPACE_FED

/**
 */
template< class T >
class GLAutoPtr 
{
public:
  /***/
  GLAutoPtr()
  { m_pObject = nullptr; }
  
  /***/
  GLAutoPtr( T* pObject )
  { m_pObject = pObject; }
  
  /***/
  virtual ~GLAutoPtr()
  { 
    if ( m_pObject != nullptr )
    { 
      delete m_pObject;
      m_pObject = nullptr;
    }
  }

  T& operator = ( T* pObject )
  { 
    m_pObject = pObject; 
    return *m_pObject;
  }
  
  T* operator ->()
  { return m_pObject; }
    
  operator T*()
  { return m_pObject; }

protected:

private:
  T* m_pObject;
  
};

#endif // GLAUTOPTR_H
