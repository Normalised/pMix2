#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class PMixPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
  PMixPluginAudioProcessorEditor (PMixPluginAudioProcessor&);
  ~PMixPluginAudioProcessorEditor();

  void paint (Graphics&) override;
  void resized() override;

private:
  PMixPluginAudioProcessor& processor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PMixPluginAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
