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


#ifndef GLVERTEX_H
#define GLVERTEX_H

#include "GLCommonDefs.h"
#include "fedlibrary/include/FString.h"
#include "GLFW/glfw3.h"
#include "GLObject.h"


USING_NAMESPACE_FED

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
class GLVertex : public GLObject
{
public:
  
  /***/
  GLVertex();

  /***/
  ~GLVertex();
  
protected:
  
private:
  
  GLPositionType  m_Position[3];
  GLPositionType  m_Normal[3];
  GLTex0Type      m_Texture0[2];
  GLTex1Type      m_Texture1[2];
};

#include "GLVertex.inl"

#endif // GLVERTEX_H
