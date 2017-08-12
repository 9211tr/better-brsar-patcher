//
//  Better Wii BRSTM BRSAR Patcher v1.0.0.
//  A better utility for patching BRSAR files (can patch w/ BRSTMs up to 4GB)!
//  Copyright © 2017 9211tr.
//
//  Better Wii BRSTM BRSAR Patcher is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Better Wii BRSTM BRSAR Patcher is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Better Wii BRSTM BRSAR Patcher. If not, see: http://www.gnu.org/licenses/
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool charWhiteSpace(char c)
{
    if (c == ' ' || (c >= '\x09' && c <= '\x0D') || c == '\xA0' || c == '\x85')
        return true;

    return false;
}
bool stringWhiteSpaceOrNull(std::string str, bool checkIfNullToo = false)
{
    if (checkIfNullToo && str == "") return true;
    for (unsigned int ui = 0; ui < str.length(); ui++)
         if (!charWhiteSpace(str.at(ui))) return false;

    return true;
}


std::string stringReplace(std::string str, std::string partToReplace, std::string replaceWith)
{
    for (unsigned int ui = 0; (ui = str.find(partToReplace, ui)) != std::string::npos; ui += replaceWith.length())
         str.replace(ui, partToReplace.length(), replaceWith);

    return str;
}


enum EndianType { ERROR = -1, BIG, LITTLE };
EndianType osEndian()
{
    unsigned short v = 0xBBAB;
    return (CHAR_BIT != 8 || sizeof(unsigned short) != 2 ? EndianType::ERROR : *(unsigned char *)&v == 0xBB && *((unsigned char *)&v+1) == 0xAB ? EndianType::BIG : *(unsigned char *)&v == 0xAB && *((unsigned char *)&v+1) == 0xBB ? EndianType::LITTLE : EndianType::ERROR);
}


void byteArrayReverse(unsigned char *array, int length)
{
    unsigned char *uc = array+length-1;
    while (array < uc)
    {
           unsigned char swap = *array;
           *array++ = *uc;
           *uc-- = swap;
    }
}


class BRSARPatchingList
{
    private:
       class BRSTMList
       {
           public:
              std::string name;
              std::string description;
              unsigned int brsarFileOffset;

              void free() { brsarFileOffset = 0x00000000; name = description = ""; }
       };
       std::vector<BRSTMList> list;

    public:
       std::string gameName;
       std::string patchAuthorName;
       std::string patchAuthorContactInfo;

       void addBRSTM(unsigned int BRSARFileOffset, std::string BRSTMName, std::string BRSTMDescription)
       {
           BRSTMList bl;
           bl.brsarFileOffset = BRSARFileOffset;
           bl.name = BRSTMName;
           bl.description = BRSTMDescription;
           list.push_back(bl);
           bl.free();
       }

       unsigned int brstmCount() { return list.size(); }
       BRSTMList getbrstmInfo(unsigned int index) { return list.at(index); }
       void free() { gameName = patchAuthorName = patchAuthorContactInfo = ""; for (unsigned int ui = 0; ui < list.size(); list.at(ui).free(), ui++); std::vector<BRSTMList>().swap(list); }
};


std::fstream fs;
BRSARPatchingList bpl;
std::string holder = "";

