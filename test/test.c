#include <windows.h>
#include <mfapi.h>
#include <mfplay.h>
#include <mfreadwrite.h>
#include <stdio.h>

#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

int main()
{
    HRESULT hr = S_OK;
    IMFSourceReader *pReader = NULL;

    // Initialize Media Foundation
    hr = MFStartup(MF_VERSION);
    if (FAILED(hr))
    {
        printf("MFStartup failed.\n");
        return hr;
    }

    // Create a source reader
    char fileName[] = "C:\\Users\\jeman\\downloads\\RR.wav";
    wchar_t wfileName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, fileName, -1, wfileName, MAX_PATH);
    hr = MFCreateSourceReaderFromURL(wfileName, NULL, &pReader);
    if (FAILED(hr))
    {
        printf("Failed to create source reader.\n");
        goto done;
    }

    // Start playback
    IMFMediaSource *pSource = NULL;
    hr = pReader->GetServiceForStream(MF_SOURCE_READER_FIRST_AUDIO_STREAM, GUID_NULL, IID_PPV_ARGS(&pSource));
    if (FAILED(hr))
    {
        printf("Failed to get audio stream.\n");
        goto done;
    }

    IMFMediaSink *pSink = NULL;
    hr = MFCreateAudioRenderer(NULL, &pSink);
    if (FAILED(hr))
    {
        printf("Failed to create audio renderer.\n");
        goto done;
    }

    hr = pSink->AddStreamSink(0, pSource, NULL);
    if (FAILED(hr))
    {
        printf("Failed to add stream sink.\n");
        goto done;
    }

    hr = pSink->Start(pSource);
    if (FAILED(hr))
    {
        printf("Failed to start playback.\n");
        goto done;
    }

    printf("Press any key to stop playback...\n");
    getchar();

    hr = pSink->Stop();
    if (FAILED(hr))
    {
        printf("Failed to stop playback.\n");
        goto done;
    }

    done:
    if (pSink)
    {
        pSink->Release();
    }
    if (pSource)
    {
        pSource->Release();
    }
    if (pReader)
    {
        pReader->Release();
    }

    MFShutdown();
    return 0;
}
