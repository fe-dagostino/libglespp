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


#ifndef GLSCENETEXTNODE_H
#define GLSCENETEXTNODE_H

#include "GLSceneNode.h"
#include "GLText.h"
#include "GLProgram.h"
#include "GLTransformationsMatrix.h"


class GLSceneTextNode : public GLSceneNode
{
  ENABLE_FRTTI(GLSceneTextNode)
public:
  /**
   * @param sInstanceName it must be an unique name for the scene where it can be
   *                      addressed using this name.
   * @param text          a pointer to GLText instance; this instance can be shared
   *                      between more nodes.
   * @param program       can be a pointer to an external program that has been 
   *                      shared between more nodes or can be nullptr.
   *                      In the first case program pointer will be released on 
   *                      node destruction only when his references counter will be 1.
   *                      In the second case a default program with default the following
   *                      defautl sharders will be created.
   * 
   *                 #version 100
   *                 precision mediump float;
   *                 uniform   mat4 u_m4MVP;
   *                 attribute vec2 a_v2Point;
   *                 attribute vec2 a_v2TexCoord;
   *                 varying   vec2 v_v2TexCoord;
   *                 void main()
   *                 {
   *                   gl_Position  = u_m4MVP * vec4( a_v2Point, 0, 1.0 );
   *                   v_v2TexCoord = a_v2TexCoord;
   *                 };
   * 
   *                 #version 100
   *                 precision mediump float;
   *                 varying   vec2      v_v2TexCoord;
   *                 uniform   sampler2D u_2dTexture;
   *                 uniform   vec4      u_v4Color;
   *                 void main()
   *                 {
   *                   gl_FragColor = vec4(1, 1, 1, texture2D(u_2dTexture, v_v2TexCoord).a) * u_v4Color;
   *                 }
   */
  GLSceneTextNode( const FString& sInstanceName, GLText* text, GLProgram* program );
  /***/
  virtual ~GLSceneTextNode();
  
  /***/  
  virtual BOOL render( GLCamera* pCamera, const glm::mat4& mView );
  
  /***/
  inline  GLTransformationsMatrix&   getMatrixModel()
  { return m_matModel; }
  
protected:
  /***/
  virtual VOID    OnSetReference( GLReference* ref );
  
private:
  GLTransformationsMatrix        m_matModel;
  GLAutoRef<GLProgram>           m_program;
  std::vector<glm::vec2>         m_vertices;
  std::vector<glm::vec2>         m_texCoord;
};

#endif // GLSCENETEXTNODE_H
