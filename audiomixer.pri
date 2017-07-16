static: DEFINES += DISABLE_FFT

# Disables rendering of the waveform
#DEFINES += DISABLE_WAVEFORM

# If defined, superimpose the progress bar on the waveform
DEFINES += SUPERIMPOSE_PROGRESS_ON_WAVEFORM

# Perform spectrum analysis calculation in a separate thread
DEFINES += SPECTRUM_ANALYSER_SEPARATE_THREAD

# Suppress warnings about strncpy potentially being unsafe, emitted by MSVC
win32: DEFINES += _CRT_SECURE_NO_WARNINGS

win32 {
    # audiomix_build_dir is defined with a leading slash so that it can
    # be used in contexts such as
    #     ..$${audiomix_build_dir}
    # without the result having a trailing slash where audiomix_build_dir
    # is undefined.
    build_pass {
        CONFIG(release, release|debug): audiomix_build_dir = /release
        CONFIG(debug, release|debug): audiomix_build_dir = /debug
    }
}
