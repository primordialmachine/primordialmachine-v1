#if !defined(MACHINE_RUNTIME_H_INCLUDED)
#define MACHINE_RUNTIME_H_INCLUDED

#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Arguments.h"
#include "Runtime/ArrayUtilities.h"
#include "Runtime/Assertions.h"
#include "Runtime/ByteBuffer.h"
#include "Runtime/ByteBufferReader.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/Io.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/LogModule.h"
#include "Runtime/Machine.h"
#include "Runtime/Object/ClassType.h"
#include "Runtime/Object/InterfaceType.h"
#include "Runtime/Object/Object.h"
#include "Runtime/String.h"
#include "Runtime/StringBuffer.h"
#include "Runtime/Time.h"
#include "Runtime/Value.h"
#undef MACHINE_RUNTIME_PRIVATE

#endif // MACHINE_RUNTIME_H_INCLUDED