int main(int argc, char *argv[])
{
    // Print the program's text banner.
    std::cout << "\n\n\nBetter Wii BRSTM BRSAR Patcher v1.0.0.\nA better utility for patching BRSAR files (can patch w/ BRSTMs up to 4GB)!\nBy 9211tr." << std::endl << std::endl << std::endl;

    // Necessary Variables.
    unsigned int entryNum = 0;
    bool *optionsChecked = new bool[4]();
    std::string brsarPatchName = "DEFAULT.BPTH", brsarFileName = "", brstmFileName = "", infoTXTfilename = "";

    if (argc < 2)
    {
        std::cout << "Please see the README.TXT file for\nmore information on the command options and how to use this program.";
        goto immediateExit;
    }
    else
    {
        if (!_stricmp(argv[1], "-b") || !_stricmp(argv[1], "-i") || !_stricmp(argv[1], "-d") || !_stricmp(argv[1], "-q"))
            goto skipBRSARpatchName;

        // Process command options.
        brsarPatchName = argv[1];
        skipBRSARpatchName:
        unsigned int nextOptionIndex = 1+!strcmp(brsarPatchName.c_str(), argv[1]);
        for (int i = nextOptionIndex; i < argc; i++)
        {
             //
             // "<unknown>" (error message) option.
             //
             if (nextOptionIndex >= argc) break;
             if (_stricmp(argv[nextOptionIndex], "-b") && _stricmp(argv[nextOptionIndex], "-i") && _stricmp(argv[nextOptionIndex], "-d") && _stricmp(argv[nextOptionIndex], "-q"))
             {
                 std::cerr << "ERROR: Unknown option, '" << argv[nextOptionIndex] << "'.";
                 goto immediateExit;
             }
             //
             // "-b" (BRSAR input file) option.
             //
             else
             if (!optionsChecked[0] && !_stricmp(argv[i], "-b"))
             {
                 optionsChecked[0] = true;
                 try
                 {
                     if ((i+1) < argc)
                     {
                         brsarFileName = argv[i+1];
                         if (!_stricmp(argv[i+1], "-b") || !_stricmp(argv[i+1], "-i") || !_stricmp(argv[i+1], "-d") || !_stricmp(argv[i+1], "-q"))
                             throw std::exception("");
                     }
                     else
                         throw std::exception("");

                     nextOptionIndex = i+1+1;
                 }
                 catch (std::exception)
                 {
                     std::cerr << "ERROR: Please specify the BRSAR filename.";
                     goto immediateExit;
                 }
             }
             //
             // "-i" (BRSAR patch file info) option.
             //
             else
             if (!optionsChecked[1] && !_stricmp(argv[1+!strcmp(brsarPatchName.c_str(), argv[1])], "-i"))
             {
                 optionsChecked[1] = true;
                 nextOptionIndex = 1+!strcmp(brsarPatchName.c_str(), argv[1])+1;
                 break;
             }
             //
             // "-d" (direct BRSTM patch) option.
             //
             else
             if (!optionsChecked[2] && !_stricmp(argv[i], "-d"))
             {
                 optionsChecked[2] = true;
                 try
                 {
                     if ((i+1) < argc)
                     {
                         if (!_stricmp(argv[i+1], "-b") || !_stricmp(argv[i+1], "-i") || !_stricmp(argv[i+1], "-d") || !_stricmp(argv[i+1], "-q"))
                             throw std::exception("");

                         unsigned int ui = strlen(argv[i+1]);
                         for (; ui >= 0; ui--)
                              if (argv[i+1][ui] == ' ') break;

                         entryNum = std::stoi(((std::string)argv[i+1]).substr(0, ui));
                         brstmFileName = ((std::string)argv[i+1]).substr(ui+1, strlen(argv[i+1]));
                     }
                     else
                         throw std::exception("");

                     nextOptionIndex = i+1+1;
                 }
                 catch (std::exception)
                 {
                     std::cerr << "ERROR: Please specify the patch entry number and BRSTM filename.";
                     goto immediateExit;
                 }
             }
             //
             // "-q" (quiet mode) option.
             //
             else
             if (!optionsChecked[3] && !_stricmp(argv[i], "-q"))
             {
                 optionsChecked[3] = true;
                 nextOptionIndex = i+1;
             }
        }
    }

    // Quiet mode (-q option) is not permitted if we're not doing a direct BRSTM patch.
    if (!optionsChecked[2] && optionsChecked[3])
    {
        std::cerr << "ERROR: Quiet mode is not permitted unless if doing direct BRSTM patch.";
        goto immediateExit;
    }


    // Open Patch File (if we failed to open it, exit with error).
    fs.open(brsarPatchName, std::ios::in | std::ios::binary);
    if (!fs)
    {
        std::cerr << "ERROR: Cannot open BRSAR patch file, \"" << brsarPatchName << "\".";
        goto immediateExit;
    }

    // Check Patch File Header Identifier. If it's not "Better Wii BRSTM BRSAR Patcher File:", exit with error.
    // The header is not case sensitive.
    std::getline(fs, holder);

    // Remove "\r" (carriage return byte) if line feed format is CR+LF.
    holder = (holder.substr(holder.length() - 1, 1) == "\r" ? holder.substr(0, holder.length() - 1) : holder);
    if (_stricmp(holder.c_str(), "Better Wii BRSTM BRSAR Patcher File:"))
    {
        fs.close();
        std::cerr << "ERROR: BRSAR patch file is invalid.";
        goto immediateExit;
    }

    // Get Wii Game Name.
    bool foundGameName = false, foundPatchAuthorName = false, foundPatchAuthorContactInfo = false;
    while (!foundGameName && std::getline(fs, holder))
    {
           // Remove "\r" (carriage return byte) if line feed format is CR+LF.
           holder = (holder.substr(holder.length() - 1, 1) == "\r" ? holder.substr(0, holder.length() - 1) : holder);

           if (!stringWhiteSpaceOrNull(stringReplace(holder, "\\n", "\n"), true))
           {
               bpl.gameName = stringReplace(holder, "\\n", "\n");
               foundGameName = true;
           }
    }

    // Get Patch File Author Name.
    while (!foundPatchAuthorName && std::getline(fs, holder))
    {
           // Remove "\r" (carriage return byte) if line feed format is CR+LF.
           holder = (holder.substr(holder.length() - 1, 1) == "\r" ? holder.substr(0, holder.length() - 1) : holder);

           if (stringReplace(holder, "\\n", "\n") != "")
           {
               bpl.patchAuthorName = (stringWhiteSpaceOrNull(stringReplace(holder, "\\n", "\n")) ? "" : stringReplace(holder, "\\n", "\n"));
               foundPatchAuthorName = true;
           }
    }

    // Get Patch File Author Contact Information.
    while (!foundPatchAuthorContactInfo && std::getline(fs, holder))
    {
           // Remove "\r" (carriage return byte) if line feed format is CR+LF.
           holder = (holder.substr(holder.length() - 1, 1) == "\r" ? holder.substr(0, holder.length() - 1) : holder);

           if (stringReplace(holder, "\\n", "\n") != "")
           {
               bpl.patchAuthorContactInfo = (stringWhiteSpaceOrNull(stringReplace(holder, "\\n", "\n")) ? "" : stringReplace(holder, "\\n", "\n"));
               foundPatchAuthorContactInfo = true;
           }
    }

    // Get Every BRSTM Track List Entry.
    try
    {
        unsigned int offset = 0;   // BRSAR BRSTM entry offset.
        bool listEntryInfoFound = false;
        std::string name = "", description = "";   // BRSTM(s) Name/Description.
        while (std::getline(fs, holder))
        {
               // Remove "\r" (carriage return byte) if line feed format is CR+LF.
               holder = (holder.substr(holder.length() - 1, 1) == "\r" ? holder.substr(0, holder.length() - 1) : holder);

               if ((listEntryInfoFound ? stringReplace(holder, "\\n", "\n") : holder) != "")
               {
                   // Make sure we get the entry's info (the BRSAR File Offset and BRSTM Name), FIRST, before getting the entry's description.
                   if (!listEntryInfoFound)
                   {
                       // Get the length of where the offset (in text) is.
                       unsigned int ui = 0;
                       for (; ui < holder.length(); ui++)
                            if (holder.at(ui) == ' ') break;

                       // Verify offset to make sure it's valid. If it's valid, use it, otherwise throw an exception.
                       if (holder.substr(0, ui).find("0x") == 0 || holder.substr(0, ui).find("0X") == 0)
                       {
                           if (holder.substr(2, ui - 2) == "" || holder.substr(2, ui - 2).find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos)
                               throw std::invalid_argument("BRSAR File Offset Number is Invalid.");
                       }
                       else
                       {
                           if (holder.substr(0, ui) == "" || holder.substr(0, ui).find_first_not_of("0123456789") != std::string::npos)
                               throw std::invalid_argument("BRSAR File Offset Number is Invalid.");
                       }
                       offset = std::stoi(holder.substr(0, ui), 0, (holder.substr(0, ui).find("0x") == 0 || holder.substr(0, ui).find("0X") == 0 ? 16 : 10));

                       // Make sure the BRSTM Name IS NOT NULL/EMPTY OR ONLY WHITESPACE CHARACTERS.
                       if (stringWhiteSpaceOrNull(holder.substr(ui + 1, holder.length()), true))
                           throw std::invalid_argument("BRSTM Name cannot be null/empty or whitespace characters.");

                       name = holder.substr(ui + 1, holder.length());
                       listEntryInfoFound = true;
                   }
                   else   // Once we got the entry's info, start getting the description. This is optional, please put an \n as the description instead to mark it as null/empty, DO NOT LEAVE IT AS NULL/EMPTY IN YOUR TEXT EDITOR. ALSO, PLEASE USE \n (NOT \N) FOR A NEWLINE, DO NOT DIRECTLY PUT A NEWLINE (BY PRESSING THE "ENTER" KEY IN YOUR TEXT EDITOR) OR ISSUES WILL OCCUR.
                   {
                       description = (stringWhiteSpaceOrNull(stringReplace(holder, "\\n", "\n")) ? "" : stringReplace(holder, "\\n", "\n"));
                       bpl.addBRSTM(offset, name, description);
                       listEntryInfoFound = false;
                   }
               }
        }
    }
    catch (std::exception &e)
    {
        fs.close();
        bpl.free();
        std::cerr << "EXCEPTION: " << e.what() << "\nMemory Location: 0x" << &e << ".";
        goto immediateExit;
    }
    fs.close();

    // Check if BRSAR (if "-i" option isn't used), AND BRSTM file (if "-d" option is used) exists.
    if (!optionsChecked[1])
    {
        fs.open(brsarFileName, std::ios::in | std::ios::binary);
        if (!fs)
        {
            std::cerr << "ERROR: Cannot open BRSAR file, \"" << brsarFileName << "\".";
            goto immediateExit;
        }
        fs.close();
    }
    if (optionsChecked[2])
    {
        fs.open(brstmFileName, std::ios::in | std::ios::binary);
        if (!fs)
        {
            std::cerr << "ERROR: Cannot open BRSTM file, \"" << brstmFileName << "\".";
            goto immediateExit;
        }
        fs.close();
    }


    // Print warning message. If "-i" or "-q" option is used, don't print anything.
    if (!optionsChecked[3] && !optionsChecked[1])
    {
        char response = 0;
        std::cout << "WARNING: This'll make PERMANENT CHANGES to the BRSAR file.\n"
                  << "So make a backup of your BRSAR file, FIRST, in case something goes wrong.\n"
                  << "Type \"Y\" to continue, or any other key to exit: ";

        std::cin >> std::setw(1) >> response;
        if (response != 'Y' && response != 'y')
            goto immediateExit;
    }


    //
    // Set up the patching of the BRSAR file (with "choosing").
    //
    std::cout.fill('0');
    if (optionsChecked[0] && !optionsChecked[2])
    {
        // List Patch File Information.
        std::cout << "\n\n\nPatch File Name: \"" << brsarPatchName << "\".\n\nWii Game Name: " << bpl.gameName << "\n\nPatch File Author: " << bpl.patchAuthorName << "\n\nPatch File Author Contact: " << bpl.patchAuthorContactInfo << std::endl << std::endl << std::endl;

        // List Patch File BRSTM Track Entries.
        for (unsigned int ui = 0; ui < bpl.brstmCount(); ui++)
             std::cout << "Entry #" << std::dec << (ui+1) << ": " << bpl.getbrstmInfo(ui).name << " (BRSAR Offset 0x" << std::setw(8) << std::uppercase << std::hex << bpl.getbrstmInfo(ui).brsarFileOffset << ")\n" << bpl.getbrstmInfo(ui).description << std::endl << std::endl;

        // Prompt user the BRSTM file name and then which entry to patch to in the BRSAR file.
        std::cout << "\nNOTE: If a BRSTM in the game is not listed above, it might be that it's unused.\nIf it's really an error and you're sure that it isn't unused in the game,\ncontact the author of the patch file.\n\n";
        while (true)
        {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

               std::cout << "Type in the BRSTM file name: ";
               std::cin >> brstmFileName;

               fs.open(brstmFileName, std::ios::in | std::ios::binary);
               if (!fs)
                   std::cerr << "ERROR: Cannot open BRSTM file, \"" << brstmFileName << "\".";
               else
               {
                   fs.close();
                   std::cout << std::endl << std::endl;
                   break;
               }
               fs.close();
               std::cout << std::endl << std::endl;
        }
        while (true)
        {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

               std::cout << "Type in an entry number, ranging from 1 to " << std::dec << bpl.brstmCount() << "\nto patch the BRSAR file (\"" << brsarFileName << "\"): ";
               std::cin >> entryNum;
               std::cout << std::endl;
               if (entryNum > 0 && entryNum <= bpl.brstmCount()) break;
        }
        std::cout << std::endl;
    }
    else
    //
    // Print the infos of the BRSAR patch file.
    //
    if (optionsChecked[1])
    {
        bool optionChecked = false;
        std::ostringstream output;
        output.fill('0');
        if (!optionChecked && (1+!strcmp(brsarPatchName.c_str(), argv[1])+1) < argc && !_stricmp(argv[1+!strcmp(brsarPatchName.c_str(), argv[1])+1], "-f"))
        {
            optionChecked = true;
            if ((1+!strcmp(brsarPatchName.c_str(), argv[1])+1+1) < argc)
                infoTXTfilename = argv[1+!strcmp(brsarPatchName.c_str(), argv[1])+1+1];
        }

        // List Patch File Information.
        output << "Patch File Name: \"" << brsarPatchName << "\".\r\n\r\nWii Game Name: " << stringReplace(bpl.gameName, "\n", "\r\n") << "\r\n\r\nPatch File Author: " << stringReplace(bpl.patchAuthorName, "\n", "\r\n") << "\r\n\r\nPatch File Author Contact: " << stringReplace(bpl.patchAuthorContactInfo, "\n", "\r\n") << "\r\n\r\n\r\n";

        // List Patch File BRSTM Track Entries.
        for (unsigned int ui = 0; ui < bpl.brstmCount(); ui++)
             output << "Entry #" << std::dec << (ui+1) << ": " << bpl.getbrstmInfo(ui).name << " (BRSAR Offset 0x" << std::setw(8) << std::uppercase << std::hex << bpl.getbrstmInfo(ui).brsarFileOffset << ")\r\n" << stringReplace(bpl.getbrstmInfo(ui).description, "\n", "\r\n") << "\r\n\r\n";

        output << "\r\nNOTE: If a BRSTM in the game is not listed above, it might be that it's unused.\r\nIf it's really an error and you're sure that it isn't unused in the game,\r\ncontact the author of the patch file.\r\n\r\n";


        std::cout << output.str();
        if (optionChecked)
        {
            fs.open((stringWhiteSpaceOrNull(infoTXTfilename, true) ? brsarPatchName + "_info.txt" : infoTXTfilename), std::ios::out | std::ios::binary);
            if (!fs)
            {
                std::cerr << "ERROR: Output info text file could not be created.";
                goto immediateExit;
            }
            fs << output.str();
            fs.close();

            std::cout << "The infos were successfully written to a text file (\"" << (stringWhiteSpaceOrNull(infoTXTfilename, true) ? brsarPatchName + "_info.txt" : infoTXTfilename) << "\").";
        }
    }



    // Patch BRSAR file (if we're not displaying the infos of a BRSAR patch file)!
    // First, get the BRSTM file size and then patch the BRSAR file.
    if (!optionsChecked[1])
    {
        // Make sure entry number is in the range of 1 to the total number of BRSTMs found in the patch file.
        std::cout << std::endl;
        if (entryNum < 1 || entryNum > bpl.brstmCount())
        {
            std::cerr << "ERROR: Entry number cannot be lesser than 1 or greater than " << std::dec << bpl.brstmCount() << ".";
            goto immediateExit;
        }


        unsigned int brstmFileSize = 0;
        fs.open(brstmFileName, std::ios::in | std::ios::binary);
        if (!fs)
        {
            std::cerr << "ERROR: Cannot open BRSTM file, \"" << brstmFileName << "\".";
            goto immediateExit;
        }
        fs.seekg(0, std::ios::end);
        brstmFileSize = fs.tellg();
        fs.close();

        unsigned char existingBytes[4];
        fs.open(brsarFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
        if (!fs)
        {
            std::cerr << "ERROR: Cannot open BRSAR file, \"" << brsarFileName << "\".";
            goto immediateExit;
        }
        fs.seekg(0, std::ios::end);
        if (bpl.getbrstmInfo(entryNum - 1).brsarFileOffset < fs.tellg())
            fs.seekg(bpl.getbrstmInfo(entryNum - 1).brsarFileOffset, std::ios::beg);
        else
        {
            fs.close();
            std::cerr << "ERROR: The BRSAR file offset (0x" << std::setw(8) << std::uppercase << std::hex << bpl.getbrstmInfo(entryNum - 1).brsarFileOffset << ") is beyond the end of the BRSAR file.";
            goto immediateExit;
        }
        fs.read((char *)existingBytes, 4);
        fs.seekg(fs.tellg() - (std::streamsize)4, std::ios::beg);

        EndianType et = osEndian();
        if (et == EndianType::ERROR)
        {
            fs.close();
            std::cerr << "ERROR: Cannot determine machine endianness (byte order) to patch BRSAR file.";
            goto immediateExit;
        }
        else
        if (et == EndianType::LITTLE)
            byteArrayReverse((unsigned char *)&brstmFileSize, 4);

        fs.write((char *)&brstmFileSize, 4);
        fs.close();

        std::cout << "Patched Entry #" << std::dec << entryNum << " (" << bpl.getbrstmInfo(entryNum - 1).name << ").\n\nBRSAR File Offset 0x" << std::setw(8) << std::uppercase << std::hex << bpl.getbrstmInfo(entryNum - 1).brsarFileOffset << ":\nChanged bytes [";
        for (unsigned int ui = 0; ui < 4; ui++)
             std::cout << "0x" << std::setw(2) << std::uppercase << std::hex << (int)existingBytes[ui] << (ui == 3 ? "" : " ");

        std::cout << "] (from BRSAR File)\nwith bytes    [";
        for (unsigned int ui = 0; ui < 4; ui++)
             std::cout << "0x" << std::setw(2) << std::uppercase << std::hex << (int)((unsigned char *)&brstmFileSize)[ui] << (ui == 3 ? "" : " ");

        std::cout << "] (from BRSTM File).";
    }


    immediateExit:
    std::cout << std::endl << std::endl << std::endl;
    delete[] optionsChecked;
    return 0;
}
