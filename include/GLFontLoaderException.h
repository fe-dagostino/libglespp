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
