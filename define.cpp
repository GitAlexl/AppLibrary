#include "define.h"
#include <conio.h>
#include "cappitems.h"

int MessageSelectMenuItem(int iMaxCount)
{
    char szText[256] = "";
    int iReturn = 0;
    while(true)
    {
        std::cout << "Select the menu item: ";
        std::cin >> szText;
        iReturn = atoi(szText);
        if(iReturn <= iMaxCount && iReturn != 0)
            return iReturn;
        std::cout << "Menu selection error!!!" << std::endl;

    }
    return iReturn;
}
int MessageSelectItem()
{
    char szText[256] = "";
    int iReturn = 0;
    while(true)
    {
        std::cout << "Select the item: ";
        std::cin >> szText;
        iReturn = atoi(szText);
        if(iReturn != 0)
            return iReturn;
        std::cout << "Selection error!!!" << std::endl;

    }
    return iReturn;
}

int MessageInfo(char *pszText)
{
    std::cout << pszText << std::endl;
    return 1;
}
int MessageInfoWait(char *pszText)
{
    char chSelect = 0;
    std::cout << pszText;
    getch();
    std::cout << std::endl;
    return 1;
}


int MessageYesNo(char *pszText)
{
    char chSelect = 0;
    while(true)
    {
        std::cout << pszText;
        std::cin >> chSelect;
        if(chSelect == 'y' || chSelect == 'Y') return 1;
        if(chSelect == 'n' || chSelect == 'N') return 0;
    }
    return 0;
}



bool GetNameBookById(int iID , char* pszTextOut)
{
    sBook recR;
    CDataFile fileR(recR.GetFileName());
    int coutnLineShow = 0;
    while(true)
    {
        if(fileR.ReadData(reinterpret_cast<char*>(&recR),sizeof(recR)))
        {
            if(recR.GetID()  == iID)
            {
                strncpy(pszTextOut, recR.GetName(), sizeof(pszTextOut));
                return true;
            }
        }
        else
            break;
    }
    return false;
}


bool GetNamePersonById(int iID , char* pszTextOut)
{
    sPerson recR;
    CDataFile fileR(recR.GetFileName());
    int coutnLineShow = 0;
    while(true)
    {
        if(fileR.ReadData(reinterpret_cast<char*>(&recR),sizeof(recR)))
        {
            if(recR.GetID()  == iID)
            {
                strncpy(pszTextOut, recR.GetFIO(), sizeof(pszTextOut));
                return true;
            }
        }
        else
            break;
    }
    return false;
}
