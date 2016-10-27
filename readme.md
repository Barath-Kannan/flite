
         Flite: a small run-time speech synthesis engine
                      version 2.0.0-release
          Copyright Carnegie Mellon University 1999-2014
                      All rights reserved
                      http://cmuflite.org

This is a c++ and cmake port of the flite library (WIP) by me (Barath Kannan).

Flite is a small fast run-time speech synthesis engine.  It is the
latest addition to the suite of free software synthesis tools
including University of Edinburgh's Festival Speech Synthesis System
and Carnegie Mellon University's FestVox project, tools, scripts and
documentation for building synthetic voices.  However, flite itself
does not require either of these systems to compile and run.

The core Flite library was developed by Alan W Black <awb@cs.cmu.edu>
(mostly in his so-called spare time) while employed in the Language
Technologies Institute at Carnegie Mellon University.  The name
"flite", originally chosen to mean "festival-lite" is perhaps doubly
appropriate as a substantial part of design and coding was done over
30,000ft while awb was travelling, and (usually) isn't in meetings.

The voices, lexicon and language components of flite, both their
compression techniques and their actual contents were developed by
Kevin A. Lenzo <lenzo@cs.cmu.edu> and Alan W Black <awb@cs.cmu.edu>.

Flite is the answer to the complaint that Festival is too big, too slow,
and not portable enough.

o Flite is designed for very small devices, such as PDAs, and also
  for large server machines which need to serve lots of ports.
o Flite is not a replacement for Festival but an alternative run time
  engine for voices developed in the FestVox framework where size and
  speed is crucial.
o Flite is all in ANSI C, it contains no C++ (until now) or Scheme,
  thus requires more care in programming, and is harder to customize
  at run time.
o It is thread safe
o Voices, lexicons and language descriptions can be compiled
  (mostly automatically for voices and lexicons) into C representations
  from their FestVox formats
o All voices, lexicons and language model data are const and in the
  text segment (i.e. they may be put in ROM).  As they are linked in
  at compile time, there is virtually no startup delay.
o Although the synthesized output is not exactly the same as the same
  voice in Festival they are effectively equivalent.  That is, flite
  doesn't sound better or worse than the equivalent voice in festival,
  just faster, smaller and scalable.
o For standard diphone voices, maximum run time memory
  requirements are approximately less than twice the memory requirement
  for the waveform generated.  For 32bit archtectures
  this effectively means under 1M.
o The flite program supports, synthesis of individual strings or files
  (utterance by utterance) to direct audio devices or to waveform files.
o The flite library offers simple functions suitable for use in specific
  applications.
Flite is distributed with a single 8K diphone voice (derived from the
cmu_us_kal voice), a pruned lexicon (derived from
cmulex) and a set of models for US English.  Here are comparisons
with Festival using basically the same 8KHz diphone voice
                Flite    Festival
   core code    60K      2.6M
   USEnglish    100K     ??
   lexicon      600K     5M
   diphone      1.8M     2.1M
   runtime      <1M      16-20M

On a 500Mhz PIII, a timing test of the first two chapters of
"Alice in Wonderland" (doc/alice) was done.  This produces about
1300 seconds of speech.  With flite it takes 19.128 seconds (about
70.6 times faster than real time) with Festival it takes 97 seconds
(13.4 times faster than real time).  On the ipaq (with the 16KHz diphones)
flite synthesizes 9.79 time faster than real time.

Requirements:  

o CMake build system. On windows this can acquired from the installer on their website.
  Otherwise, your operating systems package manager will be able to acquire it.
o A compiler compatible cmake. Most compilers are already compatible.
o An audio device isn't required as flite can write its output to
  a waveform file.

Windows systems may need to specify the generator when generating the build files.

Supported platforms:

Cmake version has been tested on:
o Ubuntu with GCC
o Windows with Visual studio

News
----

New in 2.0.0 (Dec 2014)
    o Indic language support (Hindi, Tamil and Telugu)
    o SSML support
    o CG voices as files accessilble by file:/// and http://
      (and set of 13 voices to load)
    o random forest (multimodel support) improves voice quality
    o Supports diffrent sample rates/mgc order to tune for speed
    o Kal diphone 500K smaller
    o Fixed lots of API issues
    o thread safe (again) after initialization
    o Generalized tokenstreams (used in Bard Storyteller)
    o simple-Pulseaudio support
    o Improved Android support
    o Removed PalmOS support from distribution
    o Companion multilingual ebook reader Bard Storyteller
       http://festvox.org/bard/

New in 1.4.1 (March 2010)
    o better ssml support (actually does something)
    o better clunit support (smaller)
    o Android support

New in 1.4 (December 2009)
    o crude multi-voice selection support (may change)
    o 4 basic voices are included 3 clustergen (awb, rms and slt) plus
      the kal diphone database
    o CMULEX now uses maximum onset for syllabification
    o alsa support
    o Clustergen support (including mlpg with mixed excitation)
      But is still slow on limited processors
    o Windows support with Visual Studio (specifically for the Olympus
        Spoken Dialog System)
    o WinCE support is redone with cegcc/mingw32ce with example
        example TTS app: Flowm: Flite on Windows Mobile
    o Speed-ups in feature interpretation limiting calls to alloc
    o Speed-ups (and fixes) for converting clunits festvox voices

