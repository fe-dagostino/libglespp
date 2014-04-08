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
  virtual BOOL render( GLCamera* pCamera, const glm::mat4& mView );

protected:
  
};

#endif // GLSCENECAMERANODE_H
