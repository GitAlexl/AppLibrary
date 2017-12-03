template<class T>
CLibrary<T>::CLibrary()
{
    strcpy(m_fileName, m_SelectItem.GetFileName());
    initMaxId();
}
template<class T>
CLibrary<T>::~CLibrary(){}
template<class T>
int CLibrary<T>::GetMaxID(){return m_iMaxID;}
template<class T>
void CLibrary<T>::SetMaxID(int iMaxId) {m_iMaxID  = iMaxId;}
template<class T>
void CLibrary<T>::initMaxId()
{
    m_iMaxID = 0;
    CDataFile fileR(m_fileName);
    T recRead;
    while(true)
    {
        if(fileR.ReadData(reinterpret_cast<char*>(&recRead),sizeof(T)))
        {
            if(m_iMaxID < recRead.GetID())
                m_iMaxID =  recRead.GetID();
        }
        else
            break;
    }
}
template<class T>
void CLibrary<T>::SetSelectItem(T& recSet) { m_SelectItem = recSet;}
template<class T>
bool CLibrary<T>::GetSelectItem(T& recGet)
{
    if(m_SelectItem.GetID() != 0) recGet = m_SelectItem;
    return m_SelectItem.GetID() != 0;
};
template<class T>
void CLibrary<T>::ClearSelectItem(){m_SelectItem.Clear();}

template<class T>
void CLibrary<T>::ShowListItem()
{
    system("cls");
    CDataFile fileR(m_fileName);
    T recRead;
    int coutnLineShow = 0;
    while(true)
    {
        if(fileR.ReadData(reinterpret_cast<char*>(&recRead),sizeof(T)))
        {
            if(recRead.GetID() > 0)
            {
                recRead.ShowInfo();
                coutnLineShow++;
                if(coutnLineShow == COUNT_SHOW_LINE)
                {
                    if(0 == MessageYesNo(TEXT_Q_CONTINUE_OUTPUN_RESULT))
                        break;
                    else
                        coutnLineShow = 0;
                }
            }
        }
        else
            break;
    }
    //MessageInfoWait(TEXT_I_CONTINUE);
    std::cout << std::endl;
}

template<class T>
void CLibrary<T>::ShowListItem(std::vector<std::shared_ptr<T>>& vPtr)
{
    system("cls");
    int coutnLineShow = 0;
    for(auto itShow : vPtr )//    for(int iIndex = 0; iIndex < vPtr.size(); iIndex++)
    {
        itShow->GetPtr()->ShowInfo();
        coutnLineShow++;
        if(coutnLineShow == COUNT_SHOW_LINE)
        {
            if(0 == MessageYesNo(TEXT_Q_CONTINUE_OUTPUN_RESULT))
                break;
            else
                coutnLineShow = 0;
        }
    }
    std::cout << std::endl;
    MessageInfoWait(TEXT_I_CONTINUE);
}
template<class T>
bool CLibrary<T>::FindInFile(int iId, T& itemFind)
{
    T recRead;
    CDataFile fileR(m_fileName);
    while(true)
    {
        if(fileR.ReadData(reinterpret_cast<char*>(&recRead),sizeof(T)))
        {
            if(recRead.GetID() == iId)
            {
                SetSelectItem(recRead);
                itemFind = recRead;
                return true;
            }
        }
        else
            break;
    }
    return false;
}

template<class T>
bool CLibrary<T>::Add()
{
    system("cls");
    std::shared_ptr<T> ptrNewItem( new T());

    if(ptrNewItem->FillItem())
    {
        ptrNewItem->SetID(GetMaxID()+1);
        CDataFile fileR(m_fileName);
        if(fileR.WriteData(reinterpret_cast<char*>(ptrNewItem->GetPtr()), sizeof(T)))
        {
            m_iMaxID++;
            return true;
        }
    }
    return false;
}

