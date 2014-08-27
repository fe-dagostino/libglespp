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


#ifndef GLSCENECAMERANODE_H
#define GLSCENECAMERANODE_H

#include "GLCommonDefs.h"
#include "FObject.h"
#include "GLCamera.h"
#include "GLSceneNodeBase.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

USING_NAMESPACE_FED

class GLSceneCameraNode : public GLSceneNodeBase
{
  ENABLE_FRTTI(GLSceneCameraNode)
public:
  /***/
  GLSceneCameraNode( const FString& sInstanceName, GLCamera* cam );
  /***/
  virtual ~GLSceneCameraNode();
  
  /***/
  inline const GLCamera* getCamera() const 
  { return dynamic_cast<const GLCamera*>( getReference() ); }
  inline GLCamera*       getCamera()
  { return dynamic_cast<GLCamera*>( getReference() ); }

  /***/  
  virtual BOOL render( const glm::mat4& mProjection, GLCamera* pCamera );

protected:
  
};

#endif // GLSCENECAMERANODE_H
