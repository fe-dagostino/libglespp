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


#ifndef GLFREETYPEFONT_H
#define GLFREETYPEFONT_H

#include "GLCommonDefs.h"
#include "GLFont.h"
#include "GLSize.h"

/**
 *  Forward declaration will avoid FT includes.
 */
struct FT_FaceRec_;
typedef struct FT_FaceRec_*  FT_Face;

class GLFontLoader;


class GLFreeTypeFont : public GLFont
{
  ENABLE_FRTTI( GLFreeTypeFont )
public:
  /***/
  GLFreeTypeFont( FT_Face face, const GLSize& size );
  /***/
  virtual ~GLFreeTypeFont();
  
  /**
   * Retrieve font size, in pixels, for both width and height.
   */
  virtual const GLSize&     getSize() const;
  /**
   * Will set font size in pixels.
   * if only one values will be specified and the other one is zero,
   * it will be considered as a square size.
   */
  virtual VOID              setSize( const GLSize& size );
  /***/
  virtual VOID              getMargins( GLsizei& left, GLsizei& top, GLsizei& right, GLsizei& bottom ) const;
  /***/
  virtual VOID              setMargins( GLsizei  left, GLsizei  top, GLsizei  right, GLsizei  bottom );
  /**
   * @param sText   widechar text used to generate GLText instance.
   * @param frColor foreground  color.
   */
  virtual GLText*           getText( const FWString& sText, const glm::vec4& frColor );
 
  /***/
  FT_Face                   getFace() const;
  
private:
  FT_Face  m_face;
  GLSize   m_size;
  GLsizei  m_left, m_top, m_right, m_bottom;
};

#endif // GLFREETYPEFONT_H
