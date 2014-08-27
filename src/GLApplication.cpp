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


#include "../include/GLApplication.h"
#include "../include/GLProgramsCollector.h"
#include "../include/GLResourcesCollector.h"


GENERATE_CLASSINFO( GLApplication, FSingleton )
IMPLEMENT_SINGLETON( GLApplication )


static void error_callback(int iError, const char* description)
{
  if ( GLApplication::IsValid() )
  {
    GLApplicationEvents* pEvents = GLApplication::GetInstance().getEvents();
    
    if ( pEvents != nullptr )
    {
      FString  sDescription( description );
      
      pEvents->OnError( iError, sDescription );
    }
  }
}

VOID GLApplication::init( GLApplicationEvents* pEvents )
{
  Initialize();
  
  GetInstance().setEvents( pEvents );
    
  if (!glfwInit())
  {
    if ( GetInstance().getEvents() != nullptr )
    {
      GetInstance().getEvents()->OnInitializeError();
    }
  }
  
  //Reset time
  GetInstance().setTime(0.0f);
}

VOID GLApplication::final()
{
  Finalize();
}

GLApplicationEvents* GLApplication::setEvents( GLApplicationEvents* pEvents )
{
  GLApplicationEvents* pRetValue = m_pEvents;
  
  m_pEvents = pEvents;
  
  return pRetValue;
}

GLApplicationEvents* GLApplication::getEvents() const
{
  return m_pEvents;
}
  
VOID     GLApplication::pollEvents()
{
  glfwPollEvents();
}

VOID     GLApplication::waitEvents()
{
  glfwWaitEvents();
}

FString  GLApplication::getVersion() const
{
  int major, minor, rev;
  glfwGetVersion( &major, &minor, &rev );
  return FString( 0, "%d.%d.%d", major, minor, rev );
}

DOUBLE GLApplication::getTime() const
{
  return glfwGetTime();
}
  
VOID   GLApplication::setTime( DOUBLE dTime )
{
  glfwSetTime( dTime );
}

void GLApplication::_detectMonitors()
{
  // Remove all items and release object.
  while ( m_mapMonitors.empty() == FALSE )
  {
      MonitorsMap::iterator  _iter         = m_mapMonitors.begin();
      GLMonitor*             _pMonitorInfo = _iter->second;
      
      m_mapMonitors.erase( _iter );
      delete _pMonitorInfo;
  }
  
  
  int           iMonitorCount  = 0;
  GLFWmonitor** ppMonitors     = nullptr;
  
  ppMonitors = glfwGetMonitors( &iMonitorCount );
  for ( int i=0; i < iMonitorCount; i++ )
  {
    GLMonitor* pMonitor = new GLMonitor( ppMonitors[i] );
    
    if ( m_mapMonitors.find( pMonitor->getName().GetBuffer() ) == m_mapMonitors.end() )
    {
      m_mapMonitors[pMonitor->getName().GetBuffer()] = pMonitor;
    }
    else
    {
      //@todo trace error
      delete pMonitor;
    }
  }
}

FTList<GLMonitor* >*    GLApplication::getMonitorsList()
{
  _detectMonitors();
  
  FTList<GLMonitor* >* retList = new FTList<GLMonitor* >();

  MonitorsMap::iterator  _iter         = m_mapMonitors.begin();
  while ( _iter != m_mapMonitors.end() )
  {
    retList->PushTail( new GLMonitor( *(_iter->second) ) );
    
    _iter++;
  }
  
  return retList;
}

const GLMonitor* GLApplication::getMonitorByName( const FString& sName )
{
  if ( sName.IsEmpty() )
    return nullptr;
    
  // if map is empty it will be populated
  if ( m_mapMonitors.empty() )
    _detectMonitors();
  
  MonitorsMap::const_iterator iter = m_mapMonitors.find( sName.GetBuffer() );
  if ( iter == m_mapMonitors.end() )
    return nullptr;
  
  return iter->second;
}  

VOID     GLApplication::OnInitialize()
{
  GLProgramsCollector::Initialize();
  GLResourcesCollector::Initialize();
  
  m_pEvents = nullptr;
  
  glfwSetErrorCallback(error_callback);
}

VOID     GLApplication::OnFinalize()
{
  GLProgramsCollector::GetInstance().Finalize();
  GLResourcesCollector::GetInstance().Finalize();
  
  glfwTerminate();
}