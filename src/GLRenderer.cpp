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


#include "../include/GLRenderer.h"

GLRenderer::GLRenderer()
  : m_glExtensions( NULL )
{
  
}

GLRenderer::~GLRenderer()
{
  
}
  
BOOL     GLRenderer::getVendor  ( FString& sVendor   )
{
  const GLubyte*  pRet = glGetString(GL_VENDOR);
  if ( pRet == nullptr )
    return FALSE;
  
  sVendor.Format( 0, "%s", pRet );

  return TRUE;
}

BOOL     GLRenderer::getRenderer( FString& sRenderer )
{
  const GLubyte*  pRet = glGetString(GL_RENDERER);
  if ( pRet == nullptr )
    return FALSE;
  
  sRenderer.Format( 0, "%s", pRet );

  return TRUE;  
}
  
BOOL     GLRenderer::getVersion( FString& sVersion )
{
  const GLubyte*  pRet = glGetString(GL_VERSION);
  if ( pRet == nullptr )
    return FALSE;
  
  sVersion.Format( 0, "%s", pRet );

  return TRUE;  
}

BOOL     GLRenderer::getShaderVersion( FString& sShaderVersion )
{
  const GLubyte*  pRet = glGetString(GL_SHADING_LANGUAGE_VERSION);
  if ( pRet == nullptr )
    return FALSE;
  
  sShaderVersion.Format( 0, "%s", pRet );

  return TRUE;  
}

GLExtensions* GLRenderer::getExtensions()
{
  if ( m_glExtensions == nullptr )
  {
    m_glExtensions = new GLExtensions();
  }
  
  return m_glExtensions;
}


