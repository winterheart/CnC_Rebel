;
;	Command & Conquer Renegade(tm)
;	Copyright 2025 Electronic Arts Inc.
;
;	This program is free software: you can redistribute it and/or modify
;	it under the terms of the GNU General Public License as published by
;	the Free Software Foundation, either version 3 of the License, or
;	(at your option) any later version.
;
;	This program is distributed in the hope that it will be useful,
;	but WITHOUT ANY WARRANTY; without even the implied warranty of
;	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;	GNU General Public License for more details.
;
;	You should have received a copy of the GNU General Public License
;	along with this program.  If not, see <http://www.gnu.org/licenses/>.
;

;***********************************************************************************************
;***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
;***********************************************************************************************
;*                                                                                             *
;*                 Project Name : Command & Conquer                                            *
;*                                                                                             *
;*                     $Archive:: /Commando/Code/Tools/VerStamp/VerStamp.asm                  $*
;*                                                                                             *
;*                      $Author:: Steve_t                                                     $*
;*                                                                                             *
;*                     $Modtime:: 12/05/01 1:02a                                              $*
;*                                                                                             *
;*                    $Revision:: 4                                                           $*
;*                                                                                             *
;*---------------------------------------------------------------------------------------------*
;* Functions:                                                                                  *
;*                                                                                             *
;* main_ -- Program entry point. Does most of the work                                         *
;* Print -- Prints a string to stdout                                                          *
;* Alloc -- Allocate memory from the heap                                                      *
;* Free  -- Free memory                                                                        *
;* Search_Buffer -- Search a buffer for occurance of given data                                *
;* Get_Build -- Load and update the build number                                               *
;*                                                                                             *
;* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


;
; Why is this written in assembly language when C++ would clearly be more appropriate?
; Because I can and I need the practice.
;
; Anyone offended should feel free to rewrite it in C++.
;

		.686
		.k3d
		.mmx
		.model	flat

;***********************************************************************************************
; Prototypes for Win32 API calls.
;

; Printing
;
OutputDebugString	proto 	STDCALL string:ptr byte
GetStdHandle		proto	STDCALL handle_type:dword
WriteConsole		proto	STDCALL handle:dword, string:ptr byte, numchars:dword, charswritten:ptr dword, reserved:ptr dword

; File functions
;
CloseHandle		proto	STDCALL handle:dword
CreateFile		proto	STDCALL file_name:ptr byte, access_mode:dword, share_mode:dword, sec_attr:ptr byte, creation_disposition:dword, flags:dword, template:dword
GetFileSize		proto	STDCALL handle:dword, file_size_high:ptr dword
ReadFile		proto	STDCALL handle:dword, buffer:ptr byte, bytes_to_read:dword, bytes_read:ptr dword, overlapped:ptr byte
GetFileTime		proto	STDCALL handle:dword, create_time:ptr dword, access_time:ptr dword, write_time:ptr dword
SetFileTime		proto	STDCALL handle:dword, create_time:ptr dword, access_time:ptr dword, write_time:ptr dword
FileTimeToLocalFileTime	proto	STDCALL utc_time:ptr dword, local_time:ptr dword
SetFilePointer		proto	STDCALL handle:dword, distance:dword, dist_high:ptr dword, method:dword
WriteFile		proto	STDCALL handle:dword, buffer:ptr byte, bytes:dword, bytes_written:ptr dword, overlapped:ptr byte


; Heap functions
;
HeapAlloc		proto	STDCALL handle:dword, flags:dword, bytes:dword
HeapFree		proto	STDCALL handle:dword, flags:dword, memptr:ptr byte
HeapCreate		proto	STDCALL flags:dword, startsize:dword, maxsize:dword
HeapDestroy		proto	STDCALL handle:dword

; Misc APIs
;
GetUserName		proto	STDCALL buffer:ptr byte, buffer_len:ptr dword
GetCommandLine		proto	STDCALL


;***********************************************************************************************
; Local prototypes.
;
Search_Buffer		proto	C source_ptr:ptr byte, dest_ptr:ptr byte, source_len:dword, dest_len:dword
main			proto	STDCALL
Parse_Command_Line	proto	C
String_To_Int 		proto	C


