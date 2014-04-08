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


#ifndef GLSCENENODEBASE_H
#define GLSCENENODEBASE_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "GLReference.h"

class GLCamera;

/**
 */
class GLSceneNodeBase : public GLObject
{
  ENABLE_FRTTI(GLSceneNodeBase)
public:
  /***/
  GLSceneNodeBase( const FString& sInstanceName, GLReference* pRef );
  /***/
  virtual ~GLSceneNodeBase();
  
  /**
   * Return node instance name.
   */
  inline const FString&        getName() const
  { return m_sInstanceName; }

  /**
   * Return node type
   */
  const FRTTI*                 getRunTimeTypeInfo() const;

  /***/
  inline const GLReference*    getReference() const
  { return m_ref; }

  /***/
  inline GLReference*          getReference()
  { return m_ref; }

  /**
   * Method will set the new reference returning the previous one.
   * Note that counter on new reference will be increased by one
   * instead counter on old reference will be decreased by one and
   * if returned reference counter is ZERO it means that it is not
   * referenced so must be attached to a different node or released.
   */
  GLReference*                 setReference( GLReference* ref );
  
  /**
   * @param pCamera    pointer to the active camera it will provide
   *                   projection matrix.
   */
  virtual BOOL    render( GLCamera* pCamera, const glm::mat4& mView ) = 0;
  
protected:
  /***/
  virtual VOID    OnSetReference( GLReference* ref ) {}
  
private:
  const FString           m_sInstanceName;
  GLAutoRef<GLReference>  m_ref;
};

#endif // GLSCENENODEBASE_H
