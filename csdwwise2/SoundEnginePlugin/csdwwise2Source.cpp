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

#include "csdwwise2Source.h"
#include "../csdwwise2Config.h"

#include <AK/AkWwiseSDKVersion.h>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <sys/stat.h>

static bool FileExistsFast(const char* p) {
    if (!p || !*p) return false;
    struct stat st {};
    return ::stat(p, &st) == 0 && (st.st_mode & S_IFREG);
}

static bool ReadCsdPath(char outPath[], size_t outCap)
{
    outPath[0] = '\0';

    auto trim_trailing = [](std::string& s) {
        while (!s.empty()) {
            char c = s.back();
            if (c == '\r' || c == '\n' || c == ' ' || c == '\t') s.pop_back();
            else break;
        }
        };

    auto strip_utf8_bom = [](std::string& s) {
        if (s.size() >= 3 &&
            static_cast<unsigned char>(s[0]) == 0xEF &&
            static_cast<unsigned char>(s[1]) == 0xBB &&
            static_cast<unsigned char>(s[2]) == 0xBF)
        {
            s.erase(0, 3);
        }
        };

    // 1) Manifest (works even if Wwise is already running)
    if (const char* la = std::getenv("LOCALAPPDATA")) {
        if (la && *la) {
            char manifest[1024];
            std::snprintf(manifest, sizeof(manifest), "%s\\csdwwise\\current.txt", la);

            std::ifstream f(manifest, std::ios::in | std::ios::binary);
            if (f) {
                std::string line;
                line.reserve(512);
                std::getline(f, line);
                trim_trailing(line);
                strip_utf8_bom(line);

                if (!line.empty() && FileExistsFast(line.c_str())) {
                    std::snprintf(outPath, outCap, "%s", line.c_str());
                    return true;
                }
            }
        }
    }

    // 2) Environment variable (good for new Wwise processes)
    if (const char* env = std::getenv("CSDWWISE_CSD_PATH")) {
        if (FileExistsFast(env)) {
            std::snprintf(outPath, outCap, "%s", env);
            return true;
        }
    }

    // 3) Optional default via repo env var: CSDWWISE_REPO\csd\1.csd
    if (const char* repo = std::getenv("CSDWWISE_REPO")) {
        char candidate[1024];
        std::snprintf(candidate, sizeof(candidate), "%s\\csd\\1.csd", repo);
        if (FileExistsFast(candidate)) {
            std::snprintf(outPath, outCap, "%s", candidate);
            return true;
        }
    }

    return false;
}

AK::IAkPlugin* Createcsdwwise2Source(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, csdwwise2Source());
}

AK::IAkPluginParam* Createcsdwwise2SourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, csdwwise2SourceParams());
}

//AK_IMPLEMENT_PLUGIN_FACTORY(csdwwise2Source, AkPluginTypeSource, csdwwise2Config::CompanyID, csdwwise2Config::PluginID)

AK::PluginRegistration csdwwise2SourceRegistration(
    AkPluginTypeSource,
    csdwwise2Config::CompanyID,
    csdwwise2Config::PluginID,
    Createcsdwwise2Source,
    Createcsdwwise2SourceParams
);


csdwwise2Source::csdwwise2Source()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

csdwwise2Source::~csdwwise2Source()
{
}

AKRESULT csdwwise2Source::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{

    m_pParams = (csdwwise2SourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    //m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

    // Use Duration from bank or default. Loops 0 means infinite per Wwise.
    const AkReal32 seconds = m_pParams ? m_pParams->RTPC.fDuration : 1.0f;
    const AkInt16  loops = in_pContext->GetNumLoops();
    m_durationHandler.Setup(seconds, loops, in_rFormat.uSampleRate);

    char csdPath[1024];
    if (!ReadCsdPath(csdPath, sizeof(csdPath))) {
        std::printf("[csdwwise2] No .csd selected. Set CSDWWISE_CSD_PATH or run the csdwwise CLI.\n");
        return AK_Fail;
    }

    if (!m_csound.load(csdPath)) {
        std::printf("[csdwwise2] Failed to load .csd: %s\n", csdPath);
        return AK_Fail;
    }

    return AK_Success;
}

AKRESULT csdwwise2Source::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT csdwwise2Source::Reset()
{
    return AK_Success;
}

AKRESULT csdwwise2Source::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void csdwwise2Source::Execute(AkAudioBuffer* out_pBuffer)
{
    m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
    m_durationHandler.ProduceBuffer(out_pBuffer);

    const AkUInt32 uNumChannels = out_pBuffer->NumChannels();
    const AkUInt16 uFrames = out_pBuffer->uValidFrames;
    const int ksmps = m_csound.getKsmps();
    if (ksmps <= 0) {
        // Output silence if Csound not initialized
        for (AkUInt32 i = 0; i < uNumChannels; ++i)
        {
            AkReal32* AK_RESTRICT pBuf = (AkReal32 * AK_RESTRICT)out_pBuffer->GetChannel(i);
            for (AkUInt16 f = 0; f < uFrames; ++f)
            {
                pBuf[f] = 0.0f;
            }
        }
        return;
    }

    std::vector<float> csdBuffer(ksmps, 0.0f);
    AkUInt16 framesProcessed = 0;
    while (framesProcessed < uFrames) {
        int framesToProcess = std::min<int>(ksmps, uFrames - framesProcessed);
        if (m_csound.performBlock(csdBuffer.data(), framesToProcess)) {
            for (AkUInt32 i = 0; i < uNumChannels; ++i)
            {
                AkReal32* AK_RESTRICT pBuf = (AkReal32 * AK_RESTRICT)out_pBuffer->GetChannel(i);
                for (int f = 0; f < framesToProcess; ++f)
                {
                    pBuf[framesProcessed + f] = csdBuffer[f];
                }
            }
        }
        else {
            // Output silence for this block
            for (AkUInt32 i = 0; i < uNumChannels; ++i)
            {
                AkReal32* AK_RESTRICT pBuf = (AkReal32 * AK_RESTRICT)out_pBuffer->GetChannel(i);
                for (int f = 0; f < framesToProcess; ++f)
                {
                    pBuf[framesProcessed + f] = 0.0f;
                }
            }
        }
        framesProcessed += framesToProcess;
    }
}

AkReal32 csdwwise2Source::GetDuration() const
{
    return m_durationHandler.GetDuration() * 1000.0f;
}