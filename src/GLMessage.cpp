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


#include "../include/GLMessage.h"

GENERATE_CLASSINFO( GLMessage, GLObject )


GLMessage::GLMessage( GLWindow* pWindow )
  : m_pWindow( pWindow ), m_pEvent( NULL )
{
}
  
GLMessage::~GLMessage()
{
  if (m_pEvent!=NULL)
  {
    delete m_pEvent;
    m_pEvent = NULL;
  }
}


BOOL GLMessage::execute()
{
  BOOL bResult = OnExecute();
  
  signal();
  
  return bResult;
}

void GLMessage::wait()
{ 
  if (m_pEvent!=NULL)
    m_pEvent->Wait(INFINITE); 
}

void GLMessage::event()
{
  if ( m_pEvent == NULL )
  {
    m_pEvent = new FEvent();
    m_pEvent->Reset();
  }
}

void GLMessage::signal()
{ 
  if (m_pEvent!=NULL)
    m_pEvent->Signal(); 
}

bool GLMessage::release()
{
  return (m_pEvent!=NULL);
}
  
