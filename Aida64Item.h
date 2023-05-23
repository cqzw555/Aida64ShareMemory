#pragma once
#include "PluginInterface.h"
#include <string>

class Aida64Type {
public:
    std::wstring label;
    std::wstring uint;
    Aida64Type(std::wstring,std::wstring);
    Aida64Type();
};

class Aida64Item : public IPluginItem
{
public:
    Aida64Item(std::wstring,std::wstring);
    ~Aida64Item();
    virtual const wchar_t* GetItemName() const override;
    virtual const wchar_t* GetItemId() const override;
    virtual const wchar_t* GetItemLableText() const override;
    virtual const wchar_t* GetItemValueText() const override;
    virtual const wchar_t* GetItemValueSampleText() const override;
    virtual bool IsCustomDraw() const override;
    virtual int GetItemWidthEx(void* hDC) const override;
    virtual void DrawItem(void* hDC, int x, int y, int w, int h, bool dark_mode) override;
    void setLabel(std::wstring label) {
        this->label = label;
    };
    void setUint(std::wstring unit) {
        this->unit = unit;
    };
    std::wstring str;
    std::wstring unit;
private:
    std::wstring name;
    std::wstring nodeid;
    std::wstring label;
    
};
