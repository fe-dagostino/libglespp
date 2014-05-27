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


#include "../include/GLViewPort.h"


GLViewPort::GLViewPort( )
  : m_pSceneGraph( NULL )
{
  m_matProjection.get() = glm::mat4( 1.0f );
}

GLViewPort::GLViewPort( GLSceneGraph* pSceneGraph, const glm::mat4& mProjection )
  : m_pSceneGraph( pSceneGraph )
{
  m_matProjection.get() = mProjection;
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

VOID GLViewPort::setArea( GLint x, GLint y, GLsizei width, GLsizei height )
{
  glViewport( x, y, width, height );
}

VOID GLViewPort::getArea( GLint& x, GLint& y, GLsizei& width, GLsizei& height )
{
  GLint viewport[4];
  
  glGetIntegerv(GL_VIEWPORT, viewport);
  
  x      = viewport[0];
  y      = viewport[1];
  width  = viewport[2];
  height = viewport[3];
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