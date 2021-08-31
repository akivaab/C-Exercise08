#include <stdlib.h>
#include "miniz.h"

int main(size_t argc, char *argv[])
{
    //if argv[1] ends with .zip:
        mz_zip_archive zipFile;
        memset(&zipFile, 0, sizeof(zipFile));
        mz_bool initFile = mz_zip_reader_init_file(&zipFile, argv[1], 0);
        if (!initFile)
        {
            //ERROR
            return 0;
        }
        char *newFolder = strtok_s(argv[1], ".", &newFolder);
        for (size_t index = 0; index < zipFile.m_total_files; ++index)
        {
            char *filename = strcat_s(newFolder, sizeof(*newFolder), ("/puppy%u", index));
            size_t numBytes = mz_zip_reader_get_filename(&zipFile, index, filename, 0);
            mz_zip_reader_get_filename(&zipFile, index, filename, numBytes);
            mz_zip_reader_extract_file_to_file(&zipFile, argv[1], filename, 0);
        }

}
