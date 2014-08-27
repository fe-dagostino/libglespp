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


#ifndef GLSCENENODEBASE_H
#define GLSCENENODEBASE_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "GLViewPort.h"
#include "GLReference.h"


class GLCamera;
class GLAnimation;

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
  
  /***/
  GLAnimation*                 getAnimation();
  /***/
  GLAnimation*                 setAnimation( GLAnimation* ref );
  
  /**
   * @param pCamera    pointer to the active camera it will provide
   *                   projection matrix.
   */
  virtual BOOL    render( const glm::mat4& mProjection, GLCamera* pCamera ) = 0;
  
protected:
  /***/
  virtual VOID    OnSetReference( GLReference* ref ) {}
  /***/
  virtual VOID    OnSetAnimation( GLAnimation* ani ) {}
  
  
private:
  const FString           m_sInstanceName;
  GLAutoRef<GLReference>  m_ref;
  GLAutoRef<GLAnimation>  m_ani;
  
};

#endif // GLSCENENODEBASE_H
