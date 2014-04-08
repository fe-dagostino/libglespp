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


#include "../include/GLSceneNodeBase.h"
#include "../include/GLReference.h"

GENERATE_CLASSINFO(GLSceneNodeBase, GLObject)

GLSceneNodeBase::GLSceneNodeBase( const FString& sInstanceName, GLReference* pRef )
 : m_sInstanceName( sInstanceName )
{
  m_ref.attach(pRef);
}

GLSceneNodeBase::~GLSceneNodeBase()
{
  GLReference* pRef = m_ref.detach();
  if ( pRef != nullptr )
  {
    if (pRef->count() == 0 )
    {
      delete pRef;
    }
  }
}

const FRTTI*          GLSceneNodeBase::getRunTimeTypeInfo() const
{
  return GetRunTimeInfo();
}  

GLReference*          GLSceneNodeBase::setReference( GLReference* ref )
{
  GLReference*  pOldRef = m_ref.detach();

  m_ref.attach(ref);
  
  OnSetReference( ref );
  
  return pOldRef;
}
