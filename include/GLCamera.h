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


#ifndef GLCAMERA_H
#define GLCAMERA_H

#include "GLCommonDefs.h"
#include "FObject.h"
#include "GLSceneNodeBase.h"
#include "GLReference.h"
#include "GLTransformationsMatrix.h"
#include "glm/glm.hpp"

USING_NAMESPACE_FED


class GLCamera : public GLReference
{
public:
  
  /***/
  GLCamera( BOOL bActivate );
  /***/
  virtual ~GLCamera();
  
  /**
   */
  inline BOOL                         isActive() const
  { return m_bActive; }
  /***/
  BOOL                                setActive( BOOL bActive );
  
  /**
   * glm::vec3 cameraPosition = glm::vec3(4,3,3); // Camera is at (4,3,3), in World Space
   * glm::vec3 cameraTarget   = glm::vec3(0,0,0); // and looks at the origin
   * glm::vec3 upVector       = glm::vec3(0,1,0);  // Head is up (set to 0,-1,0 to look upside-down)
   *
   * glm::mat4 CameraMatrix = glm::lookAt(
   *                                         cameraPosition, // the position of your camera, in world space
   *                                         cameraTarget,   // where you want to look at, in world space
   *                                         upVector        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
   *                                     );
   */
  inline GLTransformationsMatrix&     getViewMatrix()
  { return m_matView; }
  
  /***/  
  const glm::vec3&                    getPosition() const
  { return m_vPosition; }
  /***/
  void                                setPosition( const glm::vec3& vPos );
  
  /***/
  const glm::vec3&                    getCenter() const
  { return m_vCenter; }
  /***/
  void                                setCenter( const glm::vec3& vCenter );

  /***/
  const glm::vec3&                    getUp() const
  { return m_vUp; }
  /***/
  void                                setUp( const glm::vec3& vUp );
  
private:
  /***/
  void lookAt();
  
protected:
  BOOL                    m_bActive;
  GLTransformationsMatrix m_matView;
  
  glm::vec3 m_vPosition;  // Camera Position (eyes)
  glm::vec3 m_vCenter;    // Where the camera is pointed to
  glm::vec3 m_vUp;        // Top of the camera
};

#endif // GLCAMERA_H
