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


#ifndef GLVERTICES_H
#define GLVERTICES_H

#include "GLCommonDefs.h"
#include "FString.h"
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
