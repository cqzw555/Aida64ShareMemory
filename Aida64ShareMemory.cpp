#include "pch.h"
#include "Aida64ShareMemory.h"
#include "DataManager.h"
#include "OptionsDlg.h"
#include "Common.h"
#include <string>
#define BUF_SIZE 4096
CAida64ShareMemory CAida64ShareMemory::m_instance;

CAida64ShareMemory::CAida64ShareMemory()
{
    readSharememory();
    srand(1024);
    auto randnodeid = [](int n) {
        std::wstring res;
        for (int i = 0; i < n; i++) 
            res += std::to_wstring(rand()%10);
        return res;
    };
    for (auto p : g_data.values) {
        if (types.find(p.first) != types.end()) {
            Aida64Item item =  Aida64Item(p.first, randnodeid(8));
            item.setLabel(types[p.first].label);
            item.setUint(types[p.first].uint);
            items.emplace_back(item);
            idx[p.first] = (size_t)(items.size() - 1);
        }
    }
    return;
}

CAida64ShareMemory& CAida64ShareMemory::Instance()
{
    return m_instance;
}

IPluginItem* CAida64ShareMemory::GetItem(int index)
{
    auto n = items.size();
    if (index < n) {
        return &items[index];
    }
    return nullptr;
}

const wchar_t* CAida64ShareMemory::GetTooltipInfo()
{
    return m_tooltip_info.c_str();
}

void CAida64ShareMemory::readSharememory() {
    g_data.values.clear();
    const wchar_t* t_name = L"AIDA64_SensorValues";
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, t_name);
    if (hMapFile)
    {
        LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        // 将共享内存数据拷贝出来
        char szBuffer[BUF_SIZE] = {};
        strcpy_s(szBuffer, (char*)lpBase);
        // 解除文件映射
        UnmapViewOfFile(lpBase);
        // 关闭内存映射文件对象句柄
        CloseHandle(hMapFile);
        auto current_label_begin = strstr(szBuffer, "<label>");
        do {
            current_label_begin += strlen("<label>");
            auto current_label_end = strstr(current_label_begin, "</label>");
            auto current_value_begin = strstr(current_label_begin, "<value>") + strlen("<value>");
            auto current_value_end = strstr(current_label_begin, "</value>");
            std::wstring name = std::wstring{ current_label_begin, current_label_end };
            if (*(current_value_end + strlen("</value>")) == '\0')
                break;
            g_data.values[name] = atof(current_value_begin);
            current_label_begin = strstr(current_value_end, "<label>");
        } while (current_label_begin != NULL);
    }
    return;
}

void CAida64ShareMemory::DataRequired()
{
    readSharememory();
    std::wstring tmp = L"";
    for (auto p : g_data.values) {
        if (idx.find(p.first) != idx.end()) {
            auto val = std::to_wstring(p.second).substr(0,4);
            if (val[3] == (wchar_t)'.') val = val.substr(0, 3) + items[idx[p.first]].unit;
            else val += items[idx[p.first]].unit;
            items[idx[p.first]].str = val;
            tmp += types[p.first].label + L":" + val + L"\n";
        }
    }
    m_tooltip_info = tmp.substr(0,tmp.size()-1);
    return;
}

ITMPlugin::OptionReturn CAida64ShareMemory::ShowOptionsDialog(void* hParent)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CWnd* pParent = CWnd::FromHandle((HWND)hParent);
    COptionsDlg dlg(pParent);
    dlg.m_data = g_data.m_setting_data;
    if (dlg.DoModal() == IDOK)
    {
        g_data.m_setting_data = dlg.m_data;
        return ITMPlugin::OR_OPTION_CHANGED;
    }
    return ITMPlugin::OR_OPTION_UNCHANGED;
}

const wchar_t* CAida64ShareMemory::GetInfo(PluginInfoIndex index)
{
    static CString str;
    switch (index)
    {
    case TMI_NAME:
        return g_data.StringRes(IDS_PLUGIN_NAME).GetString();
    case TMI_DESCRIPTION:
        return g_data.StringRes(IDS_PLUGIN_DESCRIPTION).GetString();
    case TMI_AUTHOR:
        //TODO: 在此返回作者的名字
        return L"cqzw555";
    case TMI_COPYRIGHT:
        //TODO: 在此返回版权信息
        return L"Copyright (C) by cqzw555 2023";
    case ITMPlugin::TMI_URL:
        //TODO: 在此返回URL
        return L"None";
        break;
    case TMI_VERSION:
        //TODO: 在此修改插件的版本
        return L"0.01";
    default:
        break;
    }
    return L"";
}

void CAida64ShareMemory::OnExtenedInfo(ExtendedInfoIndex index, const wchar_t* data)
{
    switch (index)
    {
    case ITMPlugin::EI_CONFIG_DIR:
        //从配置文件读取配置
        g_data.LoadConfig(std::wstring(data));
        break;
    default:
        break;
    }
}

ITMPlugin* TMPluginGetInstance()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return &CAida64ShareMemory::Instance();
}
