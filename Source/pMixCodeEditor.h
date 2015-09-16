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

namespace CodeEditorMenuIDs
{
  static const int fileMenu      = 0x000000;
  static const int editMenu      = 0x000001;
  static const int viewMenu      = 0x000002;
  static const int helpMenu      = 0x000003;
};

class CodeEditor : public Component
                 , public MenuBarModel
                 , public ChangeListener
{
public:
  CodeEditor(PMixAudioEngine& audioEngine, GraphEditor& graphEditor);
  ~CodeEditor();
  void paint (Graphics& g) override;
  
  void resized() override;
  
  void changeListenerCallback (ChangeBroadcaster* source);
  void buttonClicked (Button* button);
  
  StringArray getMenuBarNames() override;
  PopupMenu getMenuForIndex (int menuIndex, const String& menuName) override;
  void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
  
  void clear();
  
private:
  FaustTokeniser tokeniser;
  CodeDocument codeDocument;
  
  ScopedPointer<MenuBarComponent> menuBar;
  ScopedPointer<CodeEditorComponent> editor;
  ScopedPointer<WebBrowser> webBrowser;
  ScopedPointer<Console> console;

  PMixAudioEngine& audioEngine;
  GraphEditor& graphEditor;

  StretchableLayoutManager verticalLayout;
  ScopedPointer<StretchableLayoutResizerBar> dividerBar1, dividerBar2;
  FaustAudioPluginInstance* selectedFaustAudioPluginInstance;
  uint32 selectedNodeID;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeEditor);
};



#endif  // CODEEDITOR_H_INCLUDED
