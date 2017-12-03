#include "capplibrary.h"

CAppLibrary::CAppLibrary(): m_Books()
{
    m_Menu.CreateMenu(this);
    iMainRunPopap = 0;
}


void CAppLibrary::clear()
{
    m_Books.ClearFile();
    m_Person.ClearFile();
}



int CAppLibrary::AppRun()
{
    m_Menu.Run();
    return 1;
}


 int CAppLibrary::exitApp(int iParam1, int iParam2)
 {
     clear();
     std::cout << "Goodbye!!!!" <<  std::endl;
     return -100;
 }
 int CAppLibrary::popaMenu(int iParam1, int iParam2)
 {
     iMainRunPopap = iParam2;
     return 10;
 }

 int CAppLibrary::backMenu(int iParam1, int iParam2)
 {
     m_Books.ClearSelectItem();
     m_Person.ClearSelectItem();
    return -10;
 }
 int CAppLibrary::addItem(int iParam1, int iParam2)
 {
    while(true)
    {
        system("cls");
        if(iMainRunPopap == 1) m_Books.Add();
        if(iMainRunPopap == 2) m_Person.Add();
        m_Books.ClearSelectItem();
        m_Person.ClearSelectItem();
        if(0 == MessageYesNo(TEXT_Q_CONTINUE_ADDING) )
            break;
    }
    return 1;
 }

 int CAppLibrary::viewItems(int iParam1, int iParam2)
 {
    system("cls");
    if(iMainRunPopap == 1)   { m_Books.ShowListItem();m_Menu.BuildMenu(100);}
    if(iMainRunPopap == 2)   { m_Person.ShowListItem();m_Menu.BuildMenu(200);}
    return 1;
 }

 int CAppLibrary::findItem(int iParam1, int iParam2)
 {
     system("cls");
     if(iMainRunPopap == 1) if(m_Books.Find())  m_Menu.BuildMenu(100);
     if(iMainRunPopap == 2) if(m_Person.Find())  m_Menu.BuildMenu(200);
     return 1;
 }

 int CAppLibrary::deleteItem(int iParam1, int iParam2)
 {
     if(iMainRunPopap == 1)
     {
         if(m_Books.Delete())		 MessageInfoWait("Book is delete!");
         m_Books.ClearSelectItem();
     }
     if(iMainRunPopap == 2)
     {
         if(m_Person.Delete())		 MessageInfoWait("Person is delete!");
         m_Person.ClearSelectItem();
     }

     return -10;
 }

 int CAppLibrary::editItem(int iParam1, int iParam2)
 {
     if(iMainRunPopap == 1)
     {
        if(m_Books.Edit())		 MessageInfoWait("Book is edit!");
        m_Books.ClearSelectItem();
     }
     if(iMainRunPopap == 2)
     {
         if(m_Person.Edit())		 MessageInfoWait("Person is edit!");
         m_Person.ClearSelectItem();
     }
     return -10;
 }
int CAppLibrary::selectItem(int iParam1, int iParam2)
{
    int iRetValue = -10;
    if(iMainRunPopap == 1 && m_Books.SelectBook())
    {
        iRetValue = m_Menu.BuildMenu(iParam2);
        m_Books.ClearSelectItem();
    }

    if(iMainRunPopap == 2 && m_Person.SelectBook())
    {
        iRetValue = m_Menu.BuildMenu(iParam2);
        m_Person.ClearSelectItem();
    }
     return -13;

 }
int CAppLibrary::addPersonBook(int iParam1, int iParam2)
{

    m_Person.ShowListItem();
    int iID = MessageSelectItem();

    sPerson recP;
    sBook recB;
    m_Person.FindInFile( iID, recP);

    m_Books.GetSelectItem(recB);
    m_Person.GetSelectItem(recP);

    if(MessageYesNo("Add book to the person?") == 1)
    {
        std::shared_ptr<sBook> ptrEditBook( new sBook (recB));
        ptrEditBook->AddRelID(recP.GetID());
        m_Books.UpdateItem(ptrEditBook);

        std::shared_ptr<sPerson> ptrEditPerson( new sPerson(recP));
        ptrEditPerson->AddRelID(recB.GetID());
        m_Person.UpdateItem(ptrEditPerson);
    }
    return -13;
}

int CAppLibrary::delPersonBook(int iParam1, int iParam2)
{
    sPerson recP;
    sBook recB;
    m_Books.GetSelectItem(recB);

    if(MessageYesNo("Delete book from person(y/n)?") == 1)
    {
        std::shared_ptr<sBook> ptrEditBook( new sBook (recB));
        ptrEditBook->DelRelID(0);
        m_Books.UpdateItem(ptrEditBook);

        std::shared_ptr<sPerson> ptrEditPerson( new sPerson(recP));
        ptrEditPerson->DelRelID(recB.GetID());
        m_Person.UpdateItem(ptrEditPerson);
    }
    return -13;
}

int CAppLibrary::delBookPerson(int iParam1, int iParam2)
{
    sPerson recP;
    sBook recB;

    m_Person.GetSelectItem(recP);
    recP.ShowListBook();

    int iSelID  = MessageSelectItem();

    m_Books.FindInFile(iSelID, recB);

    if(MessageYesNo("Delete book from person(y/n)?") == 1)
    {
        std::shared_ptr<sBook> ptrEditBook( new sBook (recB));
        ptrEditBook->DelRelID(0);
        m_Books.UpdateItem(ptrEditBook);

        std::shared_ptr<sPerson> ptrEditPerson( new sPerson(recP));
        ptrEditPerson->DelRelID(recB.GetID());
        m_Person.UpdateItem(ptrEditPerson);
    }
    return -13;
}
int CAppLibrary::addBookPerson(int iParam1, int iParam2)
{
    m_Books.ShowListItem();
    int iID = MessageSelectItem();

    sBook recB;
    sPerson recP;
    m_Books.FindInFile( iID, recB);

    m_Books.GetSelectItem(recB);
    m_Person.GetSelectItem(recP);

    if(MessageYesNo("Add book to the person?") == 1)
    {
        std::shared_ptr<sBook> ptrEditBook( new sBook (recB));
        ptrEditBook->AddRelID(recP.GetID());
        m_Books.UpdateItem(ptrEditBook);

        std::shared_ptr<sPerson> ptrEditPerson( new sPerson(recP));
        ptrEditPerson->AddRelID(recB.GetID());
        m_Person.UpdateItem(ptrEditPerson);
    }
    return -13;


    return -13;
}

void CAppLibrary::ShowInfo()
{
    if(iMainRunPopap == 1) m_Books.ShowInfo();
    if(iMainRunPopap == 2) m_Person.ShowInfo();
}
