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


#include "../include/GLResourcesCollector.h"

GENERATE_CLASSINFO( GLResourcesCollector, FSingleton )
IMPLEMENT_SINGLETON( GLResourcesCollector )

#ifdef _LINUX
# define RESOURCES_PATH  "/etc/gles-gui/media"
#else
# define RESOURCES_PATH  "./media"
#endif


GLReference*   GLResourcesCollector::find( const FString& sResourceName )
{
  ResourcesMap::iterator  iter = m_mapResources.find( sResourceName.GetBuffer() );
  if ( iter == m_mapResources.end() )
    return nullptr;

  return iter->second->ref;
}

BOOL           GLResourcesCollector::attach( const FString& sResourceName, GLReference* pResource )
{
  ResourcesMap::iterator  iter = m_mapResources.find( sResourceName.GetBuffer() );
  if ( iter != m_mapResources.end() )
    return FALSE;
  
  ResourceItem* pItem = new ResourceItem( sResourceName, pResource );
  
  m_mapResources[pItem->name.GetBuffer()] = pItem; 
  
  return TRUE;  
}

GLReference*   GLResourcesCollector::detach( const FString& sResourceName )
{
  ResourcesMap::iterator  iter = m_mapResources.find( sResourceName.GetBuffer() );
  if ( iter == m_mapResources.end() )
    return nullptr;
  
  ResourceItem* pItem = iter->second;
  GLReference*  pProgram = (GLReference*)pItem->ref.detach();
  
  m_mapResources.erase(iter);
  delete pItem;
  
  return pProgram; 
}

VOID     GLResourcesCollector::OnInitialize()
{
  m_sResourcesPath = RESOURCES_PATH;
}

VOID     GLResourcesCollector::OnFinalize()
{
}
