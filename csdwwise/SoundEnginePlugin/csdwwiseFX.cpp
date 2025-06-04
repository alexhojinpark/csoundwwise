/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2025 Audiokinetic Inc.
*******************************************************************************/

#include "csdwwiseFX.h"
#include "../csdwwiseConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreatecsdwwiseFX(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, csdwwiseFX());
}

AK::IAkPluginParam* CreatecsdwwiseFXParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, csdwwiseFXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(csdwwiseFX, AkPluginTypeEffect, csdwwiseConfig::CompanyID, csdwwiseConfig::PluginID)

csdwwiseFX::csdwwiseFX()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

csdwwiseFX::~csdwwiseFX()
{
}

AKRESULT csdwwiseFX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (csdwwiseFXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    return AK_Success;
}

AKRESULT csdwwiseFX::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT csdwwiseFX::Reset()
{
    return AK_Success;
}

AKRESULT csdwwiseFX::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeEffect;
    out_rPluginInfo.bIsInPlace = true;
	out_rPluginInfo.bCanProcessObjects = false;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void csdwwiseFX::Execute(AkAudioBuffer* io_pBuffer)
{
    const AkUInt32 uNumChannels = io_pBuffer->NumChannels();

    // Use a local copy of the RTPC value for thread safety and RTPC update support
    // AkReal32 fGain = m_pParams->RTPC.fPlaceholder;
    
    AkUInt16 uFramesProcessed;
    for (AkUInt32 i = 0; i < uNumChannels; ++i)
    {
        AkReal32* AK_RESTRICT pBuf = (AkReal32* AK_RESTRICT)io_pBuffer->GetChannel(i);

        uFramesProcessed = 0;
        while (uFramesProcessed < io_pBuffer->uValidFrames)
        {
            // Execute DSP in-place here
            pBuf[uFramesProcessed] = pBuf[uFramesProcessed] * AK_DBTOLIN(m_pParams->RTPC.fPlaceholder);
            ++uFramesProcessed;
        }
    }
    // Mark parameter as consumed (RTPC update handled)
    m_pParams->m_paramChangeHandler.ResetAllParamChanges();
}

AKRESULT csdwwiseFX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
