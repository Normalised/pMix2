#ifndef __PARAMVIEW_JUCEHEADER__
#define __PARAMVIEW_JUCEHEADER__

#include "JuceHeader.h"
#include "pMixAudioEngine.h"

class ParamSlider  : public Slider
{
public:
  ParamSlider (AudioProcessor& p, const int index_);
  void setValueEx(float value);
  void valueChanged();
  String getTextFromValue (double /*value*/);
  
private:
  AudioProcessor& owner;
  const int index;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamSlider)
};

#pragma mark ProcessorParameterPropertyComp
class ProcessorParameterPropertyComp :  public PropertyComponent
                                     ,  private AudioProcessorListener
                                     ,  private Timer
{
public:
  ProcessorParameterPropertyComp (const String& name, AudioProcessor& p, const int index_);
  ~ProcessorParameterPropertyComp();
  void refresh();
  void audioProcessorChanged (AudioProcessor*);
  void audioProcessorParameterChanged (AudioProcessor*, int parameterIndex, float);
  void timerCallback() override;
  
private:  
  AudioProcessor& owner;
  const int index;
  bool volatile paramHasChanged;
  ParamSlider slider;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProcessorParameterPropertyComp)
};

class ParamView : public Component
                , public ChangeListener
{
public:  
  ParamView(PMixAudioEngine& audioEngine);
  
  ~ParamView();
  void paint (Graphics& g) override;
  void resized() override;
  void changeListenerCallback (ChangeBroadcaster* source);
  void addEditor(AudioProcessor* p);
  
private:
  PMixAudioEngine& audioEngine;
  Array<uint32> sectionNodes;
  PropertyPanel panel;
};

#endif //__PARAMVIEW_JUCEHEADER__