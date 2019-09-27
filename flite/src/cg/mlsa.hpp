#pragma once

#include "flite/cg/cg.hpp"

#include "flite/audio/audio.hpp"
#include "flite/synthcommon/wave.hpp"

#include "./vc.hpp"

/* static void waveampcheck(DVECTOR wav, XBOOL msg_flag); */

#define RANDMAX 32767
#define B0 0x00000001
#define B28 0x10000000
#define B31 0x80000000
#define B31_ 0x7fffffff
#define Z 0x00000000

typedef struct _VocoderSetup {
    int fprd;
    int iprd;
    int seed;
    int pd;
    unsigned long next;
    Boolean gauss;
    double p1;
    double pc;
    double pj;
    double pade[21];
    double* ppade;
    double *c, *cc, *cinc, *d1;
    double rate;

    int sw;
    double r1, r2, s;

    int x;

    /* for postfiltering */
    int size;
    double* d;
    double* g;
    double* mc;
    double* cep;
    double* ir;
    int o;
    int irleng;

    /* for MIXED EXCITATION */
    int ME_order;
    int ME_num;
    double* hpulse;
    double* hnoise;

    double* xpulsesig;
    double* xnoisesig;

    const double* const* h;

} VocoderSetup;

static void init_vocoder(double fs, int framel, int m, VocoderSetup* vs, cst_cg_db* cg_db);
static void vocoder(double p, double* mc, const float* str, int m, cst_cg_db* cg_db, VocoderSetup* vs, cst_wave* wav, long* pos);
static double mlsadf(double x, double* b, int m, double a, int pd, double* d, VocoderSetup* vs);
static double mlsadf1(double x, double* b, int m, double a, int pd, double* d, VocoderSetup* vs);
static double mlsadf2(double x, double* b, int m, double a, int pd, double* d, VocoderSetup* vs);
static double mlsafir(double x, double* b, int m, double a, double* d);
static double nrandom(VocoderSetup* vs);
static double rnd(unsigned long* next);
static unsigned long srnd(unsigned long seed);
static void mc2b(double* mc, double* b, int m, double a);
static double b2en(double* b, int m, double a, VocoderSetup* vs);
static void b2mc(double* b, double* mc, int m, double a);
static void freqt(double* c1, int m1, double* c2, int m2, double a, VocoderSetup* vs);
static void c2ir(double* c, int nc, double* h, int leng);

static void free_vocoder(VocoderSetup* vs);
