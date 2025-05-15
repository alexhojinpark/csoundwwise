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

#include "csoundwwise_sourceSource.h"
#include "../csoundwwise_sourceConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* Createcsoundwwise_sourceSource(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, csoundwwise_sourceSource());
}

AK::IAkPluginParam* Createcsoundwwise_sourceSourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, csoundwwise_sourceSourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(csoundwwise_sourceSource, AkPluginTypeSource, csoundwwise_sourceConfig::CompanyID, csoundwwise_sourceConfig::PluginID)

csoundwwise_sourceSource::csoundwwise_sourceSource()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

csoundwwise_sourceSource::~csoundwwise_sourceSource()
{
}

AKRESULT csoundwwise_sourceSource::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (csoundwwise_sourceSourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

    return AK_Success;
}

AKRESULT csoundwwise_sourceSource::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT csoundwwise_sourceSource::Reset()
{
    return AK_Success;
}

AKRESULT csoundwwise_sourceSource::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void csoundwwise_sourceSource::Execute(AkAudioBuffer* out_pBuffer)
{
    m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
    m_durationHandler.ProduceBuffer(out_pBuffer);

    const AkUInt32 uNumChannels = out_pBuffer->NumChannels();

    AkUInt16 uFramesProduced;
    for (AkUInt32 i = 0; i < uNumChannels; ++i)
    {
        AkReal32* AK_RESTRICT pBuf = (AkReal32* AK_RESTRICT)out_pBuffer->GetChannel(i);

        uFramesProduced = 0;
        while (uFramesProduced < out_pBuffer->uValidFrames)
        {
            // Generate output here
            *pBuf++ = 0.0f;
            ++uFramesProduced;
        }
    }
}

AkReal32 csoundwwise_sourceSource::GetDuration() const
{
    return m_durationHandler.GetDuration() * 1000.0f;
}
