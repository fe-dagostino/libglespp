

#include <iostream>
#include <libavc++/avapplication.h>
#include <libavc++/avdecoder.h>
#include <libavc++/avimage.h>
#include <libavc++/avsample.h>
#include <libavc++/avresample.h>
#include <libavc++/avsampleoptions.h>

using namespace libavcpp;

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <FThread.h>
#include <FMutexCtrl.h>
#include <FStopWatch.h>
#include <FTMailbox.tlh>

#include "include/GLApplication.h"
#include "include/GLVertexShader.h"
#include "include/GLFragmentShader.h"
#include "include/GLProgram.h"
#include "include/GLVertices.h"

#include "portaudio.h"
#include <ao/ao.h>

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
//#define FRAMES_PER_BUFFER (512)
#define FRAMES_PER_BUFFER (1152)

#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) 

#define WRITE_TO_FILE   (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

 /* Non-linear amplifier with soft distortion curve. */
float CubicAmplifier( float input )
{
    float output, temp;
    if( input < 0.0 )
    {
         temp = input + 1.0f;
         output = (temp * temp * temp) - 1.0f;
     }
     else
     {
         temp = input - 1.0f;
         output = (temp * temp * temp) + 1.0f;
     }
 
     return output;
 }
 
#define FUZZ(x) CubicAmplifier(CubicAmplifier(CubicAmplifier(CubicAmplifier(x))))

static int gNumNoInputs = 0;


 
  
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

using namespace libavcpp;


class AVThread : protected FThread, public IAVDecoderEvents
{
  
public:
  AVThread()
    : FThread( NULL, FThread::TP_ABOVE_NORMAL, 1048576 ),
      m_pAvDecoder(NULL), m_outStream( NULL ), m_mbxAudio( "Audio Samples Mailbox" ,NULL )
  {
    m_outParameters.device = paNoDevice;
  }

  using FThread::Wait;
  
  /***/
  void start( FString sFilename )
  {
    //////////////////////////////////
    // Initialize decoder
    CAVStreamOptions  avOpts( sFilename, NULL/*pFormatName*/, AV_SET_BEST_VIDEO_CODEC|AV_SET_BEST_AUDIO_CODEC );
    
    m_pAvDecoder = new CAVDecoder();

    m_pAvDecoder->setDecoderEvents( this, false );    

    m_pAvDecoder->open( &avOpts, 0.0 );
    
    m_bExit = FALSE;

    FThread::Start();
  }
  
  /***/
  void stop()
  {
    FThread::Stop();
    
    if ( m_outStream != NULL )
    {
      PaError err = Pa_CloseStream( m_outStream );
      if ( err != paNoError )
      {
	// @todo
      }
      
      m_outStream = NULL;
    }
  }
  
  void getImage( CAVImage& rAvImage )
  {
    FMutexCtrl _mutex( m_mtxAvImage );
    
    rAvImage.init( m_avImage, -1, -1 );
  }
    
protected:
  
  /**/
  void Run()
  {
    m_swSyncFPS.Reset();
    
    while ( m_bExit == FALSE )
    {
      //printf( "-_swSyncFPS.Peek()[%f] >= *_dLastPST[%f]\n", m_swSyncFPS.Peek(), m_dLastPST );
      if ( m_swSyncFPS.Peek() >= m_dLastPST )
      {
	//printf( "*_swSyncFPS.Peek()[%f] >= *_dLastPST[%f]\n", m_swSyncFPS.Peek(), m_dLastPST );
	
	AVResult  avResult = m_pAvDecoder->read( AVD_EXIT_ON_NEXT_AUDIO_FRAME|AVD_EXIT_ON_NEXT_VIDEO_FRAME );
	if ( avResult == AVResult::eAVEndOfFile )
	{
	  printf( "set exit\n" );
	  m_bExit = true;
	}
      }
      else
      {
	FThread::Sleep(1);
      }
    }

    printf( "exit\n" );
  }
  
