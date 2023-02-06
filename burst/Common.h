#pragma once

// Common usage
#include "common/Types.h"
#include "common/Meta.h"
#include "common/Concepts.h"
#include "common/Error.h"

// Info
#include "common/Application.h"
#include "common/Engine.h"

// Presentables
#include "common/Presentables/IPresentable.h"
#include "common/Presentables/IRealtimePresentable.h"
#include "common/Presentables/IWindow.h"
#include "common/Presentables/IScalingPresentable.h"
#include "common/Presentables/IFullscreenPresentable.h"

// Custom types
#include "common/Types/IToken.h"
#include "common/Types/AbstractPointer.h"
#include "common/Types/SignalList.h"
#include "common/Types/CappedStack.h"
#include "common/Types/Address.h"
#include "common/Types/Buffer.h"

// Behavior types
#include "common/Types/Behavior/Enum.h"
#include "common/Types/Behavior/EnumAccess.h"
#include "common/Types/Behavior/MemoryComparable.h"

// Types
#include "common/Input/Input.h"
#include "common/Input/Providers/ICharacterInputProvider.h"
#include "common/Input/Providers/IMouseInputProvider.h"
#include "common/Input/Providers/IKeyInputProvider.h"

// Logging
#include "common/Log.h"
#include "common/Logging/ILogger.h"
#include "common/Logging/ConsoleLogger.h"

// Misc
#include "common/Utils/File.h"
#include "common/Utils/Monitor.h"
#include "common/Utils/Mainloop.h"

// Iterators
#include "common/Types/Iterators/RangedIterable.h"
#include "common/Types/Iterators/IndexIterator.h"
#include "common/Types/Iterators/TiedIterator.h"
#include "common/Types/Iterators/Functions.h"
