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


#ifndef GLANIMATION_H
#define GLANIMATION_H

#include "GLCommonDefs.h"
#include "GLReference.h"
#include "GLTransformationsMatrix.h"

/**
 */
class GLAnimation : public GLReference
{
public:
  /***/
  GLAnimation();
  /***/
  virtual ~GLAnimation();
  
  /***/
  GLTransformationsMatrix&   getMatrix();
  
private:
  GLTransformationsMatrix   m_matAnimation;  
};

#endif // GLANIMATION_H