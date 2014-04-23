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

#include "LOGGING/FLogger.h"

#ifdef _USE_FREEIMAGE
extern "C"
{
# include "images/images.h"
}
#endif

GENERATE_CLASSINFO( GLImage, GLObject )

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


GLboolean   GLImage::load( ImageLoader il, const FString& sFilename )
{
  if ( il == eilFreeImage )
  {
#ifdef _USE_FREEIMAGE
    m_pData = fi_load( sFilename.GetBuffer(), &m_uiDataSize, &m_iWidth, &m_iHeight );
    if (m_pData==nullptr)
    {
      ERROR_INFO( FString( 0, "Failed to load Image [%s]", sFilename.GetBuffer() ), load() );
      return FALSE;
    }
    
    LOG_INFO( FString( 0, "Loaded Image [%s] MEM BYTES [%d] W:[%d] Pixel x H:[%d] D:[32] Bits", sFilename.GetBuffer(), m_uiDataSize, m_iWidth, m_iHeight ), load() );
    return TRUE;
#else  //_USE_FREEIMAGE
    ERROR_INFO( "Use: cmake -DUSE_FREEIMAGE=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_FREEIMAGE
  }

  if ( il == eilLibAV )
  {
#ifdef _USE_AVCPP

#else  //_USE_AVCPP
    ERROR_INFO( "Use: cmake -DUSE_AVCPP=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_AVCPP    
  }
  
  return FALSE;
}

