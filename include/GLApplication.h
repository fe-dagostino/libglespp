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


#ifndef GLAPPLICATION_H
#define GLAPPLICATION_H

#include "GLCommonDefs.h"
#include "FSingleton.h"
#include "FTList.tlh"
#include "GLFW/glfw3.h"
#include "GLShape.h"
#include "GLMonitor.h"

#include <map>

USING_NAMESPACE_FED

class GLApplicationEvents 
{
public:
  /***/
  virtual VOID OnInitializeError(/* @todo */) = 0;
  /***/
  virtual VOID OnError( INT iError, const FString& sDescription ) = 0;
  /***/
  virtual VOID OnFinalizeError(/* @todo */) = 0;
};

class GLApplication : protected FSingleton
{
  ENABLE_FRTTI( GLApplication )
  DECLARE_SINGLETON( GLApplication )
private:
  struct lstr
  {
    bool operator()( const char* pKey1, const char* pKey2 ) const
    {	return ( strcmp(pKey1, pKey2 )  < 0);	}
  };

  typedef std::map<const char*, GLMonitor*, lstr>  MonitorsMap;
public:
  /***/
  static VOID init( GLApplicationEvents* pEvents, const FString& sShadersPath, const FString& sMediaPath );
  /***/
  VOID        final();
  
  /***/
  GLApplicationEvents* setEvents( GLApplicationEvents* pEvents );
  /***/
  GLApplicationEvents* getEvents() const;
  
  /***/
  VOID                 pollEvents();
  /***/
  VOID                 waitEvents();
  /***/ 
  FString              getVersion() const;
  
  /**
   * Return time in seconds since application initialization.
   */
  DOUBLE               getTime() const;
  /***/
  VOID                 setTime( DOUBLE dTime );
  
  /**
   * Return the list with all available Monitors Information.
   * 
   * NOTE: Returned list pointer and its elements must be released by caller.
   */
  FTList<GLMonitor* >* getMonitorsList();
  
  /***/
  const GLMonitor*     getMonitorByName( const FString& sName );
private:
  /**
   * Reload monitors map
   */
  VOID            _detectMonitors();
  
protected:
  /***/
  VOID     OnInitialize() override;
  /***/
  VOID     OnFinalize() override;

private:
  GLApplicationEvents*    m_pEvents;
  mutable MonitorsMap     m_mapMonitors;  
};

#endif // GLAPPLICATION_H