;***********************************************************************************************
; Externs for linking to Win32 APIs
;
externdef 	__imp__CreateFileA@28:dword
externdef	__imp__GetFileSize@8:dword
externdef	__imp__CloseHandle@4:dword
externdef       __imp__OutputDebugStringA@4:dword
externdef	__imp__GetStdHandle@4:dword
externdef	__imp__WriteConsoleA@20:dword
externdef	__imp__HeapAlloc@12:dword
externdef	__imp__HeapFree@12:dword
externdef	__imp__HeapCreate@12:dword
externdef	__imp__HeapDestroy@4:dword
externdef	__imp__ReadFile@20:dword
externdef	__imp__WriteFile@20:dword
externdef	__imp__GetFileTime@16:dword
externdef	__imp__SetFileTime@16:dword
externdef	__imp__FileTimeToLocalFileTime@8:dword
externdef	__imp__SetFilePointer@16:dword
externdef	__imp__GetUserNameA@8:dword
externdef	__imp__GetCommandLineA@0:dword


;***********************************************************************************************
; Equates
;
STD_OUTPUT_HANDLE	equ	-11
INVALID_HANDLE_VALUE	equ	-1
FILE_BEGIN		equ	0


;***********************************************************************************************
; Data segment.
;
		.data

StandardOutput		dd	INVALID_HANDLE_VALUE
Scrap			dd	0
FileHandle		dd	INVALID_HANDLE_VALUE
ExeAddr			dd	0
ExeSize			dd	0
BuildStampAddr		dd	0
DateStampAddr		dd	0
ProcessHeap		dd	0
BuildNumber		dd	0
ChunkSize		dd	0
BuildNumberSpecified	dd	0

FileTimeWrite		dd	0,0
FileTimeCreate		dd	0,0
FileTimeAccess		dd	0,0
LocalFileTime		dd	0,0

MyFileName		db	256 dup (0)

FileName		db	"renegade.exe",0
			db	256 dup (0)

BuildNumberFileName	db	".\build.bin",0
			db	256 dup (0)

FileNameList		dd	FileName,BuildNumberFileName

Args			db	256 dup (0)
ArgumentList		dd	8 dup (0)



IDString		db	"VerStamp - Version stamping utility for Renegade",13,10
			db	"Version 1.2",13,10
			db	"Programmer - Steve T.",13,10
			db	"Usage: VerStamp options <path to exe> <path to build number file>",13,10
			db	"	Options: -n<num>	set build number",13,10
			db      0

SearchingString		db	"Opening target .EXE",13,10,0
OpenFailedString	db	"Failed to open target .EXE - aborting.",13,10,0
SizeFailedString        db	"Unable to get size of target .EXE - aborting",13,10,0
NoMemString		db	"Out of memory - aborting",13,10,0
ReadFailureString	db	"Error reading target .EXE - aborting",13,10,0
ReadOKString		db	"Target .EXE read OK",13,10,0
StampNotFound		db	"Unable to find stamp signature in target .exe",13,10,0
BuildStampFound		db	"Found build stamp signature in target .exe",13,10,0
DateStampFound		db	"Found date stamp signature in target .exe",13,10,0
FileTimeFailedString	db	"Unable to get time of last modification to target .EXE - aborting",13,10,0
WritingString		db	"Modifying target .EXE",13,10,0
FilePointerFailedString	db	"Failed to set file pointer - aborting",13,10,0
LoadingBuildString	db	"Reading build number from build file",13,10,0
ReadBuildFailureString	db	"Error reading build file - setting build numnber to 1",13,10,0
UnrecognisedOption	db	"Unrecognised command line option",13,10,0


			align 4
BuildNumberSearchString	db	"Insert1Build2Number3Here4   ",0
			align 4
BuildDateSearchString	db	"Insert1Build2Date3Here4     ",0



;***********************************************************************************************
; Code Segment
;
;

		_text segment para public use32 'CODE'

		org	0



