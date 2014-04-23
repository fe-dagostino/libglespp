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


#ifndef GLFONTLOADEREXCEPTION_H
#define GLFONTLOADEREXCEPTION_H

#include "GLCommonDefs.h"
#include "FException.h"

USING_NAMESPACE_FED

class GLFontLoaderException : public FException
{
  ENABLE_FRTTI( GLFontLoaderException );
public:
  enum EXCEPTION_CODES {
                         INITIALIZE_ERROR,
                         WRONG_THREAD,
                         FONT_FILENAME_NOT_FOUND
                       };

  /***/
  GLFontLoaderException( DWORD nErrorCode );
  /**
   *  Constructor.
   *  Require only a single parameter. 
   *  @param nErrorCode is and exception type code.
   */
  GLFontLoaderException( const FString& sErrorMsg, DWORD nErrorCode );
  
  /***/
  virtual ~GLFontLoaderException();
  
private:
  /***/
  VOID  AddMessageCodeToErrorMsg( DWORD nErrorCode );

};

#endif // GLFONTLOADEREXCEPTION_H
