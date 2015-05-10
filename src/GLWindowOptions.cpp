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


#include "../include/GLWindowOptions.h"

GLWindowOptions::GLWindowOptions(
                   const FString& sMonitor,
                   const FString& sTitle,
                   INT            iPosX, 
                   INT            iPosY, 
                   INT            iWidth, 
                   INT            iHeight
                 )
   : m_sMonitor( sMonitor ), m_sTitle( sTitle ),
     m_iPosX( iPosX ), m_iPosY( iPosY ),
     m_iWidth( iWidth ), m_iHeight( iHeight )
{
  
}
  
GLWindowOptions::~GLWindowOptions()
{
  
}


  
  