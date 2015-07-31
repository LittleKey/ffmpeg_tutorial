#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);

int main(int argc, char *argv[]) {
    av_register_all();

    AVFormatContext *pFormatCtx = NULL;

    // Open video file
    if (avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)
        return -1;


    // Retrieve stream infomation
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
        return -1;

    av_dump_format(pFormatCtx, 0, argv[1], 0);

    int i;
    AVCodecContext *pCodecCtxOrig = NULL;
    AVCodecContext *pCodecCtx = NULL;

    // Find the first video stream
    int videoStream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1)
        return -1;

    // Get a pointer to the codec context for video stream
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    AVCodec *pCodec = NULL;

    // Find the decoder for the video stream
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        fprintf(stderr, "Unsupported codecn");
        return -1;
    }
    // Copy context
    /*
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
        fprintf(stderr, "Counldn't copy codec context");
        return -1;
    }
    */
    // Open codec
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
        return -1;

    AVFrame *pFrame = NULL;

    // Allocate video frame
    pFrame = av_frame_alloc();

    // Allocate an AVFrame structure
    AVFrame *pFrameRGB = av_frame_alloc();
    if (pFrameRGB == NULL)
        return -1;

    uint8_t *buffer = NULL;
    int numBytes;
    // Determine required buffer size and allocate buffer
    numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
            pCodecCtx->height);
    buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
            pCodecCtx->width, pCodecCtx->height);

    struct SwsContext *sws_ctx = NULL;
    int frameFinished;
    AVPacket packet;
    sws_ctx = sws_getContext(pCodecCtx->width,
            pCodecCtx->height,
            pCodecCtx->pix_fmt,
            pCodecCtx->width,
            pCodecCtx->height,
            PIX_FMT_RGB24,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
        );

    i = 0;
    while (av_read_frame(pFormatCtx, &packet) >= 0) {
        if (packet.stream_index == videoStream) {
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
            if (frameFinished) {
            sws_scale(sws_ctx, (uint8_t const * const*)pFrame->data,
                    pFrame->linesize, 0, pCodecCtx->height,
                    pFrameRGB->data, pFrameRGB->linesize);
            }
            ++i;
            if (i <= 240 && i >= 230) {
                SaveFrame(pFrameRGB, pCodecCtx->width,
                        pCodecCtx->height, i);
            }
        }
    }
    av_free_packet(&packet);

    av_free(buffer);
    av_free(pFrameRGB);

    av_free(pFrame);

    avcodec_close(pCodecCtx);

    avformat_close_input(&pFormatCtx);

    return 0;
}

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
    FILE *pFile;
    char szFilename[32];
    int y;

    sprintf(szFilename, "frame%d.ppm", iFrame);
    pFile = fopen(szFilename, "wb");
    if (pFile == NULL)
        return;

    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    for (y = 0; y < height; y++) {
        fwrite(pFrame->data[0] + y*pFrame->linesize[0], 1, width*3, pFile);
    }
    fclose(pFile);
}
