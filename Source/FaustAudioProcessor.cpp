/*
  ==============================================================================

    FaustAudioProcessor.cpp
    Author:  Oliver Larkin

  ==============================================================================
*/

#include "FaustAudioProcessor.h"
#include "FaustAudioProcessorParameter.h"

FaustAudioProcessor::FaustAudioProcessor()
: fDSPfactory(nullptr)
, fDSP(nullptr)
{
}

FaustAudioProcessor::~FaustAudioProcessor()
{
  freeDSP();
  
  fDSPfactory->removeInstance(this);
}

void FaustAudioProcessor::fillInPluginDescription (PluginDescription& description) const
{
  description.name = "Faust Effect";
  description.descriptiveName = "JIT compiled Faust Effect";
  description.pluginFormatName = "Faust JIT compiled";
  description.category = "na";
  description.manufacturerName = "bleh";
  description.version = "0.0.1";
  description.fileOrIdentifier = "";
  description.lastFileModTime = Time(0);
  description.isInstrument = false;
  description.hasSharedContainer = false;
  description.numInputChannels = fDSP->getNumInputs();
  description.numOutputChannels = fDSP->getNumOutputs();
}

//static
void FaustAudioProcessor::fillInitialInPluginDescription (PluginDescription& description)
{
  description.name = "Faust Effect";
  description.descriptiveName = "JIT compiled Faust Effect";
  description.pluginFormatName = "Faust JIT compiled";
  description.category = "na";
  description.manufacturerName = "bleh";
  description.version = "0.0.1";
  description.fileOrIdentifier = "";
  description.lastFileModTime = Time(0);
  description.isInstrument = false;
  description.hasSharedContainer = false;
  description.numInputChannels = 1;
  description.numOutputChannels = 1;
}

void FaustAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  if (!fDSP)
    createDSP();
  
  fDSP->init(sampleRate);
  setPlayConfigDetails(fDSP->getNumInputs(),  fDSP->getNumOutputs(), sampleRate, samplesPerBlock);
}

void FaustAudioProcessor::releaseResources()
{
}

void FaustAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
  const ScopedLock lock(fDSPfactory->fDSPMutex);
  
  if (fDSP != nullptr)
    fDSP->compute(buffer.getNumSamples(), (FAUSTFLOAT**)buffer.getArrayOfReadPointers(), (FAUSTFLOAT**)buffer.getArrayOfWritePointers());
}

void FaustAudioProcessor::reset()
{
}

bool FaustAudioProcessor::hasEditor() const
{
  return false;
}

AudioProcessorEditor* FaustAudioProcessor::createEditor()
{
  return nullptr;
}

const String FaustAudioProcessor::getName() const
{
  if(fJSONInterface["name"].toString().length())
  {
    return fJSONInterface["name"].toString();
  }
  else
    return "Faust Effect";
}

const String FaustAudioProcessor::getInputChannelName (int channelIndex) const
{
  return "unknown";
}

const String FaustAudioProcessor::getOutputChannelName (int channelIndex) const
{
  return "unknown";
}

bool FaustAudioProcessor::isInputChannelStereoPair (int index) const
{
  return false;
}

bool FaustAudioProcessor::isOutputChannelStereoPair (int index) const
{
  return false;
}


bool FaustAudioProcessor::acceptsMidi() const
{
  return false;
}

bool FaustAudioProcessor::producesMidi() const
{
  return false;
}

bool FaustAudioProcessor::silenceInProducesSilenceOut() const
{
  return true;
}

double FaustAudioProcessor::getTailLengthSeconds() const
{
  return 0.;
}

int FaustAudioProcessor::getNumPrograms()
{
  return 1;
}

int FaustAudioProcessor::getCurrentProgram()
{
  return 0;
}

void FaustAudioProcessor::setCurrentProgram (int index)
{
}

const String FaustAudioProcessor::getProgramName (int index)
{
  return "Default";
}

void FaustAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void FaustAudioProcessor::getStateInformation (MemoryBlock& destData)
{
  XmlElement xml ("FAUSTGEN");
  fDSPfactory->getStateInformation(xml);
  copyXmlToBinary (xml, destData);
}

void FaustAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
  
  if (xmlState != nullptr)
  {
    if (xmlState->hasTagName ("FAUSTGEN"))
    {
      fDSPfactory->setStateInformation(*xmlState);
    }
  }
  
  if (!fDSP)
    createDSP();
}

void FaustAudioProcessor::createDSP()
{
  const ScopedLock lock(fDSPfactory->fDSPMutex);

  fDSP = fDSPfactory->createDSPAux(this);
  jassert(fDSP);
  
  // Initialize User Interface
  fDSP->buildUserInterface(this);

  Result res = JSON::parse(fDSPfactory->getJSON(), fJSONInterface);
  
  // Initialize at the system's sampling rate
  if (getSampleRate() == 0)
    fDSP->init(44100.);
  else
    fDSP->init(getSampleRate());
  
  updateHostDisplay();
}

void FaustAudioProcessor::freeDSP()
{
  deleteDSPInstance(fDSP);
  fDSP = 0;
}

bool FaustAudioProcessor::allocateFactory(const string& effect_name, const String& path)
{
  bool res = false;
  
  if (FaustgenFactory::gFactoryMap.find(effect_name) != FaustgenFactory::gFactoryMap.end())
  {
    fDSPfactory = FaustgenFactory::gFactoryMap[effect_name];
  }
  else
  {
    fDSPfactory = new FaustgenFactory(effect_name, path);
    FaustgenFactory::gFactoryMap[effect_name] = fDSPfactory;
    res = true;
  }
  
  fDSPfactory->addInstance(this);
  return res;
}

void FaustAudioProcessor::updateSourcecode()
{
  // Create a new DSP instance
  createDSP();

  // state is modified...
  //set_dirty();
}

String FaustAudioProcessor::getSourcecode()
{
  return fDSPfactory->getSourcecode();
}

void FaustAudioProcessor::highlightON(const String& error)
{
  //TODO:highlightON
}

void FaustAudioProcessor::highlightOFF()
{
  //TODO:highlightOFF
}

void FaustAudioProcessor::openTabBox(const char* label)
{
  //TODO:
}

void FaustAudioProcessor::openHorizontalBox(const char* label)
{
  //TODO:
}

void FaustAudioProcessor::openVerticalBox(const char* label)
{
  //TODO:
}

void FaustAudioProcessor::closeBox()
{
  //TODO:
}

void FaustAudioProcessor::addButton(const char* label, FAUSTFLOAT* zone)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeBool, 0, 0, 1, 1, "", zone));
}

void FaustAudioProcessor::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeBool, 0, 0, 1, 1, "", zone));
}

void FaustAudioProcessor::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeFloat, init, min, max, step, "", zone));
}

void FaustAudioProcessor::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeFloat, init, min, max, step, "", zone));
}

void FaustAudioProcessor::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeFloat, init, min, max, step, "", zone));
}

void FaustAudioProcessor::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
  //TODO:
}

void FaustAudioProcessor::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
  //TODO:
}

void FaustAudioProcessor::initialize(const String &path)
{
  // Empty (= no name) FaustAudioProcessor will be internally separated as groups with different names
  if (!fDSPfactory)
  {
    String effect_name;
    effect_name << "FaustgenFactory-" << FaustgenFactory::gFaustCounter;
    allocateFactory(effect_name.toStdString(), path);
  }
  
  fDSPfactory->addLibraryPath(path);
}