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


#ifndef GLVERTICES_H
#define GLVERTICES_H

#include "GLCommonDefs.h"
#include "fedlibrary/include/FString.h"
#include "GLFW/glfw3.h"
#include "GLObject.h"
#include "GLVertex.h"


USING_NAMESPACE_FED

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
class GLVertices : public GLObject
{
public:

  enum MemoryModel {
    eArrayOfStructures,
    eStructureOfArrays
  };
  
  /***/
  GLVertices( MemoryModel eModel, GLint iVertices );

  /***/
  ~GLVertices();

  void usePosition();
  void useNormal();
  void useTextureCoordinate0();
  void useTextureCoordinate1();
  
protected:
private:
  /***/
  void freep( void** pPointer );
  
private:
  MemoryModel     m_eMemoryModel;
  
  GLVertex<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >*       m_pArrayOfStructures;
  
  GLPositionType* m_pPosition;
  GLNormalType*   m_pNormal;
  GLTex0Type*     m_pTex0;
  GLTex1Type*     m_pTex1;
};

#include "GLVertices.inl"

#endif // GLVERTICES_H
