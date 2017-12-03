#include "cappitems.h"

#include "cappitems.h"


sBaseElemet::sBaseElemet(){}
sBaseElemet::sBaseElemet(int iId){Clear(); m_iID = iId;}
sBaseElemet::sBaseElemet(sBaseElemet& sBaseElemet){Clear(); m_iID = sBaseElemet.m_iID;}
void	sBaseElemet::Clear(){m_iID = 0;}
void	sBaseElemet::SetID(int iID){m_iID = iID;}
int		sBaseElemet::GetID(){return m_iID;}
//sBaseElemet* sBaseElemet::GetPtr(){return this;};
bool	sBaseElemet::IsDelete(){return m_iID < 0;}
bool	sBaseElemet::SetDelete(){return m_iID *= -1; return  m_iID < 0;}

//****************************************************************************************************************************************
sBook::sBook():sBaseElemet(){Clear();}
sBook::sBook(const char* szName, const char* szAuthor, int lYear, int iID, int iPersonID) :sBaseElemet(iID), m_iYear(lYear), m_iPersonID(iPersonID)
{
      strncpy(m_szName, szName, sizeof(m_szName));
      strncpy(m_szAuthor, szAuthor, sizeof(m_szAuthor));
}
sBook::sBook(sBook& _Book):sBaseElemet(_Book)
{
    m_iYear = _Book.m_iYear;	m_iPersonID = _Book.m_iPersonID;
    strncpy(m_szName, _Book.m_szName, sizeof(m_szName));
    strncpy(m_szAuthor, _Book.m_szAuthor, sizeof(m_szAuthor));
}
void	sBook::Clear()
{
    sBaseElemet::Clear();
    m_iYear = m_iPersonID = 0;
    m_szName[0] = m_szAuthor[0] = 0x00;
}
void sBook::SetName(const char* pszName)	{strncpy(m_szName, pszName, sizeof(m_szName));}             char* sBook::GetName(){ return m_szName;}
void sBook::SetAuthor(const char* pszAuthor){strncpy(m_szAuthor, pszAuthor, sizeof(m_szAuthor));}		char* sBook::GetAuthor(){return m_szAuthor;}
bool sBook::SetYear(int iYear)
{
    if(iYear < 1800  || iYear > 2200) return false;
    m_iYear = iYear;
    return true;
}
int sBook::GetYear(){return m_iYear;}
bool sBook::AddRelID(int iPersonID){m_iPersonID = iPersonID; return true;}
bool sBook::DelRelID(int iPersonID){m_iPersonID = 0;return true;}
void sBook::ShowInfo()
{
    std::cout << "ID: " << GetID() << "; ";
    std::cout << "Title: " << m_szName << "; ";
    std::cout << "Author: " << m_szAuthor << "; ";
    std::cout << "Year: " << m_iYear << "; ";
    char szText[256] = "";
    if(GetNamePersonById(GetID(),szText))
        std::cout << "PersonID: " << szText;
    std::cout << std::endl;
}


bool sBook::CompareLike(sBaseElemet& RecCompareBase)
{
    sBook* pRecCompare = (reinterpret_cast<sBook*>(&RecCompareBase));
    if(pRecCompare->GetID() != 0)			if(GetID() != pRecCompare->GetID())								return false;
    if(pRecCompare->m_iPersonID != 0)		if(m_iPersonID != pRecCompare->m_iPersonID)					return false;
    if(pRecCompare->m_iYear != 0)			if(m_iYear != pRecCompare->m_iYear)							return false;
    if(strlen(pRecCompare->m_szName) > 1)
        if(!strstr(m_szName, pRecCompare->m_szName))
            return false;
    if(strlen(pRecCompare->m_szAuthor)> 1)	if(!strstr(pRecCompare->m_szAuthor,m_szAuthor))	return false;
    return true;
}

bool sBook::FillItem(bool withCheckFild)
{
    char szText[256] = "";
    std::string str;
    try
    {
        if(withCheckFild)
        {
            std::cout << "Book title :";	std::cin >> szText;	SetName(szText);
            std::cout << "Book author :";	std::cin >> szText;	SetAuthor(szText);
            do
            {
                std::cout << "Book year :";
                std::cin >> szText;
                if(SetYear(atoi(szText))) break;
                else
                    std::cout << "Input error year!" << std::endl;
            } while (true);
        }
        else
        {
            std::cout << "Book title :";	std::cin >> szText;	SetName(szText);
            std::cout << "Book author :";	std::cin >> szText;	SetAuthor(szText);
            std::cout << "Book year :";	std::cin >> szText;	SetYear(atoi(szText));
        }
    }
    catch(...) {return false;}
    return true;
}

