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


#ifndef GLSCENEMODELNODE_H
#define GLSCENEMODELNODE_H

#include "GLSceneNode.h"
#include "GLModel.h"


class GLSceneModelNode : public GLSceneNode
{
  ENABLE_FRTTI(GLSceneModelNode)
public:
  /***/
  GLSceneModelNode( const FString& sInstanceName, GLModel* text );
  /***/
  virtual ~GLSceneModelNode();
  
  /***/  
  virtual BOOL render( const GLCamera* pCamera, const glm::mat4& mView );
  
private:
  glm::mat4         m_matModel;

};

#endif // GLSCENEMODELNODE_H
