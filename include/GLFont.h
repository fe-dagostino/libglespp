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


#ifndef GLFONT_H
#define GLFONT_H

#include "GLCommonDefs.h"
#include "FObject.h"
#include "FWString.h"
#include "GLSize.h"
#include "GLReference.h"
#include "glm/glm.hpp"

USING_NAMESPACE_FED

class GLText;
class GLFontLoader;

/**
 */
class GLFont : public FObject, public GLReference
{
  ENABLE_FRTTI( GLFont )
public:
  /***/
  GLFont();
  /***/
  virtual ~GLFont();  
  
  /**
   * Retrieve font size, in pixels, for both width and height.
   */
  virtual const GLSize&     getSize() const = 0;
  /**
   * Will set font size in pixels.
   * if only one values will be specified and the other one is zero,
   * it will be considered as a square size.
   */
  virtual VOID              setSize( const GLSize& size ) = 0;
  
  /**
   * Retrieve current margins in pixels on each side.
   */
  virtual VOID              getMargins( GLsizei& left, GLsizei& top, GLsizei& right, GLsizei& bottom ) const = 0;
  /**
   * Will set margins on four sides.
   */
  virtual VOID              setMargins( GLsizei  left, GLsizei  top, GLsizei  right, GLsizei  bottom ) = 0;
  
  /**
   * @param sText   widechar text used to generate GLText instance.
   * @param frColor foreground  color.
   */
  virtual GLText*           getText( const FWString& sText, const glm::vec4& frColor ) = 0;
  
private:
  
};

#endif // GLFONT_H
