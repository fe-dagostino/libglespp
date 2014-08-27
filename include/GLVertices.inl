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


#define VERTEX_POS_SIZE            3  // x, y and z
#define VERTEX_NORMAL_SIZE         3  // x, y and z
#define VERTEX_TEXCOORD0_SIZE      2  // s and t
#define VERTEX_TEXCOORD1_SIZE      2  // s and t
#define VERTEX_POS_INDX            0
#define VERTEX_NORMAL_INDX         1
#define VERTEX_TEXCOORD0_INDX      2
#define VERTEX_TEXCOORD1_INDX      3

// the following 4 defines are used to determine location of various
// attributes if vertex data is are stored as an array of structures
#define VERTEX_POS_OFFSET          0
#define VERTEX_NORMAL_OFFSET       3
#define VERTEX_TEXCOORD0_OFFSET    6
#define VERTEX_TEXCOORD1_OFFSET    8

#define VERTEX_ATTRIB_SIZE     (VERTEX_POS_SIZE + VERTEX_NORMAL_SIZE + VERTEX_TEXCOORD0_SIZE + VERTEX_TEXCOORD1_SIZE)

template<typename GLDataType>
unsigned short getGLType()
{
  if ( typeid( GLDataType ) == typeid( int ) )
    return GL_INT;
  
  if ( typeid( GLDataType ) == typeid( float ) )
    return GL_FLOAT;
  
  return 0x0000;
}


template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::GLVertices(MemoryModel eModel, GLint iVertices )
 :   m_eMemoryModel(eModel), m_pArrayOfStructures( NULL ), m_pPosition( NULL ), m_pNormal( NULL ), m_pTex0( NULL ), m_pTex1( NULL )
{
  if ( m_eMemoryModel == eArrayOfStructures )
  {
    m_pArrayOfStructures = (GLVertex<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >*)malloc(iVertices * sizeof(GLVertex<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >));
  }
  
  if ( m_eMemoryModel == eStructureOfArrays )
  {  
    m_pPosition = (GLPositionType*)malloc(iVertices * VERTEX_POS_SIZE       * sizeof(GLPositionType) );
    m_pNormal   = (GLNormalType  *)malloc(iVertices * VERTEX_NORMAL_SIZE    * sizeof(GLNormalType)   );
    m_pTex0     = (GLTex0Type    *)malloc(iVertices * VERTEX_TEXCOORD0_SIZE * sizeof(GLTex0Type)     );
    m_pTex1     = (GLTex1Type    *)malloc(iVertices * VERTEX_TEXCOORD1_SIZE * sizeof(GLTex1Type)     );
  }
}

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::~GLVertices()
{
  if ( m_eMemoryModel == eArrayOfStructures )
  {
    freep( (void**)&m_pArrayOfStructures );
  }
  
  if ( m_eMemoryModel == eStructureOfArrays )
  {
    freep( (void**)&m_pPosition );
    freep( (void**)&m_pNormal   );
    freep( (void**)&m_pTex0     );
    freep( (void**)&m_pTex1     );
  }
}

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
void GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::usePosition()
{
  if ( m_eMemoryModel == eArrayOfStructures )
  {
    // m_pPosition is vertex attribute 0
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, getGLType<GLPositionType>(), GL_FALSE, sizeof(GLVertex<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >), m_pArrayOfStructures);
  }
  
  if ( m_eMemoryModel == eStructureOfArrays )
  {
    // m_pPosition is vertex attribute 0
    glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, getGLType<GLPositionType>(), GL_FALSE, VERTEX_POS_SIZE * sizeof(GLPositionType), m_pPosition);
  }
}

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
void GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::useNormal()
{
  if ( m_eMemoryModel == eArrayOfStructures )
  {
    // m_pNormal is vertex attribute 1
    //glVertexAttribPointer(VERTEX_NORMAL_INDX, VERTEX_NORMAL_SIZE, getGLType<GLNormalType>(), GL_FALSE, sizeof(GLVertex<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >), m_pArrayOfStructures  );
  }
  
  if ( m_eMemoryModel == eStructureOfArrays )
  {
    // m_pNormal is vertex attribute 1
    glVertexAttribPointer(VERTEX_NORMAL_INDX, VERTEX_NORMAL_SIZE, getGLType<GLNormalType>(), GL_FALSE, VERTEX_NORMAL_SIZE * sizeof(GLNormalType), m_pNormal);
  }
}

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
void GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::useTextureCoordinate0()
{
  if ( m_eMemoryModel == eArrayOfStructures )
  {
  }
  
  if ( m_eMemoryModel == eStructureOfArrays )
  {
    // texture coordinate 0 is vertex attribute 2
    glVertexAttribPointer(VERTEX_TEXCOORD0_INDX, VERTEX_TEXCOORD0_SIZE, getGLType<GLTex0Type>, GL_FALSE, VERTEX_TEXCOORD0_SIZE * sizeof(GLTex0Type), m_pTex0);
  }  
}

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
void GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::useTextureCoordinate1()
{
  if ( m_eMemoryModel == eArrayOfStructures )
  {
  }
  
  if ( m_eMemoryModel == eStructureOfArrays )
  {
    // texture coordinate 1 is vertex attribute 3
    glVertexAttribPointer(VERTEX_TEXCOORD1_INDX, VERTEX_TEXCOORD1_SIZE, getGLType<GLTex1Type>, GL_FALSE, VERTEX_TEXCOORD1_SIZE * sizeof(GLTex1Type), m_pTex1);
  }
}

template<typename GLPositionType, typename GLNormalType, typename GLTex0Type, typename GLTex1Type >
void GLVertices<GLPositionType, GLNormalType, GLTex0Type, GLTex1Type >::freep( void** pPointer )
{
  if ( pPointer == NULL )
    return;
  
  free( pPointer );
  pPointer = NULL;
}



