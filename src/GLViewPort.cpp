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


#include "GLViewPort.h"
#include "GLSceneGraph.h"


GLViewPort::GLViewPort( )
  : m_pSceneGraph( NULL ), m_pos( 0.0f, 0.0f ), m_size( 2, 2 )
{
  m_matProjection.get() = glm::mat4( 1.0f );
  
  reset();
}

GLViewPort::GLViewPort( GLSceneGraph* pSceneGraph, const glm::mat4& mProjection )
  : m_pSceneGraph( pSceneGraph ), m_pos( 0.0f, 0.0f ), m_size( 2, 2 )
{
  m_matProjection.get() = mProjection;
  
  reset();
}

GLViewPort::~GLViewPort()
{
  
}

GLSceneGraph* GLViewPort::setScene( GLSceneGraph* pSceneGraph )
{
  GLSceneGraph* pRetVal = m_pSceneGraph;
  
  m_pSceneGraph = pSceneGraph;
  
  return pRetVal;
}

GLSceneGraph* GLViewPort::getScene() const
{
  return m_pSceneGraph;
}

VOID GLViewPort::use()
{
  glViewport( m_pos.x, m_pos.y, m_size.width, m_size.height );
}

VOID GLViewPort::reset()
{
  GLint viewport[4];	
  glGetIntegerv(GL_VIEWPORT, viewport);
  
  setArea( viewport[0], viewport[1], viewport[2], viewport[3] );
}

VOID GLViewPort::setArea( GLint x, GLint y, GLsizei width, GLsizei height )
{
  m_pos.x       = x;
  m_pos.y       = y;
  m_size.width  = width;
  m_size.height = height;  
}

VOID GLViewPort::getArea( GLint& x, GLint& y, GLsizei& width, GLsizei& height ) const
{
  x      = m_pos.x;
  y      = m_pos.y;
  width  = m_size.width;
  height = m_size.height;
}


VOID GLViewPort::clearBuffer( GLbitfield mask )
{
  glClear( mask );
}

BOOL GLViewPort::render()
{
  if ( m_pSceneGraph == NULL )
    return FALSE;
  
  m_pSceneGraph->render( getProjectionMatrix().get() );
  
  return TRUE;
}
