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


#include "../include/GLSceneLayerNode.h"

#include "../include/GLVertexShader.h"
#include "../include/GLFragmentShader.h"
#include "../include/GLCamera.h"
#include "../include/GLAnimation.h"

#include "fedlibrary/include/LOGGING/FLogger.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

USING_NAMESPACE_LOGGING

GENERATE_CLASSINFO( GLSceneLayerNode, GLSceneNode )


GLSceneLayerNode::GLSceneLayerNode( const FString& sInstanceName, GLLayer* layer )
 : GLSceneNode( sInstanceName, layer )
{
  // Init model matrix
  m_matModel = glm::mat4( 1.0f );
}
  
GLSceneLayerNode::~GLSceneLayerNode()
{
}  
  
BOOL GLSceneLayerNode::render( const glm::mat4& mProjection, GLCamera* pCamera )
{
  GLLayer* layer = dynamic_cast<GLLayer*>(getReference());
  if ( layer == nullptr )
    return FALSE;
  
  if ( layer->isVisible() == FALSE )
    return FALSE;

  // Retrieving camera (view) matrix from active camera.
  // If not present an identity matrix will be used.
  glm::mat4  mView = (pCamera==nullptr)?glm::mat4(1.0f):pCamera->getViewMatrix().get();
  
  glm::mat4  mvp =  mProjection * mView * m_matModel.get();
  if (getAnimation() != nullptr)
    mvp *= getAnimation()->getMatrix().get();
  
  return layer->render( mvp );
}

