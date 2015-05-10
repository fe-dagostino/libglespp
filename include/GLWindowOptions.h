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


#ifndef GLWINDOWOPTIONS_H
#define GLWINDOWOPTIONS_H

#include "GLCommonDefs.h"
#include "GLReference.h"
#include "FString.h"


USING_NAMESPACE_FED

class GLWindowOptions : public GLReference
{
public:
  /***/
  GLWindowOptions(
                   const FString& sMonitor,
                   const FString& sTitle,
                   INT            iPosX, 
                   INT            iPosY, 
                   INT            iWidth, 
                   INT            iHeight
                 );
  
  /***/
  virtual ~GLWindowOptions();
  
  /***/
  inline const FString&   getMonitor() const
  { return m_sMonitor; }
  /***/
  inline const FString&   getTitle() const
  { return m_sTitle;   }
  /***/
  inline const INT        getPosX() const
  { return m_iPosX;    }
  /***/
  inline const INT        getPosY() const
  { return m_iPosY;    }
  /***/
  inline const INT        getWidth() const
  { return m_iWidth;    }
  /***/
  inline const INT        getHeight() const
  { return m_iHeight;    }
  
private:
  const FString m_sMonitor;
  const FString m_sTitle;
  const INT     m_iPosX;
  const INT     m_iPosY;
  const INT     m_iWidth; 
  const INT     m_iHeight;
};

#endif // GLWINDOWOPTIONS_H
