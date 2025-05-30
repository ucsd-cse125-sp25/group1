/* ============================================================================================================= */
/* FMOD Core API - Built-in effects header file.                                                                 */
/* Copyright (c), Firelight Technologies Pty, Ltd. 2004-2025.                                                    */
/*                                                                                                               */
/* In this header you can find parameter structures for FMOD system registered DSP effects                       */
/* and generators.                                                                                               */
/*                                                                                                               */
/* For more detail visit:                                                                                        */
/* https://fmod.com/docs/2.03/api/core-api-common-dsp-effects.html#fmod_dsp_type                                 */
/* ============================================================================================================= */

#ifndef _FMOD_DSP_EFFECTS_H
#define _FMOD_DSP_EFFECTS_H

typedef enum
{
    FMOD_DSP_TYPE_UNKNOWN,
    FMOD_DSP_TYPE_MIXER,
    FMOD_DSP_TYPE_OSCILLATOR,
    FMOD_DSP_TYPE_LOWPASS,
    FMOD_DSP_TYPE_ITLOWPASS,
    FMOD_DSP_TYPE_HIGHPASS,
    FMOD_DSP_TYPE_ECHO,
    FMOD_DSP_TYPE_FADER,
    FMOD_DSP_TYPE_FLANGE,
    FMOD_DSP_TYPE_DISTORTION,
    FMOD_DSP_TYPE_NORMALIZE,
    FMOD_DSP_TYPE_LIMITER,
    FMOD_DSP_TYPE_PARAMEQ,
    FMOD_DSP_TYPE_PITCHSHIFT,
    FMOD_DSP_TYPE_CHORUS,
    FMOD_DSP_TYPE_ITECHO,
    FMOD_DSP_TYPE_COMPRESSOR,
    FMOD_DSP_TYPE_SFXREVERB,
    FMOD_DSP_TYPE_LOWPASS_SIMPLE,
    FMOD_DSP_TYPE_DELAY,
    FMOD_DSP_TYPE_TREMOLO,
    FMOD_DSP_TYPE_SEND,
    FMOD_DSP_TYPE_RETURN,
    FMOD_DSP_TYPE_HIGHPASS_SIMPLE,
    FMOD_DSP_TYPE_PAN,
    FMOD_DSP_TYPE_THREE_EQ,
    FMOD_DSP_TYPE_FFT,
    FMOD_DSP_TYPE_LOUDNESS_METER,
    FMOD_DSP_TYPE_CONVOLUTIONREVERB,
    FMOD_DSP_TYPE_CHANNELMIX,
    FMOD_DSP_TYPE_TRANSCEIVER,
    FMOD_DSP_TYPE_OBJECTPAN,
    FMOD_DSP_TYPE_MULTIBAND_EQ,
    FMOD_DSP_TYPE_MULTIBAND_DYNAMICS,

    FMOD_DSP_TYPE_MAX,
    FMOD_DSP_TYPE_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_TYPE;

/*
    ===================================================================================================

    FMOD built in effect parameters.  
    Use DSP::setParameter with these enums for the 'index' parameter.

    ===================================================================================================
*/

typedef enum
{
    FMOD_DSP_OSCILLATOR_TYPE,
    FMOD_DSP_OSCILLATOR_RATE
} FMOD_DSP_OSCILLATOR;


typedef enum
{
    FMOD_DSP_LOWPASS_CUTOFF,
    FMOD_DSP_LOWPASS_RESONANCE
} FMOD_DSP_LOWPASS;


typedef enum
{
    FMOD_DSP_ITLOWPASS_CUTOFF,
    FMOD_DSP_ITLOWPASS_RESONANCE
} FMOD_DSP_ITLOWPASS;


typedef enum
{
    FMOD_DSP_HIGHPASS_CUTOFF,
    FMOD_DSP_HIGHPASS_RESONANCE
} FMOD_DSP_HIGHPASS;


typedef enum
{
    FMOD_DSP_ECHO_DELAY,
    FMOD_DSP_ECHO_FEEDBACK,
    FMOD_DSP_ECHO_DRYLEVEL,
    FMOD_DSP_ECHO_WETLEVEL,
    FMOD_DSP_ECHO_DELAYCHANGEMODE
} FMOD_DSP_ECHO;


typedef enum
{
    FMOD_DSP_ECHO_DELAYCHANGEMODE_FADE,
    FMOD_DSP_ECHO_DELAYCHANGEMODE_LERP,
    FMOD_DSP_ECHO_DELAYCHANGEMODE_NONE
} FMOD_DSP_ECHO_DELAYCHANGEMODE_TYPE;


typedef enum FMOD_DSP_FADER
{
    FMOD_DSP_FADER_GAIN,
    FMOD_DSP_FADER_OVERALL_GAIN,
} FMOD_DSP_FADER;


typedef enum
{
    FMOD_DSP_FLANGE_MIX,
    FMOD_DSP_FLANGE_DEPTH,
    FMOD_DSP_FLANGE_RATE
} FMOD_DSP_FLANGE;


typedef enum
{
    FMOD_DSP_DISTORTION_LEVEL
} FMOD_DSP_DISTORTION;


typedef enum
{
    FMOD_DSP_NORMALIZE_FADETIME,
    FMOD_DSP_NORMALIZE_THRESHOLD,
    FMOD_DSP_NORMALIZE_MAXAMP
} FMOD_DSP_NORMALIZE;


typedef enum
{
    FMOD_DSP_LIMITER_RELEASETIME,
    FMOD_DSP_LIMITER_CEILING,
    FMOD_DSP_LIMITER_MAXIMIZERGAIN,
    FMOD_DSP_LIMITER_MODE,
} FMOD_DSP_LIMITER;


typedef enum
{
    FMOD_DSP_PARAMEQ_CENTER,
    FMOD_DSP_PARAMEQ_BANDWIDTH,
    FMOD_DSP_PARAMEQ_GAIN
} FMOD_DSP_PARAMEQ;


typedef enum FMOD_DSP_MULTIBAND_EQ
{
    FMOD_DSP_MULTIBAND_EQ_A_FILTER,
    FMOD_DSP_MULTIBAND_EQ_A_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_A_Q,
    FMOD_DSP_MULTIBAND_EQ_A_GAIN,
    FMOD_DSP_MULTIBAND_EQ_B_FILTER,
    FMOD_DSP_MULTIBAND_EQ_B_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_B_Q,
    FMOD_DSP_MULTIBAND_EQ_B_GAIN,
    FMOD_DSP_MULTIBAND_EQ_C_FILTER,
    FMOD_DSP_MULTIBAND_EQ_C_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_C_Q,
    FMOD_DSP_MULTIBAND_EQ_C_GAIN,
    FMOD_DSP_MULTIBAND_EQ_D_FILTER,
    FMOD_DSP_MULTIBAND_EQ_D_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_D_Q,
    FMOD_DSP_MULTIBAND_EQ_D_GAIN,
    FMOD_DSP_MULTIBAND_EQ_E_FILTER,
    FMOD_DSP_MULTIBAND_EQ_E_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_E_Q,
    FMOD_DSP_MULTIBAND_EQ_E_GAIN,
} FMOD_DSP_MULTIBAND_EQ;


typedef enum FMOD_DSP_MULTIBAND_EQ_FILTER_TYPE
{
    FMOD_DSP_MULTIBAND_EQ_FILTER_DISABLED,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_12DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_24DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_48DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_12DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_24DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_48DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWSHELF,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHSHELF,
    FMOD_DSP_MULTIBAND_EQ_FILTER_PEAKING,
    FMOD_DSP_MULTIBAND_EQ_FILTER_BANDPASS,
    FMOD_DSP_MULTIBAND_EQ_FILTER_NOTCH,
    FMOD_DSP_MULTIBAND_EQ_FILTER_ALLPASS,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_6DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_6DB,
} FMOD_DSP_MULTIBAND_EQ_FILTER_TYPE;


typedef enum FMOD_DSP_MULTIBAND_DYNAMICS
{
    FMOD_DSP_MULTIBAND_DYNAMICS_LOWER_FREQUENCY,
    FMOD_DSP_MULTIBAND_DYNAMICS_UPPER_FREQUENCY,
    FMOD_DSP_MULTIBAND_DYNAMICS_LINKED,
    FMOD_DSP_MULTIBAND_DYNAMICS_USE_SIDECHAIN,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_MODE,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_GAIN,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_THRESHOLD,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_RATIO,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_ATTACK,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_RELEASE,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_GAIN_MAKEUP,
    FMOD_DSP_MULTIBAND_DYNAMICS_A_RESPONSE_DATA,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_MODE,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_GAIN,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_THRESHOLD,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_RATIO,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_ATTACK,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_RELEASE,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_GAIN_MAKEUP,
    FMOD_DSP_MULTIBAND_DYNAMICS_B_RESPONSE_DATA,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_MODE,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_GAIN,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_THRESHOLD,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_RATIO,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_ATTACK,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_RELEASE,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_GAIN_MAKEUP,
    FMOD_DSP_MULTIBAND_DYNAMICS_C_RESPONSE_DATA,
} FMOD_DSP_MULTIBAND_DYNAMICS;


typedef enum FMOD_DSP_MULTIBAND_DYNAMICS_MODE_TYPE
{
    FMOD_DSP_MULTIBAND_DYNAMICS_MODE_DISABLED,
    FMOD_DSP_MULTIBAND_DYNAMICS_MODE_COMPRESS_UP,
    FMOD_DSP_MULTIBAND_DYNAMICS_MODE_COMPRESS_DOWN,
    FMOD_DSP_MULTIBAND_DYNAMICS_MODE_EXPAND_UP,
    FMOD_DSP_MULTIBAND_DYNAMICS_MODE_EXPAND_DOWN
} FMOD_DSP_MULTIBAND_DYNAMICS_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PITCHSHIFT_PITCH,
    FMOD_DSP_PITCHSHIFT_FFTSIZE,
    FMOD_DSP_PITCHSHIFT_OVERLAP,
    FMOD_DSP_PITCHSHIFT_MAXCHANNELS
} FMOD_DSP_PITCHSHIFT;


