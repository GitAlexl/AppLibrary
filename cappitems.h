#ifndef CAPPITEMS_H
#define CAPPITEMS_H
#include "define.h"


class sBaseElemet
{
    int m_iID;
public:
    sBaseElemet();
    sBaseElemet(int iID);
    sBaseElemet(sBaseElemet& sBaseElemet);
    void SetID(int iID); int GetID();
    bool	IsDelete();
    bool	SetDelete();

    virtual bool	CompareLike(sBaseElemet&) = 0;
    virtual void	Clear();
    virtual void	ShowInfo() = 0;
    virtual char* GetFileName() = 0;
    virtual bool FillItem(bool withCheckFild = true )= 0;
    virtual bool AddRelID(int iID) = 0;
    virtual bool DelRelID(int iID) = 0;
};


class sBook : public sBaseElemet
{
    char m_szName[256];
    char m_szAuthor[256];
    int m_iYear;
    int m_iPersonID;
public:
    void SetName(const char* pszName); char* GetName();
    void SetAuthor(const char* pszAuthor); char* GetAuthor();
    bool SetYear(int iYaer); int GetYear();
    bool AddRelID(int iID);
    bool DelRelID(int iID);

    sBook* GetPtr(){return this;};

    bool CompareLike(sBaseElemet&);
    void	Clear();
    void	ShowInfo();
    sBook();
    sBook(sBook &_Book);
    sBook(const char* szName, const char* szAuthor, int lYear, int iID = 0, int iPersonID = 0);
    char* GetFileName(){return "books.dat";}
    bool FillItem(bool withCheckFild = true );
};

class sPerson : public sBaseElemet
{
    char m_szFIO[256];
    char m_szAdress[256];
    int		m_BookID[20];
    void sortArrayBook();

public:
    void SetFIO(const char* pszFIO); char* GetFIO();
    void SetAdress(const char* pszAdres); char* GetAdress();
    bool AddRelID(int iID);
    bool DelRelID(int iID);

    sPerson* GetPtr(){return this;};

    bool CompareLike(sBaseElemet&);
    void	Clear();
    void	ShowInfo();
    void	ShowListBook();
    sPerson();
    sPerson(sPerson &_Book);
    sPerson(const char* szFIO, const char* szAdress, int iID = 0);
    char* GetFileName(){return "persons.dat";}
    bool FillItem(bool withCheckFild = true );
};

//typedef std::shared_ptr<sBook> prtBook;
template <class T>
class CLibrary
{
    T	m_SelectItem;
    char m_fileName[256];;
    int m_iMaxID;
    void initMaxId();

public:
    CLibrary();
    ~CLibrary();
    void ShowListItem();
    void ShowListItem(std::vector<std::shared_ptr<T> >&);

    bool Add();
    bool Find();
    bool Delete();
    bool Edit();
    bool SelectBook();

    int GetMaxID(); void SetMaxID(int iMaxId);
    void SetSelectItem(T&); bool GetSelectItem(T&); void ClearSelectItem();
    void ShowInfo();
    bool FindInFile(int iId, T&);
    bool UpdateItem(std::shared_ptr<T> ptrBookEdit);
    bool ClearFile();
};
#include "cappitems.hpp"

#endif // CAPPITEMS_H