;***********************************************************************************************
;* main_ -- Program entry point                                                                *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	Usual command line stuff                                                       *
;*                                                                                             *
;*                                                                                             *
;* OUTPUT:      Exit code                                                                      *
;*                                                                                             *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/19/98 10:43PM ST : Created.                                                            *
;*=============================================================================================*
externdef main	:near

main		proc STDCALL

		pushad
		cld

		;invoke	OutputDebugString, ADDR TestString

		;
		; Get the standard console output handle.
		;
		invoke	GetStdHandle, STD_OUTPUT_HANDLE
		mov	[StandardOutput],eax

		lea	eax,IDString
		call	Print

		;
		; Create a 32Mb heap for the process so we can allocate memory. Allow it to grow if needed.
		;
		invoke	HeapCreate, 0, 33554432, 0
		mov	[ProcessHeap],eax
		test	eax,eax
		jnz	@@heap_ok
		lea	eax,NoMemString
		call	Print
		mov	eax,1
		jmp	@@out


@@heap_ok:      ;
		; Parse the command line.
		;
		call	Parse_Command_Line

		;
		; Read in the build number
		;
		call	Get_Build

		;
		; Open RENEGADE.EXE
		;
		lea	eax,SearchingString
		call	Print
		invoke	CreateFile, ADDR FileName, 80000000h, 1h, 0, 3h, 80h, 0
		mov	[FileHandle],eax

		;
		; Check the file handle and bail if it's bad.
		;
		cmp	eax,INVALID_HANDLE_VALUE
		jnz	@@file_open_ok
		lea	eax,OpenFailedString
		call	Print
		mov	eax,1
		jmp	@@out


@@file_open_ok:
		;
		; Get the time the file was last modified.
		;
		invoke	GetFileTime, FileHandle, ADDR FileTimeCreate, ADDR FileTimeAccess, ADDR FileTimeWrite
		test	eax,eax
		jnz	@@got_file_time
		lea	eax,FileTimeFailedString
		call	Print
		mov	eax,1
		jmp	@@out


@@got_file_time:
		;
		; Convert it to the local time.
		;
		invoke	FileTimeToLocalFileTime, ADDR FileTimeWrite, ADDR LocalFileTime

		;
		; Get the size of RENEGADE.EXE
		;
		invoke	GetFileSize, FileHandle, 0
		mov	[ExeSize],eax
		cmp	eax,0ffffffffh
		jnz	@@size_ok
		lea	eax,SizeFailedString
		call	Print
		mov	eax,1
		jmp	@@out

		;
		; Allocate a buffer to load the file into.
		;
@@size_ok:      add	eax,1024
		call	Alloc
		test	eax,eax
		jnz	@@got_buffer
		lea	eax,NoMemString
		call	Print
		mov	eax,1
		jmp	@@out


@@got_buffer:	mov	[ExeAddr],eax
		mov	[ChunkSize],1048576
		call	Search_By_Chunk
		mov	[BuildStampAddr],eax

		;
		; Close the file.
		;
		push	eax
		mov	edx,[FileHandle]
		invoke	CloseHandle, edx
		pop	eax

		;
		; See if we found the build string.
		;
		test	eax,eax
		jnz	@@found_build_number
		lea	eax,StampNotFound
		call	Print
		mov	eax,1
		jmp	@@out


@@found_build_number:
		lea	eax,BuildStampFound
		call	Print


		;
		; Write the build number into place.
		;
		mov	edi,[BuildStampAddr]
		mov	eax,[BuildNumber]
		lea	edi,[edi+28]
		stosd

		;
		; Write the users name into place
		;
		mov	[Scrap],32
		invoke	GetUserName, edi, ADDR Scrap

		;
		; Try to find the build date stamp in the .EXE
		; It is probably near the first stamp so just back up a little and try from there.
		;
		mov	eax,[BuildStampAddr]
		sub	eax,1024
		mov	ebx,eax
		sub	ebx,[ExeAddr]
		neg	ebx
		add	ebx,[ExeSize]
		invoke	Search_Buffer, ADDR BuildDateSearchString, eax, 28, ebx
		test	eax,eax
		jnz	@@found_build_date
		lea	eax,StampNotFound
		call	Print
		mov	eax,1
		jmp	@@out


