//------------------------------------------------------------------------
// Copyright(c) 2021 rpuhalovich.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace rpuhalovich {
//------------------------------------------------------------------------
static const Steinberg::FUID kVReverbProcessorUID (0xE7280A59, 0x02025C15, 0xAF2E4592, 0xF1F0E02F);
static const Steinberg::FUID kVReverbControllerUID (0x6C0C1949, 0x73A75D12, 0x8DCFA5CC, 0x216CADEF);

#define VReverbVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace rpuhalovich