typedef enum
{
    FMOD_DSP_CHORUS_MIX,
    FMOD_DSP_CHORUS_RATE,
    FMOD_DSP_CHORUS_DEPTH,
} FMOD_DSP_CHORUS;


typedef enum
{
    FMOD_DSP_ITECHO_WETDRYMIX,
    FMOD_DSP_ITECHO_FEEDBACK,
    FMOD_DSP_ITECHO_LEFTDELAY,
    FMOD_DSP_ITECHO_RIGHTDELAY,
    FMOD_DSP_ITECHO_PANDELAY
} FMOD_DSP_ITECHO;

typedef enum
{
    FMOD_DSP_COMPRESSOR_THRESHOLD, 
    FMOD_DSP_COMPRESSOR_RATIO, 
    FMOD_DSP_COMPRESSOR_ATTACK,
    FMOD_DSP_COMPRESSOR_RELEASE,
    FMOD_DSP_COMPRESSOR_GAINMAKEUP,
    FMOD_DSP_COMPRESSOR_USESIDECHAIN,
    FMOD_DSP_COMPRESSOR_LINKED
} FMOD_DSP_COMPRESSOR;

typedef enum
{
    FMOD_DSP_SFXREVERB_DECAYTIME,
    FMOD_DSP_SFXREVERB_EARLYDELAY,
    FMOD_DSP_SFXREVERB_LATEDELAY,
    FMOD_DSP_SFXREVERB_HFREFERENCE,
    FMOD_DSP_SFXREVERB_HFDECAYRATIO,
    FMOD_DSP_SFXREVERB_DIFFUSION,
    FMOD_DSP_SFXREVERB_DENSITY,
    FMOD_DSP_SFXREVERB_LOWSHELFFREQUENCY,
    FMOD_DSP_SFXREVERB_LOWSHELFGAIN,
    FMOD_DSP_SFXREVERB_HIGHCUT,
    FMOD_DSP_SFXREVERB_EARLYLATEMIX,
    FMOD_DSP_SFXREVERB_WETLEVEL,
    FMOD_DSP_SFXREVERB_DRYLEVEL
} FMOD_DSP_SFXREVERB;

