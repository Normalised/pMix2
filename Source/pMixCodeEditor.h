/*
  ==============================================================================

    CodeEditor.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#ifndef CODEEDITOR_H_INCLUDED
#define CODEEDITOR_H_INCLUDED

#include "JuceHeader.h"
#include "pMixAudioEngine.h"
#include "pMixWebBrowser.h"
#include "pMixConsole.h"
#include "pMixGraphEditor.h"
#include "FaustAudioProcessor.h"
#include "FaustCodeTokenizer.h"

class CodeEditor : public Component
                 , public ChangeListener
                 , public Button::Listener
{
public:
  CodeEditor(PMixAudioEngine& audioEngine, GraphEditor& graphEditor);
  
  void paint (Graphics& g) override;
  
  void resized() override;
  
  void changeListenerCallback (ChangeBroadcaster* source);
  void buttonClicked (Button* button);
  
private:
  FaustTokeniser tokeniser;
  CodeDocument codeDocument;
  ScopedPointer<CodeEditorComponent> editor;
  ScopedPointer<WebBrowser> webBrowser;
  ScopedPointer<Console> console;

  PMixAudioEngine& audioEngine;
  GraphEditor& graphEditor;

  StretchableLayoutManager verticalLayout;
  ScopedPointer<StretchableLayoutResizerBar> dividerBar1, dividerBar2;

  TextButton compileButton;
  TextButton svgButton;
  FaustAudioProcessor* selectedFaustAudioProcessor;
  uint32 selectedNodeID;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeEditor);
};



#endif  // CODEEDITOR_H_INCLUDED
