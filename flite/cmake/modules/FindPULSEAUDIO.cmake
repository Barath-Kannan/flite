#.rst:
# FindPULSEAUDIO
# --------
#
# Find Pulse Audio
#
# Find the pulse audio libraries (pulse)
#
# ::
#
#   This module defines the following variables:
#      PULSEAUDIO_FOUND        - True if PULSEAUDIO_INCLUDE_DIR & PULSEAUDIO_LIBRARY are found
#      PULSEAUDIO_LIBRARIES    - Set when PULSEAUDIO_LIBRARY is found
#      PULSEAUDIO_INCLUDE_DIRS - Set when PULSEAUDIO_INCLUDE_DIR is found
#
# ::
#
#      PULSEAUDIO_INCLUDE_DIR - where to find pulseaudio.h, etc.
#      PULSEAUDIO_LIBRARY     - the pulse library

find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h
    DOC "The PulseAudio (pulse) include directory"
)

find_library(PULSEAUDIO_LIBRARY NAMES pulse
    DOC "The PulseAudio (pulse) library"
)

find_package_handle_standard_args(PULSEAUDIO
    REQUIRED_VARS PULSEAUDIO_LIBRARY PULSEAUDIO_INCLUDE_DIR)

if(PULSEAUDIO_FOUND)
    set( PULSEAUDIO_LIBRARIES ${PULSEAUDIO_LIBRARY} )
    set( PULSEAUDIO_INCLUDE_DIRS ${PULSEAUDIO_INCLUDE_DIR} )
endif()

mark_as_advanced(PULSEAUDIO_INCLUDE_DIR PULSEAUDIO_LIBRARY)