  virtual void   OnStartDecoder( const AVCodecContext* pAVVideoCodec, const AVCodecContext* pAVAudioCodec )
  {
    /*
    int driver = ao_default_driver_id();

    // The format of the decoded PCM samples
    ao_sample_format sample_format;
    sample_format.bits = 8;
    if (pAVAudioCodec->sample_fmt == AV_SAMPLE_FMT_U8) 
    {
	sample_format.bits = 8;
    } else if (pAVAudioCodec->sample_fmt == AV_SAMPLE_FMT_S16)
    {
	sample_format.bits = 16;
    } else if (pAVAudioCodec->sample_fmt == AV_SAMPLE_FMT_S32)
    {
	sample_format.bits = 32;
    }
    
    sample_format.channels = pAVAudioCodec->channels;
    sample_format.rate = pAVAudioCodec->sample_rate;
    sample_format.byte_format = AO_FMT_NATIVE;
    sample_format.matrix = 0;
    
    m_pAODevice = ao_open_live(driver, &sample_format, NULL);

    return ;*/
        
    /////////////////////
    // Initialize audio
    if ( m_outParameters.device == paNoDevice )
    {
      m_outParameters.device = Pa_GetDefaultOutputDevice();
      if (m_outParameters.device != paNoDevice)
      {
	int      iSampleRate     = pAVAudioCodec->sample_rate;
	uint64_t iChannelLayout  = AV_CH_LAYOUT_STEREO;
	
	
	m_outParameters.channelCount              = pAVAudioCodec->channels;                     
	
	m_outParameters.sampleFormat              = 0;
	if ( pAVAudioCodec->sample_fmt == AV_SAMPLE_FMT_U8 )
	  m_outParameters.sampleFormat            = paInt8;
	else if ( pAVAudioCodec->sample_fmt == AV_SAMPLE_FMT_S16 )
	  m_outParameters.sampleFormat            = paInt16;
	else if ( pAVAudioCodec->sample_fmt == AV_SAMPLE_FMT_S32 )
	  m_outParameters.sampleFormat            = paFloat32;
	
	m_outParameters.suggestedLatency          = Pa_GetDeviceInfo( m_outParameters.device )->defaultLowOutputLatency;
	m_outParameters.hostApiSpecificStreamInfo = NULL;
	
	PaError err = Pa_IsFormatSupported( NULL, &m_outParameters,  iSampleRate );
	if ( err != paFormatIsSupported )
	{
	  m_outParameters.channelCount            = 2;                     
	  m_outParameters.sampleFormat            = paFloat32;
	  iSampleRate                             = 48000;
	  if ( pAVAudioCodec->channel_layout != 0 )
	    iChannelLayout = pAVAudioCodec->channel_layout;
	  
	  m_pAVResample = new CAVResample();
	  m_pAVResample->open( 
			      new CAVSampleOptions( pAVAudioCodec->channels, iChannelLayout, pAVAudioCodec->sample_rate, pAVAudioCodec->sample_fmt ), 
			      new CAVSampleOptions(                       2, AV_CH_LAYOUT_STEREO, iSampleRate, AV_SAMPLE_FMT_FLT )
 			    );
	}
	
	err = Pa_OpenStream(
				    &m_outStream,
				    NULL, /* no input */
				    &m_outParameters,
				    iSampleRate, //SAMPLE_RATE,
				    FRAMES_PER_BUFFER, // paFramesPerBufferUnspecified, //FRAMES_PER_BUFFER,
				    paClipOff,      /* we won't output out of range samples so don't bother clipping them */
				    playCallback,
				    this 
				   );
	if( err != paNoError )
	{
	  // @todo
	}
	
	if (m_outStream != NULL )
	{
	  err = Pa_StartStream(m_outStream);
	  if( err != paNoError )
	  {
	    // @todo
	  }
	}
      } // if (m_outParameters.device != paNoDevice)
    } // if ( m_outParameters.device == paNoDevice )
  }
   
  /**
    *  Event will be raised just in presence of one key frame.
    *  In presence of key frame events will be raised in the following sequence
    *  OnVideoKeyFrame() and after that OnVideoFrame(). 
    */
  virtual void   OnVideoKeyFrame( const AVFrame* pAVFrame, const AVStream* pAVStream, const AVCodecContext* pAVCodecCtx, double pts )
  {
    
  }

