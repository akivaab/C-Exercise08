#include <string.h>
#include "miniz.h"

void unzip(const char *zipFile, const char *path)
{
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));

    auto status = mz_zip_reader_init_file(&zip_archive, zipFile, 0);
    if (!status)
    {
        //ERROR;
        //return files;
    }

    int fileCount = (int)mz_zip_reader_get_num_files(&zip_archive);
    if (fileCount == 0)
    {
        mz_zip_reader_end(&zip_archive);
        //return files;
    }
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, 0, &file_stat))
    {
        mz_zip_reader_end(&zip_archive);
        //return files;
    }
    // Get root folder
    //char *lastDir = "";
    //char *base = slash_path(get_path(file_stat.m_filename)); // path delim on end
    //char *base = strcat_s(path, sizeof(path), file_stat.m_filename);//
    //base = strcat_s(base, sizeof(base), "/"); // path delim on end//

    // Get and print information about each file in the archive.
    for (int i = 0; i < fileCount; i++)
    {
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat))
        {
            continue;
        }
        if (mz_zip_reader_is_file_a_directory(&zip_archive, i))
        {
            continue; // skip directories for now
        }
        char *fileName = strcat_s(path, sizeof(path), file_stat.m_filename); // make path relative
        //char *destFile = strcat_s(path, fileName, sizeof(path)); // make full dest path
        //auto newDir = get_path(fileName); // get the file's path
        /*if (fileName)
        {
            if (!os::dir::make(combine_path(path, newDir))) // creates the directory
            {

            }
        }*/
        mz_zip_reader_extract_to_file(&zip_archive, i, fileName, 0);
        /*if (mz_zip_reader_extract_to_file(&zip_archive, i, fileName, 0))
        {
            files.emplace_back(destFile);
        }*/
    }

    // Close the archive, freeing any resources it was using
    mz_zip_reader_end(&zip_archive);
}

