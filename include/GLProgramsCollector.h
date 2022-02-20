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


#ifndef GLPROGRAMSCOLLECTOR_H
#define GLPROGRAMSCOLLECTOR_H

#include "GLCommonDefs.h"
#include "GLReference.h"
#include "GLProgram.h"

#include "FSingleton.h"

#include <map>
#include <vector>
#include <string>

USING_NAMESPACE_FED


/**
 * Singleton used in order to store shared programs.
 */
class GLProgramsCollector : protected FSingleton
{
  ENABLE_FRTTI( GLProgramsCollector )
  DECLARE_SINGLETON( GLProgramsCollector )  
public:
  /***/
  inline VOID            setShadersPath( const FString& sShadersPath )
  { m_sShadersPath = sShadersPath; }
  /***/
  inline const FString&  getShadersPath() const
  { return m_sShadersPath;         }
  
  /***/
  GLProgram*   find( const FString& sProgramName );
  /***/
  GLProgram*   create( const FString& sProgramName, const std::vector< std::pair<int,std::string> >& attributes );

  /***/
  BOOL         attach( const FString& sProgramName, GLProgram* pProgram );
  /***/
  GLProgram*   detach( const FString& sProgramName );
  
  
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

  struct ProgramItem 
  {
    ProgramItem( const FString& sName, GLProgram* pProgram )
    {
      name = sName;
      ref.attach(pProgram);
    }
    
    ~ProgramItem()
    {
      ref.detach();
    }
    
    FString                 name;
    GLAutoRef<GLProgram>    ref;
  };
  
  typedef std::map<const char*, ProgramItem*, lstr>  ProgramsMap;
  
private:
  FString          m_sShadersPath;
  ProgramsMap      m_mapPrograms;
  
};

#endif // GLPROGRAMSCOLLECTOR_H
