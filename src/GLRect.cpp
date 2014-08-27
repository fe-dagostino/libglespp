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

