#include "head/wf.h"

namespace workFile
{

    bool find = false;
    std::string path = "";

    std::uint32_t val = 0;
#if defined _WIN32
    void FindFiles(std::string folderName, std::string &fileName)
    {
        WIN32_FIND_DATA FileData;
        std::string folderNameWithSt = folderName + "*";
        HANDLE FirstFile = FindFirstFile(folderNameWithSt.c_str(), &FileData);
        if (FirstFile != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (strcmp(FileData.cFileName, ".") != 0 && strcmp(FileData.cFileName, "..") != 0)
                {
                    if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    {
                        if (find)
                            return;
                        std::string NewPath = folderName + FileData.cFileName + "\\";
                        ++val;
                        uint32_t i = 0;
                        uint32_t val_tmp = val;
                        for (; val_tmp > 0; i++)
                        {
                            val_tmp /= 10;
                        }
                        FindFiles(NewPath, fileName);
                    }
                    else
                    {
                        if (FileData.cFileName == fileName)
                        {
                            find = true;
                            path = folderName;
                            return;
                        }
                    }
                }
            } while (FindNextFile(FirstFile, &FileData));
        }
    }
#endif
    std::string getPath()
    {
        std::string tmp = path;
        return tmp;
    }
    void cls()
    {
        path.clear();
        return;
    }
}
