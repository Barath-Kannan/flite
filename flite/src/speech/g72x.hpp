#pragma once

#include "flite/synthcommon/wave.hpp"

#define AUDIO_ENCODING_ULAW (1)   /* ISDN u-law */
#define AUDIO_ENCODING_ALAW (2)   /* ISDN A-law */
#define AUDIO_ENCODING_LINEAR (3) /* PCM 2's-complement (0-center) */

/*
 * The following is the definition of the state structure
 * used by the G.721/G.723 encoder and decoder to preserve their internal
 * state between successive calls.  The meanings of the majority
 * of the state structure fields are explained in detail in the
 * CCITT Recommendation G.721.  The field names are essentially indentical
 * to variable names in the bit level description of the coding algorithm
 * included in this Recommendation.
 */
struct g72x_state {
    long yl;   /* Locked or steady state step size multiplier. */
    short yu;  /* Unlocked or non-steady state step size multiplier. */
    short dms; /* Short term energy estimate. */
    short dml; /* Long term energy estimate. */
    short ap;  /* Linear weighting coefficient of 'yl' and 'yu'. */

    short a[2];  /* Coefficients of pole portion of prediction filter. */
    short b[6];  /* Coefficients of zero portion of prediction filter. */
    short pk[2]; /*
			 * Signs of previous two samples of a partially
			 * reconstructed signal.
			 */
    short dq[6]; /*
			 * Previous 6 samples of the quantized difference
			 * signal represented in an internal floating point
			 * format.
			 */
    short sr[2]; /*
			 * Previous 2 samples of the quantized difference
			 * signal represented in an internal floating point
			 * format.
			 */
    char td;     /* delayed tone detect, new in 1988 version */
};

/* External function definitions. */

extern void g72x_init_state(struct g72x_state*);
extern int g721_encoder(
    int sample,
    int in_coding,
    struct g72x_state* state_ptr);
extern int g721_decoder(
    int code,
    int out_coding,
    struct g72x_state* state_ptr);
extern int g723_24_encoder(
    int sample,
    int in_coding,
    struct g72x_state* state_ptr);
extern int g723_24_decoder(
    int code,
    int out_coding,
    struct g72x_state* state_ptr);
extern int g723_40_encoder(
    int sample,
    int in_coding,
    struct g72x_state* state_ptr);
extern int g723_40_decoder(
    int code,
    int out_coding,
    struct g72x_state* state_ptr);

/* Internal functions */
int g72x_predictor_zero(struct g72x_state* state_ptr);
int g72x_predictor_pole(struct g72x_state* state_ptr);
int g72x_step_size(struct g72x_state* state_ptr);
int g72x_quantize(
    int d,        /* Raw difference signal sample */
    int y,        /* Step size multiplier */
    short* table, /* quantization table */
    int size);    /* table size of short integers */
int g72x_reconstruct(
    int sign, /* 0 for non-negative value */
    int dqln, /* G.72x codeword */
    int y);   /* Step size multiplier */
void g72x_update(
    int code_size,                 /* distinguish 723_40 with others */
    int y,                         /* quantizer step size */
    int wi,                        /* scale factor multiplier */
    int fi,                        /* for long/short term energies */
    int dq,                        /* quantized prediction difference */
    int sr,                        /* reconstructed signal */
    int dqsez,                     /* difference from 2-pole predictor */
    struct g72x_state* state_ptr); /* coder state pointer */
