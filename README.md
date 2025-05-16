# csoundwwise

`csoundwwise_effect` folder contains effect plug-in wwise.

`csoundwwise_source` folder contains source plug-in for wwise.

### Source Plug-in vs. Effect Plug-in in Wwise

| Plug-in Type       | Description                  | Primary Use                        | Input/Output                        |
| ------------------ | ---------------------------- | ---------------------------------- | ----------------------------------- |
| **Source Plug-in** | Generates audio from scratch | Synths, samplers, procedural audio | No audio input → Audio output       |
| **Effect Plug-in** | Processes incoming audio     | Filters, reverbs, modulation FX    | Audio input → Modified audio output |

Todo:
- (In-progress) Understand the Wwise Plug-in Architecture
    - Authoring plug-in (UI + Metadata in Wwise Authoring app)
    - Sound engine plug-in (the C++ DSP code that runs in the Wwise engine)
- Define the Integration Point with Csound
    - embed and run `.csd` file using the Csound C++ API
- Work on source plug-in first

Finished:
- (done) csoundwwise plug-in setup
    - able to build solution in visual studio
    - plug-in visible in wwise
- (done) Read wwise documentation and follow tutorials