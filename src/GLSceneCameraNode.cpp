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


#include "../include/GLSceneCameraNode.h"


GENERATE_CLASSINFO( GLSceneCameraNode, GLSceneNodeBase )

GLSceneCameraNode::GLSceneCameraNode( const FString& sInstanceName, GLCamera* cam )
 : GLSceneNodeBase( sInstanceName, cam )
{
  
}

GLSceneCameraNode::~GLSceneCameraNode()
{

}

BOOL GLSceneCameraNode::render( const glm::mat4& mProjection, GLCamera* pCamera )
{
  return TRUE;
}
