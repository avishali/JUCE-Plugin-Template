# JUCE Plugin Template

A minimal, clean template for creating new JUCE audio plugins using CMake.

## Quick Start

1. **Copy this template** to create your new plugin:
   ```bash
   cp -r plugin-template my-new-plugin
   cd my-new-plugin
   ```

2. **Update plugin configuration** in `CMakeLists.txt`:
   - `PLUGIN_NAME` - Your plugin name
   - `COMPANY_NAME` - Your company name
   - `PLUGIN_CODE` - 4-character plugin code (e.g., "MyPl")
   - `MANUFACTURER_CODE` - 4-character manufacturer code (must have at least one uppercase)

3. **Rename source files** (optional but recommended):
   - `Source/PluginProcessor.h/cpp` → `Source/YourPluginProcessor.h/cpp`
   - `Source/PluginEditor.h/cpp` → `Source/YourPluginEditor.h/cpp`
   - Update class names in the files

4. **Set JUCE path**:
   ```bash
   export JUCE_PATH=/path/to/JUCE
   ```

5. **Build**:
   ```bash
   cmake -S . -B build -DJUCE_PATH=$JUCE_PATH
   cmake --build build
   ```

   Or use CMake presets:
   ```bash
   cmake --preset default
   cmake --build build
   ```

## Plugin Formats

By default, the template builds:
- **AU** (macOS)
- **VST3** (macOS/Windows)
- **Standalone** (macOS/Windows)

To add AAX support, add `AAX` to `PLUGIN_FORMATS` and set `AAX_SDK_PATH`.

## Structure

```
plugin-template/
├── CMakeLists.txt          # Main build configuration
├── CMakePresets.json       # CMake presets for common build configs
├── CMake/
│   └── CPM.cmake          # CMake package manager (optional)
├── Source/
│   ├── PluginProcessor.h  # Audio processor header
│   ├── PluginProcessor.cpp # Audio processor implementation
│   ├── PluginEditor.h     # UI editor header
│   └── PluginEditor.cpp   # UI editor implementation
└── README.md              # This file
```

## Customization

### Adding Parameters

The template uses a minimal processor. To add parameters:
1. Use `juce::AudioProcessorValueTreeState` (APVTS) for parameter management
2. Or use direct getter/setter methods with `std::atomic` for thread-safe access

### Adding UI Components

1. Add your UI components to `Source/` or create a `Source/ui/` subdirectory
2. Update `CMakeLists.txt` to include new source files
3. Implement your UI in `PluginEditor.cpp`

### Adding DSP Code

1. Add DSP processing in `PluginProcessor::processBlock()`
2. Use `juce::dsp` modules for common DSP operations
3. Link additional JUCE modules in `CMakeLists.txt` if needed

## Build Systems

### Ninja (Default)
```bash
cmake -S . -B build -G Ninja -DJUCE_PATH=$JUCE_PATH
cmake --build build
```

### Xcode
```bash
cmake -S . -B build-xcode -G Xcode -DJUCE_PATH=$JUCE_PATH
open build-xcode/PluginTemplate.xcodeproj
```

### Visual Studio (Windows)
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -DJUCE_PATH=$JUCE_PATH
cmake --build build --config Release
```

## Requirements

- CMake 3.22 or higher
- JUCE framework (latest version recommended)
- C++17 compatible compiler
- macOS: Xcode Command Line Tools
- Windows: Visual Studio 2019 or later

## Notes

- The template uses minimal JUCE modules: `juce_audio_utils`, `juce_gui_basics`, `juce_dsp`
- Add more modules as needed in `CMakeLists.txt`
- The template does not include AAX support by default (requires AAX SDK)
- All paths use environment variables or CMake cache variables for portability
