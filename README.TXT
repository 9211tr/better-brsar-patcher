THE README CONTAINS IMPORTANT INFORMATION,
PLEASE READ ALL PARTS OF IT PROPERLY/CAREFULLY.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤°`°¤ø,¸¸,ø¤°`°¤

      BETTER WII BRSTM BRSAR
          PATCHER v1.0.0

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤°`°¤ø,¸¸,ø¤°`°¤


Better Wii BRSTM BRSAR Patcher v1.0.0.
A better utility for patching BRSAR files (can patch w/ BRSTMs up to 4GB)!
Copyright © 2017 9211tr.


Better Wii BRSTM BRSAR Patcher is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Better Wii BRSTM BRSAR Patcher is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Better Wii BRSTM BRSAR Patcher. If not, see: http://www.gnu.org/licenses/

---------------------------------------------------------------------------------------------------

Better Wii BRSTM BRSAR Patcher is written in Visual C++ for a 32-bit platform.
You'll need Microsoft Visual Studio 2010 (w/ Service Pack 1 update installed) Ultimate or
Express (or higher version of Visual Studio) to open/compile the source code.
You'll also need a 32-bit (or higher, 64-bit) OS to do your testing and to open the source
code. Simply click on the SLN file of the source code to open it with Microsoft Visual
Studio.

To get the source code, please go to its Github page: https://github.com/9211tr/better-brsar-patcher


This app is a command-line application, please open up the Windows Command Prompt (e.g.
by searching/opening for "cmd.exe" in the start menu) and by typing in the necessary command
option usages.

This app was originally intended to modify the BRSAR file of New Super Mario Bros. Wii.
However, this can also be used to modify any other BRSAR in any other Wii Game.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤

       LICENSING INFORMATION

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤


BEFORE USING BETTER WII BRSTM BRSAR PATCHER, READ ITS LICENSE, FIRST (BY VIEWING THE FILE  LICENSE.TXT  ).
THE LICENSE USED BY BETTER WII BRSTM BRSAR PATCHER IS THE GNU GPL v3+.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤`°¤ø,¸,ø¤°`°¤ø,¸,ø¤

           PROGRAM REQUIREMENTS
        AND RECOMMNEDED STUFF TO BE 
      INSTALLED FOR RUNNING IT ON YOUR
                 COMPUTER

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤`°¤ø,¸,ø¤°`°¤ø,¸,ø¤


Microsoft Windows XP SP3 (or later) 32-bit (or higher, 64-bit) installed.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤`°¤ø,¸,ø¤°`°¤ø,¸,ø¤

       COMMAND OPTIONS DOCUMENTATION

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤`°¤ø,¸,ø¤°`°¤ø,¸,ø¤


@  LIST OF COMMAND OPTIONS AND WHAT ACTION IT DOES


NOTE: All command options aren't case
sensitive (unlike in other command-line programs).
 ---------------------------------------------------------------
| Command |               What the Command Option               |
| Option  |                   does or Invokes                   |
|---------|-----------------------------------------------------|
|   -b    |         Specifies the BRSAR file to patch.          |
|---------|-----------------------------------------------------|
|   -i    |        Prints out the info of a patch file.         |
|---------|-----------------------------------------------------|
|   -d    | Direct BRSTM patch to the BRSAR (without choosing). |
|---------|-----------------------------------------------------|
|   -q    |   Quiet mode. Only can be used if you're doing a    |
|         |                 direct BRSTM patch.                 |
 ---------------------------------------------------------------


@  USAGES


1. Patching a BRSAR file (with "choosing"):
     btrwiibrstmbrsarpatch <brsarPatchFile> -b <brsarFile>

NOTE: <brsarPatchFile> is the BRSAR patch file (a file that ends with the .BPTH file extension).
If <brsarPatchFile> is empty (not specified), the default patch file will be used (it is normally
called "DEFAULT.BPTH").



2. Patching a BRSAR file (without "choosing" [i.e. DIRECTLY]):
     btrwiibrstmbrsarpatch <brsarPatchFile> -b <brsarFile> -d "<entryNumber> <brstmFile>"

