#ifndef CAPPLIBRARY_H
#define CAPPLIBRARY_H


#include "define.h"
#include "appmenu.h"
#include "cappitems.h"

class CAppLibrary
{
    AppMenu m_Menu;
    CLibrary<sBook> m_Books;
    CLibrary<sPerson> m_Person;

    void clear();

    int exitApp(int iParam1, int iParam2);
    int popaMenu(int iParam1, int iParam2);
    int backMenu(int iParam1, int iParam2);
    int addItem(int iParam1, int iParam2);
    int viewItems(int iParam1, int iParam2);
    int findItem(int iParam1, int iParam2);
    int deleteItem(int iParam1, int iParam2);
    int editItem(int iParam1, int iParam2);
    int selectItem(int iParam1, int iParam2);

    int addPersonBook(int iParam1, int iParam2);
    int addBookPerson(int iParam1, int iParam2);
    int delPersonBook(int iParam1, int iParam2);
    int delBookPerson(int iParam1, int iParam2);

    int iMainRunPopap;
public:
    CAppLibrary();
    int AppRun();

    void ShowInfo();
    friend  AppMenu;
};

#endif // CAPPLIBRARY_H