typedef enum
{
    FMOD_DSP_LOWPASS_SIMPLE_CUTOFF
} FMOD_DSP_LOWPASS_SIMPLE;


typedef enum
{
    FMOD_DSP_DELAY_CH0,
    FMOD_DSP_DELAY_CH1,
    FMOD_DSP_DELAY_CH2,
    FMOD_DSP_DELAY_CH3,
    FMOD_DSP_DELAY_CH4,
    FMOD_DSP_DELAY_CH5,
    FMOD_DSP_DELAY_CH6,
    FMOD_DSP_DELAY_CH7,
    FMOD_DSP_DELAY_CH8,
    FMOD_DSP_DELAY_CH9,
    FMOD_DSP_DELAY_CH10,
    FMOD_DSP_DELAY_CH11,
    FMOD_DSP_DELAY_CH12,
    FMOD_DSP_DELAY_CH13,
    FMOD_DSP_DELAY_CH14,
    FMOD_DSP_DELAY_CH15,
    FMOD_DSP_DELAY_MAXDELAY
} FMOD_DSP_DELAY;


typedef enum
{
    FMOD_DSP_TREMOLO_FREQUENCY,
    FMOD_DSP_TREMOLO_DEPTH,
    FMOD_DSP_TREMOLO_SHAPE,
    FMOD_DSP_TREMOLO_SKEW,
    FMOD_DSP_TREMOLO_DUTY,
    FMOD_DSP_TREMOLO_SQUARE,
    FMOD_DSP_TREMOLO_PHASE,
    FMOD_DSP_TREMOLO_SPREAD
} FMOD_DSP_TREMOLO;