@@found_build_date:
		mov	[DateStampAddr],eax
		lea	eax,DateStampFound
		call	Print

		;
		; Move the build date into the stamp location.
		;
		mov	edi,[DateStampAddr]
		lea	edi,[edi+28]
		mov	esi,offset LocalFileTime
		movsd
		movsd

		;
		; Open RENEGADE.EXE again so we can write the changes back out.
		;
		lea	eax,WritingString
		call	Print
		invoke	CreateFile, ADDR FileName, 40000000h, 1h, 0, 3h, 80h, 0
		mov	[FileHandle],eax
		cmp	eax,INVALID_HANDLE_VALUE
		jnz	@@open_for_write
		lea	eax,OpenFailedString
		call	Print
		mov	eax,1
		jmp	@@out

@@open_for_write:
		;
		; Write out the changes made at the build stamp address
		;
		mov	eax,[BuildStampAddr]
		add	eax,28
		push	eax
		sub	eax,[ExeAddr]
		push	eax
		invoke	SetFilePointer, FileHandle, eax, 0, FILE_BEGIN
		pop	ebx
		cmp	eax,ebx
		pop	esi

		jz	@@fp_set_ok1
		lea	eax,FilePointerFailedString
		call	Print
		mov	eax,1
		jmp	@@out

		;
		; Write out the changes made at the build date address
		;
@@fp_set_ok1:	invoke	WriteFile, FileHandle, esi, 36, ADDR Scrap, 0

		mov	eax,[DateStampAddr]
		add	eax,28
		push	eax
		sub	eax,[ExeAddr]
		push	eax
		invoke	SetFilePointer, FileHandle, eax, 0, FILE_BEGIN
		pop	ebx
		cmp	eax,ebx
		pop	esi

		jz	@@fp_set_ok2
		lea	eax,FilePointerFailedString
		call	Print
		mov	eax,1
		jmp	@@out

@@fp_set_ok2:	invoke	WriteFile, FileHandle, esi, 8, ADDR Scrap, 0

		;
		; Set the file time back to what it was before we modified the file.
		;
		invoke	SetFileTime, FileHandle, ADDR FileTimeCreate, ADDR FileTimeAccess, ADDR FileTimeWrite

		;
		; Close the file.
		;
		mov	eax,[FileHandle]
		invoke	CloseHandle, eax

		;
		; Free the memory used by the image.
		;
		mov	eax,[ExeAddr]
		call	Free

		;
		; Success!
		;
		xor     eax,eax

@@out:		mov	ebx,[ProcessHeap]
		test	ebx,ebx
		jz	@@no_heap_free
		push	eax
		invoke	HeapDestroy, ebx
		pop	eax


@@no_heap_free:	popad

		ret

main		endp





;***********************************************************************************************
;* Print -- Prints out a string to standard output                                             *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	eax - string                                                                   *
;*                                                                                             *
;*                                                                                             *
;* OUTPUT:      true if string printed OK                                                      *
;*                                                                                             *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/19/98 11:12PM ST : Created.                                                            *
;*=============================================================================================*
Print		proc

		;
		; Check the std out handle for validity
		;
		cmp	[StandardOutput], INVALID_HANDLE_VALUE
		jnz	@@handle_ok
		xor	eax,eax
		ret


@@handle_ok:	;
		; Count the number of characters in the string.
		;
		mov	esi,eax
		xor	dl,dl

@@loop:		cmp	[esi],dl
		jz	@@counted
		inc	esi
		jmp	@@loop

		;
		; Use the WriteConsole API to output the string.
		;
@@counted:	mov	ecx,esi
		sub	ecx,eax

		push	ecx
		invoke	WriteConsole, StandardOutput, eax, ecx, ADDR Scrap, 0
		pop	ecx

		xor	eax,eax
		cmp	ecx,[Scrap]

		sete	al
		ret

Print           endp



