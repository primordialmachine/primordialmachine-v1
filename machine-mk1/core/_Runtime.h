#if !defined(MACHINE_RUNTIME_H_INCLUDED)
#define MACHINE_RUNTIME_H_INCLUDED

#define MACHINE_RUNTIME_PRIVATE (1)
#include "Ring2/_Include.h"
#include "Runtime/Arguments.h"
#include "Runtime/ArrayUtilities.h"
#include "Runtime/ByteBuffer.h"
#include "Runtime/ByteBufferReader.h"
#include "Runtime/Io.h"
#include "Runtime/Machine.h"
#include "Runtime/StaticVariablesModule.h"
#include "Runtime/StringBuffer.h"
#include "Runtime/Time.h"
#include "Runtime/WeakReference.h"
#undef MACHINE_RUNTIME_PRIVATE

#endif // MACHINE_RUNTIME_H_INCLUDED
