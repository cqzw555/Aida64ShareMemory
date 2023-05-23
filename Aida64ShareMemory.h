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
    // 如需增加，在这里修改
    // 共享内存中的名字，{显示标签，单位}
    std::map<std::wstring, Aida64Type> types = {
        {L"GPU",{L"GPU功率",L"W"}},
        {L"CPU Package",{L"CPU功率",L"W"}},
        {L"CPU GT Cores",{L"核显功率",L"W"}},
        {L"CPU IA Cores",{L"CPU核心功率",L"W"}},
        {L"GPU TDP%",{L"GPU TDP%",L"%"}},
    };
};

#ifdef __cplusplus
extern "C" {
#endif
    __declspec(dllexport) ITMPlugin* TMPluginGetInstance();

#ifdef __cplusplus
}
#endif
