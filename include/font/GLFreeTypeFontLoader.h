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



#ifndef GLFREETYPEFONTLOADER_H
#define GLFREETYPEFONTLOADER_H

#include "GLCommonDefs.h"
#include "GLFontLoader.h"
#include "GLSize.h"

/**
 *  Forward declaration will avoid FT includes.
 */
struct FT_LibraryRec_;
typedef struct FT_LibraryRec_  *FT_Library;


class GLFreeTypeFontLoader : public GLFontLoader
{
public:
  /***/
  GLFreeTypeFontLoader();
  /***/
  virtual ~GLFreeTypeFontLoader();
  /***/
  virtual GLFont*  createFont( const FString& sFontFileName, const GLSize& size );
  /***/
  virtual BOOL     deleteFont( GLFont*& font );

private:
  PTHREAD_T      m_tid;
  FT_Library     m_library;   /* handle to library     */

};

#endif // GLFREETYPEFONTLOADER_H
