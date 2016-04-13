/*
  ==============================================================================

    pMixDocument.h
    Author:  Oliver Larkin
 
  ==============================================================================
*/

#ifndef PMIXDOCUMENT_H_INCLUDED
#define PMIXDOCUMENT_H_INCLUDED

#include "JuceHeader.h"
#include "pMixDefaultColours.h"
#include "pMixConstants.h"

class PMixAudioEngine;

class PMixDocument : public FileBasedDocument
                   , public Timer

{
public:
  PMixDocument (PMixAudioEngine& audioEngine);
  ~PMixDocument();
  
  void timerCallback();

  void addPreset(const uint32 nodeId, double x, double y);
  void setPresetPosition(const uint32 nodeId, const int presetIdx, double x, double y);
  void getPresetPosition(const uint32 nodeId, const int presetIdx, double& x, double& y) const;
  double getPresetWeight(const uint32 nodeId, const int presetIdx);
  void removePreset(const uint32 nodeId, const int presetIdx);
  void setPresetName(const uint32 nodeId, const int presetIdx, String newName);

  void setNodeIPos(const uint32 nodeId, double x, double y);
  void getNodeIPos(const uint32 nodeId, double& x, double& y) const;
  void updateCoefficients(const AudioProcessorGraph::Node::Ptr node);

  void setNodeColour(const uint32 nodeId, const Colour colour);
  Colour getNodeColour(const uint32 nodeId) const;
  
  int getNumNodes() const noexcept;
  const AudioProcessorGraph::Node::Ptr getNode (const int index) const noexcept;
  const AudioProcessorGraph::Node::Ptr getNodeForId (const uint32 uid) const noexcept;
  
  uint32 addNode (const PluginDescription* desc, double x, double y);
  void removeNode (const uint32 nodeId);
  void disconnectNode (const uint32 nodeId);
  
  bool getParameterIsInterpolated(const uint32 nodeId, const int paramIdx);
  void setParameterToInterpolate(const uint32 nodeId, const int paramIdx, bool interpolate);

  void removeIllegalConnections();
  void setNodePosition (const uint32 nodeId, double x, double y);
  void getNodePosition (const uint32 nodeId, double& x, double& y) const;
  int getNumConnections() const noexcept;
  const AudioProcessorGraph::Connection* getConnection (const int index) const noexcept;
  const AudioProcessorGraph::Connection* getConnectionBetween (uint32 sourceNodeId, int sourceNodeChannel, uint32 destNodeId, int destNodeChannel) const noexcept;
  bool canConnect (uint32 sourceNodeId, int sourceNodeChannel, uint32 destNodeId, int destNodeChannel) const noexcept;
  bool addConnection (uint32 sourceNodeId, int sourceNodeChannel, uint32 destNodeId, int destNodeChannel);
  void removeConnection (const int index);
  void removeConnection (uint32 sourceNodeId, int sourceNodeChannel, uint32 destNodeId, int destNodeChannel);
  void clear();
  
  XmlElement* createXml() const;
  void createNodeFromXml (XmlElement& xml, const String& newSourceCode = String::empty);
  void restoreFromXml (const XmlElement& xml);
  static XmlElement* createNodeXml (AudioProcessorGraph::Node* const node) noexcept;

  String getDocumentTitle();
  Result loadDocument (const File& file);
  Result saveDocument (const File& file);

  File getLastDocumentOpened();
  void setLastDocumentOpened (const File& file);
  // The special channel index used to refer to a node's midi channel
  static const int midiChannelNumber;
  
  void setSnappingGrid (const int numPixels, const bool active, const bool shown);
  
  int getSnappingGridSize() const noexcept                                { return snapGridPixels; }
  bool isSnapActive (const bool disableIfCtrlKeyDown) const noexcept;
  bool isSnapShown() const noexcept                                       { return snapShown; }
  
  int snapPosition (int pos) const noexcept;
  void setComponentOverlayOpacity (const float alpha);
  float getComponentOverlayOpacity() const noexcept                       { return componentOverlayOpacity; }
  
  void beginTransaction();
  void beginTransaction (const String& name);
  bool perform (UndoableAction* const action, const String& actionName);

  UndoManager& getUndoManager() noexcept                                  { return undoManager; }

  void initialize();
  
  String getLibraryPath();
  
private:
  UndoManager undoManager;
  PMixAudioEngine& audioEngine;
  uint32 lastUID;
  uint32 getNextUID() noexcept;

  int snapGridPixels;
  bool snapActive, snapShown;
  float componentOverlayOpacity;
  PMixDefaultColours defaultColours;
  const File drawPath;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PMixDocument)
};


#endif   // PMIXDOCUMENT_H_INCLUDED
