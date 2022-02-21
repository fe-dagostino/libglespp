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


#include "GLCamera.h"

#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale, glm::perspective


GLCamera::GLCamera( BOOL bActivate )
 : GLReference(), m_bActive( bActivate ),
   m_vPosition( 0, 0, 0 ), m_vCenter( 0, 0, 0 ), m_vUp( 0, 0, 0 )
{
  lookAt();
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

void                GLCamera::setPosition( const glm::vec3& vPos )
{
  m_vPosition     = vPos;
  lookAt();
}

void                GLCamera::setCenter( const glm::vec3& vCenter )
{
  m_vCenter       = vCenter;
  lookAt();
}

void                GLCamera::setUp( const glm::vec3& vUp )
{
  m_vUp           = vUp;
  lookAt();
}

void                GLCamera::lookAt()
{
  m_matView.get() = glm::lookAt( m_vPosition, m_vCenter, m_vUp );
}

