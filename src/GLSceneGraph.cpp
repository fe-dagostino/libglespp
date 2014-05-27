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


#include "../include/GLSceneGraph.h"

#define GLM_FORCE_RADIANS
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale, glm::perspective

GLSceneGraph::GLSceneGraph( )
  : GLSceneNode( "Root", nullptr ),
    m_red(0.0f), m_green(0.0f), m_blue(0.0f), m_alpha(1.0f)
{
  //m_matView.get() = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
}

GLSceneGraph::~GLSceneGraph()
{
  
}

VOID        GLSceneGraph::setBackground( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
  m_red   = red;
  m_green = green;
  m_blue  = blue;
  m_alpha = alpha;
}

VOID GLSceneGraph::getBackground( GLclampf& red, GLclampf& green, GLclampf& blue, GLclampf& alpha )
{
  red     = m_red;
  green   = m_green;
  blue    = m_blue;
  alpha   = m_alpha;
}

const GLSceneCameraNode*  GLSceneGraph::getActiveCamera() const
{
  const GLSceneNode::SceneNodeMap* mapCameras = getSceneNodeMap( "GLSceneCameraNode" );
  if ( mapCameras == nullptr )
    return nullptr;
  
  for( auto NodeBasePtr : *mapCameras )
  {
    const GLSceneCameraNode* pCameraNode = dynamic_cast<const GLSceneCameraNode*>(NodeBasePtr.second);
    if ( pCameraNode->getCamera()->isActive() )
      return pCameraNode;
  }
  
  return nullptr;
}
  
BOOL GLSceneGraph::render( const glm::mat4& mProjection )
{
  const GLSceneCameraNode* pActiveCamera = getActiveCamera();
  GLCamera*                pCamera       = (pActiveCamera!=nullptr)?(GLCamera*)pActiveCamera->getCamera():nullptr; 

  return render( mProjection, pCamera );
}

BOOL GLSceneGraph::render( const glm::mat4& mProjection, GLCamera* pCamera )
{ 
  ///////////////////
  // Reset background color
  glClearColor( m_red, m_green, m_blue, m_alpha );
  
  /*
  for ( auto snm : m_mMap )
  {
    for ( auto sn : *(snm.second) )
    {
      GLSceneNodeBase* node = dynamic_cast<GLSceneNodeBase*>(sn.second);
      
      node->render( pCamera, mView );
    }
  }*/
  for ( auto n : m_vRender )
  {
    n->render( mProjection, pCamera );
  }
  
  return TRUE; 
}
 
BOOL GLSceneGraph::OnAddSceneNode( GLSceneNodeBase* pSceneNode )
{
  m_vRender.push_back( pSceneNode );
  return TRUE;
}



