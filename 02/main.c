#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }
    AVFormatContext *pFormatCtx;
    if (avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)
        return -1;
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
        return -1;
    av_dump_format(pFormatCtx, 0, argv[1], 0);

    AVCodecContext *pCodecCtx = NULL;
    AVCodec *pCodec = NULL;
    int videoStream = -1;

    for (int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1)
        exit(-1);

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        fprintf(stderr, "%s\n", "Unsupported codecn");
        exit(-1);
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
        exit(-1);

    SDL_Window *surface;
    surface = SDL_CreateWindow(argv[1],
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            pCodecCtx->width,
            pCodecCtx->height,
            SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    if (!surface) {
        fprintf(stderr, "%s\n", "SDL: could not set video mode - exiting");
        exit(1);
    }

    SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = SDL_CreateRenderer(surface, -1, 0);
    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &surface, &renderer);
    SDL_RenderSetLogicalSize(renderer, pCodecCtx->width, pCodecCtx->height);
    texture = SDL_CreateTexture(renderer,
            SDL_P)

    struct SWSContext *sws_ctx = NULL;
}
