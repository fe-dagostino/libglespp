

#include "FSingleton.h"
#include "FStopWatch.h"

#include "GLApplication.h"
#include "GLWindowEvents.h"
#include "GLSceneGraph.h"
#include "GLViewPort.h"
#include "GLWindow.h"
#include "GLFpsSync.h"

#include "font/GLFreeTypeFontLoader.h"

#include "GLSceneTextNode.h"
#include "GLSceneLayerNode.h"

#include "widgets/GLLabel.h"

#include "LOGGING/FLogger.h"
#include "LOGGING/FConsoleLogDevice.h"
#include "LOGGING/FLogDeviceCollector.h"
#include "LOGGING/FLogMessageColorization.h"

USING_NAMESPACE_FED
USING_NAMESPACE_LOGGING

int     s_argc = 0;
char**  s_argv = nullptr;



class GlesGui : protected FSingleton, protected GLApplicationEvents, protected GLWindowEvents
{
  ENABLE_FRTTI( GlesGui )
  DECLARE_SINGLETON( GlesGui )
public:

  /***/
  VOID             Run()
  {
    m_pWindow = new GLWindow();
    if ( m_pWindow == nullptr )
    {
      ERROR_INFO( "Unable to start application", Run() )
      return ;
    }
    
    // Add this as listener for WindowEvents
    m_pWindow->connect( this );
    
    if ( m_bFullScreen == TRUE )
      m_pWindow->createFullScreen( "", "BCM GUI Application", m_iWidth, m_iHeight, GLWindow::epfCalling );
    else
	m_pWindow->create( "BCM GUI Application", 0, 0, m_iWidth, m_iHeight, GLWindow::epfCalling );

    m_pSceneGraph = new GLSceneGraph();
    if ( m_pSceneGraph == nullptr )
    {
      ERROR_INFO( "Unable to allocate SceneGraph", Run() )
      return ;
    }
    
    ////////////////////////////////
    ///  Free Type Font Loader
    GLFontLoader* fl = new GLFreeTypeFontLoader();
    
    fl->setFontsPath( "/usr/share/fonts/" );
    
    //GLFont* font = fl->createFont( "FreeMono.ttf", GLSize( 0, 500) );
    GLFont* font = fl->createFont( "truetype/fontsquirrel/TitanOne-Regular.ttf", GLSize( 0, 50) );
    
    
    font->setMargins( 0, 0, 0, 0 );
    
    GLText* text = font->getText( L"B.K.M. S.r.l.", glm::vec4( 255,0,0,1 ) ); 
    
    GLSceneTextNode* tnode = new GLSceneTextNode( "Text1", text, nullptr );
    
    tnode->getMatrixModel().translate( 0, 0, -1 );
    
    m_pSceneGraph->addSceneNode( new GLSceneCameraNode( "MainCamera", new GLCamera( TRUE ) ) );
    
    GLSceneCameraNode* pMainCamera = dynamic_cast<GLSceneCameraNode*>(m_pSceneGraph->getSceneNode( "GLSceneCameraNode", "MainCamera" ));
    
    pMainCamera->getCamera()->getProjectionMatrix().get() = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 50.0f);
    pMainCamera->getCamera()->getProjectionMatrix().translate( 0, 0, 0.0f );
    
    // Add text node
    m_pSceneGraph->addSceneNode( tnode );
    
    m_pViewPort   = new GLViewPort( m_pSceneGraph ); 


    FStopWatch  swTotSeconds;
    FStopWatch  swParSeconds;
    FStopWatch  swRender;
    DOUBLE      dTotFrames = 0.0f;
    DOUBLE      dParFrames = 0.0f;
    
    GLFpsSync   fps;
    fps.setFps( m_dFps );

    ///////////////
    int _iWidth  = 0;
    int _iHeight = 0;

    
    GLLayer* pLayer1 = new GLLayer( *m_pViewPort );
    GLLayer* pLayer2 = new GLLayer( *m_pViewPort );
    GLLayer* pLayer3 = new GLLayer( *m_pViewPort );
    GLLayer* pLayer4 = new GLLayer( *m_pViewPort );
    GLLayer* pLayer5 = new GLLayer( *m_pViewPort );
    
