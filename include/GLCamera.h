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
   * eg.
   * Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   * glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
   */
  inline GLTransformationsMatrix&     getProjectionMatrix()
  { return m_matProjection; }
  
protected:
  BOOL                    m_bActive;
  GLTransformationsMatrix m_matProjection;
  
};

#endif // GLCAMERA_H
