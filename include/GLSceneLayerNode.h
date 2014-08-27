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


#ifndef GLSCENELAYERNODE_H
#define GLSCENELAYERNODE_H

#include "GLCommonDefs.h"
#include "GLSceneNode.h"
#include "widgets/GLLayer.h"
#include "GLProgram.h"
#include "GLTransformationsMatrix.h"


/**
 */
class GLSceneLayerNode : public GLSceneNode
{
  ENABLE_FRTTI(GLSceneLayerNode)
public:
  /**
   * @param sInstanceName it must be an unique name for the scene where it can be
   *                      addressed using this name.
   * @param layer         a pointer to GLText instance; this instance can be shared
   *                      between more nodes.
   */
  GLSceneLayerNode( const FString& sInstanceName, GLLayer* layer );
  /***/
  virtual ~GLSceneLayerNode();
  
  /***/  
  virtual BOOL render( const glm::mat4& mProjection, GLCamera* pCamera );
  
  /***/
  inline  GLTransformationsMatrix&   getMatrixModel()
  { return m_matModel; }
  
private:
  GLTransformationsMatrix   m_matModel;
};

#endif // GLSCENELAYERNODE_H
