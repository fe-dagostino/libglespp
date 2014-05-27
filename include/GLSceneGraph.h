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


#ifndef GLSCENEGRAPH_H
#define GLSCENEGRAPH_H

#include "GLCommonDefs.h"
#include "FString.h"

#include "GLFW/glfw3.h"
#include "GLSceneNode.h"
#include "GLSceneCameraNode.h"

#include <map>
#include <vector>
#include <functional>

USING_NAMESPACE_FED


class GLSceneGraph : public GLSceneNode
{
public:
 
  /***/
  GLSceneGraph();

  /***/
  ~GLSceneGraph();
  
  /**
   * Return current active camera that will be used during render operation.
   * If there is no camera, return value will be nullptr and identity matrix
   * will be used for render.
   */
  const GLSceneCameraNode*  getActiveCamera() const;
  
  
  /***/
  VOID    setBackground( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
  /***/
  VOID    getBackground( GLclampf& red, GLclampf& green, GLclampf& blue, GLclampf& alpha );
  
  /***/
  BOOL    render( const glm::mat4& mProjection );
  
protected:  
  /**
   * Iterate on all childs in order to render them.
   * 
   * @todo implements rendering order
   */
  virtual BOOL render( const glm::mat4& mProjection, GLCamera* pCamera );

  /***/
  virtual BOOL OnAddSceneNode( GLSceneNodeBase* pSceneNode );
  
private:
  GLclampf   m_red, m_green, m_blue, m_alpha;  

  std::vector<GLSceneNodeBase*>    m_vRender;
};

#endif // GLSCENEGRAPH_H
