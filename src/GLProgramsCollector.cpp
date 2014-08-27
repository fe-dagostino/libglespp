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


#include "../include/GLProgramsCollector.h"
#include "../include/GLVertexShader.h"
#include "../include/GLFragmentShader.h"

#include "LOGGING/FLogger.h"
#include <fcntl.h>

GENERATE_CLASSINFO( GLProgramsCollector, FSingleton )
IMPLEMENT_SINGLETON( GLProgramsCollector )

#ifdef _LINUX
# define SHADER_PATH  "/etc/gles-gui/shaders"
#else
# define SHADER_PATH  "./shaders"
#endif

GLProgram*   GLProgramsCollector::find( const FString& sProgramName )
{
  ProgramsMap::iterator  iter = m_mapPrograms.find( sProgramName.GetBuffer() );
  if ( iter == m_mapPrograms.end() )
    return nullptr;

  return iter->second->ref;
}

    
GLProgram*   GLProgramsCollector::create( const FString& sProgramName, const std::vector< std::pair<int,std::string> >&  attributes )
{
  GLProgram* pProgram = GLProgramsCollector::GetInstance().find( sProgramName );
  if ( pProgram == nullptr )
  {
    LOG_INFO( FString(  0, "ShaderPath [%s] - ProgramName [%s]", GLProgramsCollector::GetInstance().getShadersPath().GetBuffer(), sProgramName.GetBuffer() ), create() )
    FString           _sVS(0, "%s/%s.vs", GLProgramsCollector::GetInstance().getShadersPath().GetBuffer(), sProgramName.GetBuffer() );
    FString           _sFS(0, "%s/%s.fs", GLProgramsCollector::GetInstance().getShadersPath().GetBuffer(), sProgramName.GetBuffer() );
    GLVertexShader    _vertexShader;
    GLFragmentShader  _fragmentShader;
    BOOL              _bVertexShader   = FALSE;
    BOOL              _bfragmentShader = FALSE;
    
    _bVertexShader   = _vertexShader.loadFromFile( _sVS );
    if ( _bVertexShader == FALSE )
    {
      FString sLog;
      _vertexShader.getLog(sLog);
      ERROR_INFO( FString( 0, "Vertex Shader [%s]\n", sLog.GetBuffer()), create() );
    }
    
    _bfragmentShader = _fragmentShader.loadFromFile( _sFS );
    if ( _bVertexShader == FALSE )
    {
      FString sLog;
      _fragmentShader.getLog(sLog);
      ERROR_INFO( FString( 0, "Fragment Shader [%s]\n", sLog.GetBuffer()), create() );
    }
    
    if (
         ( _bVertexShader == TRUE ) && ( _bfragmentShader == TRUE )
       )
    {
      pProgram = new GLProgram();
    
      pProgram->attachShaders( &_vertexShader, &_fragmentShader );

      for ( auto pair : attributes )
      {
	pProgram->bindAttribLocation( pair.first, pair.second.data() );
      }
      
      pProgram->link();

      //
      GLProgramsCollector::GetInstance().attach( sProgramName, pProgram );    
    }
  }
    
  return pProgram;
}


BOOL         GLProgramsCollector::attach( const FString& sProgramName, GLProgram* pProgram )
{
  ProgramsMap::iterator  iter = m_mapPrograms.find( sProgramName.GetBuffer() );
  if ( iter != m_mapPrograms.end() )
    return FALSE;
  
  ProgramItem* pItem = new ProgramItem( sProgramName, pProgram );
  
  m_mapPrograms[pItem->name.GetBuffer()] = pItem; 
  
  return TRUE;
}

GLProgram*   GLProgramsCollector::detach( const FString& sProgramName )
{
  ProgramsMap::iterator  iter = m_mapPrograms.find( sProgramName.GetBuffer() );
  if ( iter == m_mapPrograms.end() )
    return nullptr;
  
  ProgramItem* pItem = iter->second;
  GLProgram*   pProgram = (GLProgram*)pItem->ref.detach();
  
  m_mapPrograms.erase(iter);
  delete pItem;
  
  return pProgram;
}

VOID     GLProgramsCollector::OnInitialize()
{
  m_sShadersPath = SHADER_PATH;
}

VOID     GLProgramsCollector::OnFinalize()
{
}