template<class T>
bool CLibrary<T>::Find()
{
    system("cls");
    T	recRead;
    std::shared_ptr<T> ptrFindItem( new T());
    std::vector<std::shared_ptr<T>> vFind;

    if(!ptrFindItem->FillItem(false)) return false;
    CDataFile fileR(m_fileName);

    while(true)
    {
        if(fileR.ReadData(reinterpret_cast<char*>(&recRead),sizeof(T)))
        {
            if(recRead.CompareLike(*(ptrFindItem->GetPtr())))
            {
                std::shared_ptr<T> ptrFindItem( new T(recRead));
                vFind.push_back(ptrFindItem);
            }
        }
        else
            break;
    }
    if(vFind.size() != 0)
    {
        ShowListItem(vFind);
        return true;
    }

    MessageInfoWait("Item not found!");
    return false;
}
template<class T>
bool CLibrary<T>::Delete()
{
    system("cls");
    T recDel;
    if(GetSelectItem(recDel))
    {
        recDel.ShowInfo();
        if(MessageYesNo("Delete select item(y/n)? "))
        {
            recDel.SetDelete();
            std::shared_ptr<T> ptrDelItem( new T (recDel));
            if(UpdateItem(ptrDelItem))
                return true;
        }
    }
    return false;
}
template<class T>
bool CLibrary<T>::Edit()
{
    system("cls");
    T  recEdit;
    if(GetSelectItem(recEdit))
    {
        recEdit.ShowInfo();
        if(MessageYesNo("Edit select item(y/n)? "))
        {
            system("cls");
            std::shared_ptr<T> ptrNewItem( new T (recEdit));
            if(ptrNewItem->FillItem())
                if(UpdateItem(ptrNewItem) )
                    return true;
        }
    }
    return false;
}
template<class T>
bool CLibrary<T>::UpdateItem(std::shared_ptr<T> ptrItemEdit)
{
    int iSeek = -1;
    {
        CDataFile fileR(m_fileName);
        T  recRead;
        while(true)
        {
            if(fileR.ReadData(reinterpret_cast<char*>(&recRead),sizeof(T )))
            {
                if(recRead.GetID() == ptrItemEdit->GetID() || recRead.GetID() == (ptrItemEdit->GetID()*-1) )
                {
                    iSeek = fileR.GetPoss();break;
                }
            }
            else
                break;
        }

        if(iSeek != -1)
        {
            iSeek -= sizeof(T);
            if(iSeek >= 0)
            {
                CDataFile fileR(m_fileName);
                fileR.SetPos(iSeek);
                fileR.WriteData(reinterpret_cast<char*>(ptrItemEdit->GetPtr()), sizeof(T), iSeek);
                return true;
            }
        }
    }
    return false;
}
template<class T>
bool CLibrary<T>::SelectBook()
{
    T recSelect;
    int iID = MessageSelectItem();
    if(iID != 0 && FindInFile(iID,recSelect))
    {
        return true;
    }
    return false;
}
template<class T>
void CLibrary<T>::ShowInfo()
{
    T recCurr;
    if(GetSelectItem(recCurr))
    {
        std::cout << "Select current item : ";
        recCurr.ShowInfo();
    }
}
template<class T>
bool CLibrary<T>::ClearFile()
{
    std::vector<std::shared_ptr<T> > vRaed;

    {
        CDataFile fileR(m_fileName);
        T  recRead;
        while(true)
        {
            if(fileR.ReadData(reinterpret_cast<char*>(&recRead),sizeof(T )))
            {
                if(recRead.GetID() > 0)
                {
                    std::shared_ptr<T> ptrNewItem (new T(recRead));
                    vRaed.push_back(ptrNewItem);
                }
            }
            else
                break;
        }
    }

    CDataFile fileW(m_fileName);
    fileW.ClearFile();


    for(auto it : vRaed)
        fileW.WriteData(reinterpret_cast<char*>(it->GetPtr()), sizeof(T)) ;
    return true;
}
