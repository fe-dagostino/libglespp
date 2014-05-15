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


#include "../include/GLHandleObject.h"


GENERATE_CLASSINFO( GLHandleObject, GLObject )


GLHandleObject::GLHandleObject()
  : m_uiId(0)
{
}

GLHandleObject::~GLHandleObject()
{
}

BOOL    GLHandleObject::isValid() const
{ 
  return (m_uiId!=0);
}


GLuint  GLHandleObject::getId() const
{ 
  return m_uiId;  
}
  
void    GLHandleObject::setId( GLuint uiId )
{ 
  m_uiId = uiId;
}

