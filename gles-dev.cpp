

#include "FSingleton.h"
#include "FStopWatch.h"

#include "GLApplication.h"
#include "GLWindowEvents.h"
#include "GLSceneGraph.h"
#include "GLViewPort.h"
#include "GLWindow.h"
#include "GLFpsSync.h"
#include "GLAnimation.h"

#include "font/GLFreeTypeFontLoader.h"

#include "GLSceneTextNode.h"
#include "GLSceneLayerNode.h"

#include "widgets/GLLabel.h"
#include <GLAutoPtr.h>

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
    
    GLAutoPtr<GLWindowOptions> ptrOptions = new GLWindowOptions( (m_bFullScreen==TRUE)?"main":"", 
								 "GLES DEV Application",
								 0, 0, 
								 m_iWidth, m_iHeight );
    
    m_pWindow->create( ptrOptions, GLWindow::epfCalling );
    
    m_pSceneGraph = new GLSceneGraph();
    if ( m_pSceneGraph == nullptr )
    {
      ERROR_INFO( "Unable to allocate SceneGraph", Run() )
      return ;
    }
    
    GLRenderer* glRenderer = m_pWindow->getRenderer();
    FString     sVendor;
    FString     sRenderer;
    FString     sVersion;
    FString     sShaderVersion;
    
    glRenderer->getVendor  ( sVendor );
    printf( "Vendor:         [%s]\n", sVendor.GetBuffer() );
    glRenderer->getRenderer( sRenderer );
    printf( "Renderer:       [%s]\n", sRenderer.GetBuffer() );    
    glRenderer->getVersion( sVersion );
    printf( "Version:        [%s]\n", sVersion.GetBuffer() );    
    glRenderer->getShaderVersion( sShaderVersion );
    printf( "Shader Version: [%s]\n", sShaderVersion.GetBuffer() );
    
    
    GLCamera*  pCamera =  new GLCamera( TRUE );
    
    //glm::vec3 cameraPosition = glm::vec3(4,3,3); // Camera is at (4,3,3), in World Space
    //glm::vec3 cameraTarget   = glm::vec3(0,0,0); // and looks at the origin
    //glm::vec3 upVector       = glm::vec3(0,1,0);  // Head is up (set to 0,-1,0 to look upside-down)
    glm::vec3 cameraPosition = glm::vec3(0,0,1); // Camera is at (4,3,3), in World Space
    glm::vec3 cameraTarget   = glm::vec3(0,0,0); // and looks at the origin
    glm::vec3 upVector       = glm::vec3(0,1,0);  // Head is up (set to 0,-1,0 to look upside-down)

    glm::mat4 CameraMatrix = glm::lookAt(
                                            cameraPosition, // the position of your camera, in world space
                                            cameraTarget,   // where you want to look at, in world space
                                            upVector        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
                                        );
    pCamera->getViewMatrix().get() = CameraMatrix;
    //pCamera->getViewMatrix().get() = glm::mat4(1.0);
    //pCamera->getViewMatrix().get() = glm::ortho( (float)0, (float)m_iWidth, (float)m_iHeight, (float)0 );
    //pCamera->getViewMatrix().get() = glm::perspective(45.0f, (float)m_iWidth / (float)m_iHeight, 0.1f, 50.0f);
    //pCamera->getViewMatrix().get() = glm::perspective(45.0f, (float)m_iWidth / (float)m_iHeight, 0.1f, 50.0f);
	
    m_pSceneGraph->addSceneNode( new GLSceneCameraNode( "MainCamera", pCamera ) );
  
    
    //glm::mat4 mProjection = glm::mat4( 0.1f );
    //glm::mat4 mProjection = glm::perspective(45.0f, (float)m_iWidth / (float)m_iHeight, 0.1f, 50.0f); 
    //glm::mat4 mProjection = glm::perspective(0.785398163f, (float)m_iWidth / (float)m_iHeight, 0.1f, 50.0f); 
    //glm::mat4 mProjection = glm::ortho( (float)0, (float)m_iWidth, (float)m_iHeight, (float)0, 0.1f, 500.0f );
    //glm::mat4 mProjection = glm::ortho( -1.0f*(float)m_iWidth/2, (float)m_iWidth/2, (float)m_iHeight/2, -1.0f*(float)m_iHeight/2, 0.1f, 500.0f );
    glm::mat4 mProjection = glm::perspectiveFov(45.0f, (float)m_iWidth, (float)m_iHeight, 0.1f, 500.0f);
  
    m_pViewPort   = new GLViewPort( m_pSceneGraph, mProjection ); 
  
    //
    
    
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
    
    pLayer1->setPosition( -1.0f*m_iWidth/2, -1.0f*m_iHeight/2, TRUE );

    
    m_pSceneGraph->addSceneNode( new GLSceneLayerNode( "Layer1", pLayer1 ) );
    
    m_pWindow->connect( pLayer1 );
    
    
    GLSceneLayerNode* pNodeLayer1 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer1" ));
    
    //glm::mat4 mModel = glm::mat4( 0.1f );
    //glm::mat4 mModel = glm::translate( glm::mat4(1.0f), glm::vec3( 0, 0, 0 ) );
    //glm::mat4 mModel =  glm::ortho( (float)0, (float)m_iWidth, (float)m_iHeight, (float)0, 0.1f, 1000.0f );
    //glm::mat4 mModel =  glm::ortho( (float)-1.0f, (float)1.0f, (float)1.0f, (float)-1.0f );    
    //glm::mat4 mModel =  glm::perspective(45.0f, (float)m_iWidth / (float)m_iHeight, 0.1f, 50.0f);
    glm::mat4 mModel =  glm::ortho( -1.0f*(float)m_iWidth/2, (float)m_iWidth/2, (float)m_iHeight/2, -1.0f*(float)m_iHeight/2, 0.1f, 1000.0f );

    pNodeLayer1->getMatrixModel().get() =  mModel;

	
    //m_Animation.attach( new GLAnimation() );
    //pNodeLayer1->setAnimation( m_Animation );
    
    pNodeLayer1->getMatrixModel().translate( 0, 0,   0 );
    
    
    ((GLLayer*)pNodeLayer1->getReference())->setBackground( glm::vec4( 0.5,0.5,0.5, 0.2 ) );
    
    
    
    GLFreeTypeFontLoader* fl = new GLFreeTypeFontLoader();
    
    fl->setFontsPath( "/usr/share/fonts" );
    
    GLFont*  wfont = fl->createFont( "truetype/freefont/FreeMono.ttf", GLSize( 0, 40) );
    GLLabel* widget = new GLLabel(nullptr);
    
    GLTexture* pTexture = new GLTexture();
    // Using default loader FreeImage
    //pTexture->load( GLTexture::etlFreeImage, "/etc/gles-gui/media/wall.jpg" );
    
    // Using LibAV++ image loader
    //pTexture->load( GLTexture::etlLibAV, "/etc/gles-gui/media/wall.jpg" );
    
    {
//      GLCanvas* c = new GLCanvas();
      
//      GLAutoPtr<GLCanvas> canvas( c );
//      GLAutoPtr<GLTexture>  texture( pTexture);
    
      
    }
    // Using DevIL image loader
    pTexture->load( GLTexture::etlDevIL, "../resources/media/wall.jpg" );
    
    widget->setPosition( 0, 100, TRUE );
    //widget->setSize( 800, 800 );
    widget->setBackground( glm::vec4( 0,0,1,1 ) );
    //widget->setBackground( pTexture );
    
    wfont->setMargins(  10,10,10,10 );
    
    widget->setLabel( wfont, L"Testo Di Prova", glm::vec4( 1,1,1,1), wtaAutoResize );
    
    ((GLLayer*)pNodeLayer1->getReference())->setBackground( pTexture, GLWidget::eboAsIs );
      ((GLLayer*)pNodeLayer1->getReference())->addChild( widget );
    
    int counter = 0;
    FString sLabel( 0, "Counter %03d", counter++ );

    while ( m_pWindow->check( GLWindow::eWindowShouldClose ) == FALSE )
    {
      m_pWindow->getFramebufferSize( _iWidth, _iHeight );
      
      ///////////////
      m_pViewPort->setArea( 0, 0, _iWidth, _iHeight );
      m_pViewPort->use();

      // Update background color
      m_pViewPort->getScene()->setBackground( 0.2f, 0.2f, 0.2f, 0.0f );

      ///////////////
      m_pViewPort->clearBuffer( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

      sLabel.Format ( 0, "Counter %03d", counter++ );
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
    HandleKey( iKey, wMods ); 
    
    if ( m_bDefaultKeys )
      GLWindowEvents::OnKeyPressed( pWindow, iKey, iScanCode, wMods );    
  }
  /***/
  virtual VOID     OnKeyRepeated( GLWindow* pGlWindow, INT iKey, INT iScanCode, WORD wMods )
  { HandleKey( iKey, wMods ); }

protected:
  /***/
  virtual VOID     OnInitialize()
  {
    if ( ParseOptions( s_argc, s_argv ) == FALSE )
      exit(0);

    InitLogging();
    
    m_pWindow = nullptr;

    GLApplication::init( this, "../resources/shaders/", "../resources/media/" );
    
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
	printf("GLES DEV Application\n");
	printf("----------------\n");
	printf("\n");
	printf("Usage: \n");
	printf("  ./gles-dev <options>\n");
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
  VOID   HandleKey( INT iKey, WORD wMods )
  {
    double ax = 0.01f;  // angle x
    double ay = 0.01f;  // angle y
    
    GLSceneCameraNode* pMainCamera = dynamic_cast<GLSceneCameraNode*>(m_pSceneGraph->getSceneNode( "GLSceneCameraNode", "MainCamera" ));
    GLSceneLayerNode*  pLayer1     = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer1" ));
    
    if ( wMods & GLFW_MOD_CONTROL )
    {
      switch ( iKey )
      {
	case GLFW_KEY_LEFT : // left arrow
	{
	  pLayer1->getMatrixModel().rotateX( -1.0f*ax );
	}; break;
	
	case GLFW_KEY_RIGHT : // right arrow
	{
	  pLayer1->getMatrixModel().rotateX( ax );
	}; break;

	case GLFW_KEY_UP : // up arrow
	{
	  pLayer1->getMatrixModel().rotateY( -1.0f*ay );
	}; break;
	
	case GLFW_KEY_DOWN : // down arrow
	{
	  pLayer1->getMatrixModel().rotateY( ay );
	}; break;
      }
      
      return;
    }
    
    switch ( iKey )
    {
      case 67:
      {
	/*
        GLSceneLayerNode* pNodeLayer2 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer2" ));
	
	pNodeLayer2->getMatrixModel().rotateX( ax );
	*/
      }; break;
      case 66:
      {
	/*
        GLSceneLayerNode* pNodeLayer2 = dynamic_cast<GLSceneLayerNode*>(m_pSceneGraph->getSceneNode( "GLSceneLayerNode", "Layer2" ));

	pNodeLayer2->getMatrixModel().rotateX( -1.0f*ax );
	*/
      }; break;
      
      case 65 : // a
      {
	pMainCamera->getCamera()->getViewMatrix().translate( 0, 0, -0.5f );
      }; break;
      
      case 90 : // z
      {
	pMainCamera->getCamera()->getViewMatrix().translate( 0, 0, +0.5f );
      }; break;
      
      case 263 : // left arrow
      {
	pMainCamera->getCamera()->getViewMatrix().rotateX( -.1 );
      }; break;
      
      case 262 : // right arrow
      {
	pMainCamera->getCamera()->getViewMatrix().rotateX( +.1 );
      }; break;

      case 265 : // up arrow
      {
	pMainCamera->getCamera()->getViewMatrix().rotateY( -.1 );
      }; break;
      case 264 : // down arrow
      {
	pMainCamera->getCamera()->getViewMatrix().rotateY( +.1 );
      }; break;

      default :
	printf ( "key code %d\n", iKey );
      break;
    }
    
    printf( "(0) %f %f %f \n", pMainCamera->getCamera()->getViewMatrix().get()[0][0], 
			       pMainCamera->getCamera()->getViewMatrix().get()[0][1], 
			       pMainCamera->getCamera()->getViewMatrix().get()[0][2] 
	    );
    
    printf( "(1) %f %f %f \n", pMainCamera->getCamera()->getViewMatrix().get()[1][0], 
			       pMainCamera->getCamera()->getViewMatrix().get()[1][1], 
			       pMainCamera->getCamera()->getViewMatrix().get()[1][2] 
	    );
    
    printf( "(2) %f %f %f \n", pMainCamera->getCamera()->getViewMatrix().get()[2][0], 
	    		       pMainCamera->getCamera()->getViewMatrix().get()[2][1], 
			       pMainCamera->getCamera()->getViewMatrix().get()[2][2] 
	    );

    printf( "(3) %f %f %f \n", pMainCamera->getCamera()->getViewMatrix().get()[3][0], 
			       pMainCamera->getCamera()->getViewMatrix().get()[3][1], 
			       pMainCamera->getCamera()->getViewMatrix().get()[3][2] 
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
