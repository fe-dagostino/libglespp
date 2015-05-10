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
#include "GLReference.h"
#include "fedlibrary/include/FString.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale, glm::perspective
 

USING_NAMESPACE_FED

/**
 * Intended to manage automatic release of memory into heap.
 * An instance of GLAutoPtr will automatically release
 * the internal pointer on destructor. In case pointed memory
 * is an object derived form GLReference then memory
 * will be released only if reference counter is zero. 
 */
template< class T >
class GLAutoPtr 
{
public:
  /***/
  GLAutoPtr()
   : m_pObject( nullptr )
  {  }
  
  /***/
  GLAutoPtr( T* pObject )
   : GLAutoPtr()
  { *this = pObject; }
  
  /***/
  virtual ~GLAutoPtr()
  { 
    release();
  }

  T& operator = ( T* pObject )
  { 
    // Release previous allocated memory.
    // Instance can be re-used or updated with a new pointer.
    release();
    
    m_pObject = pObject;
    
    GLReference* ref = dynamic_cast<GLReference*>(m_pObject);
    if ( ref != nullptr )
    {
      (*ref)++;
    }    
    
    return *m_pObject;
  }
  
  /**
   * Detach current pointer without to release it.
   * In case the pointer is and instance of GLReference*
   * then that instance reference count will be decreased
   * by one in order to balance increasing done during init. 
   */
  T* detach()
  {
    T*           ret = m_pObject;
    GLReference* ref = dynamic_cast<GLReference*>(m_pObject);
    if ( ref != nullptr )
    {
      (*ref)--;
    }    
    
    m_pObject = nullptr;
    
    return ret;
  }
    
  const T* operator->() const
  { return m_pObject; }
  
  T* operator->()
  { return m_pObject; }
      
  operator T*()
  { return m_pObject; }
  
  operator const T*() const
  { return m_pObject; }
  
  operator T*() const
  { return m_pObject; }


protected:
private:
  /***/
  VOID release()
  {
    GLReference* ref = dynamic_cast<GLReference*>(m_pObject);
    if ( ref != nullptr )
    {
      (*ref)--;
      if ( ref->count() == 0 )
      {
	delete m_pObject;
	m_pObject = nullptr;
      }
    }
    else
    if ( m_pObject != nullptr )
    { 
      delete m_pObject;
      m_pObject = nullptr;
    }
  }
  
private:
  T* m_pObject;
  
};

#endif // GLAUTOPTR_H
