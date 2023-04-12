#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <libavcodec/avcodec.h>

typedef struct
{
    AVCodec *codec;
    AVCodecContext *context;
} Encoder;

Encoder *encoder_new()
{
    Encoder *encoder = malloc(sizeof(Encoder));
    encoder->codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!encoder->codec)
    {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    encoder->context = avcodec_alloc_context3(encoder->codec);
    if (!encoder->context)
    {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    encoder->context->bit_rate = 400000;
    encoder->context->width = 352;
    encoder->context->height = 288;
    encoder->context->time_base.num = 1;
    encoder->context->time_base.den = 25;
    encoder->context->gop_size = 10;
    encoder->context->max_b_frames = 1;
    encoder->context->pix_fmt = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(encoder->context, encoder->codec, NULL) < 0)
    {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    return encoder;
}

void encoder_free(Encoder *encoder)
{
    avcodec_close(encoder->context);
    av_free(encoder->context);
    free(encoder);
}

int main(int argc, char **argv)
{
    void *handle;
    Encoder *(*encoder_new_ptr)();
    void (*encoder_free_ptr)(Encoder *);

    handle = dlopen("libavcodec.so", RTLD_LAZY);

    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    *(void **)(&encoder_new_ptr) = dlsym(handle, "encoder_new");

    *(void **)(&encoder_free_ptr) = dlsym(handle, "encoder_free");

    Encoder *encoder = (*encoder_new_ptr)();

    AVFrame *frame;

    frame = av_frame_alloc();

    if (!frame)
    {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    frame->format = encoder->context->pix_fmt;

    frame->width = encoder->context->width;

    frame->height = encoder->context->height;

    int ret;

    ret = av_frame_get_buffer(frame, 32);

    if (ret < 0)
    {
        fprintf(stderr, "Could not allocate the video frame data\n");
        exit(1);
    }

    AVPacket packet;

    av_init_packet(&packet);

    packet.data = NULL; // packet data will be allocated by the encoder

    packet.size = 0;

    int got_output;

    if (avcodec_encode_video2(encoder->context, &packet, frame, &got_output) < 0)
    {
        fprintf(stderr, "Error encoding video frame\n");
        exit(1);
    }

    if (got_output)
    {
        printf("Write packet with size %d\n", packet.size);
        // fwrite(packet.data, 1, packet.size, output_file);
        av_packet_unref(&packet);

        av_frame_free(&frame);

        (*encoder_free_ptr)(encoder);

        dlclose(handle);

        return 0;
    }
}