;***********************************************************************************************
;* Alloc -- Allocate given number of bytes from the heap                                       *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	eax - bytes to allocate                                                        *
;*                                                                                             *
;*                                                                                             *
;* OUTPUT:      ptr to allocated memory                                                        *
;*                                                                                             *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/20/98 0:24AM ST : Created.                                                             *
;*=============================================================================================*
Alloc		proc

		;
		; Make sure the heap is valid.
		;
		mov	edx,[ProcessHeap]
		test	edx,edx
		jnz	@@alloc_heap_valid
		xor     eax,eax
		ret

		;
		; Try to allocate the memory.
		;
@@alloc_heap_valid:
		invoke	HeapAlloc, edx, 0, eax

		ret

Alloc		endp



;***********************************************************************************************
;* Free -- Free a previously allocated block of memory                                         *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	eax - ptr to memory to free                                                    *
;*                                                                                             *
;*                                                                                             *
;* OUTPUT:      nothing                                                                        *
;*                                                                                             *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/20/98 0:23AM ST : Created.                                                             *
;*=============================================================================================*
Free		proc

		;
		; Make sure the heap is valid.
		;
		mov	edx,[ProcessHeap]
		test	edx,edx
		jnz	@@free_heap_valid
		xor     eax,eax
		ret

@@free_heap_valid:
		invoke	HeapFree, edx, 0, eax

		ret

Free		endp



;***********************************************************************************************
;* Search -- Find first occurrance of source data in buffer                                    *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	ptr to data to search for                                                      *
;*              ptr to buffer                                                                  *
;*              length of search data                                                          *
;*              size of buffer                                                                 *
;*                                                                                             *
;* OUTPUT:      ptr to data match in buffer or null                                            *
;*                                                                                             *
;* Warning: Source data must be multiple of 4 bytes long                                       *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/20/98 0:23AM ST : Created.                                                             *
;*=============================================================================================*
Search_Buffer	proc C uses esi edi ebx ecx edx,
		source_ptr:ptr byte,
		dest_ptr:ptr byte,
		source_len:dword,
		dest_len:dword

		mov	edi,[dest_ptr]
		mov	esi,[source_ptr]
		mov	edx,[dest_len]
		sub	edx,[source_len]
		shr	[source_len],2

		test	edx,edx
		jz	@@failed

		mov	eax,esi
		mov	ebx,edi

@@outer_loop:	mov	ecx,[source_len]
		mov	esi,eax
		mov	edi,ebx
		repz	cmpsd
		jz	@@found

		inc	ebx
		dec	edx
		cmp	edx,[source_len]
		jae	@@outer_loop

@@failed:	xor	eax,eax
		ret


@@found:	mov	eax,ebx
		ret

Search_Buffer	endp






;***********************************************************************************************
;* Search_By_Chunk -- Find first occurrance of source data in file                             *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	Nothing                                                                        *
;*                                                                                             *
;* OUTPUT:      ptr to data match in buffer or null                                            *
;*                                                                                             *
;* Warning: None                                                                               *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/29/2001 12:39PM ST : Created.                                                          *
;*=============================================================================================*
Search_By_Chunk	proc C uses esi edi ebx ecx edx,


		;
		; Read the file in chunks. Search for the matching string in each chunk before loading the next.
		;
		xor	ebx,ebx				; Chunk number

@@next_chunk:
		mov	eax,ebx
		mov	ecx,[ChunkSize]
		imul	eax,ecx

		cmp	eax,[ExeSize]
		jae	@@str_not_found

		mov	edx,[ExeSize]
		sub	edx,eax
		cmp	edx,ecx
		jae	@@no_overrun
		mov	ecx,edx
		test	ecx,ecx
		jz	@@str_not_found

		;
		; Read a chunk of the file.
		;
@@no_overrun:	add	eax,[ExeAddr]
		push	eax
		push	ebx
		push	ecx
		invoke	ReadFile, FileHandle, eax, ecx, ADDR Scrap, 0
		pop	ecx
		pop	ebx
		pop	esi
		test	eax,eax
		jnz	@@read_ok

		lea	eax,ReadFailureString
		call	Print
		jmp	@@str_not_found

		;
		; Search this chunk.
		;
@@read_ok:      push	ecx
		test	ebx,ebx
		jz	@@skip_if_first
		sub	esi,32
		add	ecx,32

