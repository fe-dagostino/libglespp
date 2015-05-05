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


#include "../include/GLImage.h"

#include "LOGGING/FLogger.h"

#include "images/images.h"


GENERATE_CLASSINFO( GLImage, GLObject )


typedef unsigned char* (*load_image)( const char* filename, unsigned int* size, int* width, int* height );


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
  load_image load   = NULL; 
  
  if ( il == eilFreeImage )
  {
#ifdef _USE_FREEIMAGE
    load = fi_load;
#else  //_USE_FREEIMAGE
    ERROR_INFO( "Use: cmake -DUSE_FREEIMAGE=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_FREEIMAGE   
  }
  
  if ( il == eilLibAV )
  {
#ifdef _USE_AVCPP
    load = av_load;
#else  //_USE_AVCPP
    ERROR_INFO( "Use: cmake -DUSE_AVCPP=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_AVCPP    
  }
  
  if ( il == eilDevIL )
  {
#ifdef _USE_DEVIL
    load = il_load;
#else  //_USE_DEVIL
    ERROR_INFO( "Use: cmake -DUSE_DEVIL=ON in order to enable FreeImage loader", load() )
    return FALSE;
#endif //_USE_DEVIL    
  }

  if ( load == NULL )
    return FALSE;
  
  m_pData = load( sFilename.GetBuffer(), &m_uiDataSize, &m_iWidth, &m_iHeight );
  if (m_pData==nullptr)
  {
    ERROR_INFO( FString( 0, "Failed to load Texture [%s]", sFilename.GetBuffer() ), load() );
  
    return FALSE;
  }
    
  LOG_INFO( FString( 0, "Loaded Texture [%s] MEM BYTES [%d] W:[%d] Pixel x H:[%d] D:[32] Bits", sFilename.GetBuffer(), m_uiDataSize, m_iWidth, m_iHeight ), load() );
  
  return TRUE;
}

