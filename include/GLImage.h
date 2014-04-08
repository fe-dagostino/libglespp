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


#ifndef GLIMAGE_H
#define GLIMAGE_H

#include "GLCommonDefs.h"
#include "GLReference.h"
#include "GLTexture.h"

#include "GLFW/glfw3.h"

#include "FString.h"

USING_NAMESPACE_FED

/**
 */
class GLImage : public GLReference
{
public:
  /***/
  GLImage();
  /***/
  virtual ~GLImage();
  
#ifdef _USE_FREEIMAGE  
  /**
   * Loading image using FreeImage library.
   * 
   */
  GLboolean       fiLoad( const FString& sFilename );
#endif //_USE_FREEIMAGE
#ifdef _USE_AVCPP
  GLboolean       avLoad( const FString& sFilename );
#endif //_USE_AVCPP
  
  /***/
  inline GLint    getWidth() const
  { return m_iWidth; }
  /***/
  inline GLint    getHeight() const
  { return m_iHeight; }
  /***/
  inline GLubyte* getData()
  { return m_pData; }
  
public:
  GLuint        m_uiDataSize;
  GLint         m_iWidth;
  GLint         m_iHeight;
  GLubyte*      m_pData;
  
};

#endif // GLIMAGE_H
