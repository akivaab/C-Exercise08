#include <stdlib.h>
#include "miniz.h"

int main(size_t argc, char *argv[])
{
    //if argv[1] ends with .zip:
        mz_zip_archive *zipFile = NULL;
        memset(zipFile, '0', sizeof(*zipFile));
        mz_bool initFile = mz_zip_reader_init_file(zipFile, argv[1], 0);
        if (!initFile)
        {
            //ERROR
            return 0;
        }
        char *newFolder = strtok_s(argv[1], ".", &newFolder);
        for (size_t index = 0; index < zipFile->m_total_files; ++index)
        {
            char *filename = strcat_s(newFolder, sizeof(*newFolder), ("/puppy%u", index));
            size_t numBytes = mz_zip_reader_get_filename(zipFile, index, filename, 0);
            mz_zip_reader_get_filename(zipFile, index, filename, numBytes);
            mz_zip_reader_extract_file_to_file(zipFile, argv[1], filename, 0);
        }

}
/*
std::vector<std::string> os::file::unzip(std::string const &zipFile, std::string const &path, std::string const &password)
{
    std::vector<std::string> files = {};
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));

    auto status = mz_zip_reader_init_file(&zip_archive, zipFile.c_str(), 0);
    if (!status) return files;
    int fileCount = (int)mz_zip_reader_get_num_files(&zip_archive);
    if (fileCount == 0)
    {
        mz_zip_reader_end(&zip_archive);
        return files;
    }
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, 0, &file_stat))
    {
        mz_zip_reader_end(&zip_archive);
        return files;
    }
    // Get root folder
    string lastDir = "";
    string base = slash_path(get_path(file_stat.m_filename)); // path delim on end

    // Get and print information about each file in the archive.
    for (int i = 0; i < fileCount; i++)
    {
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) continue;
        if (mz_zip_reader_is_file_a_directory(&zip_archive, i)) continue; // skip directories for now
        string fileName = relative_path(base, file_stat.m_filename); // make path relative
        string destFile = combine_path(path, fileName); // make full dest path
        auto newDir = get_path(fileName); // get the file's path
        if (newDir != lastDir)
        {
            if (!os::dir::make(combine_path(path, newDir))) // creates the directory
            {

            }
        }

        if (mz_zip_reader_extract_to_file(&zip_archive, i, destFile.c_str(), 0))
        {
            files.emplace_back(destFile);
        }
    }

    // Close the archive, freeing any resources it was using
    mz_zip_reader_end(&zip_archive);
    return files;
}
*/