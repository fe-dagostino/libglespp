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