    m_pSceneGraph->addSceneNode( new GLSceneLayerNode( "Layer5", pLayer5 ) );
    m_pSceneGraph->addSceneNode( new GLSceneLayerNode( "Layer4", pLayer4 ) );
    m_pSceneGraph->addSceneNode( new GLSceneLayerNode( "Layer3", pLayer3 ) );
    m_pSceneGraph->addSceneNode( new GLSceneLayerNode( "Layer2", pLayer2 ) );
    m_pSceneGraph->addSceneNode( new GLSceneLayerNode( "Layer1", pLayer1 ) );
    
    
    m_pWindow->connect( pLayer1 );
    m_pWindow->connect( pLayer2 );
    m_pWindow->connect( pLayer3 );
    m_pWindow->connect( pLayer4 );
    m_pWindow->connect( pLayer5 );
    
    
    
    GLSceneLayerNode* pNodeLayer1 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer1" ));
    GLSceneLayerNode* pNodeLayer2 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer2" ));
    GLSceneLayerNode* pNodeLayer3 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer3" ));
    GLSceneLayerNode* pNodeLayer4 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer4" ));
    GLSceneLayerNode* pNodeLayer5 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer5" ));

    
    pNodeLayer1->getMatrixModel().translate( 0, 0,  1 );
    pNodeLayer2->getMatrixModel().translate( 0, 0,  2 );
    pNodeLayer3->getMatrixModel().translate( 0, 0,  3 );
    pNodeLayer4->getMatrixModel().translate( 0, 0,  4 );
    pNodeLayer5->getMatrixModel().translate( 0, 0,  5 );
    
    
    ((GLLayer*)pNodeLayer1->getReference())->setBackground( glm::vec4( 0.5,0.5,0.5, 0.2 ) );
    ((GLLayer*)pNodeLayer2->getReference())->setBackground( glm::vec4( 0.0,0.0,0.5, 0.3 ) );
    ((GLLayer*)pNodeLayer3->getReference())->setBackground( glm::vec4( 0.0,0.5,0.0, 0.4 ) );
    ((GLLayer*)pNodeLayer4->getReference())->setBackground( glm::vec4( 0.5,0.0,0.0, 0.5 ) );
    ((GLLayer*)pNodeLayer5->getReference())->setBackground( glm::vec4( 0.0,0.5,0.5, 1.0 ) );
    
    
    
    GLFont*  wfont = fl->createFont( "truetype/freefont/FreeMono.ttf", GLSize( 0, 40) );
    GLLabel* widget = new GLLabel(nullptr);
    
    GLTexture* pTexture = new GLTexture();
    pTexture->load( GLTexture::etlFreeImage, "/etc/gles-gui/media/wall.jpg" );
    
    widget->setPosition( 100, 100 );
    //widget->setSize( 800, 800 );
    //widget->setBackground( glm::vec4( 0,0,1,1 ) );
    //widget->setBackground( pTexture );
    
    wfont->setMargins(  10,10,10,10 );
    
    widget->setLabel( wfont, L"Testo Di Prova", glm::vec4( 1,1,1,1), wtaAutoResize );
    
    ((GLLayer*)pNodeLayer1->getReference())->setBackground( pTexture );
    ((GLLayer*)pNodeLayer1->getReference())->addChild( widget );
    
