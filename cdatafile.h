#ifndef CDATAFILE_H
#define CDATAFILE_H


#include "define.h"


class CDataFile
{
    char m_szFileName[256];
    std::ifstream fileR; //(m_fileName,std::ios::binary|std::ios::in);
    std::ofstream fileW; //(m_fileName,std::ios::binary|std::ios::out);
public:
    CDataFile();
    CDataFile(char* pszFileName);
    ~CDataFile();
    bool ReadData(char* pData, int p_size);
    bool WriteData(char* pData, int p_size, int iSeekSet = -1);
    int GetPoss();  void SetPos(int);
    bool ClearFile();

};
#endif // CDATAFILE_H
