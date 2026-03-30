# Hack Utility Library

A lightweight utility library for game hacking, providing commonly used functions for both **external** and **internal** projects.

---

## 📌 Overview

This library is designed to simplify repetitive tasks such as:

* Process handling
* Module base address retrieval
* Pointer resolution (DMA)
* Memory patching and NOP operations

It supports both:

* **External hacks** (separate process)
* **Internal hacks** (DLL injection)

---

## 📂 Structure

```
lib/
├── Utility/
│   ├── external/
│   │   ├── include/
│   │   └── src/
│   │
│   └── internal/
│       ├── include/
│       └── src/
```

---

## 🚀 Features

### External

* `FindProcessID`
  → Get process ID by process name

* `GetBaseModuleAddress`
  → Retrieve base address of a module

* `FindDMAAddy`
  → Resolve multi-level pointers

---

### Internal

* `mem::Patch` / `mem::PatchEX`
  → Write bytes into memory

* `mem::Nop` / `mem::NopEX`
  → Replace instructions with NOP

---

## 🛠️ Requirements

* Windows
* C++ (MSVC recommended)
* WinAPI

---

## ⚠️ Important

> ⚡ Must be compiled as **x86 (32-bit)**

Most target games (e.g., AssaultCube) are 32-bit.
Using x64 will cause injection or memory access to fail.

---

## 🔧 Usage

### External Example

```cpp
DWORD procID = FindProcessID(L"ac_client.exe");
uintptr_t moduleBase = GetBaseModuleAddress(procID, L"ac_client.exe");

uintptr_t dynamicPtr = FindDMAAddy(hProcess, moduleBase + 0x10F4F4, { 0x374, 0x14, 0x0 });
```

---

### Internal Example

```cpp
mem::Patch((BYTE*)address, (BYTE*)"\x90\x90", 2);
mem::Nop((BYTE*)address, 6);
```

---

## 📌 Notes

* Designed for learning and experimentation
* Not intended for bypassing anti-cheat systems
* Use in controlled environments only

---

## 📄 License

This project is for educational purposes only.