  /**
    *  Event will be raised for each frame coming from the stream.
    *  Return value true in order to continue decoding, false to interrupt.
    *  Note: this event will be raised also for each key frame.
    */
  virtual bool   OnVideoFrame( const AVFrame* pAVFrame, const AVStream* pAVStream, const AVCodecContext* pAVCodecCtx, double pts )
  {
    FMutexCtrl _mutex( m_mtxAvImage );
    
    m_dLastPST = pts;
    m_avImage.init( pAVFrame, pAVCodecCtx, -1, -1 );
    
    return true;
  }

  /**
    *  Event will be raised for each frame coming from the stream.
    *  Return value true in order to continue decoding, false to interrupt.
    *  Note: this event will be raised for each frame.
    */
  virtual bool   OnFilteredVideoFrame( const AVFilterBufferRef* pAVFilterBufferRef, const AVStream* pAVStream, const AVCodecContext* pAVCodecCtx, double pts )
  {
    return true;
  }

  
  /**
    *  Event will be raised for each frame coming from the stream.
    *  Return value true in order to continue decoding, false to interrupt.
    */
  virtual bool   OnAudioFrame( const AVFrame* pAVFrame, const AVStream* pAVStream, const AVCodecContext* pAVCodecCtx, double pts )
  {
    // Send the buffer contents to the audio device
    //ao_play(m_pAODevice, (char*)pAVFrame->data, pAVFrame->linesize[0] );
/*
    m_pAVResample->convert( pAVCodecCtx, pAVFrame, m_avSample );
    
    printf( "int linesize[%d] -- out linesize[%d]\n", pAVFrame->linesize[0], m_avSample.getSize(0) );
    
    int iSamples = m_avSample.getSamples();
    
    Pa_WriteStream( m_outStream, m_avSample.getData(0), m_avSample.getSamples() );
*/    
    
    CAVSample* pSample = new CAVSample();

    m_pAVResample->convert( pAVCodecCtx, pAVFrame, *pSample );
    
    //pSample->init( pAVFrame, pAVCodecCtx );
    
    m_mbxAudio.Write( new AudioData( pSample, pts ) );
    
    return true;
  }
  
private:

  /* This routine will be called by the PortAudio engine when audio is needed.
  ** It may be called at interrupt level on some machines so don't do anything
  ** that could mess up the system like calling malloc() or free().
  */
  static int playCallback( 	
			    const void *inputBuffer, void *outputBuffer,
			    unsigned long framesPerBuffer,
			    const PaStreamCallbackTimeInfo* timeInfo,
			    PaStreamCallbackFlags statusFlags,
			    void *userData 
			 )
  {
    int paRetValue = paContinue;
    
    AVThread*  pAVThread    = (AVThread*)userData;
    AudioData* pAudioSample = pAVThread->m_mbxAudio.Read();
    if ( pAudioSample == NULL )
      return paRetValue;
    
    
    CAVSample* pAVSample = pAudioSample->_pSample;
     
     SAMPLE *src = (SAMPLE *)pAVSample->getData(0);
     
     SAMPLE *out = (SAMPLE*)outputBuffer;
     
     const SAMPLE *in = (const SAMPLE*)inputBuffer;
     unsigned int i;
     (void) timeInfo; /* Prevent unused variable warnings. */
     (void) statusFlags;
     (void) userData;
 
     //Pa_WriteStream( pAVThread->m_outStream, pAVSample->getData(0), pAVSample->getSamples() );
     
     if( inputBuffer == NULL )
     {
         for( i=0; i<framesPerBuffer; i++ )
         {
	    if (src != NULL )
	    {
             *out++ = *src++;  /* left - silent */
             *out++ = *src++;  /* right - silent */
	    }
         }
     }
     else
     {
         for( i=0; i<framesPerBuffer; i++ )
         {
             *out++ = FUZZ(*in++);  /* left - distorted */
             *out++ = *in++;          /* right - clean */
         }
     }
   
    if ( pAudioSample != NULL )
    {
      delete pAudioSample;
      pAudioSample = NULL;
    }
    
    return paRetValue;
  }
  
private:
  struct AudioData
  {
    AudioData( CAVSample* pAudioSample, double pts )
    {
      _pSample = pAudioSample;
      _pts     = pts;      
    }
    
    ~AudioData()
    {
      if ( _pSample != NULL )
      {
	delete _pSample;
	_pSample = NULL;
      }
    }
    