    int counter = 0;
    while ( m_pWindow->check( GLWindow::eWindowShouldClose ) == FALSE )
    {
      m_pWindow->getFramebufferSize( _iWidth, _iHeight );
      
      ///////////////
      m_pViewPort->setArea( 0, 0, _iWidth, _iHeight );

      // Update background color
      m_pViewPort->getScene()->setBackground( 0.2f, 0.2f, 0.2f, 0.0f );

      ///////////////
      m_pViewPort->clearBuffer( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

      FString sLabel( 0, "Counter %03d", counter++ );
      if (counter > 999 )
	counter = 0;
      widget->setLabel( wfont, sLabel, glm::vec4( 1,1,1,1), wtaCentered );

      
      ///////////////
      m_pViewPort->render();
      

      if ( m_bVerticalSync == TRUE )
      {
	// Wait for vertical sync, at least one moonitor refresh
	// 
	m_pWindow->setSwapInterval(1);
	
	DOUBLE dTime = fps.sync();
	if ( dTime > 0 )
	{      
	  FThread::Sleep( dTime * 1000 );
	}
      }

      
      if ( m_bShowStats == TRUE )
      {
	dParFrames += 1.0f;
	dTotFrames += 1.0f;
	
	printf( "TOT %.2f fps : CUR %.2f fps : RENDER TIME %.4f          \r", (dTotFrames / swTotSeconds.Peek()), (dParFrames / swParSeconds.Peek()), swRender.Peek() );
	
	swRender.Reset();
	
	if ( swParSeconds.Peek() >= 1 )
	{
	  dParFrames = 0.0f;
	  swParSeconds.Reset();
	}
      }    
      
      ///////////////
      m_pWindow->swapBuffers();
      
      ///////////////
      // Will process messages that requires to be executed on main thread.
      m_pWindow->processMessage();
      
      ///////////////
      GLApplication::GetInstance().pollEvents();
    }
    
    delete m_pWindow;
    m_pWindow = nullptr;
    
  }
  
// GLApplicationEvents implementation  
protected:
  /***/
  virtual VOID OnInitializeError(){}
  /***/
  virtual VOID OnError( INT iError, const FString& sDescription ){}
  /***/
  virtual VOID OnFinalizeError(){}
  
// GLWindowEvents implementation  
protected:
  /***/
  virtual VOID     OnCreating( GLWindow* pWindow )
  {
    glfwWindowHint( GLFW_RED_BITS  , 8        );
    glfwWindowHint( GLFW_GREEN_BITS, 8        );
    glfwWindowHint( GLFW_BLUE_BITS , 8        );
    glfwWindowHint( GLFW_ALPHA_BITS, 8        );
    glfwWindowHint( GLFW_DECORATED , GL_FALSE );
  
    GLWindowEvents::OnCreating( pWindow );
  }
  /***/
  virtual VOID     OnKeyPressed( GLWindow* pWindow, INT iKey, INT iScanCode, WORD wMods )
  { 
    HandleKey( iKey ); 
    
    if ( m_bDefaultKeys )
      GLWindowEvents::OnKeyPressed( pWindow, iKey, iScanCode, wMods );    
  }
  /***/
  virtual VOID     OnKeyRepeated( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
  { HandleKey( iKey ); }

protected:
  /***/
  virtual VOID     OnInitialize()
  {
    if ( ParseOptions( s_argc, s_argv ) == FALSE )
      exit(0);

    InitLogging();
    
    m_pWindow = nullptr;

    GLApplication::init( this );
    
    LOG_INFO( FString( 0, "GLFW Version %s", GLApplication::GetInstance().getVersion().GetBuffer() ), OnInitialize() );
  }
  /***/
  virtual VOID     OnFinalize()
  {
    GLApplication::GetInstance().final();
    
    FinalLogging();
  }

private:
  /***/
  VOID   setDefaults()
  {
    m_bDefaultKeys  = FALSE;
    m_bFullScreen   = TRUE;
    m_bVerticalSync = TRUE;
    m_bShowStats    = FALSE;
    m_iWidth        = 1024;
    m_iHeight       =  768;
    m_dFps          = 10.0;    
  }

  /***/
  BOOL   ParseOptions( int argc, char* argv[] )
  {
    setDefaults();
    
    int ndx = 0;
    while ( ++ndx < argc )
    {
      FString sArg( argv[ndx] );
      
      if ( sArg == "--help" )
      {
	printf("BCM GUI Application\n");
	printf("----------------\n");
	printf("\n");
	printf("Usage: \n");
	printf("  ./bcm-gui <options>\n");
	printf("\n");
	printf("Options:\n");
	printf("\n");
	printf("  --help                       Display this help.\n");
	printf("  --dkeys                      Enable handling for default keys.\n");
	printf("                               eg. ESC - exit to close window.\n");
	printf("  --windowed                   Enable windowed mode.\n");
	printf("  --nosync                     Avoid FPS limits and VSYNC.\n");
	printf("                               This option could help for performances tuning.\n");
	printf("  --stats                      Show AVG ( Average ) and CUR ( Current ) FPS.\n");
	printf("  --width  <pixels>            Overwrite default 1024 pixels.\n");
	printf("  --height <pixels>            Overwrite default  768 pixels.\n");
	printf("  --fps    <value>             Overwrite default   10 fps.\n");
	printf("\n");
	
	return false;
      }
      else
      if ( sArg == "--dkeys" )
      {
	m_bDefaultKeys  = TRUE;
      }
      else
      if ( sArg == "--windowed" )
      {
	m_bFullScreen   = FALSE;
      }
      else
      if ( sArg == "--nosync" )
      {
	m_bVerticalSync = FALSE;
      }
      else
      if ( sArg == "--stats" )
      {
	m_bShowStats    = TRUE;
      }
      else
      if ( sArg == "--width" )
      {
	FString sValue( argv[++ndx] );
	m_iWidth = (INT)sValue;
      }
      else
      if ( sArg == "--height" )
      {
	FString sValue( argv[++ndx] );
	m_iHeight = (INT)sValue;
      }
      else
      if ( sArg == "--fps" )
      {
	FString sValue( argv[++ndx] );
	m_dFps = (DOUBLE)sValue;
      }
    }
    
    return true;
  }

  /***/
  VOID   HandleKey( INT iKey )
  {
    GLSceneCameraNode* pMainCamera = dynamic_cast<GLSceneCameraNode*>(m_pSceneGraph->getSceneNode( "GLSceneCameraNode", "MainCamera" ));
    
    switch ( iKey )
    {
      case 65 : // a
      {
	pMainCamera->getCamera()->getProjectionMatrix().translate( 0, 0, -.1 );
      }; break;
      
      case 90 : // z
      {
	pMainCamera->getCamera()->getProjectionMatrix().translate( 0, 0, +.1 );
      }; break;
      
      case 263 : // left arrow
      {
	pMainCamera->getCamera()->getProjectionMatrix().rotateX( -.1 );
      }; break;
      
      case 262 : // right arrow
      {
	pMainCamera->getCamera()->getProjectionMatrix().rotateX( +.1 );
      }; break;

      case 265 : // up arrow
      {
	pMainCamera->getCamera()->getProjectionMatrix().rotateY( -.1 );
      }; break;
      case 264 : // down arrow
      {
	pMainCamera->getCamera()->getProjectionMatrix().rotateY( +.1 );
      }; break;

      default :
	printf ( "key code %d\n", iKey );
      break;
    }
    
    printf( "(0) %f %f %f \n", pMainCamera->getCamera()->getProjectionMatrix().get()[0][0], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[0][1], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[0][2] 
	    );
    
    printf( "(1) %f %f %f \n", pMainCamera->getCamera()->getProjectionMatrix().get()[1][0], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[1][1], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[1][2] 
	    );
    
    printf( "(2) %f %f %f \n", pMainCamera->getCamera()->getProjectionMatrix().get()[2][0], 
	    		       pMainCamera->getCamera()->getProjectionMatrix().get()[2][1], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[2][2] 
	    );

    printf( "(3) %f %f %f \n", pMainCamera->getCamera()->getProjectionMatrix().get()[3][0], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[3][1], 
			       pMainCamera->getCamera()->getProjectionMatrix().get()[3][2] 
	    );
  }

  void   InitLogging()
  {
    FLogDeviceCollector::Initialize();

    const FLogMessageColorization* pLogMessageColorization  = new FLogMessageColorization();

    ILogDevice* _pLogDevice0 = new FConsoleLogDevice( "CONSOLE", pLogMessageColorization );

    FLogDeviceCollector::GetInstance().AddDevice( _pLogDevice0 );

    FLogger::Initialize();

    FLogger::GetInstance().RegisterDevice( "CONSOLE" );
  
    FLogger::GetInstance().GetGlobalMailbox()->SetLogMessageFlags( 0xFFFFFFFF );
    FLogger::GetInstance().GetGlobalMailbox()->SetVerbosityFlags ( 0xFFFFFFFF );
  }

  void   FinalLogging()
  {
    FThread::Sleep( 100 );
  
    FLogger::GetInstance().Finalize();
  }
  
private:
  BOOL            m_bDefaultKeys;
  BOOL            m_bFullScreen;
  BOOL            m_bVerticalSync;
  BOOL            m_bShowStats;
  INT             m_iWidth;
  INT             m_iHeight;
  DOUBLE          m_dFps;

  GLWindow*       m_pWindow;
  GLSceneGraph*   m_pSceneGraph;
  GLViewPort*     m_pViewPort;
};

GENERATE_CLASSINFO( GlesGui, FSingleton )
IMPLEMENT_SINGLETON( GlesGui )

int main( int argc, char* argv[] )
{
  s_argc = argc;
  s_argv = argv;
  
  GlesGui::Initialize();
  
  GlesGui::GetInstance().Run();
  
  GlesGui::GetInstance().Finalize();
  
  return 0;
}