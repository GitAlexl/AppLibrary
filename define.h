#ifndef DEFINE_H
#define DEFINE_H

#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include <fstream>
#include "cdatafile.h"


#define COUNT_SHOW_LINE 10
#define TEXT_Q_CONTINUE "Continue(y/n)? "
#define TEXT_Q_CONTINUE_OUTPUN_RESULT "To continue the output of the results? (y/n)? "
#define TEXT_Q_CONTINUE_ADDING "Continue adding? (y/n)? "
#define TEXT_Q_CONTINUE_ADDING "Continue adding? (y/n)? "
#define TEXT_I_CONTINUE "Press any key to to continue...."
#define  MAX_COUNT_REL_BOOK 20


int MessageSelectMenuItem(int iMaxCount);
int MessageSelectItem();
int MessageYesNo(char *pszText);
int MessageInfo(char *pszText);
int MessageInfoWait(char *pszText);


bool GetNameBookById(int iID , char* pszTextOut);
bool GetNamePersonById(int iID , char* pszTextOut);

#endif // DEFINE_H