//***********************************************************************************************************************


sPerson::sPerson():sBaseElemet(){Clear();}
sPerson::sPerson(const char* szFIO, const char* szAdres,int iID) :sBaseElemet(iID)
{
      strncpy(m_szFIO, m_szFIO, sizeof(m_szFIO));
      strncpy(m_szAdress, m_szAdress, sizeof(m_szAdress));
      for(int i = 0; i < MAX_COUNT_REL_BOOK; i++) m_BookID[i] = 0;
}
sPerson::sPerson(sPerson& _Person):sBaseElemet(_Person)
{
    strncpy(m_szFIO, _Person.m_szFIO, sizeof(m_szFIO));
    strncpy(m_szAdress, _Person.m_szAdress, sizeof(m_szAdress));
     for(int i = 0; i < MAX_COUNT_REL_BOOK; i++) m_BookID[i] =  _Person.m_BookID[i];

}
void	sPerson::Clear()
{
    sBaseElemet::Clear();
    m_szFIO[0] = m_szAdress[0] = 0x00;
    for(int i = 0; i < MAX_COUNT_REL_BOOK; i++) m_BookID[i] = 0;
}
void sPerson::SetFIO(const char* pszFIO)	{strncpy(m_szFIO, pszFIO, sizeof(m_szFIO));}             char* sPerson::GetFIO(){ return m_szFIO;}
void sPerson::SetAdress(const char* pszAdress){strncpy(m_szAdress, pszAdress, sizeof(m_szAdress));}		char* sPerson::GetAdress(){return m_szAdress;}
void sPerson::ShowInfo()
{
    std::cout << "ID: " << GetID() << "; ";
    std::cout << "FIO: " << m_szFIO << "; ";
    std::cout << "Adress: " << m_szAdress << "; ";
    std::cout << "Books: " ;

    for (int iIndex = 0; iIndex < MAX_COUNT_REL_BOOK; iIndex++)
    {
        if(m_BookID[iIndex] != 0)
        {
            char szText[256] = "";
            if( GetNameBookById(m_BookID[iIndex], szText))
                std::cout << szText << " " ;
        }
    }
    std::cout << std::endl;
}
void sPerson::ShowListBook()
{
    for (int iIndex = 0; iIndex < MAX_COUNT_REL_BOOK; iIndex++)
    {
        if(m_BookID[iIndex] != 0)
        {
            char szText[256] = "";
            if( GetNameBookById(m_BookID[iIndex], szText))
                std::cout << m_BookID[iIndex] << " "  << szText << std::endl ;
        }
    }
}


bool sPerson::CompareLike(sBaseElemet& RecCompareBase)
{
    sPerson* pRecCompare = (reinterpret_cast<sPerson*>(&RecCompareBase));
    if(pRecCompare->GetID() != 0)			if(GetID() != pRecCompare->GetID())				return false;
    if(strlen(pRecCompare->m_szFIO) > 1)	if(!strstr(m_szFIO, pRecCompare->m_szFIO))		return false;
    if(strlen(pRecCompare->m_szAdress) > 1)	if(!strstr(pRecCompare->m_szAdress,m_szAdress))	return false;
    return true;
}

bool sPerson::FillItem(bool withCheckFild)
{
    char szText[256] = "";
    std::string str;
    try
    {
        std::cout << "FIO :";		std::cin >> szText;	SetFIO(szText);
        std::cout << "Adress :";	std::cin >> szText;	SetAdress(szText);
    }
    catch(...) {return false;}
    return true;
}

void sPerson::sortArrayBook()
{
    for(int i = 0; i < MAX_COUNT_REL_BOOK; i++)
        for(int i1 = 0; i1 < MAX_COUNT_REL_BOOK -1; i1++)
            if( m_BookID[i1] > m_BookID[i1+1])
            { int iTemp =  m_BookID[i1]; m_BookID[i1] = m_BookID[i1+1]; m_BookID[i1+1] = iTemp;}
}

bool sPerson::AddRelID(int iBookID)
{
    for(int iIndex = 0; iIndex < MAX_COUNT_REL_BOOK; iIndex++)
        if(m_BookID[iIndex] == 0 ||  m_BookID[iIndex] == iBookID)
        {
            m_BookID[iIndex] = iBookID;
            sortArrayBook();
            return true;
        }
    return false;
}

bool sPerson::DelRelID(int iBookID)
{
    for(int iIndex = 0; iIndex < MAX_COUNT_REL_BOOK; iIndex++)
        if(m_BookID[iIndex] == iBookID)
        {
            m_BookID[iIndex] = 0;
            sortArrayBook();
            return true;
        }
        return false;
}

bool DelBookID(int iBookID);
