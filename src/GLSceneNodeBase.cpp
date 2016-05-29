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


#include "../include/GLSceneNodeBase.h"
#include "../include/GLReference.h"

GENERATE_CLASSINFO(GLSceneNodeBase, GLObject)

GLSceneNodeBase::GLSceneNodeBase( const FString& sInstanceName, GLReference* pRef )
 : m_sInstanceName( sInstanceName ), m_ref( pRef )
{
  
}

GLSceneNodeBase::~GLSceneNodeBase()
{
}

const FRTTI*          GLSceneNodeBase::getRunTimeTypeInfo() const
{
  return GetRunTimeInfo();
}  

GLReference*          GLSceneNodeBase::setReference( GLReference* ref )
{
  GLReference*  pOldRef = m_ref.detach();

  m_ref = ref;
  
  OnSetReference( ref );
  
  return pOldRef;
}

GLAnimation*          GLSceneNodeBase::getAnimation()
{
  return m_ani;
}

GLAnimation*          GLSceneNodeBase::setAnimation( GLAnimation* ani )
{
  GLAnimation*  pOldAni = m_ani.detach();

  m_ani = ani;
  
  OnSetAnimation( ani );
  
  return pOldAni;
}


