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


#ifndef GLOBJECT_H
#define GLOBJECT_H

#include "GLCommonDefs.h"
#include "fedlibrary/include/FString.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale, glm::perspective
 

USING_NAMESPACE_FED

/**
 */
class GLObject : public FObject
{
  ENABLE_FRTTI(GLObject)
public:
  /***/
  GLObject();
  /***/
  virtual ~GLObject();

protected:

private:
  
};

#endif // GLOBJECT_H
