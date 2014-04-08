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


#include "../include/GLFontLoaderException.h"

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
  }
}

