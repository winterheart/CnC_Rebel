/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*++

Copyright (c) 1993  Microsoft Corporation

Module Name:

    monopub.h

Abstract:

    This module contains the PUBLIC (viewable by driver & Win32 apps)
    definitions for the IOCTLs supported by the MONO device driver.

Environment:

    Kernel & User mode

Revision History:

    03-22-93 : created

--*/

//
// Define the various device type values.  Note that values used by Microsoft
// Corporation are in the range 0-32767, and 32768-65535 are reserved for use
// by customers.
//
#define FILE_DEVICE_MONO  0x00008000

//
// The MONO device driver IOCTLs
//
#define IOCTL_MONO_CLEAR_SCREEN	CTL_CODE(FILE_DEVICE_MONO, 0x801, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_PRINT_RAW		CTL_CODE(FILE_DEVICE_MONO, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_SET_CURSOR		CTL_CODE(FILE_DEVICE_MONO, 0x802, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_SCROLL			CTL_CODE(FILE_DEVICE_MONO, 0x803, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_BRING_TO_TOP	CTL_CODE(FILE_DEVICE_MONO, 0x804, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_SET_ATTRIBUTE	CTL_CODE(FILE_DEVICE_MONO, 0x805, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_PAN				CTL_CODE(FILE_DEVICE_MONO, 0x806, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_LOCK				CTL_CODE(FILE_DEVICE_MONO, 0x807, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_UNLOCK			CTL_CODE(FILE_DEVICE_MONO, 0x808, METHOD_BUFFERED, FILE_WRITE_DATA)
#define IOCTL_MONO_SET_POS			CTL_CODE(FILE_DEVICE_MONO, 0x809, METHOD_BUFFERED, FILE_WRITE_DATA)

