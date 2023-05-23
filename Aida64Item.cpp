#include "pch.h"
#include "Aida64Item.h"
#include "DataManager.h"
#include <string>

Aida64Type::Aida64Type(std::wstring l, std::wstring u)
{
    this->label = l;
    this->uint = u;
}
Aida64Type::Aida64Type(){};

Aida64Item::Aida64Item(std::wstring name, std::wstring nodeid)
{
    this->name = name;
    this->nodeid = nodeid;
}
Aida64Item::~Aida64Item()
{
}

const wchar_t *Aida64Item::GetItemName() const
{
    return name.c_str();
}

const wchar_t *Aida64Item::GetItemId() const
{
    return nodeid.c_str();
}

const wchar_t *Aida64Item::GetItemLableText() const
{

    return label.c_str();
}

const wchar_t *Aida64Item::GetItemValueText() const
{
    return str.c_str();
}

const wchar_t *Aida64Item::GetItemValueSampleText() const
{
    return L"10000";
}

bool Aida64Item::IsCustomDraw() const
{
    return false;
}

int Aida64Item::GetItemWidthEx(void *hDC) const
{
    CDC *pDC = CDC::FromHandle((HDC)hDC);
    return 60;
}

void Aida64Item::DrawItem(void *hDC, int x, int y, int w, int h, bool dark_mode)
{
    CDC *pDC = CDC::FromHandle((HDC)hDC);
    CRect rect(CPoint(x, y), CSize(w, h));
}
