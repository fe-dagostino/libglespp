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

#include "../include/GLImage.h"

#ifdef _USE_FREEIMAGE
extern "C"
{
# include "images/images.h"
}
#endif


GLImage::GLImage()
 : m_iWidth(0), m_iHeight(0), m_pData(nullptr)
{

}

GLImage::~GLImage()
{
  if ( m_pData != nullptr )
  {
    free( m_pData );
    m_pData = nullptr;
  }
}

#ifdef _USE_FREEIMAGE
GLboolean   GLImage::fiLoad( const FString& sFilename )
{
  m_pData = fi_load( sFilename.GetBuffer(), &m_uiDataSize, &m_iWidth, &m_iHeight );
  if (m_pData==nullptr)
    return false;
  
  return true;
}
#endif //_USE_FREEIMAGE


#ifdef _USE_AVCPP
GLboolean   GLImage::avLoad( const FString& sFilename )
{
  
  
  return TRUE;
}

#endif //_USE_AVCPP

