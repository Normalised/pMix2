/*
  ==============================================================================

    CommandIDs.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#ifndef COMMANDIDS_H_INCLUDED
#define COMMANDIDS_H_INCLUDED


namespace CommandIDs
{
  static const int recentFilesMenu        = 0x200000;
  //                                    ... 0x200064 reserved
  static const int clear                  = 0x2FFFFF;
  static const int showParameters         = 0x300000;
  static const int open                   = 0x300001;
  static const int save                   = 0x300002;
  static const int saveAs                 = 0x300003;
  static const int showPrefs              = 0x300004;
  static const int aboutBox               = 0x300005;
  static const int cut                    = StandardApplicationCommandIDs::cut;
  static const int copy                   = StandardApplicationCommandIDs::copy;
  static const int paste                  = StandardApplicationCommandIDs::paste;
  static const int del                    = StandardApplicationCommandIDs::del;
  static const int quit                   = StandardApplicationCommandIDs::quit;
  static const int undo                   = StandardApplicationCommandIDs::undo;
  static const int redo                   = StandardApplicationCommandIDs::redo;
  static const int selectAll              = StandardApplicationCommandIDs::selectAll;
  static const int deselectAll            = StandardApplicationCommandIDs::deselectAll;
  static const int zoomIn                 = 0x30000A;
  static const int zoomOut                = 0x30000B;
  static const int zoomNormal             = 0x30000C;
  
  static const int showISpace             = 0x30000D;
  static const int showGraphEditor        = 0x30000E;
  static const int showCodeEditor         = 0x30000F;

  static const int newAudioInput          = 0x300010;
  static const int newAudioOutput         = 0x300011;
  static const int newMIDIInput           = 0x300012;
  static const int newMIDIOutput          = 0x300013;
  static const int newFaustEffect         = 0x300014;
  
  static const int floatGraphEditor       = 0x300015;
  static const int floatISpace            = 0x300016;
  static const int floatCodeEditor        = 0x300017;
  static const int floatParameters        = 0x300018;
  
}


#endif  // COMMANDIDS_H_INCLUDED
