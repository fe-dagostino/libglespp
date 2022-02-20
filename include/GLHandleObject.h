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


#ifndef GLHANDLEOBJECT_H
#define GLHANDLEOBJECT_H

#include "GLCommonDefs.h"
#include "FString.h"
#include "GLObject.h"
#include "GLFW/glfw3.h"

USING_NAMESPACE_FED

class GLHandleObject : public GLObject
{
  ENABLE_FRTTI( GLHandleObject )
public:
  /***/
  GLHandleObject();
  /***/
  virtual ~GLHandleObject();

  /**
   * Used to check identifier validity.
   */
  BOOL    isValid() const;

protected:
  /**
   * Return shader object identifier.
   */
  GLuint  getId() const;
  
  /**
   * Initialize uid value.
   */
  void    setId( GLuint uiId );

private:
  GLuint    m_uiId;
  
};

#endif // GLHANDLEOBJECT_H
