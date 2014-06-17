#ifndef __PTVHEADER__
#define __PTVHEADER__

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterGraph.h"

class  ParamTreeViewRootItem  : public TreeViewItem
{
public:
  ParamTreeViewRootItem ();
  ~ParamTreeViewRootItem();
  int getItemWidth() const;
  int getItemHeight() const;
  String getUniqueName() const;
  bool mightContainSubItems();
  void paintItem (Graphics& g, int width, int height);
  void itemOpennessChanged (bool isNowOpen);
};

class  ParamTreeViewParamItem  : public TreeViewItem
{
public:
  ParamTreeViewParamItem (String paramName);
  ~ParamTreeViewParamItem();
  int getItemWidth() const;
  int getItemHeight() const;
  String getUniqueName() const;
  bool mightContainSubItems();
  void paintItem (Graphics& g, int width, int height);
  void itemOpennessChanged (bool isNowOpen);
  
private:
  String mName;
};

class  ParamTreeViewPluginItem  : public TreeViewItem
{
public:
  ParamTreeViewPluginItem (FilterGraph& graph_, const uint32 filterID_);
  ~ParamTreeViewPluginItem();
  int getItemWidth() const;
  int getItemHeight() const;
  String getUniqueName() const;
  bool mightContainSubItems();
  void paintItem (Graphics& g, int width, int height);
  void itemOpennessChanged (bool isNowOpen);

private:
  FilterGraph& graph;
  const uint32 filterID;
};

class  ParamTreeView  : public Component,
  public ChangeListener
/*, public DragAndDropContainer */
/*, public ButtonListener*/
{
public:
  ParamTreeView(FilterGraph& graph_);
  ~ParamTreeView();
  
  void paint (Graphics& g);
  void resized();
  void showCustomTreeView();
  void changeListenerCallback (ChangeBroadcaster*);
  void addPlugin(const uint32 filterID_);
  //void buttonClicked (Button*)

  juce_UseDebuggingNewOperator

private:
  FilterGraph& graph;
  ScopedPointer <TreeViewItem> rootItem;
  ScopedPointer <TreeView> treeView;

};


#endif
