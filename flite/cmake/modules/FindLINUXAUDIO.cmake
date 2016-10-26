#.rst:
# FindLINUXAUDIO
# --------
#
# Find Linux Audio
#
# Find the linux audio headers
#
# ::
#
#   This module defines the following variables:
#      LINUXAUDIO_FOUND        - True if LINUXAUDIO_INCLUDE_DIR is found
#      LINUXAUDIO_INCLUDE_DIRS - Set when LINUXAUDIO_INCLUDE_DIR is found
#
# ::
#
#      LINUXAUDIO_INCLUDE_DIR - where to find pulseaudio.h, etc.

find_path(LINUXAUDIO_INCLUDE_DIR NAMES sys/soundcard.h
    DOC "The Linux audio include directory"
)
find_package_handle_standard_args(LINUXAUDIO
    REQUIRED_VARS LINUXAUDIO_INCLUDE_DIR)

if(LINUXAUDIO_FOUND)
    set( LINUXAUDIO_INCLUDE_DIRS ${LINUX_INCLUDE_DIR} )
endif()

mark_as_advanced(LINUXAUDIO_INCLUDE_DIR)

