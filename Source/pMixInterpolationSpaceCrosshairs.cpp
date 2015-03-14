/*
  ==============================================================================

    pMixInterpolationSpaceCrosshairs.cpp
    Author:  Oliver Larkin

  ==============================================================================
*/

#include "pMixInterpolationSpaceCrosshairs.h"

InterpolationSpaceIPos::InterpolationSpaceIPos(PMixAudioEngine& audioEngine, const uint32 filterID, Colour colour)
: audioEngine(audioEngine)
, colour(colour)
, filterID(filterID)
{
}

InterpolationSpaceIPos::~InterpolationSpaceIPos ()
{
}

void InterpolationSpaceIPos::resized ()
{
  int radius = getWidth()/2;
  boundsConstrainer.setMinimumOnscreenAmounts(radius, radius, radius, radius);
  //  label->centreWithSize(getWidth()-5, 20);
}

void InterpolationSpaceIPos::mouseDown (const MouseEvent& e)
{
  myDragger.startDraggingComponent (this, e);
  toFront (true);
}

void InterpolationSpaceIPos::mouseDrag (const MouseEvent& e)
{
  Point<double> normalizedPos;
  normalizedPos.x = getX() / (double) getParentWidth();
  normalizedPos.y = getY() / (double) getParentHeight();
  audioEngine.getDoc().setFilterIPos(filterID, normalizedPos.x, normalizedPos.y);
  
  myDragger.dragComponent (this, e, &boundsConstrainer);
  getParentComponent()->repaint();
}

void InterpolationSpaceIPos::mouseUp (const MouseEvent& e)
{
}

void InterpolationSpaceIPos::paint (Graphics& g)
{
  g.setColour(colour);

  PathStrokeType stroke (2.5f);

  Path linePath;
  
  float mw = getWidth()/2.f;
  float mh = getHeight()/2.f;

  linePath.startNewSubPath(0, mh);
  linePath.lineTo(getWidth(), mh);
  linePath.startNewSubPath(mw, 0);
  linePath.lineTo(mw, getHeight());
  g.strokePath(linePath, stroke);
  
  g.fillEllipse ((getWidth()/2.f) - 5.f, (getHeight()/2.f)  - 5.f, 10.f, 10.f);
  g.setColour(Colours::black);
  g.drawEllipse((getWidth()/2.f) - 5.f, (getHeight()/2.f)  - 5.f, 10.f, 10.f, 1.f);
}

void InterpolationSpaceIPos::update()
{
  const AudioProcessorGraph::Node::Ptr f (audioEngine.getDoc().getNodeForId (filterID));
  
  if (f == nullptr)
  {
    delete this;
    return;
  }
  
  colour = audioEngine.getDoc().getFilterColour(filterID);
  repaint();
}

pMixInterpolationSpaceCrossHairs::pMixInterpolationSpaceCrossHairs(PMixAudioEngine& audioEngine)
: audioEngine(audioEngine)
{
  setInterceptsMouseClicks(false, true);
  audioEngine.getDoc().addChangeListener (this);
}

pMixInterpolationSpaceCrossHairs::~pMixInterpolationSpaceCrossHairs()
{
  audioEngine.getDoc().removeChangeListener(this);
  deleteAllChildren();
}

void pMixInterpolationSpaceCrossHairs::changeListenerCallback (ChangeBroadcaster* source)
{
  updateComponents();
  repaint();
}

void pMixInterpolationSpaceCrossHairs::paint (Graphics& g)
{
//  g.setColour(Colours::black);
//  
//  PathStrokeType stroke (2.5f);
//  
//  for (int f=0; f<getNumChildComponents(); f++)
//  {
//    Array<Point<float>>& positions = presetsLocations.getReference(f);
//    Path linePath;
//
//    float mw = getChildComponent(f)->getX() + getChildComponent(f)->getWidth()/2.f;
//    float mh = getChildComponent(f)->getY() + getChildComponent(f)->getHeight()/2.f;
//    
//    for (int preset = 0; preset < positions.size(); preset++)
//    {
//      linePath.startNewSubPath(mw, mh);
//      linePath.lineTo(positions[preset]);
//    }
//
//    g.strokePath(linePath, stroke);
//  }
}

void pMixInterpolationSpaceCrossHairs::resized()
{
}

void pMixInterpolationSpaceCrossHairs::updateComponents()
{
  for (int i = getNumChildComponents(); --i >= 0;)
  {
    if (InterpolationSpaceIPos* const ic = dynamic_cast <InterpolationSpaceIPos*> (getChildComponent (i)))
      ic->update();
  }

  for (int i = audioEngine.getDoc().getNumFilters(); --i >= 0;)
  {
    const AudioProcessorGraph::Node::Ptr f (audioEngine.getDoc().getNode (i));
    
    if (getComponentForFilter (f->nodeId) == nullptr)
    {
      if (f->properties.getVarPointer("presets") != nullptr)
      {
        var iposx = f->properties["iposx"];
        var iposy = f->properties["iposy"];
        Array<var>* presets = f->properties.getVarPointer("presets")->getArray();

        if (presets->size() >= 2)
        {
          InterpolationSpaceIPos* comp = new InterpolationSpaceIPos(audioEngine, f->nodeId, audioEngine.getDoc().getFilterColour(f->nodeId));
          float r = 50.f;
          float x = getWidth() * (float) iposx;
          float y = getHeight() * (float) iposy;
          comp->setBounds(x, y, r, r);
          
          addAndMakeVisible(comp);
        }
      }
    }
  }
}

InterpolationSpaceIPos* pMixInterpolationSpaceCrossHairs::getComponentForFilter (const uint32 filterID) const
{
  for (int i = getNumChildComponents(); --i >= 0;)
  {
    if (InterpolationSpaceIPos* const ic = dynamic_cast <InterpolationSpaceIPos*> (getChildComponent (i)))
      if (ic->filterID == filterID)
        return ic;
  }
  
  return nullptr;
}