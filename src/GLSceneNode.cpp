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

#include "../include/GLSceneNode.h"
#include "../include/GLReference.h"

GENERATE_CLASSINFO( GLSceneNode, GLSceneNodeBase )

GLSceneNode::GLSceneNode( const FString& sInstanceName, GLReference* ref )
  : GLSceneNodeBase( sInstanceName, ref )
{
  
}

GLSceneNode::~GLSceneNode()
{  
  for ( auto mmsn : m_mMap )
  {
    for ( auto msn : *(mmsn.second) )
    {
      delete msn.second;
    }
    
    delete mmsn.second;
  }
}

BOOL                               GLSceneNode::addSceneNode( GLSceneNodeBase* pSceneNode )
{  
  // Using RTTI to retrieve instance class name
  FString sClassName = pSceneNode->GetRunTimeInfo()->GetClassName();
  
  std::map< FString, SceneNodeMap* >::const_iterator  _iter = m_mMap.find( sClassName );
  if ( _iter == m_mMap.end() )
  {
    SceneNodeMap* pSceneNodeMap = new SceneNodeMap();
    m_mMap[sClassName] = pSceneNodeMap;
    
    // When map is not present it will be added and then a recursive call to 
    // addSceneNode will add the node to it.
    return addSceneNode( pSceneNode );
  }
  
  SceneNodeMap& rSceneNodeMap = *dynamic_cast<SceneNodeMap*>(_iter->second);
  
  // If a scene node with the same instance name is already present the function return false.
  if ( rSceneNodeMap.find(pSceneNode->getName().GetBuffer()) != rSceneNodeMap.end() )
    return FALSE;
  
  // Scene Node will be registered and then function return TRUE 
  rSceneNodeMap[pSceneNode->getName().GetBuffer()] = pSceneNode;
  
  return OnAddSceneNode( pSceneNode );
}

GLSceneNodeBase*      GLSceneNode::getSceneNode( const FString& sNodeClass, const FString& sInstanceName )
{
  if ( sNodeClass.IsEmpty() || sInstanceName.IsEmpty() )
    return nullptr;
  
  std::map< FString, SceneNodeMap* >::const_iterator  _iter = m_mMap.find( sNodeClass );
  if ( _iter == m_mMap.end() )
    return nullptr;
  
  SceneNodeMap& rSceneNodeMap = *dynamic_cast<SceneNodeMap*>(_iter->second);

  SceneNodeMap::iterator _nodeIterator = rSceneNodeMap.find(sInstanceName.GetBuffer());
  if ( _nodeIterator == rSceneNodeMap.end() )
    return nullptr;
  
  return _nodeIterator->second;
}  

const GLSceneNode::SceneNodeMap*   GLSceneNode::getSceneNodeMap( const FString& sNodeType ) const
{
  std::map< FString, SceneNodeMap* >::const_iterator  _iter = m_mMap.find( sNodeType );
  if ( _iter == m_mMap.end() )
    return nullptr;
  
  return (_iter->second);
}


  
  
  

