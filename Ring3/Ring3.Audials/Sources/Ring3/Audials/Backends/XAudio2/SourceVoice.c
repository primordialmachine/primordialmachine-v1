#include "Ring3/Audials/Backends/XAudio2/SourceVoice.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

#include "Ring3/Audials/Backends/XAudio2/XAudio2.h"
#include "Ring3/Audials/Backends/XAudio2/Diagnostics.h"

/*callback*/ static inline void
_SourceVoice_onBufferEnd
  (
    THIS_
    void* p
  )
{
  fprintf(stdout, "<on buffer end>\n");
  _Buffer* buffer = (_Buffer*)p;
  _Buffer_unref(buffer);
}

/*callback*/ static inline void
_SourceVoice_onBufferStart
  (
    THIS_
    void* p
  )
{
  fprintf(stdout, "<on buffer start>\n");
}

/*callback*/ static inline void
_SourceVoice_onLoopEnd
  (
    THIS_
    void* p
  )
{
  //fprintf(stdout, "<on loop end>\n");
}

/*callback*/ static inline void
_SourceVoice_onStreamEnd
  (
    THIS
  )
{
  //fprintf(stdout, "<on stream end>\n");
}

/*callback*/ static inline void
_SourceVoice_onVoiceProcessingPassStart
  (
    THIS_
    UINT32 bytesRequired
  )
{
  //fprintf(stdout, "<on voice processing pass start\n");
}

/*callback*/ static inline void
_SourceVoice_onVoiceProcessingPassEnd
  (
    THIS
  )
{
  //fprintf(stdout, "<on voice processing pass end>\n");
}

/*callback*/ static inline void
_SourceVoice_onVoiceError
  (
    THIS_
    void* p,
    HRESULT e
  )
{
  //fprintf(stdout, "<on voice error>\n");
}


int
_SourceVoice_construct
  (
    _SourceVoice* sourceVoice,
    IXAudio2* xaudio2,
    _PcmDescriptor const* pcmDescriptor
  )
{
  sourceVoice->pcmDescriptor = *pcmDescriptor;

  // callbacks.
  sourceVoice->callbacks.lpVtbl = &sourceVoice->callbacksVtbl;
  sourceVoice->callbacks.lpVtbl->OnBufferStart = &_SourceVoice_onBufferStart;
  sourceVoice->callbacks.lpVtbl->OnBufferEnd = &_SourceVoice_onBufferEnd;
  sourceVoice->callbacks.lpVtbl->OnLoopEnd = &_SourceVoice_onLoopEnd;
  sourceVoice->callbacks.lpVtbl->OnStreamEnd = &_SourceVoice_onStreamEnd;
  sourceVoice->callbacks.lpVtbl->OnVoiceProcessingPassStart = _SourceVoice_onVoiceProcessingPassStart;
  sourceVoice->callbacks.lpVtbl->OnVoiceError = &_SourceVoice_onVoiceError;
  sourceVoice->callbacks.lpVtbl->OnVoiceProcessingPassEnd = &_SourceVoice_onVoiceProcessingPassEnd;

  // wave format.
  WAVEFORMATEX wfmt = { 0 };
  wfmt.cbSize = 0;
  wfmt.wFormatTag = WAVE_FORMAT_PCM;
  wfmt.nChannels = pcmDescriptor->numberOfChannels;
  wfmt.nSamplesPerSec = pcmDescriptor->samplesPerSecondPerChannel;
  wfmt.wBitsPerSample = pcmDescriptor->bitsPerSample;
  wfmt.nBlockAlign = (wfmt.nChannels * wfmt.wBitsPerSample) / 8;
  wfmt.nAvgBytesPerSec = wfmt.nSamplesPerSec * wfmt.nBlockAlign;

  HRESULT hr = xaudio2->lpVtbl->CreateSourceVoice(xaudio2,
                                                  &sourceVoice->sourceVoice,
                                                  &wfmt,
                                                  0,
                                                  1.0f,
                                                  &sourceVoice->callbacks,
                                                  NULL,
                                                  NULL);
  if (FAILED(hr)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(hr, "unable to create XAudio2 source voice\n");
    return 1;
  }

  sourceVoice->rc = 1;

  return 0;  
}

int
_SourceVoice_create
  (
    _SourceVoice** sourceVoice,
    IXAudio2* xaudio2,
    _PcmDescriptor const* pcmDescriptor
  )
{
  _SourceVoice* sourceVoice1 = malloc(sizeof(_SourceVoice));
  if (!sourceVoice1) {
    fprintf(stderr, "%s:%d: unable to allocate object of type `%s` of size %zu.\n",
                    __FILE__, __LINE__, "_SourceVoice", sizeof(_SourceVoice));
    return 1;
  }
  memset(sourceVoice1, 0, sizeof(_SourceVoice));
  if (_SourceVoice_construct(sourceVoice1, xaudio2, pcmDescriptor)) {
    free(sourceVoice1);
    sourceVoice1 = NULL;
    return 1;
  }
  *sourceVoice = sourceVoice1;
  return 0;
}

void
_SourceVoice_destruct
  (
    _SourceVoice* sourceVoice
  )
{
  assert(NULL != sourceVoice);
  assert(0 == sourceVoice->rc);
  sourceVoice->sourceVoice->lpVtbl->DestroyVoice(sourceVoice->sourceVoice);
  sourceVoice->sourceVoice = NULL;
}

void
_SourceVoice_destroy
  (
    _SourceVoice* sourceVoice
  )
{
  assert(NULL != sourceVoice);
  assert(0 == sourceVoice->rc);
  _SourceVoice_destruct(sourceVoice);
  free(sourceVoice);
}

void
_SourceVoice_ref
  (
    _SourceVoice* sourceVoice
  )
{
  sourceVoice->rc++;
}

void
_SourceVoice_unref
  (
    _SourceVoice* sourceVoice
  )
{
  if (0 == --sourceVoice->rc) {
    _SourceVoice_destroy(sourceVoice);
  }
}

int
_SourceVoid_isPlaying
  (
    bool* isPlaying,
    _SourceVoice* sourceVoice
  )
{
  XAUDIO2_VOICE_STATE state;
  sourceVoice->sourceVoice->lpVtbl->GetState(sourceVoice->sourceVoice, &state, 0);
  *isPlaying = state.BuffersQueued > 0;
  return 0;
}

#endif // Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2
