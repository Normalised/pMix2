/*
==============================================================================

pMixAboutBox.h
Author:  Oliver Larkin

==============================================================================
*/

#ifndef PMIXABOUTBOX_H_INCLUDED
#define PMIXABOUTBOX_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class pMixAboutBox    : public Component
{
public:
  pMixAboutBox()
  {
    setSize (400, 300);
  }

  ~pMixAboutBox()
  {
  }

  void paint (Graphics& g)
  {
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (24.0f);
    g.drawText ("pMix 2", getLocalBounds(), Justification::centred, true);
  }

  void resized()
  {
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pMixAboutBox)
};


#endif  // PMIXABOUTBOX_H_INCLUDED
