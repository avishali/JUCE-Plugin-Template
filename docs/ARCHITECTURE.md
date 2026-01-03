# Architecture Overview
### JUCE Plugin Template — Control, Focus, and Hardware Flow

This document provides a **single-source architectural overview** of the JUCE Plugin Template.
It explains *how data flows* and *why responsibilities are separated the way they are*.

If you understand this page, you understand the entire template.

---

## 1. Core design principle

> **One source of truth. Explicit routing. Normalized hardware.**

Everything in this template is built around three ideas:

1. **Parameters own truth**
2. **All control flows are explicit**
3. **Hardware operates in normalized space (0..1)**

No layer is allowed to “cheat”.

---

## 2. The one diagram (read this first)

```
                    ┌────────────────────┐
                    │        UI           │
                    │  (MainView, Sliders)│
                    └─────────┬──────────┘
                              │ intent (native)
                              ▼
                    ┌────────────────────┐
                    │   BindingRegistry   │
                    │  (normalized 0..1) │
                    └───────┬─────┬──────┘
                            │     │
          normalized intent  │     │ normalized mirror
                            │     ▼
                            │  ┌────────────────────┐
                            │  │ Hardware OUTPUT     │
                            │  │ (LEDs / Focus / UI) │
                            │  └────────────────────┘
                            │
                            ▼
                    ┌────────────────────┐
                    │     Parameters     │
                    │  (DSP + persistence)│
                    └─────────┬──────────┘
                              │ native values
                              ▼
                    ┌────────────────────┐
                    │        DSP          │
                    │  (Audio Processing)│
                    └────────────────────┘


Hardware INPUT (encoders, faders)
          │
          ▼
┌────────────────────┐
│ PluginHardwareAdapter│
│  (normalized input) │
└─────────┬──────────┘
          │
          ▼
   BindingRegistry
```

### How to read this diagram

- **Vertical flow** = ownership and authority
- **Left side** = intent (UI / hardware input)
- **Right side** = feedback (hardware output)
- **Center** = routing and normalization

---

## 3. Layer responsibilities

### Parameters (DSP authority)
- Own all parameter values
- Clamp and validate
- Persist state (including UI state)
- Never depend on UI or hardware

> If state exists, it belongs here.

---

### BindingRegistry (routing spine)
- Maps ControlId → parameter behavior
- Converts normalized ↔ native values
- Single place where ranges are defined

> If routing logic exists, it belongs here.

---

### UI (MainView)
- Expresses user intent only
- Shows state (visualization)
- Handles focus and layout
- Never owns DSP state

> UI asks for changes — it never decides truth.

---

### Hardware Input
- Receives encoder / fader / button events
- Always normalized (0..1)
- Never touches DSP directly

> Hardware sends intent, not commands.

---

### Hardware Output
- Mirrors current state
- Shows focus and values
- Never drives logic

> Hardware output is a view, not a controller.

---

## 4. Focus as a first-class signal

Focus is treated as **data**, not UI decoration.

Focus:
- Has a ControlId
- Is persisted in plugin state
- Drives:
  - UI highlight
  - Hardware routing
  - Hardware LEDs

This mirrors how real control surfaces work.

---

## 5. Why this scales

This architecture scales because:

- Adding parameters does not add complexity
- Hardware protocols can be swapped without touching DSP
- UI changes do not affect control logic
- Debugging is linear and traceable

You can always answer:
> “Where did this value come from?”

---

## 6. Anti-patterns (do not do this)

❌ UI writing DSP values directly  
❌ Hardware output modifying parameters  
❌ Multiple sources of truth  
❌ Implicit observers and hidden callbacks  

If you see these, the architecture is being violated.

---

## 7. Mental checklist when adding code

Before adding logic, ask:

1. Is this **intent** or **truth**?
2. Is this **normalized** or **native**?
3. Does this introduce a second source of truth?

If you hesitate — stop and re-evaluate.

---

## 8. Final note

JUCE is the *toolkit*.
This architecture is the *system*.

Treat it like a platform, not a project.
