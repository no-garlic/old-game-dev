
#ifndef __LOADING_SCREEN_SEQUENCE_H_
#define __LOADING_SCREEN_SEQUENCE_H_


#include "libEngine.h"


// Displays a sequence of loading screens with a quick fade to black
// in-between each one.
class LoadingScreenSequence : private Unique
{
public:
  // Constructor and destructor
  LoadingScreenSequence();
  virtual ~LoadingScreenSequence();

  // Iniitalise the loading screen assets (creates the UI and loads
  // the textures.
  bool Init(FileHandle handle);

  // Start the sequence of loading screens. Each image is displayed for 'imageTime'
  // and the screen fades to whatever color the config specifies for 'fadeTime' between
  // each image.
  void Start(float imageTime, float fadeTime);

  // Get the progress of the entire sequence (from 0 to 100).
  uint GetProgress();

  // Has the seuence finished (ie, the progress is 100)
  bool HasFinished();

  // Called to update the sequence each frame
  void Update();

  // Called to render the sequence each frame
  void Render();

private:
  // Update the image that is displayed
  void UpdateImage();

  // Update the fade image / alpha
  void UpdateTransition();

private:
  UI               *m_pUI;                    // The user interface
  UIImage          *m_pFadeImage;             // The fade image
  Array<UIImage *>  m_LoadingScreenImages;    // All loading screens
  float             m_FadeTime;               // Time to fade between images
  float             m_TotalTime;              // The total time for the sequence
  float             m_ElapsedTime;            // The elapsed time since the sequence started
  bool              m_HasFinished;            // Has the sequence finished
  float             m_Progress;               // The progress (0 to 100)

};


#endif // __LOADING_SCREEN_SEQUENCE_H_

// -- EOF