@@skip_if_first:invoke	Search_Buffer, ADDR BuildNumberSearchString, esi, 28, ecx
		pop	ecx
		test	eax,eax
		jne	@@found_string

		cmp	ecx,[ChunkSize]
		jl	@@str_not_found
		inc	ebx			; Chunk number
		jmp	@@next_chunk


@@str_not_found:xor	eax,eax

@@found_string:	ret

Search_By_Chunk	endp




;***********************************************************************************************
;* Get_Build -- Load and update the build number                                               *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	nothing                                                                        *
;*                                                                                             *
;* OUTPUT:      new build number                                                               *
;*                                                                                             *
;* Warning: Source data must be multiple of 4 bytes long                                       *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/20/98 0:23AM ST : Created.                                                             *
;*=============================================================================================*
Get_Build	proc

		cmp	[BuildNumberSpecified],0
		jnz	@@already_got_bn


		lea	eax,LoadingBuildString
		call	Print
		invoke	CreateFile, ADDR BuildNumberFileName, 80000000h, 1h, 0, 3h, 80h, 0
		mov	[FileHandle],eax

		;
		; Check the file handle and dont read if it's bad.
		;
		cmp	eax,INVALID_HANDLE_VALUE
		jnz	@@load_ok

		;
		; There was an error so print a message.
		;
		lea	eax,ReadBuildFailureString
		call	Print
		jmp	@@load_done

@@load_ok:	invoke	ReadFile, FileHandle, ADDR BuildNumber, 4, ADDR Scrap, 0
		invoke	CloseHandle, FileHandle

		;
		; Increment the build number
		;
@@load_done:	inc	BuildNumber

		;
		; Write it out again.
		;
		invoke	CreateFile, ADDR BuildNumberFileName, 40000000h, 1h, 0, 4h, 80h, 0
		mov	[FileHandle],eax
		invoke	WriteFile, FileHandle, ADDR BuildNumber, 4, ADDR Scrap, 0
		invoke	CloseHandle, FileHandle

@@already_got_bn:
		ret

Get_Build	endp








;***********************************************************************************************
;* Break_Command_Line -- Break the command line into seperate args                             *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	Nothing                                                                        *
;*                                                                                             *
;* OUTPUT:      Nothing                                                                        *
;*                                                                                             *
;* Warning: None                                                                               *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/29/2001 12:39PM ST : Created.                                                          *
;*=============================================================================================*
Break_Command_Line proc C
		local	arguments:dword
		local	done:dword
		local	argslen:dword

		mov	[arguments],0
		mov	[done],0
		mov	[argslen],0


		;
		; Get a pointer to the command line.
		;
		invoke	GetCommandLine
		mov	esi,eax

		;
		; Command line ptr is esi
		;
@@cmd_out_lp:	mov	ebx,esi
		mov	ecx,255

@@cmd_line_lp:	cmp	byte ptr [esi],0
		jz	@@end_cmd_line
		cmp	byte ptr [esi],32
		jz	@@got_cmd_line_str
		inc	esi
		dec	ecx
		jnz	@@cmd_line_lp

@@end_cmd_line:	mov	[done],1

@@got_cmd_line_str:
		cmp	ebx,esi
		jz	@@outy

		lea	edi,Args
		add	edi,argslen

		mov	eax,[arguments]
		mov	[eax * 4 + ArgumentList],edi

@@got_dest_str:	mov	al,[ebx]
		inc	ebx
		inc	[argslen]
		stosb
		cmp	ebx,esi
		jb	@@got_dest_str

		mov	byte ptr [edi],0
		inc	[argslen]

		inc	esi

		inc	[arguments]

		cmp	[done],0
		jz	@@cmd_out_lp

@@outy:		mov	eax,arguments
		ret

Break_Command_Line endp




;***********************************************************************************************
;* Parse_Command_Line -- Suck the goodness out of the command line                             *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	Nothing                                                                        *
;*                                                                                             *
;* OUTPUT:      Nothing                                                                        *
;*                                                                                             *
;* Warning: None                                                                               *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/29/2001 12:39PM ST : Created.                                                          *
;*=============================================================================================*
Parse_Command_Line proc C
		local	argnum:dword
		local	num_args:dword
		local	file_number:dword

		call	Break_Command_Line
		cmp	eax,1
		jbe	@@pcl_out

		mov	[num_args],eax

		;
		; Parse options first. Ignore the first argument - it's the path to the .exe
		;
		mov	[argnum],1

