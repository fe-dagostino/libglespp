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


#ifndef GLRESOURCESCOLLECTOR_H
#define GLRESOURCESCOLLECTOR_H

#include "GLCommonDefs.h"
#include "GLReference.h"

#include "FSingleton.h"

#include <map>
#include <vector>
#include <string>

USING_NAMESPACE_FED

class GLResourcesCollector : public FSingleton
{
  ENABLE_FRTTI( GLResourcesCollector )
  DECLARE_SINGLETON( GLResourcesCollector )
public:
  /***/
  inline VOID            setResourcesPath( const FString& sResourcesPath )
  { m_sResourcesPath = sResourcesPath; }
  /***/
  inline const FString&  getResourcesPath() const
  { return m_sResourcesPath;           }
  
  /***/
  GLReference*   find( const FString& sResourceName );
  
  /***/
  BOOL           attach( const FString& sResourceName, GLReference* pResource );
  /***/
  GLReference*   detach( const FString& sResourceName );
  
protected:
  /***/
  VOID     OnInitialize() override;
  /***/
  VOID     OnFinalize() override;
  
private:
  struct lstr
  {
    bool operator()( const char* pKey1, const char* pKey2 ) const
    {	return ( strcmp(pKey1, pKey2 )  < 0);	}
  };

  struct ResourceItem 
  {
    ResourceItem( const FString& sName, GLReference* pRef )
    {
      name = sName;
      ref.attach(pRef);
    }
    
    ~ResourceItem()
    {
      ref.detach();
    }
    
    FString                 name;
    GLAutoRef<GLReference>  ref;
  };
  
  typedef std::map<const char*, ResourceItem*, lstr>  ResourcesMap;  
private:
  FString      m_sResourcesPath;
  ResourcesMap m_mapResources;
  
};

#endif // GLRESOURCESCOLLECTOR_H
