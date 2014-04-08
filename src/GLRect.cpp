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


#include "../include/GLRect.h"

GLRecti::GLRecti()
 : GLRecti( 0, 0, 0, 0 )
{

}

GLRecti::GLRecti( GLsizei l, GLsizei t, GLsizei r, GLsizei b )
 : left(l), top(t), right(r), bottom(b)
{
  
}

GLRecti::GLRecti(const GLRecti& other)
{
  *this = other;
}

GLRecti::~GLRecti()
{

}

GLRecti& GLRecti::operator=(const GLRecti& other)
{
  this->left   = other.left;
  this->top    = other.top;
  this->right  = other.right;
  this->bottom = other.bottom;
  
  return *this;
}

bool GLRecti::operator==(const GLRecti& other) const
{
  return ((this->left   == other.left  ) &&
          (this->top    == other.top   ) &&
          (this->right  == other.right ) &&
          (this->bottom == other.bottom)); 
}

