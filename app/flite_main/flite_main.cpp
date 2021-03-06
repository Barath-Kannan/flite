#include "flite/flite.hpp"
#include "flite/flite_version.hpp"

#include <boost/optional.hpp>

#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

std::vector<flite::voice> flite_set_voice_list(std::string_view voxdir);
void* flite_set_lang_list(void);

void cst_alloc_debug_summary();

/* Its not very appropriate that these are declared here */
void usenglish_init(cst_voice* v);
cst_lexicon* cmu_lex_init(void);

static void flite_version()
{
    printf("  Carnegie Mellon University, Copyright (c) 1999-2016, all rights reserved\n");
    printf("  version: %s-%s-%s %s (http://cmuflite.org)\n", FLITE_PROJECT_PREFIX, FLITE_PROJECT_VERSION, FLITE_PROJECT_STATE, FLITE_PROJECT_DATE);
}

static void flite_usage()
{
    printf("flite: a small simple speech synthesizer\n");
    flite_version();
    printf(
        "usage: flite TEXT/FILE [WAVEFILE]\n"
        "  Converts text in TEXTFILE to a waveform in WAVEFILE\n"
        "  If text contains a space the it is treated as a literal\n"
        "  textstring and spoken, and not as a file name\n"
        "  if WAVEFILE is unspecified or \"play\" the result is\n"
        "  played on the current systems audio device.  If WAVEFILE\n"
        "  is \"none\" the waveform is discarded (good for benchmarking)\n"
        "  Other options must appear before these options\n"
        "  --version   Output flite version number\n"
        "  --help      Output usage string\n"
        "  -o WAVEFILE Explicitly set output filename\n"
        "  -f TEXTFILE Explicitly set input filename\n"
        "  -t TEXT     Explicitly set input textstring\n"
        "  -p PHONES   Explicitly set input textstring and synthesize as phones\n"
        "  --set F=V   Set feature (guesses type)\n"
        "  -s F=V      Set feature (guesses type)\n"
        "  --seti F=V  Set int feature\n"
        "  --setf F=V  Set float feature\n"
        "  --sets F=V  Set string feature\n"
        "  -ssml       Read input text/file in ssml mode\n"
        "  -b          Benchmark mode\n"
        "  -l          Loop endlessly\n"
        "  -voice NAME Use voice NAME (NAME can be pathname/url to flitevox file)\n"
        "  -voicedir NAME Directory containing (clunit) voice data\n"
        "  -lv         List voices available\n"
        "  -add_lex FILENAME add lex addenda from FILENAME\n"
        "  -pw         Print words\n"
        "  -ps         Print segments\n"
        "  -psdur      Print segments and their durations (end-time)\n"
        "  -pr RelName Print relation RelName\n"
        "  -voicedump FILENAME Dump selected (cg) voice to FILENAME\n"
        "  -v          Verbose mode\n");
    exit(0);
}

static void print_voice_list(const std::vector<flite::voice>& voices)
{
    printf("Voices available: \n");
    for (const flite::voice& v : voices)
        std::cout << v->name << " ";
    std::cout << "\n";
    return;
}

static auto get_voice(
    const std::string& s,
    std::vector<flite::voice>& voices)
    -> boost::optional<flite::voice&>
{
    auto it = std::find_if(voices.begin(), voices.end(), [&](const flite::voice& voice) {
        return s == voice->name;
    });
    if (it == voices.end())
        return boost::none;
    return *it;
}

static cst_utterance* print_info(cst_utterance* u)
{
    cst_item* item;
    const char* relname;
    int printEndTime = 0;
    int printStress = 0;

    relname = utt_feat_string(u, "print_info_relation");
    if (cst_streq(relname, "SegmentEndTime")) {
        relname = "Segment";
        printEndTime = 1;
    }
    if (cst_streq(relname, "SegmentStress")) {
        relname = "Segment";
        printStress = 1;
    }

    for (item = relation_head(utt_relation(u, relname));
         item;
         item = item_next(item)) {
        if (!printEndTime)
            printf("%s", item_feat_string(item, "name"));
        else
            printf("%s:%1.3f", item_feat_string(item, "name"), item_feat_float(item, "end"));
        if (printStress == 1) {
            if (cst_streq("+", ffeature_string(item, "ph_vc")))
                printf("%s", ffeature_string(item, "R:SylStructure.parent.stress"));
        }
        printf(" ");
    }
    printf("\n");

    return u;
}

