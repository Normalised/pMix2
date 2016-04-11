/*
  ==============================================================================

    pMixGraphEditorActions.cpp
    Author:  Oliver Larkin

  ==============================================================================
*/

#include "pMixGraphEditorActions.h"
#include "pMixPluginWindow.h"

CreateNodeAction::CreateNodeAction (PMixAudioEngine& audioEngine, GraphEditor& graphEditor, const PluginDescription* desc, double x, double y) noexcept
: audioEngine(audioEngine)
, graphEditor(graphEditor)
, x(x)
, y(y)
, desc(*desc)
{
}

bool CreateNodeAction::perform()
{
  nodeID = audioEngine.getDoc().addNode (&desc, x, y);
  
  if (nodeID < 0xFFFFFFFF)
    return true;
  else
    return false;
  
}

bool CreateNodeAction::undo()
{
  PluginWindow::closeCurrentlyOpenWindowsFor (nodeID);
  audioEngine.getDoc().removeNode(nodeID);
  graphEditor.getLassoSelection().deselectAll();

  return true;
}

int CreateNodeAction::getSizeInUnits()
{
  return (int) sizeof (*this); //xxx should be more accurate
}

RemoveNodeAction::RemoveNodeAction (PMixAudioEngine& audioEngine, GraphEditor& graphEditor, uint32 nodeID) noexcept
: audioEngine(audioEngine)
, graphEditor(graphEditor)
, nodeID(nodeID)
{
  nodeXML = audioEngine.getDoc().createNodeXml(audioEngine.getGraph().getNodeForId(nodeID));
}

bool RemoveNodeAction::perform()
{
  PluginWindow::closeCurrentlyOpenWindowsFor (nodeID);
  
  audioEngine.getDoc().removeNode (nodeID);
  //graphEditor.getLassoSelection().deselectAll();

  if (nodeID < 0xFFFFFFFF)
    return true;
  else
    return false;
  
}

bool RemoveNodeAction::undo()
{
  audioEngine.getDoc().createNodeFromXml(*nodeXML);  
  return true;
}

int RemoveNodeAction::getSizeInUnits()
{
  return (int) sizeof (*this); //xxx should be more accurate
}

MoveNodeAction::MoveNodeAction (PMixAudioEngine& audioEngine, GraphEditor& graphEditor, uint32 nodeID, Point<double> startPos, Point<double> endPos) noexcept
: audioEngine(audioEngine)
, graphEditor(graphEditor)
, nodeID(nodeID)
, startPos(startPos)
, endPos(endPos)
{
}

bool MoveNodeAction::perform()
{
  audioEngine.getDoc().setNodePosition (nodeID, endPos.x, endPos.y);
  graphEditor.updateComponents();
  return true;
}

bool MoveNodeAction::undo()
{
  audioEngine.getDoc().setNodePosition (nodeID, startPos.x, startPos.y);
  graphEditor.updateComponents();
  return true;
}

int MoveNodeAction::getSizeInUnits()
{
  return (int) sizeof (*this); //xxx should be more accurate
}

CreateConnectionAction::CreateConnectionAction (PMixAudioEngine& audioEngine, uint32 srcNodeUID, int srcChannel, uint32 dstNodeUID, int dstChannel) noexcept
: audioEngine(audioEngine)
, srcNodeUID(srcNodeUID)
, srcChannel(srcChannel)
, dstNodeUID(dstNodeUID)
, dstChannel(dstChannel)
{
}

bool CreateConnectionAction::perform()
{
  return audioEngine.getDoc().addConnection (srcNodeUID, srcChannel, dstNodeUID, dstChannel);
}

bool CreateConnectionAction::undo()
{
  audioEngine.getDoc().removeConnection (srcNodeUID, srcChannel, dstNodeUID, dstChannel);
  
  return true;
}

int CreateConnectionAction::getSizeInUnits()
{
  return (int) sizeof (*this); //xxx should be more accurate
}