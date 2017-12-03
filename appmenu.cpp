#include "appmenu.h"
#include "appmenu.h"
#include "capplibrary.h"

sMenuItem::sMenuItem():m_iParentID(0),m_iID(0),m_iShowNum(0)
{
     strcpy(m_szName, "");
     m_ptrMenuEvent = nullptr;
}
 sMenuItem::sMenuItem(int iParentID, int iID, int iShowNum, const char* ptrName, funcAvent ptrMenuEvent):
    m_iParentID(iParentID),m_iID(iID),m_iShowNum(iShowNum)
 {
     strncpy(m_szName, ptrName, sizeof(m_szName));
     m_ptrMenuEvent = ptrMenuEvent;
 }

 int    sMenuItem::GetParentID() {return m_iParentID;}
 int    sMenuItem::GetID(){return m_iID;}
 int    sMenuItem::GetShowNum(){return m_iShowNum;}
 char*  sMenuItem::GetName(){return m_szName;}



//*************************************************************************************
AppMenu::AppMenu(){}

int AppMenu::BuildMenu(int uParentMenu)
{
    if(uParentMenu == -1)
        return -10;

    std::vector<prtMenuItem> vCurrMenu;

    for(auto itList: m_vItemList)
        if(itList->GetParentID() == uParentMenu)
            vCurrMenu.push_back(itList);
    ShowdMenu(vCurrMenu, uParentMenu != 100 &&  uParentMenu != 200);
    int iSelect  = MessageSelectMenuItem(vCurrMenu.size());


    for(auto itMenu : vCurrMenu)
        if(itMenu->GetShowNum() == iSelect)
        {
            while(true)
            {
               int ret = (m_ptrParentApp->*(itMenu)->m_ptrMenuEvent)(uParentMenu,itMenu->GetID());

               if(ret == -10)
                    BuildMenu(GetIdParentMenu(itMenu->GetParentID()));
               if(ret == 10)
                    BuildMenu(itMenu->GetID());
               if(ret == 1)
                    BuildMenu(uParentMenu);
               if(ret == -13)
                   return -10;


               return -100;
            }
        }
    return 1;
}
bool AppMenu::ShowdMenu(std::vector<prtMenuItem> &m_vItemShow, bool bClear)
{
    if(bClear)  system("cls");
    if(m_ptrParentApp) m_ptrParentApp->ShowInfo();
    for(auto it : m_vItemShow)
       std::cout << it->GetShowNum() << ". " << it->GetName() << std::endl;
    return true;
}


bool AppMenu::Run()
{
    while(BuildMenu(0) > 0)
    {

    }
    return true;
}

int AppMenu::GetIdParentMenu(int ID)
{
    for(auto it: m_vItemList)
       if(it->GetID() == ID)
            return it->GetParentID();
    return -1;
}


void AppMenu::CreateMenu(CAppLibrary *ptrParentApp)
{
    m_ptrParentApp = ptrParentApp;

    {prtMenuItem ptrItem( new sMenuItem(0, 1, 1, "Books",		&CAppLibrary::popaMenu));	m_vItemList.push_back(ptrItem);}
    {prtMenuItem ptrItem( new sMenuItem(0, 2, 2, "Person",		&CAppLibrary::popaMenu));	m_vItemList.push_back(ptrItem);}
    {prtMenuItem ptrItem( new sMenuItem(0, 3, 3, "Exit",		&CAppLibrary::exitApp));	m_vItemList.push_back(ptrItem);}

        {prtMenuItem ptrItem( new sMenuItem(1, 11, 1, "View all books", &CAppLibrary::viewItems));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(1, 12, 2, "Find book",		&CAppLibrary::findItem));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(1, 13, 3, "Add book",		&CAppLibrary::addItem));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(1, 14, 4, "Back",			&CAppLibrary::backMenu));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(1, 15, 5, "Exit",			&CAppLibrary::exitApp));	m_vItemList.push_back(ptrItem);}

            {prtMenuItem ptrItem( new sMenuItem(100, 101, 1, "Select book", &CAppLibrary::selectItem)); m_vItemList.push_back(ptrItem);}
            {prtMenuItem ptrItem( new sMenuItem(100, 102, 2, "Back",		&CAppLibrary::backMenu) );  m_vItemList.push_back(ptrItem);}

                {prtMenuItem ptrItem( new sMenuItem(101, 121, 1, "Delete book",	&CAppLibrary::deleteItem));		m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(101, 122, 2, "Edit book",	&CAppLibrary::editItem));		m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(101, 123, 3, "Add person",	&CAppLibrary::addPersonBook));	m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(101, 124, 4, "Delete person",&CAppLibrary::delPersonBook));	m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(101, 125, 5, "Back",		&CAppLibrary::backMenu));		m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(101, 126, 6, "Exit",		&CAppLibrary::exitApp));		m_vItemList.push_back(ptrItem);}

        {prtMenuItem ptrItem( new sMenuItem(2, 21, 1, "View persons",	&CAppLibrary::viewItems));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(2, 22, 2, "Add person",		&CAppLibrary::addItem));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(2, 23, 3, "Back",			&CAppLibrary::backMenu));	m_vItemList.push_back(ptrItem);}
        {prtMenuItem ptrItem( new sMenuItem(2, 24, 4, "Exit",			&CAppLibrary::exitApp));	m_vItemList.push_back(ptrItem);}

            {prtMenuItem ptrItem( new sMenuItem(200, 201, 1, "Select person",	&CAppLibrary::selectItem));		m_vItemList.push_back(ptrItem);}
            {prtMenuItem ptrItem( new sMenuItem(200, 202, 2, "Back",			&CAppLibrary::backMenu) );      m_vItemList.push_back(ptrItem);}

                {prtMenuItem ptrItem( new sMenuItem(201, 221, 1, "Delete person",	&CAppLibrary::deleteItem));		m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(201, 222, 2, "Edit person",		&CAppLibrary::editItem));		m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(201, 223, 3, "Add book",		&CAppLibrary::addBookPerson));	m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(201, 224, 4, "Delete book",		&CAppLibrary::delBookPerson));	m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(201, 225, 5, "Back",			&CAppLibrary::backMenu));		m_vItemList.push_back(ptrItem);}
                {prtMenuItem ptrItem( new sMenuItem(201, 226, 6, "Exit",			&CAppLibrary::exitApp));		m_vItemList.push_back(ptrItem);}
}
