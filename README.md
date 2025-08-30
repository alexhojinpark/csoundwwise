# CsoundWwise

A Wwise plugin that integrates Csound as a source plugin, allowing you to run Csound (.csd) files directly within Wwise for real-time audio synthesis and processing.

## Overview

CsoundWwise bridges the gap between Csound (a powerful computer music programming language) and Wwise (Audiokinetic's audio middleware). This plugin enables game developers and audio designers to leverage Csound's extensive synthesis capabilities directly within Wwise projects.

## Project Structure

- **`csdwwise2/`** - Active Wwise plugin project (Visual Studio solutions)
  - **`SoundEnginePlugin/`** - Runtime plugin that executes Csound files
  - **`WwisePlugin/`** - Authoring plugin for Wwise integration
  - **`FactoryAssets/`** - Plugin factory configuration
- **`csd/`** - Example Csound files for testing
- **`tools/`** - Build and utility scripts

## Features

- **Source Plugin Integration**: Runs Csound files as Wwise source plugins
- **Real-time Synthesis**: Generates audio procedurally using Csound's powerful synthesis engine
- **Cross-platform Support**: Windows builds for Visual Studio 2019 (vc160) and 2022 (vc170)
- **Flexible Configuration**: Support for both shared and static library builds

## Requirements

- **Wwise SDK** (2024.1.5 or compatible)
- **Visual Studio** 2019 or 2022
- **Csound 6** (x64) - must be installed to `C:\Program Files\Csound6_x64\`
- **Windows 10/11** (x64)

## Building

### Prerequisites

1. Install Wwise SDK and ensure it's properly configured
2. Install Csound 6 x64 to the default location
3. Open the appropriate solution file for your Visual Studio version:
   - **VS 2019**: `csdwwise2_Windows_vc160_shared.sln` or `csdwwise2_Windows_vc160_static.sln`
   - **VS 2022**: `csdwwise2_Windows_vc170_shared.sln` or `csdwwise2_Windows_vc170_static.sln`

### Build Steps

1. Open the solution file in Visual Studio
2. Set `csdwwise2_Windows_vc1XX_shared` as the startup project
3. Build the solution (Release x64 configuration recommended)
4. Copy the built plugin to your Wwise plugins directory

## Usage

### Basic Setup

1. **Select a Csound file** using the provided PowerShell script:
   ```powershell
   ./csdwwise trumpet.csd"
   ```

2. **Launch Wwise** (optional):
   ```powershell
   ./csdwwise trumpet.csd" -LaunchWwise -WwiseExe "C:\Program Files\Audiokinetic\Wwise 2024.1.5\Authoring\x64\Release\bin\Wwise.exe"
   ```

3. **In Wwise**: The plugin will appear as a source plugin option, allowing you to create audio objects using your selected Csound file.

### Example Csound Files

The `csd/` directory contains example files:
- **`trumpet.csd`** - Brass synthesis example with envelope control
- **`csound_test.csd`** - Basic test file for verification

## Architecture

### Plugin Types

| Component | Purpose | Location |
|-----------|---------|----------|
| **Authoring Plugin** | Wwise UI integration and metadata | `WwisePlugin/` |
| **Sound Engine Plugin** | Runtime Csound execution | `SoundEnginePlugin/` |
| **CsoundWrapper** | Csound API abstraction layer | `SoundEnginePlugin/CsoundWrapper.*` |

### Key Components

- **`csdwwise2Source`**: Main source plugin class that implements Wwise's `IAkSourcePlugin` interface
- **`CsoundWrapper`**: C++ wrapper around Csound's C++ API for easier integration
- **`csdwwise2SourceParams`**: Parameter management for the plugin

## Development Status

- ✅ **Plugin Framework**: Complete Wwise plugin structure
- ✅ **Build System**: Visual Studio solutions for multiple VS versions
- ✅ **Csound Integration**: Basic Csound file loading and execution
- ✅ **Wwise Integration**: Plugin appears in Wwise authoring tool
- 🔄 **Parameter System**: Basic parameter framework in place
- 📋 **Documentation**: Plugin configuration and usage examples


## License

This project includes portions of the AUDIOKINETIC Wwise Technology released under the Apache License, Version 2.0. See individual source files for specific licensing information.

## Related Links

- [Wwise Plugin Development Documentation](https://www.audiokinetic.com/library/edge/?source=SDK&id=plugin__dll.html)
- [Csound Documentation](https://csound.com/docs/)
- [Wwise SDK](https://www.audiokinetic.com/download/)