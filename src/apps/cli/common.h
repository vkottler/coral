#pragma once

/* toolchain */
#include <iostream>
#include <sstream>

/* internal */
#include "../../cli/CommandLineApp.h"

using namespace Coral;

static constexpr std::size_t depth = 1024;
using Buffer = CharBuffer<depth>;
using Processor = StringCommandProcessor<depth>;

PrintfLogger logger;
