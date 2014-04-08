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


#ifndef GLMESSAGE_H
#define GLMESSAGE_H

#include "GLCommonDefs.h"
#include "GLObject.h"
#include "fedlibrary/include/FEvent.h"

USING_NAMESPACE_FED

class GLWindow;

/**
 * Base class to be extended for managing messages at windows thread.
 * Each GLWindow had a message queue that can be processed in the main
 * loop using GLWindow.processMessage(). In order to enqueue messages
 * both GLWindow.sendMessage() and GLWindow.postMessage() can be used:
 * the first one will block exectuion of calling thread until the message
 * has been processed; instead the second one will enqueue the message
 * without to wait its execution.
 */
class GLMessage : public GLObject
{
  ENABLE_FRTTI(GLMessage)
public:
  /**
   */
  GLMessage( GLWindow* pWindow );
  /***/
  virtual ~GLMessage();
  /***/
  BOOL execute();
  /***/
  void wait();

protected:
  /**
   * Pure virtual function that will keep specific message 
   * implementation.
   */
  virtual BOOL OnExecute() = 0;

private:
  /***/
  void event();
  /***/
  void signal();
  /***/
  bool release();
  
protected:
  GLWindow* m_pWindow;
  
private:
  FEvent*   m_pEvent;
  
  friend class GLWindow;
};


#endif // GLWMESSAGE_H
