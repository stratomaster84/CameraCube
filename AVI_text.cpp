//---------------------------------------------------------------------------

#pragma hdrstop

#include "AVI_text.h"
#include <time.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)

bool _AVI_texture::AVI_Init(char *filename){
        if(_inited)
                return false;
       // AVIFileInit();
        AVIStreamOpenFromFile( &_paviStream, filename,streamtypeVIDEO, 0, OF_READ, NULL );
        if(_paviStream == NULL)
                return false;
        _pgetFrame = AVIStreamGetFrameOpen( _paviStream, NULL );
        if(_pgetFrame == NULL)
                return false;
        AVIStreamInfo( _paviStream, &_aviStreamInfo,sizeof(AVISTREAMINFO));
        
        CurrAVITime = 0.0f;

        CurrFrame = _aviStreamInfo.dwStart;
        LastFrame = CurrFrame+1;

        CurrTime = ((double)clock())/CLOCKS_PER_SEC;
        LastTime = CurrTime;

        AVITimeScale = ((double)_aviStreamInfo.dwRate) / _aviStreamInfo.dwScale;
        LenInTime = (double)_aviStreamInfo.dwLength/AVITimeScale;

        format = _RGB;

        aviplays = false;
        stopped = true;

        _inited = true;
        return true;
}

void _AVI_texture::AVI_Destroy(){
        if(!_inited)
                return;
        _inited = false;
        AVIStreamRelease( _paviStream ); // освобождаем AVI поток
        //AVIFileExit(); // закрываем библиотеку для работы с AVI
       //if(pbmi)
             //   delete [] pbmi;
}

void _AVI_texture::flipFrame(BITMAPINFO* buf){
        void* b = (void *)buf;     // Указатель на буфер
        unsigned _tmp = sizeof(BITMAPINFO);
        int __form = format;
        long count = buf->bmiHeader.biWidth*buf->bmiHeader.biHeight;
__asm{                   // Начало asm кода

                mov ecx, count
                mov ebx, b
                add ebx, _tmp

        _flip_next_RBG:
                cmp __form,_RBG
                jne _flip_next_GBR
                _label_RBG:
                        mov al,[ebx+1]
                        mov ah,[ebx+2]
                        mov [ebx+1],ah
                        mov [ebx+2],al
                        add ebx,3
                        dec ecx
                        jnz _label_RBG
                        jmp short _flip_end
        _flip_next_GBR:
                cmp __form,_GBR
                jne _flip_next_GRB
                _label_GBR:
                        mov al,[ebx]
                        mov ah,[ebx+1]
                        mov dl,[ebx+2]
                        mov [ebx],dl
                        mov [ebx+1],al
                        mov [ebx+2],ah
                        add ebx,3
                        dec ecx
                        jnz _label_GBR
                        jmp short _flip_end
        _flip_next_GRB:
                cmp __form,_GRB
                jne _flip_next_BRG
                _label_GRB:
                        mov al,[ebx]
                        mov ah,[ebx+1]
                        mov [ebx],ah
                        mov [ebx+1],al
                        add ebx,3
                        dec ecx
                        jnz _label_GRB
                        jmp short _flip_end
        _flip_next_BRG:
                cmp __form,_BRG
                jne _flip_next_BGR
                _label_BRG:
                        mov al,[ebx]
                        mov ah,[ebx+1]
                        mov dl,[ebx+2]
                        mov [ebx],ah
                        mov [ebx+1],dl
                        mov [ebx+2],al
                        add ebx,3
                        dec ecx
                        jnz _label_BRG
                        jmp short _flip_end
        _flip_next_BGR:
                cmp __form,_BGR
                jne _flip_end
                _label_BGR:
                        mov al,[ebx]
                        mov ah,[ebx+2]
                        mov [ebx],ah
                        mov [ebx+2],dl
                        add ebx,3
                        dec ecx
                        jnz _label_BGR
                        jmp short _flip_end
        _flip_end:
}
}

void _AVI_texture::Play(){
        if(!_inited)
                return;
        aviplays = true;
        stopped = false;
}
void _AVI_texture::Stop(){
        if(!_inited)
                return;

        aviplays = false;
        CurrFrame = _aviStreamInfo.dwStart;
        CurrAVITime = 0.0f;
        stopped = true;
}
void _AVI_texture::Pause(){
        if(!_inited || stopped)
                return;
        aviplays = !aviplays;
}

BITMAPINFO* _AVI_texture::GetCurrPBMI(){
        if(!_inited)
                return NULL;

        pbmi = (BITMAPINFO*)AVIStreamGetFrame( _pgetFrame, CurrFrame );

        if(LastFrame != CurrFrame){
                if(format != _RGB)
                        flipFrame(pbmi);
                LastFrame = CurrFrame;
        }

        CurrTime = ((double)clock())/CLOCKS_PER_SEC;
        if(aviplays){
                CurrAVITime += CurrTime- LastTime;
                while( CurrAVITime >= LenInTime )
                        CurrAVITime -= LenInTime;

                CurrFrame = (DWORD)( CurrAVITime * AVITimeScale );
        }
        LastTime = CurrTime;
        return pbmi;
}
_AVI_texture::_AVI_texture(){
        _inited = false;
}
_AVI_texture::_AVI_texture(char *filename){
        _inited = false;
        AVI_Init(filename);
}
_AVI_texture::~_AVI_texture(){
        AVI_Destroy();
}
void _AVI_texture::Set_Format(int __form){
        format = __form;
}
