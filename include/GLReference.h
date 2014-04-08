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


#ifndef GLREFERENCE_H
#define GLREFERENCE_H

#include "GLCommonDefs.h"
#include "FObject.h"

USING_NAMESPACE_FED

/**
 * Used to add references count.
 */
class GLReference
{
public:
  /***/
  GLReference();
  /***/
  virtual ~GLReference();
  
  /**
   * Increase references count by one.
   */
  GLReference&   operator++(int);
  /**
   * Decrease references count by one.
   */
  GLReference&   operator--(int);
  /**
   * Return references counter.
   */
  inline DWORD   count() const
  { return m_dwCount; }
  
private:
  DWORD  m_dwCount;
};


/**
 * Used to automate counter increment/decrement
 */
template< class T >
class GLAutoRef
{
public:
  
  GLAutoRef()
    : m_pRef( nullptr )
  { }
  
  GLAutoRef( T* ref )
    : m_pRef( ref )
  {
    attach(ref);
  }
  
  ~GLAutoRef()
  {
    detach();
  }
  
  bool attach( T* ref )
  { 
    if ( m_pRef != nullptr )
      return false;
      
    m_pRef = ref; 
    if (m_pRef != nullptr )
    {
      (*(GLReference*)ref)++;
    }
    
    return true;
  }
  
  GLReference*   detach()
  {
    GLReference* ref = (GLReference*)m_pRef;
    
    if (ref != nullptr )
    {
      m_pRef = nullptr;
      (*ref)--;
    }
    
    return ref;
  }
  
  operator const T*() const
  { return m_pRef; }
  
  operator T*()
  { return m_pRef; }
  
private:
  T* m_pRef;
};

#endif // GLREFERENCE_H
