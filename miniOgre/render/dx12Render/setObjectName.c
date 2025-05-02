#include <d3d12.h>



void SetObjectName(ID3D12Object* pObject, const char* pName)
{
    if (!pName)
    {
        return;
    }
#define MAX_DEBUG_NAME_LENGTH 128
    wchar_t wName[MAX_DEBUG_NAME_LENGTH] = { 0 };
    size_t  numConverted = 0;
    mbstowcs_s(&numConverted, wName, MAX_DEBUG_NAME_LENGTH, pName, MAX_DEBUG_NAME_LENGTH);
    (pObject)->lpVtbl->SetName(pObject, wName);
}