    double       _pts;
    CAVSample*   _pSample;
  };
private:
  CAVDecoder*             m_pAvDecoder;  
  CAVImage                m_avImage;
  FMutex                  m_mtxAvImage;
  volatile BOOL           m_bExit;
  double                  m_dLastPST;
  FStopWatch              m_swSyncFPS;
  
  FTMailbox<AudioData* >  m_mbxAudio;          
  PaStreamParameters      m_outParameters;
  PaStream*               m_outStream;
  ao_device*              m_pAODevice;
  
  CAVResample*            m_pAVResample;
  CAVSample               m_avSample;               
};



GLuint    textures[1];
CAVImage  avImage;



  GLchar vShaderStr[] =
	    "attribute vec4 a_position;\n"
	    "attribute vec2 a_texCoord;\n"
	    "varying vec2 v_texCoord;\n"
	    "void main()\n"
	    "{\n"
	    "	v_texCoord = a_texCoord; \n"
	    "	gl_Position = a_position; \n"
	    "}\n";
	    
  GLchar fShaderStr[] =
	    "precision mediump float;\n"
	    "varying vec2 v_texCoord;\n"
	    "uniform sampler2D s_texture;\n"
	    "void main()\n"
	    "{\n"
	    "	gl_FragColor = texture2D(s_texture, v_texCoord); \n"
	    "}\n";
	    
  GLfloat vColors[]   = { 1.0f,  0.0f, 0.0f, 0.0f,
			  0.0f,  1.0f, 0.0f, 0.0f,
			  0.0f,  0.0f, 1.0f, 0.0f,
    			  1.0f,  1.0f, 0.0f, 0.0f

		      };

  GLfloat vVertices[] = {-0.5f,  0.5f, 0.0f,
			  0.5f,  0.5f, 0.0f,
			 -0.5f, -0.5f, 0.0f,
    			  0.5f, -0.5f, 0.0f

		      };

  GLfloat vTexCoord[] = { 
    			  0.0f,  0.0f,
			  1.0f,  0.0f,
			  0.0f,  1.0f,
			  1.0f,  1.0f,
		      };



int main_( int argc, char* argv[] )
{
  GLFWwindow* winMain = NULL;

  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);

  int winWidth  = 720;
  int winHeight = 480;
  
  winMain = glfwCreateWindow(winWidth, winHeight, "Simple glPlayer", NULL, NULL);
  if (!winMain)
  {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }
  
  glfwMakeContextCurrent(winMain);

    glfwSetWindowSize( winMain, winWidth, winHeight );

  glfwSetKeyCallback(winMain, key_callback);
  
  //////////////////////////////////////////////////////////
  
  const GLfloat zNear = 1, zFar = 600, fieldOfView = 40*M_PI/180.0;  
  
  
  
//GLfloat size = zNear * tanf(fieldOfView / 2.0);   
//esFrustum(&projection, -size, size, -size / ((float) height / (float) width), size / ((float) height / (float) width), zNear, zFar);   
  
//glViewport(0, 0, width, height);  
  
  //////////////////////////////////////////////////////////
  
  glfwDestroyWindow(winMain);

  glfwTerminate();
  
  return 0;
}

