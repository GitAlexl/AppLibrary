#include "cdatafile.h"

CDataFile::CDataFile()
{
    strncpy(m_szFileName, "", sizeof(m_szFileName));
    //m_modeR = std::ios::binary|std::ios::in;
    //m_modeW = std::ios::binary|std::ios::out;
}
CDataFile::CDataFile(char* pszFileName)
{
    strncpy(m_szFileName, pszFileName, sizeof(m_szFileName));
}

CDataFile::~CDataFile()
{
    if(fileR.is_open()) fileR.close();
    if(fileW.is_open()) fileW.close();
}

bool CDataFile::ReadData(char* pData, int p_size)
{
    if(!fileR.is_open())
         fileR.open(m_szFileName,std::ios::binary|std::ios::in);

    if(!fileR)   return false;
    fileR.read(pData, p_size);
    if(fileR.eof()) return false;
    return true;
}

bool CDataFile::WriteData(char* pData, int p_size, int iSeekSet)
{
    if(!fileW.is_open())
    {
        fileW.open(m_szFileName, iSeekSet == -1 ? std::ios::binary|std::ios::out|std::ios::app : std::ios::binary|std::ios::out|std::ios::in|std::ios::ate); // app запись в конец файла
        if(-1 != iSeekSet)
            fileW.seekp(iSeekSet, std::ofstream::beg);
    }
    if(!fileW) return false;
    fileW.write(pData, p_size);
    return true;
}

int CDataFile::GetPoss()
{
    if(fileR.is_open()) return fileR.tellg();
    if(fileW.is_open()) return fileW.tellp();
    return -1;
}

void CDataFile::SetPos(int pos)
{
    if(fileR.is_open()) fileR.seekg(pos, std::ifstream::beg);
    if(fileW.is_open()) fileW.seekp(pos, std::ofstream::beg);

}
bool CDataFile::ClearFile()
{
    if(!fileW.is_open())
        fileW.open(m_szFileName, std::ios::binary|std::ios::in | std::ios::out | std::ios::trunc); //чистим файл
    if(!fileW) return false;

    fileW.close();
    return true;
}
