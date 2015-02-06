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
class GLImage : public GLObject, public GLReference
{
  ENABLE_FRTTI( GLImage )
public:
  enum ImageLoader
  {
    eilFreeImage,
    eilLibAV,
    eilDevIL
  };
  
  /***/
  GLImage();
  /***/
  virtual ~GLImage();
  
  /**
   * Loading image using FreeImage library.
   * 
   */
  GLboolean       load( ImageLoader il, const FString& sFilename );
  
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
