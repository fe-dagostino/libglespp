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


#include "../include/GLSceneTextNode.h"

#include "../include/GLVertexShader.h"
#include "../include/GLFragmentShader.h"
#include "../include/GLCamera.h"
#include <GLProgramsCollector.h>

#include "fedlibrary/include/LOGGING/FLogger.h"

USING_NAMESPACE_LOGGING

GENERATE_CLASSINFO( GLSceneTextNode, GLSceneNode )

GLSceneTextNode::GLSceneTextNode( const FString& sInstanceName, GLText* text, GLProgram* program )
 : GLSceneNode( sInstanceName, text ), m_program( program )
{
  // Init model matrix
  m_matModel.get() = glm::ortho( (float)0, (float)1024, (float)768, (float)0);
  
  // Uodate datas related to specific reference
  OnSetReference( text );
  
  if ( m_program == nullptr )
  {
    GLProgram* _pProgram        = GLProgramsCollector::GetInstance().find( "DefaultText" );
    if ( _pProgram == nullptr )
    {
     std::vector< std::pair<int,std::string> >  attributes;
   
     attributes.push_back( std::pair<int,std::string>( 0, "a_v2Point"    ) );
     attributes.push_back( std::pair<int,std::string>( 1, "a_v2TexCoord" ) );
      
     _pProgram = GLProgramsCollector::GetInstance().create( "DefaultText", attributes );
    }
    
    m_program.attach( _pProgram );
  }  
}
  
GLSceneTextNode::~GLSceneTextNode()
{
  if (m_program != nullptr )
  {
    GLReference* pReference = m_program.detach();
    if ( pReference->count() == 0 )
    {
      delete pReference;
    }
  }
}  
  
BOOL   GLSceneTextNode::render( GLCamera* pCamera, const glm::mat4& mView )
{
  GLText* text = dynamic_cast<GLText*>(getReference());
  if ( text == nullptr )
    return FALSE;
  
  if ( text->getTexture() == nullptr )
    return FALSE;

  if ( m_program == nullptr )
    return FALSE;
  
  // Retrieving projection matrix from active camera.
  // If not present an identity matrix will be used.
  glm::mat4  mProjection = (pCamera==nullptr)?glm::mat4(1.0f):pCamera->getProjectionMatrix().get();
  
  glm::mat4  mvp = mProjection * mView * m_matModel.get();
  
  // Set program as active, this will move shaders on GPU
  (*m_program).use();
    
  // Get the uniform location
  GLint MatrixID  = glGetUniformLocation( (*m_program).getId(), "u_m4MVP");
  GLint TextureID = glGetUniformLocation( (*m_program).getId(), "u_2dTexture" );
  GLint ColorID   = glGetUniformLocation( (*m_program).getId(), "u_v4Color" );
  
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(mvp) );
  glUniform4fv      ( ColorID, 1, glm::value_ptr(text->getColor()) );  

  // Render texture using current program
  text->getTexture()->render( m_vertices, m_texCoord, true, GL_TEXTURE_2D, 0, TextureID, 0, 1, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
  
  return TRUE;
}

VOID   GLSceneTextNode::OnSetReference( GLReference* ref )
{
  GLText* text = dynamic_cast<GLText*>(ref);
  
  if ( text == nullptr )
    return;
  
  // Default Texture coordinates
  m_texCoord.clear();
  m_texCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
  m_texCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
  m_texCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
  m_texCoord.push_back( glm::vec2( 1.0f, 1.0f )  );
  
  // Default Vertices coordinates it will keep aspect ratio  
  GLSize size = text->getTexture()->getSize();
  float  ar   = (float)size.height / (float)size.width;
  
  m_vertices.clear();
  m_vertices.push_back( glm::vec2(            0.0f,             0.0f ) );
  m_vertices.push_back( glm::vec2( size.width * ar,             0.0f ) );
  m_vertices.push_back( glm::vec2(            0.0f, size.height * ar ) );
  m_vertices.push_back( glm::vec2( size.width * ar, size.height * ar ) );
}
  
  
  
  
  

