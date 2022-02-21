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


#include "GLFontLoaderException.h"

GENERATE_CLASSINFO( GLFontLoaderException, FException )

GLFontLoaderException::GLFontLoaderException( DWORD nErrorCode )
  : FException( FString(), nErrorCode )
{
  m_sErroMsg = FString( GLFontLoaderException::GetClassName() ) + FString(" -:- "); 
  AddMessageCodeToErrorMsg( nErrorCode );
}

GLFontLoaderException::GLFontLoaderException( const FString& sErrorMsg, DWORD nErrorCode )
  : FException( FString(), nErrorCode )
{
  m_sErroMsg = FString( GLFontLoaderException::GetClassName() ) + FString(" -:- "); 
  AddMessageCodeToErrorMsg( nErrorCode );
  m_sErroMsg += FString("-:- MSG=") + sErrorMsg; 
}

GLFontLoaderException::~GLFontLoaderException()
{

}

VOID  GLFontLoaderException::AddMessageCodeToErrorMsg( DWORD nErrorCode )
{
  switch ( nErrorCode )
  {
    case INITIALIZE_ERROR :
      m_sErroMsg += FMAKE_STRING( INITIALIZE_ERROR );
    break;
    case WRONG_THREAD :
      m_sErroMsg += FMAKE_STRING( WRONG_THREAD );
    break;
    case FONT_FILENAME_NOT_FOUND :
      m_sErroMsg += FMAKE_STRING( FONT_FILENAME_NOT_FOUND );
    break;
  }
}

