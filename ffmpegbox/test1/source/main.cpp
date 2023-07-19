#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

extern "C"
{
    #include "libavdevice/avdevice.h"
    #include "libavutil/imgutils.h"
    #include "libavutil/opt.h"
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
    #include <libavfilter/avfilter.h>
};

#define WIDTH 1920
#define HEIGHT 1080
#define YUV_SIZE (WIDTH * HEIGHT * 3 / 2) 


typedef struct SwsContext *(*MBK_GETCONTEXT)(struct SwsContext *context, int srcW,
                                        int srcH, enum AVPixelFormat srcFormat,
                                        int dstW, int dstH,
                                        enum AVPixelFormat dstFormat, int flags,
                                        SwsFilter *srcFilter,
                                        SwsFilter *dstFilter,
                                        const double *param);

typedef int (*SCALE_DOSCALE)(struct SwsContext *c, const uint8_t *const srcSlice[],
                             const int srcStride[], int srcSliceY, int srcSliceH,
                             uint8_t *const dst[], const int dstStride[]);

MBK_GETCONTEXT m_swsgetContext_mbk;     
SCALE_DOSCALE m_doscale;                                  

int main(int argc, char* argv[]) {
    void* handle = dlopen("/home/test/tjh_test/ffmpegbox/test1/lib/libswscale.so", RTLD_NOW);
    printf("return handle: %p\n", handle);
    if (!handle) {
        printf("ERROR: Unable to load libswscale\n");
        return -1;
    }

    m_swsgetContext_mbk = (MBK_GETCONTEXT)dlsym(handle, "sws_getContext");

    m_doscale = (SCALE_DOSCALE)dlsym(handle, "sws_scale");
    int srcSliceH = 342;

    struct SwsContext *ctx = sws_getContext(208, 342, AV_PIX_FMT_YUV420P,
                                             656, 1080, AV_PIX_FMT_YUV420P,
                                             SWS_BILINEAR, NULL, NULL, NULL);

    uint8_t *src_data[4], *dst_data[4];
    int src_linesize[4], dst_linesize[4];

    uint8_t buffer[YUV_SIZE];
    FILE *file = fopen("/home/test/tjh_test/ffmpegbox/test1/yuv/1920x1080_i420_P0_4.yuv", "rb");
    fread(buffer, 1, YUV_SIZE, file);
    fclose(file);

    av_image_fill_arrays(src_data, src_linesize, buffer, AV_PIX_FMT_YUV420P, WIDTH, HEIGHT, 1);

    uint8_t *src_slice[3] = { src_data[0] + 370 * src_linesize[0] + 656, 
                              src_data[1] + 185 * src_linesize[1] + 328, 
                              src_data[2] + 185 * src_linesize[2] + 328 };

    sws_scale(ctx, (const uint8_t *const *)src_slice, src_linesize,
              0, srcSliceH, src_data, src_linesize);

    sws_freeContext(ctx);
    dlclose(handle);

    // write the result to a file
    FILE *output = fopen("/home/test/tjh_test/ffmpegbox/test1/yuv/output.yuv", "wb");
    if (output == NULL) {
        printf("ERROR: Unable to open output file\n");
        return -1;
    }
    int y_size = WIDTH * HEIGHT;
    int uv_size = y_size / 4;
    fwrite(src_data[0], 1, y_size, output);
    fwrite(src_data[1], 1, uv_size, output);
    fwrite(src_data[2], 1, uv_size, output);
    fclose(output);

    return 0;
}
