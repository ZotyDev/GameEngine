# Change Log

## v0.1.270323

Marks the first "version". Additions, changes and fixes should be logged from now on. Also marks the rewrite starting point, everything from now on is part of the rewrite.

But why rewrite? Well, premake was a fucking headache to use, I was missing many functionalities that CMake had, this alone wouldn't require a rewrite, but I was coding some questionable patterns and leaving behind awful pieces of code that I couldn't understand. There was literally a code block that worked purely by luck and the only description that past me wrote was "blah blah holy bible don't touch or this will break"...

Architecture and design goals drastically changed, allowing me some more flexibility, but also requiring a complete rewrite, lucky me for writing somewhat modular code, that will help me with the rewrite :D

### Added
- Abstraction for primitive types
- Platform detection macros
- Endianness detection macros
- Async logging using spdlog
- Precompiled file
- Basic layer system
- Barebones application class
- Custom type for handling errors (UEResult)
- Entry point
- Unit testing using gtest
- Basic filesystem wrapper
- Basic UnnamedClient implementation
- Compiles for webassembly and windows
- Global configurations
- Entry point args collector

### Note
Everything before this change is marked as obsolete and will be squashed.

### Note2
WebAssembly also compiles gtest alongside the unit tests, and this, my fellow friends, is something that I have absolutely no clue why it works or HOW it works, everything that I know is that it works and I don't remember if I did something to make it work or not, so if you are trying to do something similar, good luck c: