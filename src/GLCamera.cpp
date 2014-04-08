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


#include "../include/GLCamera.h"

#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale, glm::perspective


GLCamera::GLCamera( BOOL bActivate )
 : GLReference(), m_bActive( bActivate )
{
  m_matProjection.get() = glm::mat4(1.0);
}

GLCamera::~GLCamera()
{

}

BOOL                GLCamera::setActive( BOOL bActive )
{
  BOOL    _bPrevValue = m_bActive;
  
  m_bActive = bActive;
  
  return  _bPrevValue;
}