int main( int argc, char* argv[] )
{
  PaError paRetValue = paNoError;
  
  CAVApplication::initLibAVCPP();

  GLApplication::init(NULL);
  
  GLApplication::GetInstance().getMonitorsList();
  
  paRetValue = Pa_Initialize();
  if ( paRetValue != paNoError )
  {
    // @todo
  }
  // To initalize libao for playback
  //ao_initialize();
  
  GLFWwindow* winMain = NULL;

  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
    
  int winWidth  = 1920;//720;
  int winHeight = 1080;//480;
  int iMonitorCount = 0;
  GLFWmonitor** pMonitors = glfwGetMonitors( &iMonitorCount );
  GLFWmonitor* pMonitor = NULL;
  if ( iMonitorCount > 0 )
  {
    for ( int i=0; i < iMonitorCount; i++ )
    {
      const char* pMonitorName = glfwGetMonitorName( pMonitors[i] );
      printf( "Monitor [%d] Name [%s]\n", i, pMonitorName );
      if (strcmp(pMonitorName,"DVI-D-0")==0)
	pMonitor = pMonitors[i];
      
      const GLFWvidmode* pVideoMode = glfwGetVideoMode( pMonitors[i] ); 
    }
  }
  
  winMain = glfwCreateWindow(winWidth, winHeight, "Simple glPlayer", pMonitor, NULL);
  if (!winMain)
  {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }
  
  glfwMakeContextCurrent(winMain);

    glfwSetWindowSize( winMain, winWidth, winHeight );

  glfwSetKeyCallback(winMain, key_callback);

  //////////////////////////
  // Start decoder thread
  ///
  AVThread* pAvThread = new AVThread();
  
  pAvThread->start( argv[1] );
  
 
  //pAvThread->Wait();
	  


  glEnable(GL_TEXTURE_2D);                    // Enable texture mapping.

  GLVertices<GLfloat,GLfloat,GLfloat,GLfloat>  vertex( GLVertices<GLfloat,GLfloat,GLfloat,GLfloat>::eArrayOfStructures, 10 );
  

  GLVertexShader    _vertexShader;
  GLFragmentShader  _fragmentShader;
  GLProgram         _program;
  _vertexShader.load( vShaderStr );
  _fragmentShader.load( fShaderStr );

  FString sLogInfo;
  _vertexShader.getLog(sLogInfo);
  printf("%s\n",sLogInfo.GetBuffer());
  _fragmentShader.getLog(sLogInfo);
  printf("%s\n",sLogInfo.GetBuffer());
  
  _program.attachShaders( &_vertexShader, &_fragmentShader );
  _program.bindAttribLocation( 0, "a_texCoord" );
  _program.bindAttribLocation( 1, "a_position" );
  
  _program.link();

  // Load the vertex data
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vTexCoord);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, vVertices);

  GLfloat zDelta = 0.005f;
  
  while (!glfwWindowShouldClose(winMain))
  {
    int width, height;

    glfwGetFramebufferSize(winMain, &width, &height);
    
    glViewport(0, 0, width, height);
////////////////////////
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  vVertices[1] += zDelta;
  vVertices[0] += zDelta;

  vVertices[3] += zDelta;
  vVertices[4] -= zDelta;

  vVertices[6] -= zDelta;
  vVertices[7] += zDelta;
  
  vVertices[9] -= zDelta;
  vVertices[10] -= zDelta;
  
  if ( vVertices[1] > 1.0f )
  {
    zDelta = -0.005f;
    vVertices[1] += zDelta;
  }
  if ( vVertices[1] < 0.0f )
  {
    zDelta = 0.005f;
    vVertices[1] += zDelta;
  }
   
  // Load the vertex data
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vTexCoord);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    
  glDeleteTextures(1, &textures[0]);
    
    // Create Textures	    
    glGenTextures(1, &textures[0]);

    glActiveTexture( GL_TEXTURE0 );

    // texture 1 (poor quality scaling)
    glBindTexture(GL_TEXTURE_2D, textures[0]);   // 2d texture (x and y size)

    // Get the uniform location
    GLint location = glGetUniformLocation( _program.getId(), "s_texture");

    // Set the base map sampler to texture unit 0
    glUniform1i(location, 0);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST); // cheap scaling when image bigger than texture
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST); // cheap scaling when image smalled than texture
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    pAvThread->getImage( avImage );
    int iSize = 0;
    const unsigned char* pData = avImage.getData( 0, &iSize );
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, avImage.getWidth(), avImage.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, pData );

    
    _program.use();
    
    glActiveTexture( GL_TEXTURE0 );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
  
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
    
///////////////////////    
    glfwSwapBuffers(winMain);
    glfwPollEvents();
  }   

  glfwDestroyWindow(winMain);

  glfwTerminate();

  //////////////////////////////////
  //Finalize decoder

  // Close decoder and release resources.
    
  pAvThread->stop();
  delete pAvThread;
  
  ///////////////////////////  
    
    
  CAVApplication::deinitLibAVCPP();
    
  
  paRetValue = Pa_Terminate();
  if ( paRetValue != paNoError )
  {
    // @todo
  }
  //ao_shutdown();
  
  exit(EXIT_SUCCESS);
}

//! [code]
