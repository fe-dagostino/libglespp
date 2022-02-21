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


#include "GLExtensions.h"
#include "FDynamicLibrary.h"
#include "FStringTokenizer.h"
#include "GL/glx.h"

USING_NAMESPACE_FED

GLExtensions::GLExtensions()
{
  init();
}

GLExtensions::~GLExtensions()
{
  
}
  

BOOL    GLExtensions::init()
{
  const GLubyte*  pRet = glGetString(GL_EXTENSIONS);
  if ( pRet == NULL )
    return FALSE;
  
  FStringTokenizer  _sTokenizer( (const CHAR*)pRet, " ");
  
  FString           _sToken = _sTokenizer.GetNextToken();
  while ( _sToken.IsEmpty() == FALSE )
  {
    
    _sToken = _sTokenizer.GetNextToken();
  }
  
  return TRUE;
}