static void ef_set(cst_features* f, const char* fv, const char* type)
{
    /* set feature from fv (F=V), guesses type if not explicit type given */
    const char* val;
    char* feat;
    const char* fname;

    if ((val = strchr(fv, '=')) == 0) {
        fprintf(stderr, "flite: can't find '=' in featval \"%s\", ignoring it\n", fv);
    }
    else {
        feat = cst_strdup(fv);
        feat[cst_strlen(fv) - cst_strlen(val)] = '\0';
        fname = feat_own_string(f, feat);
        val = val + 1;
        if ((type && cst_streq("int", type)) ||
            ((type == 0) && (cst_regex_match(cst_rx_int, val))))
            feat_set_int(f, fname, atoi(val));
        else if ((type && cst_streq("float", type)) || ((type == 0) && (cst_regex_match(cst_rx_double, val))))
            feat_set_float(f, fname, atof(val));
        else
            feat_set_string(f, fname, val);
        cst_free(feat);
    }
}

int main(int argc, char** argv)
{
    struct timeval tv;
    cst_voice* v;
    const char* filename;
    const char* outtype;
    boost::optional<flite::voice&> desired_voice;
    std::string_view voice_dir;
    int i;
    float durs;
    double time_start, time_end;
    int flite_verbose, flite_loop, flite_bench;
    int explicit_filename, explicit_text, explicit_phones, ssml_mode;
#define ITER_MAX 3
    int bench_iter = 0;
    cst_features* extra_feats;
    const char* lex_addenda_file = NULL;
    const char* voicedumpfile = NULL;
    cst_audio_streaming_info* asi;
    std::vector<flite::voice> voices;

    filename = 0;
    outtype = "play"; /* default is to play */
    flite_verbose = FALSE;
    flite_loop = FALSE;
    flite_bench = FALSE;
    explicit_text = explicit_filename = explicit_phones = FALSE;
    ssml_mode = FALSE;
    extra_feats = new_features();

    flite_set_lang_list(); /* defined at compilation time */

    for (i = 1; i < argc; i++) {
        if (cst_streq(argv[i], "--version")) {
            flite_version();
            return 1;
        }
        else if (cst_streq(argv[i], "-h") || cst_streq(argv[i], "--help") || cst_streq(argv[i], "-?"))
            flite_usage();
        else if (cst_streq(argv[i], "-v"))
            flite_verbose = TRUE;
        else if (cst_streq(argv[i], "-lv")) {
            if (voices.empty())
                voices = flite_set_voice_list(voice_dir);
            print_voice_list(voices);
            exit(0);
        }
        else if (cst_streq(argv[i], "-l"))
            flite_loop = TRUE;
        else if (cst_streq(argv[i], "-b")) {
            flite_bench = TRUE;
            break; /* ignore other arguments */
        }
        else if ((cst_streq(argv[i], "-o")) && (i + 1 < argc)) {
            outtype = argv[i + 1];
            i++;
        }
        else if ((cst_streq(argv[i], "-voice")) && (i + 1 < argc)) {
            if (voices.empty()) {
                voices = flite_set_voice_list(voice_dir);
            }
            desired_voice = get_voice(argv[i + 1], voices);
            i++;
        }
        else if ((cst_streq(argv[i], "-voicedir")) && (i + 1 < argc)) {
            voice_dir = argv[i + 1];
            if (voices.empty())
                voices = flite_set_voice_list(voice_dir);
            i++;
        }
        else if ((cst_streq(argv[i], "-add_lex")) && (i + 1 < argc)) {
            lex_addenda_file = argv[i + 1];
            i++;
        }
        else if (cst_streq(argv[i], "-f") && (i + 1 < argc)) {
            filename = argv[i + 1];
            explicit_filename = TRUE;
            i++;
        }
        else if (cst_streq(argv[i], "-pw")) {
            feat_set_string(extra_feats, "print_info_relation", "Word");
            feat_set(extra_feats, "post_synth_hook_func", uttfunc_val(&print_info));
        }
        else if (cst_streq(argv[i], "-ps")) {
            feat_set_string(extra_feats, "print_info_relation", "Segment");
            feat_set(extra_feats, "post_synth_hook_func", uttfunc_val(&print_info));
        }
        else if (cst_streq(argv[i], "-psdur")) {
            // Added by AUP Mar 2013 for extracting durations (end-time) of segments
            // (useful in talking heads, etc.)
            feat_set_string(extra_feats, "print_info_relation", "SegmentEndTime");
            feat_set(extra_feats, "post_synth_hook_func", uttfunc_val(&print_info));
        }
        else if (cst_streq(argv[i], "-psstress")) {
            feat_set_string(extra_feats, "print_info_relation", "SegmentStress");
            feat_set(extra_feats, "post_synth_hook_func", uttfunc_val(&print_info));
        }
        else if (cst_streq(argv[i], "-ssml")) {
            ssml_mode = TRUE;
        }
        else if (cst_streq(argv[i], "-pr") && (i + 1 < argc)) {
            feat_set_string(extra_feats, "print_info_relation", argv[i + 1]);
            feat_set(extra_feats, "post_synth_hook_func", uttfunc_val(&print_info));
            i++;
        }
        else if (cst_streq(argv[i], "-voicedump") && (i + 1 < argc)) {
            voicedumpfile = argv[i + 1];
            i++;
        }
        else if ((cst_streq(argv[i], "-set") || cst_streq(argv[i], "-s")) && (i + 1 < argc)) {
            ef_set(extra_feats, argv[i + 1], 0);
            i++;
        }
        else if (cst_streq(argv[i], "--seti") && (i + 1 < argc)) {
            ef_set(extra_feats, argv[i + 1], "int");
            i++;
        }
        else if (cst_streq(argv[i], "--setf") && (i + 1 < argc)) {
            ef_set(extra_feats, argv[i + 1], "float");
            i++;
        }
        else if (cst_streq(argv[i], "--sets") && (i + 1 < argc)) {
            ef_set(extra_feats, argv[i + 1], "string");
            i++;
        }
        else if (cst_streq(argv[i], "-p") && (i + 1 < argc)) {
            filename = argv[i + 1];
            explicit_phones = TRUE;
            i++;
        }
        else if (cst_streq(argv[i], "-t") && (i + 1 < argc)) {
            filename = argv[i + 1];
            explicit_text = TRUE;
            i++;
        }
        else if (filename)
            outtype = argv[i];
        else
            filename = argv[i];
    }

    if (filename == NULL) filename = "-"; /* stdin */
    if (voices.empty()) {
        voices = flite_set_voice_list(voice_dir);
    }
    assert(!voices.empty());
    if (!desired_voice)
        desired_voice = voices.front();

    v = desired_voice->operator->();
    feat_copy_into(extra_feats, v->features);
    durs = 0.0;

    if (voicedumpfile != NULL) {
        flite_voice_dump(v, voicedumpfile);
        exit(0);
    }

    if (lex_addenda_file)
        flite_voice_add_lex_addenda(v, lex_addenda_file);

    if (cst_streq("stream", outtype)) {
        asi = new_audio_streaming_info();
        asi->asc = audio_stream_chunk;
        feat_set(v->features, "streaming_info", audio_streaming_info_val(asi));
    }

    if (flite_bench) {
        outtype = "none";
        filename = "A whole joy was reaping, but they've gone south, you should fetch azure mike.";
        explicit_text = TRUE;
    }

loop:
    gettimeofday(&tv, NULL);
    time_start = (double)(tv.tv_sec) + (((double)tv.tv_usec) / 1000000.0);

    if (explicit_phones)
        durs = flite_phones_to_speech(filename, v, outtype);
    else if ((strchr(filename, ' ') && !explicit_filename) || explicit_text) {
        if (ssml_mode)
            durs = flite_ssml_text_to_speech(filename, v, outtype);
        else
            durs = flite_text_to_speech(filename, v, outtype);
    }
    else {
        if (ssml_mode)
            durs = flite_ssml_file_to_speech(filename, v, outtype);
        else
            durs = flite_file_to_speech(filename, v, outtype);
    }

    gettimeofday(&tv, NULL);
    time_end = ((double)(tv.tv_sec)) + ((double)tv.tv_usec / 1000000.0);

    if (flite_verbose || (flite_bench && bench_iter == ITER_MAX))
        printf("times faster than real-time: %f\n(%f seconds of speech synthesized in %f)\n", durs / (float)(time_end - time_start), durs, (float)(time_end - time_start));

    if (flite_loop || (flite_bench && bench_iter++ < ITER_MAX))
        goto loop;

    delete_features(extra_feats);
    /*    cst_alloc_debug_summary(); */

    return 0;
}