@@pcl_opt_outer:
		mov	eax,[argnum]
		cmp	eax,[num_args]
		jae	@@pcl_out
		mov	esi,[eax*4 + ArgumentList]

		mov	al,[esi]
		cmp	al,'-'
		jz	@@pcl_option
		cmp	al,'/'
		jnz	@@pcl_get_file_list

@@pcl_option:	mov	al,[esi+1]
		cmp	al,'n'
		jz	@@pcl_port_number
		cmp	al,'N'
		jz	@@pcl_port_number

		;
		; Don't know this option
		;
		lea	eax,UnrecognisedOption
		call	Print
		inc	[argnum]
		jmp	@@pcl_opt_outer


@@pcl_port_number:
		lea	eax,[esi+2]
		call	String_To_Int
		mov	[BuildNumber],eax
		mov	[BuildNumberSpecified],1
		inc	argnum
		jmp	@@pcl_opt_outer


		;
		; Copy the file names from the argument list.
		;
@@pcl_get_file_list:
		mov	[file_number],0

@@pcl_get_file_outer_lp:
		mov	eax,[argnum]
		cmp	eax,[num_args]
		jae	@@pcl_out
		mov	esi,[eax*4 + ArgumentList]

		mov	edi,[file_number]
		mov	edi,[edi*4 + FileNameList]

@@pcl_copy_lp:	lodsb
		stosb
		test	al,al
		jnz	@@pcl_copy_lp

		inc	[file_number]
		inc	[argnum]

		;
		; Only looking for 2 file names.
		;
		cmp	[file_number],2
		jz	@@pcl_out
		jmp	@@pcl_get_file_outer_lp


@@pcl_out:	ret

Parse_Command_Line endp







;***********************************************************************************************
;* String_To_Int -- Convert a string to an int. atoi.                                          *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	eax - ptr to string                                                            *
;*                                                                                             *
;* OUTPUT:      eax - int                                                                      *
;*                                                                                             *
;* Warning: None                                                                               *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/29/2001 12:39PM ST : Created.                                                          *
;*=============================================================================================*
String_To_Int proc C

		;
		; Get the end of the string
		;
		mov	esi,eax
		or	ecx,-1
		mov	edi,esi
		xor	al,al
		repne	scasb
		dec	edi

		cmp	ecx,-1
		jz      @@nolen

		mov	ecx,1
		xor	ebx,ebx

@@more_digits:	xor	eax,eax
		dec	edi
		mov	al,[edi]
		sub	al,'0'
		imul	eax,ecx
		add	ebx,eax
		imul	ecx,10
		cmp	edi,esi
		ja	@@more_digits

		mov	eax,ebx
		ret

@@nolen:	mov	eax,0
		ret

String_To_Int endp







ifdef cuts


;***********************************************************************************************
;* Parse_Command_Line -- Suck the goodness out of the command line                             *
;*                                                                                             *
;*                                                                                             *
;* INPUT:	Nothing                                                                        *
;*                                                                                             *
;* OUTPUT:      Nothing                                                                        *
;*                                                                                             *
;* Warning: None                                                                               *
;*                                                                                             *
;* HISTORY:                                                                                    *
;*   10/29/2001 12:39PM ST : Created.                                                          *
;*=============================================================================================*
Parse_Command_Line proc C
		local	arguments:dword
		local	done:dword

		mov	[arguments],0
		mov	[done],0


		;
		; Get a pointer to the command line.
		;
		invoke	GetCommandLine
		mov	esi,eax

		;
		; Command line ptr is esi
		;
@@cmd_out_lp:	mov	ebx,esi
		mov	ecx,255

@@cmd_line_lp:	cmp	byte ptr [esi],0
		jz	@@end_cmd_line
		cmp	byte ptr [esi],32
		jz	@@got_cmd_line_str
		inc	esi
		dec	ecx
		jnz	@@cmd_line_lp

