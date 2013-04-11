#ifndef __GL_WINDOW_H__
#define __GL_WINDOW_H__


#include "ngl/Camera.h"
#include "ngl/TransformStack.h"
#include <ngl/Light.h>

#include <QtOpenGL>
#include <QTime>

//----------------------------------------------------------------------------------------------------------------------
/// @file GLWindow.h
/// @brief a basic Qt GL window class for ngl demos
/// @author Jonathan Macey
/// @modified by Octavian Mihai Vasilovici to support the deferred rendering methods.
/// @version 1.0
/// @date 28/03/13
/// Revision History :
//----------------------------------------------------------------------------------------------------------------------
class GLWindow : public QGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for GLWindow
  /// @param [in] _parent the parent window to create the GL context in
  //----------------------------------------------------------------------------------------------------------------------
  GLWindow(
           QWidget *_parent
          );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~GLWindow();
  inline void toggleAnimation(){m_animate ^=true;}

	// Process keyevents
	void processKey(
									QKeyEvent *_event
									);

private :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the x rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_spinXFace;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the y rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_spinYFace;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool m_rotate;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the Right mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool m_translate;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_origX;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_origY;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int m_origXPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int m_origYPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Our Camera
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Camera *m_cam;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief transformation stack for the gl transformations etc
  //----------------------------------------------------------------------------------------------------------------------
  ngl::TransformStack m_transformStack;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the model position for mouse movement
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_modelPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief timer id for the animation timer
  //----------------------------------------------------------------------------------------------------------------------
  int m_lightTimer;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if were animating the light
  //----------------------------------------------------------------------------------------------------------------------
  bool m_animate, light_animation;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief our light
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Light *m_light;
  //----------------------------------------------------------------------------------------------------------------------

protected:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  The following methods must be implimented in the sub class
  /// this is called when the window is created
  //----------------------------------------------------------------------------------------------------------------------
  void initializeGL();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called whenever the window is re-sized
  /// @param[in] _w the width of the resized window
  /// @param[in] _h the height of the resized window
  //----------------------------------------------------------------------------------------------------------------------
  void resizeGL(
                const int _w,
                const int _h
               );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is the main gl drawing routine which is called whenever the window needs to be re-drawn
  //----------------------------------------------------------------------------------------------------------------------
  void paintGL();

private :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseMoveEvent (
                       QMouseEvent * _event
                      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mousePressEvent (
                        QMouseEvent *_event
                       );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent (
                          QMouseEvent *_event
                         );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief called when the timer is triggered
  //----------------------------------------------------------------------------------------------------------------------
  void timerEvent(
                    QTimerEvent *_event
                   );
  //----------------------------------------------------------------------------------------------------------------------
  // @brief this method is called everytime the mouse wheel is moved inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void wheelEvent(
									 QWheelEvent *_event
								 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a method to update the light
  //----------------------------------------------------------------------------------------------------------------------
  void updateLight();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw our scene passing in the shader to use
  /// @param[in] _shader the name of the shader to use when drawing
  //----------------------------------------------------------------------------------------------------------------------
  void drawScene(
                  const std::string &_shader
                );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load all the transform values to the shader
  /// @param[in] _tx the current transform to load
  //----------------------------------------------------------------------------------------------------------------------
  void loadMatricesToShader(
                             ngl::TransformStack &_tx
                           );
};

#endif