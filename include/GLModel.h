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


#ifndef GLMODEL_H
#define GLMODEL_H

#include "GLCommonDefs.h"
#include "GLReference.h"
#include "GLMesh.h"

#include <vector>

/**
 */
class GLModel : public GLReference
{
public:
  /***/
  GLModel();
  /***/
  virtual ~GLModel();
  
private:  
  std::vector<GLMesh*>    m_vMeshes;

};

#endif // GLMODEL_H