@@end_cmd_line:	mov	[done],1

@@got_cmd_line_str:
		cmp	ebx,esi
		jz	@@outy

		mov	edi,[arguments]
		shl	edi,2
		mov	edi,[edi + FileNameList]

@@got_dest_str:	mov	al,[ebx]
		inc	ebx
		stosb
		cmp	ebx,esi
		jnz	@@got_dest_str

		inc	esi

		inc	[arguments]
		cmp	[arguments],3
		jz	@@outy

		cmp	[done],0
		jz	@@cmd_out_lp

@@outy:		ret

Parse_Command_Line endp


endif




;***********************************************************************************************
; Jump table for routing API calls without using the mangled __imp names
;
;
OutputDebugString	proc	STDCALL	;proc	STDCALL string:ptr byte
			jmp	[__imp__OutputDebugStringA@4]
OutputDebugString 	endp

GetStdHandle		proc	STDCALL	; handle_type:dword
			jmp	[__imp__GetStdHandle@4]
GetStdHandle		endp

GetFileSize		proc	STDCALL	; handle:dword, file_size_high:ptr dword
			jmp	[__imp__GetFileSize@8]
GetFileSize		endp

WriteConsole		proc	STDCALL	; handle:dword, string:ptr byte, numchars:dword, charswritten:ptr dword, reserved:ptr dword
			jmp	[__imp__WriteConsoleA@20]
WriteConsole 		endp

CreateFile		proc	STDCALL	; file_name:ptr byte, access_mode:dword, share_mode:dword, sec_attr:ptr byte, creation_disposition:dword, flags:dword, template:dword
			jmp	[__imp__CreateFileA@28]
CreateFile 		endp

CloseHandle		proc	STDCALL	; handle:dword
			jmp	[__imp__CloseHandle@4]
CloseHandle 		endp

HeapAlloc		proc	STDCALL	; handle:dword, flags:dword, bytes:dword
			jmp	[__imp__HeapAlloc@12]
HeapAlloc 		endp

HeapFree		proc	STDCALL	; handle:dword, flags:dword, memptr:ptr byte
			jmp	[__imp__HeapFree@12]
HeapFree 		endp

HeapCreate		proc	STDCALL	; flags:dword, startsize:dword, maxsize:dword
			jmp	[__imp__HeapCreate@12]
HeapCreate 		endp

HeapDestroy		proc	STDCALL	; handle:dword
			jmp	[__imp__HeapDestroy@4]
HeapDestroy 		endp

ReadFile		proc	STDCALL	; handle:dword, buffer:ptr byte, bytes_to_read:dword, bytes_read:ptr dword, overlapped:ptr byte
			jmp	[__imp__ReadFile@20]
ReadFile 		endp

WriteFile		proc	STDCALL	; handle:dword, buffer:ptr byte, bytes:dword, bytes_written:ptr dword, overlapped:ptr byte
			jmp	[__imp__WriteFile@20]
WriteFile 		endp

GetFileTime		proc	STDCALL	; handle:dword, create_time:ptr dword, access_time:ptr dword, write_time:ptr dword
			jmp	[__imp__GetFileTime@16]
GetFileTime 		endp

SetFileTime		proc	STDCALL	; handle:dword, create_time:ptr dword, access_time:ptr dword, write_time:ptr dword
			jmp	[__imp__SetFileTime@16]
SetFileTime 		endp

SetFilePointer		proc	STDCALL	; handle:dword, distance:dword, dist_high:ptr dword, method:dword
			jmp	[__imp__SetFilePointer@16]
SetFilePointer 		endp

FileTimeToLocalFileTime	proc	STDCALL	; utc_time:ptr dword, local_time:ptr dword
			jmp	[__imp__FileTimeToLocalFileTime@8]
FileTimeToLocalFileTime	endp

GetUserName		proc	STDCALL	; buffer:ptr byte, buffer_len:ptr dword
			jmp	[__imp__GetUserNameA@8]
GetUserName		endp

GetCommandLine		proc	STDCALL
			jmp	[__imp__GetCommandLineA@0]
GetCommandLine		endp

		_text	ends



end