typedef enum
{
    FMOD_DSP_SEND_RETURNID,
    FMOD_DSP_SEND_LEVEL,
} FMOD_DSP_SEND;


typedef enum
{
    FMOD_DSP_RETURN_ID,
    FMOD_DSP_RETURN_INPUT_SPEAKER_MODE
} FMOD_DSP_RETURN;


typedef enum
{
    FMOD_DSP_HIGHPASS_SIMPLE_CUTOFF
} FMOD_DSP_HIGHPASS_SIMPLE;


typedef enum
{
    FMOD_DSP_PAN_2D_STEREO_MODE_DISTRIBUTED,
    FMOD_DSP_PAN_2D_STEREO_MODE_DISCRETE
} FMOD_DSP_PAN_2D_STEREO_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PAN_MODE_MONO,
    FMOD_DSP_PAN_MODE_STEREO,
    FMOD_DSP_PAN_MODE_SURROUND
} FMOD_DSP_PAN_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PAN_3D_ROLLOFF_LINEARSQUARED,
    FMOD_DSP_PAN_3D_ROLLOFF_LINEAR,
    FMOD_DSP_PAN_3D_ROLLOFF_INVERSE,
    FMOD_DSP_PAN_3D_ROLLOFF_INVERSETAPERED,
    FMOD_DSP_PAN_3D_ROLLOFF_CUSTOM
} FMOD_DSP_PAN_3D_ROLLOFF_TYPE;


typedef enum
{
    FMOD_DSP_PAN_3D_EXTENT_MODE_AUTO,
    FMOD_DSP_PAN_3D_EXTENT_MODE_USER,
    FMOD_DSP_PAN_3D_EXTENT_MODE_OFF
} FMOD_DSP_PAN_3D_EXTENT_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PAN_MODE,
    FMOD_DSP_PAN_2D_STEREO_POSITION,
    FMOD_DSP_PAN_2D_DIRECTION,
    FMOD_DSP_PAN_2D_EXTENT,
    FMOD_DSP_PAN_2D_ROTATION,
    FMOD_DSP_PAN_2D_LFE_LEVEL,
    FMOD_DSP_PAN_2D_STEREO_MODE,
    FMOD_DSP_PAN_2D_STEREO_SEPARATION,
    FMOD_DSP_PAN_2D_STEREO_AXIS,
    FMOD_DSP_PAN_ENABLED_SPEAKERS,
    FMOD_DSP_PAN_3D_POSITION,
    FMOD_DSP_PAN_3D_ROLLOFF,
    FMOD_DSP_PAN_3D_MIN_DISTANCE,
    FMOD_DSP_PAN_3D_MAX_DISTANCE,
    FMOD_DSP_PAN_3D_EXTENT_MODE,
    FMOD_DSP_PAN_3D_SOUND_SIZE,
    FMOD_DSP_PAN_3D_MIN_EXTENT,
    FMOD_DSP_PAN_3D_PAN_BLEND,
    FMOD_DSP_PAN_LFE_UPMIX_ENABLED,
    FMOD_DSP_PAN_OVERALL_GAIN,
    FMOD_DSP_PAN_SURROUND_SPEAKER_MODE,
    FMOD_DSP_PAN_2D_HEIGHT_BLEND,
    FMOD_DSP_PAN_ATTENUATION_RANGE,
    FMOD_DSP_PAN_OVERRIDE_RANGE
} FMOD_DSP_PAN;


