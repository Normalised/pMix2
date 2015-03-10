/*
  ==============================================================================

    pMixInterpolationSpaceActions.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#ifndef PMIXINTERPOLATIONSPACEACTIONS_H_INCLUDED
#define PMIXINTERPOLATIONSPACEACTIONS_H_INCLUDED

#include "JuceHeader.h"

class MovePresetAction : public UndoableAction
{
public:
  MovePresetAction (Component* interpolationSpace, const String& componentID, Rectangle<int> startBounds, Rectangle<int> endBounds) noexcept;
  bool perform();
  bool undo();
  int getSizeInUnits();
  
private:
  Component* interpolationSpace;
  String componentID;
  Rectangle<int> startBounds;
  Rectangle<int> endBounds;
  JUCE_DECLARE_NON_COPYABLE (MovePresetAction)
};

#endif  // PMIXINTERPOLATIONSPACEACTIONS_H_INCLUDED
