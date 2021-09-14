//---------------------------------------------------------------------------

#ifndef AVI_textH
#define AVI_textH
#include <windows.h>
#include <vfw.h>

#define _RGB 0
#define _RBG 1
#define _GBR 2
#define _GRB 3
#define _BRG 4
#define _BGR 5

class _AVI_texture{
protected:
        BITMAPINFO* pbmi;

        PAVISTREAM _paviStream; // AVI поток
        PGETFRAME _pgetFrame; // ”казатель на текущий кадр в потоке
        AVISTREAMINFO _aviStreamInfo; // »нформаци€ о потоке

        double CurrAVITime;
        DWORD CurrFrame,LastFrame;
        double CurrTime,LastTime;

        double AVITimeScale;
        double LenInTime;

        int format;

        bool aviplays;
        bool stopped;
        bool _inited;
        
        void flipFrame(BITMAPINFO* buf);


public:
        bool AVI_Init(char *filename);
        void AVI_Destroy();
        BITMAPINFO *GetCurrPBMI();
        void Play();
        void Stop();
        void Pause();
        void Set_Format(int __form);

        _AVI_texture();
        _AVI_texture(char *filename);
        ~_AVI_texture();

};







//---------------------------------------------------------------------------
#endif
 