typedef enum
{
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_12DB,
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_24DB,
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_48DB
} FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_TYPE;


typedef enum
{
    FMOD_DSP_THREE_EQ_LOWGAIN,
    FMOD_DSP_THREE_EQ_MIDGAIN,
    FMOD_DSP_THREE_EQ_HIGHGAIN,
    FMOD_DSP_THREE_EQ_LOWCROSSOVER,
    FMOD_DSP_THREE_EQ_HIGHCROSSOVER,
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE
} FMOD_DSP_THREE_EQ;


typedef enum
{
    FMOD_DSP_FFT_WINDOW_RECT,
    FMOD_DSP_FFT_WINDOW_TRIANGLE,
    FMOD_DSP_FFT_WINDOW_HAMMING,
    FMOD_DSP_FFT_WINDOW_HANNING,
    FMOD_DSP_FFT_WINDOW_BLACKMAN,
    FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS
} FMOD_DSP_FFT_WINDOW_TYPE;


typedef enum
{
    FMOD_DSP_FFT_DOWNMIX_NONE,
    FMOD_DSP_FFT_DOWNMIX_MONO,
} FMOD_DSP_FFT_DOWNMIX_TYPE;


typedef enum
{
    FMOD_DSP_FFT_WINDOWSIZE,
    FMOD_DSP_FFT_WINDOW,
    FMOD_DSP_FFT_BAND_START_FREQ,
    FMOD_DSP_FFT_BAND_STOP_FREQ,
    FMOD_DSP_FFT_SPECTRUMDATA,
    FMOD_DSP_FFT_RMS,
    FMOD_DSP_FFT_SPECTRAL_CENTROID,
    FMOD_DSP_FFT_IMMEDIATE_MODE,
    FMOD_DSP_FFT_DOWNMIX,
    FMOD_DSP_FFT_CHANNEL,
} FMOD_DSP_FFT;

#define FMOD_DSP_LOUDNESS_METER_HISTOGRAM_SAMPLES 66

typedef enum
{
    FMOD_DSP_LOUDNESS_METER_STATE,
    FMOD_DSP_LOUDNESS_METER_WEIGHTING,
    FMOD_DSP_LOUDNESS_METER_INFO
} FMOD_DSP_LOUDNESS_METER;


typedef enum
{
    FMOD_DSP_LOUDNESS_METER_STATE_RESET_INTEGRATED = -3,
    FMOD_DSP_LOUDNESS_METER_STATE_RESET_MAXPEAK = -2,
    FMOD_DSP_LOUDNESS_METER_STATE_RESET_ALL = -1,
    FMOD_DSP_LOUDNESS_METER_STATE_PAUSED = 0,
    FMOD_DSP_LOUDNESS_METER_STATE_ANALYZING = 1
} FMOD_DSP_LOUDNESS_METER_STATE_TYPE;

typedef struct FMOD_DSP_LOUDNESS_METER_INFO_TYPE
{
    float momentaryloudness;
    float shorttermloudness;
    float integratedloudness;
    float loudness10thpercentile;
    float loudness95thpercentile;
    float loudnesshistogram[FMOD_DSP_LOUDNESS_METER_HISTOGRAM_SAMPLES];
    float maxtruepeak;
    float maxmomentaryloudness;
} FMOD_DSP_LOUDNESS_METER_INFO_TYPE;

typedef struct FMOD_DSP_LOUDNESS_METER_WEIGHTING_TYPE
{
    float channelweight[32];
} FMOD_DSP_LOUDNESS_METER_WEIGHTING_TYPE;

typedef enum
{
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_IR,
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_WET,
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_DRY,
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_LINKED
} FMOD_DSP_CONVOLUTION_REVERB;

typedef enum
{
    FMOD_DSP_CHANNELMIX_OUTPUT_DEFAULT,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLMONO,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLSTEREO,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLQUAD,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALL5POINT1,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALL7POINT1,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLLFE,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALL7POINT1POINT4
} FMOD_DSP_CHANNELMIX_OUTPUT;

