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


#include "../include/font/GLFreeTypeFontLoader.h"
#include "../include/font/GLFreeTypeFont.h"

#include "FFile.h"

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H


GLFreeTypeFontLoader::GLFreeTypeFontLoader()
{
  // Loader must be created / used and released at the same thread.
  m_tid = GetCurrentThreadId();

  FT_Error error = FT_Init_FreeType( &m_library );
  if ( error != 0 )
  {
    FTHROW_EXCEPTION( GLFontLoaderException, GLFontLoaderException::INITIALIZE_ERROR );
  }
}

GLFreeTypeFontLoader::~GLFreeTypeFontLoader()
{
  if ( m_tid != GetCurrentThreadId() )
  {
    FTHROW_MSG_EXCEPTION( GLFontLoaderException, "GLFontLoader must be created, used and released with the same thread.", GLFontLoaderException::WRONG_THREAD );
  }
  
  FT_Error error = FT_Done_FreeType( m_library );
  if ( error != 0 )
  {
    //@todo
  }
}
  
GLFont*  GLFreeTypeFontLoader::createFont( const FString& sFontFileName, const GLSize& size )
{
  if ( m_tid != GetCurrentThreadId() )
  {
    FTHROW_MSG_EXCEPTION( GLFontLoaderException, "GLFontLoader must be created, used and released with the same thread.", GLFontLoaderException::WRONG_THREAD );
  }
  
  FT_Face  face  =  nullptr;
  FString  sFont( 0, "%s/%s", getFontsPath().GetBuffer(), sFontFileName.GetBuffer() );
  if ( FFile::Exist( sFont, nullptr ) == FALSE )
  {
    FTHROW_MSG_EXCEPTION( GLFontLoaderException, FString( 0, "Font [%s]", sFontFileName.GetBuffer() ) , GLFontLoaderException::FONT_FILENAME_NOT_FOUND );
  }
  
  FT_Error error = FT_New_Face( m_library, sFont.GetBuffer(), 0, &face );
  if ( error != 0 )
  {
    return nullptr;
  }
      
  return new GLFreeTypeFont( face, size );
}

BOOL     GLFreeTypeFontLoader::deleteFont( GLFont*& font )
{
  if ( m_tid != GetCurrentThreadId() )
  {
    FTHROW_MSG_EXCEPTION( GLFontLoaderException, "GLFontLoader must be created, used and released with the same thread.", GLFontLoaderException::WRONG_THREAD );
  }
  
  if ( font == nullptr )
    return FALSE;
  
  if ( font->IsKindOf( "GLFreeTypeFont" ) == FALSE )
    return FALSE;
  
  delete font;
  font = nullptr;
  
  return TRUE;  
}


