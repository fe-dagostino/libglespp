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


#include "widgets/GLWidget.h"
#include "GLViewPort.h"


GENERATE_CLASSINFO( GLWidget, GLCanvas )


GLWidget::GLWidget( GLWidget* pParent )
 : m_ebo( eboUndefined ), 
   m_size( 0, 0 ), m_bVisible( TRUE ), m_bEnabled( TRUE ),
   m_pParent( nullptr ), m_eBackground( NoBackground ), m_imBackground( nullptr )
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

  // Update parent 
  widget->setParent(this);
  
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

VOID      GLWidget::setPosition( const GLPosition2D& pos )
{ 
  setPosition( pos.x, pos.y, TRUE );
}

VOID      GLWidget::setPosition( GLint x, GLint y, BOOL notify )
{ 
  if ( (m_pos.x != x) || (m_pos.y != y) )
  {
    m_pos.x = x; 
    m_pos.y = y; 
  
    _updateBkVertices();
  }
  
  if ( notify == TRUE )
  {
    OnPositionChanged( m_pos );
  }
}
  
VOID      GLWidget::setSize( const GLSize& size )
{ 
  setSize( size.width, size.height, TRUE );
}

VOID      GLWidget::setSize( GLsizei width, GLsizei height, BOOL notify )
{ 
  if (( m_size.width != width ) || (m_size.height != height))
  {
    m_size.width  = width; 
    m_size.height = height; 

    _updateBkVertices();
  }
  
  if ( notify == TRUE )
  {
    OnSizeChanged( m_size );
  }
}  

  
VOID      GLWidget::setBackground( const glm::vec4& cr )
{ 
  m_crBackground = cr;     
  m_eBackground  = SolidColor;
}
  
VOID      GLWidget::setBackground( GLTexture* texture, BackgroundOptions bo )
{ 
  m_imBackground.attach(texture);     
  
  m_eBackground  = ImageBrush;
  
  if ( m_ebo != bo )
  {
    // Default Texture coordinates
    m_bkTexCoord.clear();
    m_bkTexCoord.reserve(4);
    switch ( bo )
    {
      case eboAsIs:
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 1.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
      break;
      case eboFlipHorizontal:
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 1.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
      break;
      case eboFlipVertical:
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 1.0f )  );
      break;
      case eboFlipBoth:
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 0.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 0.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 1.0f, 1.0f )  );
        m_bkTexCoord.push_back( glm::vec2( 0.0f, 1.0f )  );
      break;
      default:
      break;
    }
    
    m_ebo = bo;
  }
}

BOOL      GLWidget::draw( const glm::mat4& mvp, const GLRecti& rect )
{
  if ( isVisible() == FALSE )
    return FALSE;
    
  GLCanvas::setMVP( mvp );
  
  GLRecti cliRect( getPosition().x, getPosition().y, getSize().width, getSize().height );
  
  OnBeginDrawing( cliRect );
  
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
  
  BOOL bRetVal = OnDraw( cliRect );
  
  OnEndDrawing( cliRect );
  
  return bRetVal;
}

VOID     GLWidget::OnKeyReleased( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode, WORD wMods )
{ 
  if (( hasFocus() == FALSE ) || ( isEnabled() == FALSE ))
    return;
    
  signalKeyReleased.emit( pGlWindow, pGlLayer, iKey, iScanCode, wMods );   
} 
  
VOID     GLWidget::OnKeyPressed ( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode, WORD wMods )
{
  if (( hasFocus() == FALSE ) || ( isEnabled() == FALSE ))
    return;
    
  handleDefaultKeys( iKey, iScanCode );
  
  signalKeyPressed.emit ( pGlWindow, pGlLayer, iKey, iScanCode, wMods ); 
} 

VOID     GLWidget::OnKeyRepeated( GLWindow* pGlWindow, GLLayer* pGlLayer, INT iKey, INT iScanCode, WORD wMods )
{ 
  if (( hasFocus() == FALSE ) || ( isEnabled() == FALSE ))
    return;
  
  handleDefaultKeys( iKey, iScanCode );
  
  signalKeyRepeated.emit( pGlWindow, pGlLayer, iKey, iScanCode, wMods );  
} 

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
  while ( ( m_Focused != m_vChildren.end()        ) && 
          (( (*m_Focused)->isFocusable() == FALSE ) || 
	   ( (*m_Focused)->isEnabled()   == FALSE ) ||
	   ( (*m_Focused)->isVisible()   == FALSE ))
	)
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

// Called only in case current widget is both visible and enabled.
VOID       GLWidget::handleDefaultKeys( INT iKey, INT iScanCode )
{
  switch ( iKey )
  {
    case GLFW_KEY_ENTER :  // ENTER KEY
    {
      // Raise on click event as for mouse when 
      OnClick.emit( this );
    }; break;
  }
}

VOID                   GLWidget::OnBeginDrawing( const GLRecti& rect )
{
  
}

BOOL                   GLWidget::OnDrawBackground( const GLRecti& rect )
{
  return TRUE;  
}

BOOL                   GLWidget::OnDraw( const GLRecti& rect )
{
  
  return TRUE;
}

VOID                   GLWidget::OnEndDrawing( const GLRecti& rect )
{
  
}

VOID                   GLWidget::OnPositionChanged( const GLPosition2D& pos )
{
  
}

VOID                   GLWidget::OnSizeChanged( const GLSize& size )
{
  
}

BOOL       GLWidget::OnUpdateBackgroundVertices()
{
  return TRUE;
}


VOID       GLWidget::_updateBkVertices( )
{
  if ( OnUpdateBackgroundVertices() == FALSE )
    return;
    
  // Remove all vertices
  m_bkVertices.clear();
  m_bkVertices.reserve(4);
  
  // Default Vertices coordinates 
  GLPosition2D pos  = getPosition();
  GLSize       size = getSize();
  
  if (getParent()!=nullptr)
  {
    pos += getParent()->getPosition();
  }
  
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
  
  _updateBkVertices();
}