New in 1.3-release (October 2005)
    o fixes to lpc residual extraction to give better quality output
    o An updated lexicon (festlex_CMU from festival-2.0.95) and better
      compression its about 30% of the previous size, with about
      the same accuracy
    o Fairly substantial code movements to better support PalmOS and
      multi-platform cross compilation builds
    o A PalmOS 5.0 port with an small example talking app ("flop")
    o runs under ix86_64 linux

New in 1.2-release  (February 2003)
    o A build process for diphone and clunits/ldom voices
      FestVox voices can be converted (sometimes) automatically
    o Various bug fixes
    o Initial support for Mac OS X (not talking to audio device yet)
      but compiles and runs
    o Text files can be synthesize to a single audio file
    o (optional) shared library support (Linux)

Compilation
-----------

In general

    git clone https://github.com/Barath-Kannan/flite flite
    cd flite
    cmake -Bbuild -H.
    cmake --build build --config Release

Usage:
------

The ./bin/flite voices contains all supported voices and you may
choose between the voices with the -voice flag and list the supported
voices with the -lw flag.  Note the kal (diphone) voice is a different
technology from the others and is much less computationally expensive
but more robotic.  For each voice additional binaries that contain
only that voice are created in ./bin/flite_FULLVOICENAME,
e.g. ./bin/flite_cmu_us_awb.

If it compiles properly a binary will be put in bin/, note by
default -g is on so it will be bigger than is actually required

   ./bin/flite "Flite is a small fast run-time synthesis engine" flite.wav

Will produce an 8KHz riff headered waveform file (riff is Microsoft's
wave format often called .WAV).

   ./bin/flite doc/alice

Will play the text file doc/alice.  If the first argument contains
a space it is treated as text otherwise it is treated as a filename.
If a second argument is given a waveform file is written to it,
if no argument is given or "play" is given it will attempt to
write directly to the audio device (if supported).  if "none"
is given the audio is simply thrown away (used for benchmarking).
Explicit options are also available.

   ./bin/flite -v doc/alice none

Will synthesize the file without playing the audio and give a summary
of the speed.

   ./bin/flite doc/alice alice.wav

will synthesize the whole of alice into a single file (previoous
versions would only give the last utterance in the file, but
that is fixed now).

An additional set of feature setting options are available, these are
*debug* options, Voices are represented as sets of feature values (see
lang/cmu_us_kal/cmu_us_kal.c) and you can override values on the
command line.  This can stop flite from working if malicious values
are set and therefor this facility is not intended to be made
available for standard users.  But these are useful for
debugging.  Some typical examples are

./bin/flite --sets join_type=simple_join doc/intro
     Use simple concatenation of diphones without prosodic modification
./bin/flite -pw doc/alice
     Print sentences as they are said
./bin/flite --setf duration_stretch=1.5 doc/alice
     Make it speak slower
./bin/flite --setf int_f0_target_mean=145 doc/alice
     Make it speak higher

The talking clock is an example talking clode as discussed on
http://festvox.org/ldom it requires a single argument HH:MM
under Unix you can call it
    ./bin/flite_time `date +%H:%M`

./bin/flite -lv
    List the voices linked in directly in this build

./bin/flite -voice rms -f doc/alice
    Speak with the US male rms voice
./bin/flite -voice awb -f doc/alice
    Speak with the "Scottish" male awb voice
./bin/flite -voice slt -f doc/alice
    Speak with the US female slt voice

./bin/flite -voice http://festvox.org/flite/voices/US/cmu_us_ksp.flitevox -f doc/alice
    Speak with KSP voice, download on the fly from festvox.org
./bin/flite -voice voices/cmu_us_ahw.flitevox -f doc/alice
    Speak with AHW voice loaded from the local file.

Voice names are identified as loadable files if the name includes a
"/" (slash) otherwise they are treated as internal names.  So if you
want to load voices from the current directory you need to prefix the
with "./".

Voice quality
-------------

So you've eagerly downloaded flite, compiled it and run it, now you
are disappointed that it doesn't sound wonderful, sure its fast and
small but what you really hoped for was the dulcit tones of a deep
baritone voice that would make you desperately hang on every phrase it
mellifluously produces.  But instead you get an 8Khz diphone voice that
sounds like it came from the last millenium.

Well, first, you are right, it is an 8KHz diphone voice from the last
millenium, and that was actually deliberate.  As we developed flite we
wanted a voice that was stable and that we could directly compare with
that very same voice in Festival.  Flite is an *engine*.  We want to
be able take voices built with the FestVox process and compile them
for flite, the result should be exactly the same quality (though of
course trading the size for quality in flite is also an option).  The
included voice is just a sample voice that was used in the testing
process.  

We expect that often voices will be loaded from external files, and we
have now set up a voice repository on
   http://festvox.org/flite/voices/LANG/*.flitevox
If you visit there with a browser you can hear the examples.  You can
also download the .flitevox files to you machine so you don't need a
network connect everytime you need to load a voice.

We are now actively adding to this list of available voices in English
and other languages.

Bard Storyteller:  http://festvox.org/bard/
-------------------------------------------

Bard is a companion app that read ebooks, both displaying them and
actually reading them to you using flite.  Bard supports a wide
range of fonts, and flite voices, and books in text, html and
epub format.  Bard is used as a evaluation of flites capabilities
and an example of a serious application using flite.
