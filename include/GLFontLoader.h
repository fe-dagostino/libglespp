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


#ifndef GLFONTLOADER_H
#define GLFONTLOADER_H

#include "GLCommonDefs.h"
#include "GLFont.h"
#include "GLReference.h"
#include "GLFontLoaderException.h"


class GLFontLoader : public GLReference
{
public:
  /***/
  GLFontLoader();
  /***/
  virtual ~GLFontLoader();
  
  /***/
  const FString& getFontsPath( ) const;
  /***/
  VOID           setFontsPath( const FString& sPath );
  
  /**
   * @param sFontFileName   
   */	
  virtual GLFont*  createFont( const FString& sFontFileName, const GLSize& size ) = 0;
  /***/
  virtual BOOL     deleteFont( GLFont*& font ) = 0;
  
protected:    
  
private:
  FString   m_sFontsPath;
  
  friend class GLFont;
};

#endif // GLFONTLOADER_H
