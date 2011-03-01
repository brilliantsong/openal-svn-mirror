#ifndef _AL_BUFFER_H_
#define _AL_BUFFER_H_

#include "AL/al.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Input formats (some are currently theoretical) */
enum SrcFmtType {
    SrcFmtByte,   /* AL_BYTE */
    SrcFmtUByte,  /* AL_UNSIGNED_BYTE */
    SrcFmtShort,  /* AL_SHORT */
    SrcFmtUShort, /* AL_UNSIGNED_SHORT */
    SrcFmtInt,    /* AL_INT */
    SrcFmtUInt,   /* AL_UNSIGNED_INT */
    SrcFmtFloat,  /* AL_FLOAT */
    SrcFmtDouble, /* AL_DOUBLE */
    SrcFmtMulaw,  /* AL_MULAW */
    SrcFmtIMA4,   /* AL_IMA4 */
};
enum SrcFmtChannels {
    SrcFmtMono,   /* AL_MONO */
    SrcFmtStereo, /* AL_STEREO */
    SrcFmtRear,   /* AL_REAR */
    SrcFmtQuad,   /* AL_QUAD */
    SrcFmtX51,    /* AL_5POINT1 (WFX order) */
    SrcFmtX61,    /* AL_6POINT1 (WFX order) */
    SrcFmtX71,    /* AL_7POINT1 (WFX order) */
};

ALboolean DecomposeInputFormat(ALenum format, enum SrcFmtChannels *chans,
                               enum SrcFmtType *type);
ALuint BytesFromSrcFmt(enum SrcFmtType type);
ALuint ChannelsFromSrcFmt(enum SrcFmtChannels chans);
static __inline ALuint FrameSizeFromSrcFmt(enum SrcFmtChannels chans,
                                           enum SrcFmtType type)
{
    return ChannelsFromSrcFmt(chans) * BytesFromSrcFmt(type);
}


/* Storable formats */
enum FmtType {
    FmtUByte = SrcFmtUByte,
    FmtShort = SrcFmtShort,
    FmtFloat = SrcFmtFloat,
};
enum FmtChannels {
    FmtMono = SrcFmtMono,
    FmtStereo = SrcFmtStereo,
    FmtRear = SrcFmtRear,
    FmtQuad = SrcFmtQuad,
    FmtX51 = SrcFmtX51,
    FmtX61 = SrcFmtX61,
    FmtX71 = SrcFmtX71,
};

ALboolean DecomposeFormat(ALenum format, enum FmtChannels *chans, enum FmtType *type);
ALuint BytesFromFmt(enum FmtType type);
ALuint ChannelsFromFmt(enum FmtChannels chans);
static __inline ALuint FrameSizeFromFmt(enum FmtChannels chans, enum FmtType type)
{
    return ChannelsFromFmt(chans) * BytesFromFmt(type);
}


typedef struct ALbuffer
{
    ALvoid  *data;
    ALsizei  size;

    ALsizei          Frequency;
    enum FmtChannels FmtChannels;
    enum FmtType     FmtType;

    enum SrcFmtChannels OriginalChannels;
    enum SrcFmtType     OriginalType;
    ALsizei OriginalSize;
    ALsizei OriginalAlign;

    ALsizei  LoopStart;
    ALsizei  LoopEnd;

    ALuint   refcount; // Number of sources using this buffer (deletion can only occur when this is 0)

    // Index to itself
    ALuint buffer;
} ALbuffer;

ALvoid ReleaseALBuffers(ALCdevice *device);

#ifdef __cplusplus
}
#endif

#endif