typedef enum
{
    FMOD_DSP_CHANNELMIX_OUTPUTGROUPING,
    FMOD_DSP_CHANNELMIX_GAIN_CH0,
    FMOD_DSP_CHANNELMIX_GAIN_CH1,
    FMOD_DSP_CHANNELMIX_GAIN_CH2,
    FMOD_DSP_CHANNELMIX_GAIN_CH3,
    FMOD_DSP_CHANNELMIX_GAIN_CH4,
    FMOD_DSP_CHANNELMIX_GAIN_CH5,
    FMOD_DSP_CHANNELMIX_GAIN_CH6,
    FMOD_DSP_CHANNELMIX_GAIN_CH7,
    FMOD_DSP_CHANNELMIX_GAIN_CH8,
    FMOD_DSP_CHANNELMIX_GAIN_CH9,
    FMOD_DSP_CHANNELMIX_GAIN_CH10,
    FMOD_DSP_CHANNELMIX_GAIN_CH11,
    FMOD_DSP_CHANNELMIX_GAIN_CH12,
    FMOD_DSP_CHANNELMIX_GAIN_CH13,
    FMOD_DSP_CHANNELMIX_GAIN_CH14,
    FMOD_DSP_CHANNELMIX_GAIN_CH15,
    FMOD_DSP_CHANNELMIX_GAIN_CH16,
    FMOD_DSP_CHANNELMIX_GAIN_CH17,
    FMOD_DSP_CHANNELMIX_GAIN_CH18,
    FMOD_DSP_CHANNELMIX_GAIN_CH19,
    FMOD_DSP_CHANNELMIX_GAIN_CH20,
    FMOD_DSP_CHANNELMIX_GAIN_CH21,
    FMOD_DSP_CHANNELMIX_GAIN_CH22,
    FMOD_DSP_CHANNELMIX_GAIN_CH23,
    FMOD_DSP_CHANNELMIX_GAIN_CH24,
    FMOD_DSP_CHANNELMIX_GAIN_CH25,
    FMOD_DSP_CHANNELMIX_GAIN_CH26,
    FMOD_DSP_CHANNELMIX_GAIN_CH27,
    FMOD_DSP_CHANNELMIX_GAIN_CH28,
    FMOD_DSP_CHANNELMIX_GAIN_CH29,
    FMOD_DSP_CHANNELMIX_GAIN_CH30,
    FMOD_DSP_CHANNELMIX_GAIN_CH31,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH0,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH1,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH2,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH3,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH4,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH5,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH6,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH7,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH8,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH9,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH10,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH11,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH12,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH13,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH14,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH15,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH16,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH17,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH18,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH19,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH20,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH21,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH22,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH23,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH24,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH25,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH26,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH27,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH28,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH29,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH30,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH31
} FMOD_DSP_CHANNELMIX;

typedef enum
{
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_AUTO = -1,
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_MONO = 0,
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_STEREO,
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_SURROUND,
} FMOD_DSP_TRANSCEIVER_SPEAKERMODE;


typedef enum
{
    FMOD_DSP_TRANSCEIVER_TRANSMIT,
    FMOD_DSP_TRANSCEIVER_GAIN,
    FMOD_DSP_TRANSCEIVER_CHANNEL,
    FMOD_DSP_TRANSCEIVER_TRANSMITSPEAKERMODE
} FMOD_DSP_TRANSCEIVER;


typedef enum
{
    FMOD_DSP_OBJECTPAN_3D_POSITION,
    FMOD_DSP_OBJECTPAN_3D_ROLLOFF,
    FMOD_DSP_OBJECTPAN_3D_MIN_DISTANCE,
    FMOD_DSP_OBJECTPAN_3D_MAX_DISTANCE,
    FMOD_DSP_OBJECTPAN_3D_EXTENT_MODE,
    FMOD_DSP_OBJECTPAN_3D_SOUND_SIZE,
    FMOD_DSP_OBJECTPAN_3D_MIN_EXTENT,
    FMOD_DSP_OBJECTPAN_OVERALL_GAIN,
    FMOD_DSP_OBJECTPAN_OUTPUTGAIN,
    FMOD_DSP_OBJECTPAN_ATTENUATION_RANGE,
    FMOD_DSP_OBJECTPAN_OVERRIDE_RANGE
} FMOD_DSP_OBJECTPAN;

#endif

