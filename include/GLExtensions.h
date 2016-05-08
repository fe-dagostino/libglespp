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


#ifndef GLEXTENSION_H
#define GLEXTENSION_H

#include "GLCommonDefs.h"
#include "FString.h"

#include <map>


class GLExtensions
{
private:
  /***/
  GLExtensions();
  /***/
  ~GLExtensions();

public:
  /**
   * Return TRUE if specified extension is supported, FALSE otherwise.
   */
  inline BOOL     isSupported( const FString& sExtName ) const
  { return (glfwExtensionSupported(sExtName.GetBuffer()) == GL_TRUE); }

  
private:
  /***/
  BOOL     init();
  
private:

  struct lstr
  {
    bool operator()(const char* s1, const char* s2) const
    {
      return strcmp(s1, s2) == 0;
    }
  };
  
  struct GLExtItem
  {
    GLExtItem( FString proc )
       : proc_name(proc)
    {
    }
  
    FString    proc_name;  // Extension name
  };
  
  typedef std::map<const char*, GLExtItem*, lstr>  ExtensionsMap;  

  ExtensionsMap   m_mapExtensions;
  
private:  
  friend class GLRenderer;
};

#endif // GLEXTENSION_H
