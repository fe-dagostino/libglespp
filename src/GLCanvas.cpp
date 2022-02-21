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


#include "GLCanvas.h"
#include "GLProgramsCollector.h"
#include "GLProgram.h"
#include "GLVertexShader.h"
#include "GLFragmentShader.h"

#include "LOGGING/FLogger.h"

GENERATE_CLASSINFO( GLCanvas, GLObject )


GLCanvas::GLCanvas()
{
  m_mvp = glm::mat4( 1.0f );
}

GLCanvas::~GLCanvas()
{
  
}
  
void   GLCanvas::drawPoints( const std::vector<glm::vec2>& points, const glm::vec4& color, GLfloat fThickness )
{
#if defined(_NV_CARD_)  
// Values are not part of ES Specs but still supported on NV cards
/* Shaders */
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A  

  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
#endif
  
  draw( GL_POINTS, points, color, fThickness );
  
#if defined(_NV_CARD_)  
  glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
#endif
}

void   GLCanvas::drawLines( const std::vector<glm::vec2>& points, const glm::vec4& color, GLfloat fThickness )
{
  glLineWidth( fThickness );
  
  draw( GL_LINE_STRIP, points, color, fThickness );
}

void   GLCanvas::drawRect( const std::vector<glm::vec2>& points, const glm::vec4& color )
{
  if ( points.size() != 4 )
    return;
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  
  draw( GL_TRIANGLE_STRIP, points, color, 1.0f );
  
  glDisable(GL_BLEND);
}

void   GLCanvas::drawRect( const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& texCoord, GLTexture* texture, GLint  tws, GLint twt )
{
  GLProgram* pProgram = GLProgramsCollector::GetInstance().find( "DefaultTexture" );
  if ( pProgram == nullptr )
  {
    std::vector< std::pair<int,std::string> >  attributes;
  
    attributes.push_back( std::pair<int,std::string>( 0, "a_v2Point" ) );
    attributes.push_back( std::pair<int,std::string>( 1, "a_v2TexCoord" ) );

    pProgram = GLProgramsCollector::GetInstance().create( "DefaultTexture", attributes );
  }
  
  GLAutoRef<GLProgram> prg(pProgram);
  if ( prg == nullptr )
    return;
  
  (*prg).use();
  
  // Get the uniform location
  GLint MatrixID  = glGetUniformLocation( (*prg).getId(), "u_m4MVP"     );
  GLint TextureID = glGetUniformLocation( (*prg).getId(), "u_2dTexture" );
  
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(m_mvp) );
  
  (*texture).render( vertices, texCoord, true, GL_TEXTURE_2D, 0, TextureID, 0, 1, tws, twt );  
}
  
void   GLCanvas::drawText( const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& texCoord, GLText* text, GLint tws, GLint twt )
{
  draw( vertices, texCoord, text, tws, twt );
}

void   GLCanvas::draw( GLenum mode, const std::vector<glm::vec2>& points, const glm::vec4& color, GLfloat fThickness )
{
  GLProgram* pProgram = GLProgramsCollector::GetInstance().find( "DefaultSolid" );
  if ( pProgram == nullptr )
  {
    std::vector< std::pair<int,std::string> >  attributes;
  
    attributes.push_back( std::pair<int,std::string>( 0, "a_v2Point" ) );
  
    pProgram = GLProgramsCollector::GetInstance().create( "DefaultSolid", attributes );
  }
  
  GLAutoRef<GLProgram> prg(pProgram);
  if ( prg == nullptr )
    return;
  
  (*prg).use();
    
  // Get the uniform location
  GLint MatrixID    = glGetUniformLocation( (*prg).getId(), "u_m4MVP"      );
  GLint ThicknessID = glGetUniformLocation( (*prg).getId(), "u_fThickness" );
  GLint ColorID     = glGetUniformLocation( (*prg).getId(), "u_v4Color"    );
  
  glUniformMatrix4fv(MatrixID   , 1, GL_FALSE, glm::value_ptr(m_mvp) );
  glUniform1f       (ThicknessID, fThickness                         );
  glUniform4fv      (ColorID    , 1, glm::value_ptr(color)           );  

  glEnableVertexAttribArray(0);
  glVertexAttribPointer    (0, 2, GL_FLOAT, GL_FALSE, 0, points.data() );

  glDrawArrays(mode, 0, points.size() ); 
  
  glDisableVertexAttribArray(0);  
}

void   GLCanvas::draw( const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& texCoord, GLText* text, GLint  tws, GLint twt )
{
  if ( text == nullptr )
    return;
  
  GLProgram* pProgram = GLProgramsCollector::GetInstance().find( "DefaultText" );
  if ( pProgram == nullptr )
  {
    std::vector< std::pair<int,std::string> >  attributes;
  
    attributes.push_back( std::pair<int,std::string>( 0, "a_v2Point"    ) );
    attributes.push_back( std::pair<int,std::string>( 1, "a_v2TexCoord" ) );
  
    pProgram = GLProgramsCollector::GetInstance().create( "DefaultText", attributes );
  }
  
  GLAutoRef<GLProgram> prg(pProgram);
  if ( prg == nullptr )
    return;
  
  (*prg).use();
  
  // Get the uniform location
  GLint MatrixID  = glGetUniformLocation( (*prg).getId(), "u_m4MVP"     );
  GLint TextureID = glGetUniformLocation( (*prg).getId(), "u_2dTexture" );
  GLint ColorID   = glGetUniformLocation( (*prg).getId(), "u_v4Color"   );
  
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(m_mvp) );
  glUniform4fv      ( ColorID, 1, glm::value_ptr(text->getColor()) );  
  
  text->getTexture()->render( vertices, texCoord, true, GL_TEXTURE_2D, 0, TextureID, 0, 1, tws, twt );
}



