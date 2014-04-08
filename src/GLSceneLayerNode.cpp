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


#include "../include/GLSceneLayerNode.h"

#include "../include/GLVertexShader.h"
#include "../include/GLFragmentShader.h"
#include "../include/GLCamera.h"

#include "fedlibrary/include/LOGGING/FLogger.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

USING_NAMESPACE_LOGGING

GENERATE_CLASSINFO( GLSceneLayerNode, GLSceneNode )


GLSceneLayerNode::GLSceneLayerNode( const FString& sInstanceName, GLLayer* layer )
 : GLSceneNode( sInstanceName, layer )
{
  // Init model matrix
  m_matModel.get() = glm::mat4( 1.0f );
  
  if ( layer != nullptr )
  {
    GLint   x,y;
    GLsizei width, height;
    
    layer->getViewPort().getArea( x,y, width, height );
    
    m_matModel.get() = glm::ortho( (float)x, (float)width, (float)height, (float)y );
  }    
}
  
GLSceneLayerNode::~GLSceneLayerNode()
{
}  
  
BOOL GLSceneLayerNode::render( GLCamera* pCamera, const glm::mat4& mView )
{
  GLLayer* layer = dynamic_cast<GLLayer*>(getReference());
  if ( layer == nullptr )
    return FALSE;
  
  if ( layer->isVisible() == FALSE )
    return FALSE;
  
  // Retrieving projection matrix from active camera.
  // If not present an identity matrix will be used.
  glm::mat4  mProjection = (pCamera==nullptr)?glm::mat4(1.0f):pCamera->getProjectionMatrix().get();
  
  glm::mat4  mvp = mProjection * mView * m_matModel.get();

  return layer->render( mvp );
}