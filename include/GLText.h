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


#ifndef GLTEXT_H
#define GLTEXT_H

#include "GLCommonDefs.h"
#include "GLFont.h"
#include "GLTexture.h"
#include "GLReference.h"
#include "glm/glm.hpp"

USING_NAMESPACE_FED

/**
 */
class GLText : public GLReference
{
public:
  /***/
  GLText( GLTexture* texture );
  /***/
  virtual ~GLText();
  
  /**
   * Default color is black.
   */
  inline  const glm::vec4& getColor() const
  { return m_color; }
  /***/
  inline  VOID             setColor( const glm::vec4& color )
  { m_color = color; }
  /***/
  inline  GLTexture*       getTexture()
  { return m_pTexture; }

private:
  GLTexture*  m_pTexture;
  glm::vec4   m_color;
};

#endif // GLTEXT_H
