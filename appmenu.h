#ifndef APPMENU_H
#define APPMENU_H

#include "define.h"

class CAppLibrary;
typedef int (CAppLibrary::*funcAvent)(int a, int b);


class sMenuItem
{
    int    m_iParentID;
    int    m_iID;
    int    m_iShowNum;
    char   m_szName[256];

public:
    int    GetParentID();
    int    GetID();
    int    GetShowNum();
    char*   GetName();

    funcAvent    m_ptrMenuEvent;
    sMenuItem();
    sMenuItem(int iParentID, int iID, int iShowNum, const char* ptrNeme, funcAvent prtMenuEvent);
};

typedef std::shared_ptr<sMenuItem> prtMenuItem;
class AppMenu
{
    bool ShowdMenu( std::vector<prtMenuItem> &m_vItemShow, bool bClear = true);
    std::vector<prtMenuItem> m_vItemList;

public:
    AppMenu();
    void CreateMenu(CAppLibrary *ptrParentApp);
    int BuildMenu(int uParentMenu);
    bool Run();
    CAppLibrary *m_ptrParentApp;
    int GetIdParentMenu(int);
};


#endif // APPMENU_H
