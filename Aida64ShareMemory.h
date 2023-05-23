#pragma once
#include "PluginInterface.h"
#include "Aida64Item.h"
#include <string>
#include <map>
#include <vector>

class CAida64ShareMemory : public ITMPlugin
{
private:
    CAida64ShareMemory();

public:
    static CAida64ShareMemory& Instance();

    virtual IPluginItem* GetItem(int index) override;
    virtual const wchar_t* GetTooltipInfo() override;
    virtual void DataRequired() override;
    virtual OptionReturn ShowOptionsDialog(void* hParent) override;
    virtual const wchar_t* GetInfo(PluginInfoIndex index) override;
    virtual void OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data) override;

private:
    void readSharememory();
private:
    static CAida64ShareMemory m_instance;
    std::vector<Aida64Item> items;
    std::map<std::wstring, size_t> idx;
    std::wstring m_tooltip_info;
    char* buffer = nullptr;
    std::map<std::wstring, Aida64Type> types = {
        {L"GPU",{L"GPU温度",L"℃"}},
        {L"CPU",{L"CPU功率",L"W"}},
        {L"CPU Package",{L"CPU功率",L"W"}},
        {L"CPU GT Cores",{L"核显功率",L"W"}},
        {L"CPU IA Cores",{L"CPU核心功率",L"W"}},
        {L"GPU TDP%",{L"GPU TDP%",L"%"}},
        {L"Motherboard",{L"主板温度",L"℃"}},
        {L"GPU Hotspot",{L"GPU热点",L"℃"} }
    };
};

#ifdef __cplusplus
extern "C" {
#endif
    __declspec(dllexport) ITMPlugin* TMPluginGetInstance();

#ifdef __cplusplus
}
#endif
