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


#include "../include/widgets/GLWidget.h"


GENERATE_CLASSINFO( GLWidget, GLCanvas )


GLWidget::GLWidget( GLWidget* pParent )
 : m_size( 0, 0 ), m_bVisible( TRUE ), m_bEnabled( TRUE ),
   m_pParent( nullptr ), m_imBackground( nullptr )
{
  m_Focused = m_vChildren.end();
  
  setParent( pParent );
}

GLWidget::~GLWidget()
{
  GLReference* pRef = m_imBackground.detach();
  if ( pRef != nullptr )
  {
    if (pRef->count() == 0)
    {
      delete pRef;
    }
  }
  
  // Release signals slot on parent.
  setParent( nullptr );
}

VOID      GLWidget::getClientArea( GLRecti& rect )
{
  rect.left   = getPosition().x;
  rect.top    = getPosition().y;
  rect.right  = getSize().width;
  rect.bottom = getSize().height;
}

BOOL      GLWidget::addChild( GLWidget* widget )
{
  for ( auto w : m_vChildren )
  {
    if ( w == widget )
      return FALSE;
  }
  
  m_vChildren.push_back( widget );

  // Iterator must be updated each time 
  // m_vChildren become changed
  m_Focused = m_vChildren.end();
  
  return TRUE;
}

BOOL      GLWidget::hasFocus() const
{
  if ( m_pParent != nullptr )
  {
    if ( m_pParent->m_Focused != m_pParent->m_vChildren.end() )
    {
      if (*(m_pParent->m_Focused) == this )
	return TRUE;
    }
  }
  
  return FALSE;
}

VOID      GLWidget::setPosition( const GLPosition& pos )
{ 
  setPosition( pos.x, pos.y );
}

VOID      GLWidget::setPosition( GLint x, GLint y )
{ 
  m_pos.x = x; m_pos.y = y; 
  
  _updateBkVertices();
  
  OnPositionChanged( m_pos );
}
  
VOID      GLWidget::setSize( const GLSize& size )
{ 
  setSize( size.width, size.height );
}

VOID      GLWidget::setSize( GLsizei width, GLsizei height )
{ 
  m_size.width = width; m_size.height = height; 
  
  _updateBkVertices();
  
  OnSizeChanged( m_size );
}  

  
VOID      GLWidget::setBackground( const glm::vec4& cr )
{ 
  m_crBackground = cr;     
  m_eBackground  = SolidColor;
}
  
VOID      GLWidget::setBackground( GLTexture* texture )
{ 
  m_imBackground.attach(texture);     
  
  m_eBackground  = ImageBrush;
  
  // Default Texture coordinates
  m_bkTexCoord.clear();
  m_bkTexCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
  m_bkTexCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
  m_bkTexCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
  m_bkTexCoord.push_back( glm::vec2( 1.0f, 1.0f )  );
  
  _updateBkVertices();
}

BOOL      GLWidget::draw( const glm::mat4& mvp, const GLRecti& rect )
{
  if ( isVisible() == FALSE )
    return FALSE;
    
  GLCanvas::setMVP( mvp );
  
  GLRecti cliRect( getPosition().x, getPosition().y, getSize().width, getSize().height );
  
  if ( OnDrawBackground( cliRect ) == TRUE )
  {
    if ( m_eBackground != NoBackground )
    {
      if ( m_eBackground == SolidColor )
      {
        drawRect( m_bkVertices, getBkColor() );
      }
  
      if ( m_eBackground == ImageBrush )
      {
        drawRect( m_bkVertices, m_bkTexCoord, m_imBackground, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );
      }
    }
  }
  
  for( auto w : m_vChildren )
  {
    w->draw( mvp, cliRect );
  }
  
  return OnDraw( cliRect );
}

VOID     GLWidget::OnKeyReleased( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode )
{ 
  if ( hasFocus() == FALSE )
    return;
  
  signalKeyReleased.emit( pGlWindow, pGlLayer, iKey, iScanCode );   
} 
  
VOID     GLWidget::OnKeyPressed ( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode )
{
  if ( hasFocus() == FALSE )
    return;
    
  signalKeyPressed.emit ( pGlWindow, pGlLayer, iKey, iScanCode ); 
} 

VOID     GLWidget::OnKeyRepeated( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode )
{ 
  if ( hasFocus() == FALSE )
    return;
  
  signalKeyRepeated.emit( pGlWindow, pGlLayer, iKey, iScanCode );  
} 

VOID  GLWidget::clientResize( const GLSize& size )
{
  m_size =  size;
  
  _updateBkVertices( );
} 

// @ FIXME each widget can have a list of focusable widgets
BOOL  GLWidget::stepFocus()
{
  if ( hasFocusable() == FALSE )
    return TRUE;
  
  // Will restart from first widget
  if ( m_Focused == m_vChildren.end() )
  {
    m_Focused = m_vChildren.begin();
  }
  else
  {
    if ( (*m_Focused)->stepFocus() == TRUE )
      m_Focused++;
  }

  // Move to the first focusable item. It can be also the last item when the loop is ended.
  while ( ( m_Focused != m_vChildren.end() ) && (*m_Focused)->isFocusable() == FALSE )
  {
    m_Focused++;
  }
  
  if ( m_Focused == m_vChildren.end() )
    return stepFocus();
  
  return FALSE;
}

BOOL       GLWidget::hasFocusable()
{
  if ( m_vChildren.empty() )
    return FALSE;
  
  for ( auto w : m_vChildren )
    if ( w->isFocusable() == TRUE )
      return TRUE;
  
  return FALSE;
}

VOID       GLWidget::handleDefaultKeys( INT iKey, INT iScanCode )
{
  switch ( iKey )
  {
    case 258 :
    {
      stepFocus();
    }; break;
  }
}

BOOL                   GLWidget::OnDrawBackground( const GLRecti& rect )
{
  return TRUE;  
}

BOOL                   GLWidget::OnDraw( const GLRecti& rect )
{
  
  return TRUE;
}

VOID                   GLWidget::OnPositionChanged( const GLPosition& pos )
{
  
}

VOID                   GLWidget::OnSizeChanged( const GLSize& size )
{
  
}

VOID       GLWidget::_updateBkVertices( )
{
  // Remove all vertices
  m_bkVertices.clear();
  
  // Default Vertices coordinates 
  GLPosition pos  = getPosition();
  GLSize     size = getSize();
  
  m_bkVertices.push_back( glm::vec2( pos.x             , pos.y + size.height ) );
  m_bkVertices.push_back( glm::vec2( pos.x + size.width, pos.y + size.height ) );
  m_bkVertices.push_back( glm::vec2( pos.x             , pos.y               ) );
  m_bkVertices.push_back( glm::vec2( pos.x + size.width, pos.y               ) );
}


VOID       GLWidget::setParent( GLWidget* pParent )
{
  if ( m_pParent != nullptr )
  {
    slotKeyReleased->disconnect();
    slotKeyPressed->disconnect();
    slotKeyRepeated->disconnect();
  }
  
  m_pParent = pParent;
  
  if ( m_pParent != nullptr )
  {
    slotKeyReleased = m_pParent->signalKeyReleased.connect( sigc::mem_fun(this, &GLWidget::OnKeyReleased) );
    slotKeyPressed  = m_pParent->signalKeyPressed.connect ( sigc::mem_fun(this, &GLWidget::OnKeyPressed ) );
    slotKeyRepeated = m_pParent->signalKeyRepeated.connect( sigc::mem_fun(this, &GLWidget::OnKeyRepeated) );
  }
}