NOTE: <entryNumber> is the number of a BRSTM track (in the patch file) you wish to patch to the BRSAR. If you don't
wish to have warnings before doing the patch, you can use the -q option to supress the warnings, although it's not recommended.
To find out the number of BRSTM tracks, you'll need to print out the info of the patch file.



3. Printing out the infos of a BRSAR patch file:
     btrwiibrstmbrsarpatch <brsarPatchFile> -i

NOTE: You can also print out the infos into a seperate TXT (text) file, using the -f option:

            btrwiibrstmbrsarpatch <brsarPatchFile> -i -f
         OR
            btrwiibrstmbrsarpatch <brsarPatchFile> -i -f <OutputTXTFile>

<OutputTXTFile> is the output file name of the text file.
If the file already exists, its contents will be destroyed.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤

       BRSAR PATCH FILE SYNTAX/FORMAT

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤


You can easily create your own BRSAR patch file
to modify any other BRSAR file in any other Wii Game.

Just create a new text document (make sure to rename
the file extension from .txt to .bpth).
Open it up with Notepad or any other text editor.

The syntax of the BRSAR patch file goes as it follows.
Type this into the text editor:

-------------------------------------

Better Wii BRSTM BRSAR Patcher File:
<gameName>
<patchFileAuthorName>
<patchFileAuthorContactInfo>

-------------------------------------

NOTE: Do not include the dashes (-).

The text, "Better Wii BRSTM BRSAR Patcher File:", is
not case sensitive.

<gameName> is the Wii Game Name. It is required and cannot be null/empty or whitespace characters.
For newline characters there, please use \n (not \N) for that, do not directly put newline characters (by
pressing the ENTER key on your keyboard) or issues will occur.

<patchFileAuthorName> is the Author of the BRSAR patch file. It is optional, and can be whitespace characters (but
not null/empty). For newline characters there, please use \n (not \N) for that, do not directly put newline characters (by
pressing the ENTER key on your keyboard) or issues will occur.

<patchFileAuthorContactInfo> is the Author's Contact Information. It is optional, and can be whitespace characters (but
not null/empty). For newline characters there, please use \n (not \N) for that, do not directly put newline characters (by
pressing the ENTER key on your keyboard) or issues will occur.



After typing that in the text editor.
Type this in, FOR EACH BRSTM:

-------------------------------

<brsarOffset> <brstmName>
<brstmDescription>

-------------------------------

NOTE: Do not include the dashes (-).

<brsarOffset> is the offset of the entry of the BRSTM in the BRSAR,
a hexadecimal offset (starting with 0x) or decimal offset.
It is required.

<brstmName> is the BRSTM file name (and yes, including the file extension, too).
It is required and cannot be null/empty or whitespace characters. And it cannot contain
newlines, too (even by using \n).

<brstmDescription> is the description of the BRSTM file.
This is usually used to describe the music/theme/etc. of the BRSTM file.
It is optional, and can be whitespace characters (but not null/empty). For
newline characters there, please use \n (not \N) for that, do not directly put
newline characters (by pressing the ENTER key on your keyboard) or issues will occur.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤

        CREDITS

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤


9211tr (on "HorizonWii": http://horizonwii.net/?page=profile&id=34 ):
The Programming.
The README.TXT creation.
The BRSAR Patch File Syntax/Format.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤

       CONTACT INFORMATION

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤°`°¤ø,¸,ø¤


I'm available on "HorizonWii".
For help/questions/support/bug reports/etc.,
contact me (by "posting a reply") at the discussion
thread on "HorizonWii": 

Oh and please read the first post (of the discussion thread) COMPLETELY and PROPERLY before you post anything.

Also too, "HorizonWii" requires you to log in w/ an account, so if you didn't created one, it's best
to register for an account, be sure to read the FAQ/Rules of "HorizonWii" (http://horizonwii.net/?page=faq), completely and properly,
first, before you attempt to register/etc.



¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤`°¤ø,¸,ø¤

      PROGRAM UPDATE HISTORY

¸,ø¤°`°¤ø,¸¸,ø¤°`°¤ø,¸,ø¤`°¤ø,¸,ø¤


v1.0.0 [08/12/2017]
   First/Initial Release.