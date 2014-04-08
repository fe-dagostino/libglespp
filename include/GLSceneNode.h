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


#ifndef GLSCENENODE_H
#define GLSCENENODE_H

#include "GLCommonDefs.h"
#include <map>
#include "FString.h"
#include "GLObject.h"
#include "GLSceneNodeBase.h"
#include "glm/glm.hpp"

USING_NAMESPACE_FED

class GLReference;

class GLSceneNode : public GLSceneNodeBase
{
  ENABLE_FRTTI(GLSceneNode)
public:
  /***/
  GLSceneNode( const FString& sInstanceName, GLReference* ref );
  /***/
  virtual ~GLSceneNode();

  /***/
  BOOL                  addSceneNode( GLSceneNodeBase* pSceneNode );
  /**
   */
  GLSceneNodeBase*      getSceneNode( const FString& sNodeClass, const FString& sInstanceName );

  /**
   * @param pCamera    pointer to the active camera it will provide
   *                   projection matrix.
   */
  virtual BOOL    render( GLCamera* pCamera, const glm::mat4& mView ) = 0;
  
  
protected:
  /***/
  virtual BOOL                  OnAddSceneNode( GLSceneNodeBase* pSceneNode ) { return TRUE; };
  
  
protected:
  struct lstr
  {
    bool operator()( const char* pKey1, const char* pKey2 ) const
    {	return ( strcmp(pKey1, pKey2 )  < 0);	}
  };

  typedef std::map<const char*, GLSceneNodeBase*, lstr>  SceneNodeMap;

  /***/
  const SceneNodeMap*   getSceneNodeMap( const FString& sNodeType ) const;
    
protected:
  std::map< FString, SceneNodeMap*, lstr >   m_mMap;
};

#endif // GLSCENENODE_H
