/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/dmt/dmt.h"
#ifdef LOVE_TTF
#include "lib/stb/stb_truetype.h"
#endif
#include "filesystem.h"
#include "font.h"

#ifdef LOVE_TTF
static const char *initTrueTypeFont(font_t *self, const void *data, int ptsize) {
  int i;

  /* Init font */
  stbtt_fontinfo font;
  if (!stbtt_InitFont(&font, data, 0)) {
    return "could not load font";
  }

  // Force blitter to use the COLOR mode
  self->forceMode = 1;

  /* Get height and scale */
  int ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
  float scale = stbtt_ScaleForMappingEmToPixels(&font, ptsize);
  self->height = (ascent - descent + lineGap) * scale + 0.5;

  /* Init image */
  int w = 128, h = 128;
retry:
  image_initBlank(&self->image, w, h);

  /* Load glyphs */
  float s = stbtt_ScaleForMappingEmToPixels(&font, 1) /
            stbtt_ScaleForPixelHeight(&font, 1);
  int res = stbtt_BakeFontBitmap(data, 0, ptsize * s, self->image.data, w, h, 0,
                                 128, self->glyphs);

  /* Retry with a larger image buffer if the buffer wasn't large enough */
  if (res < 0) {
    w <<= 1;
    h <<= 1;
    image_deinit(&self->image);
    goto retry;
  }

  /* Adjust glyph yoffsets */
  int scaledAscent = ascent * scale + 0.5;
  for (i = 0; i < 128; i++) {
    self->glyphs[i].yoff += scaledAscent;
  }

  /* Init image data and mask */
  for (i = 0; i < w * h; i++) {
    self->image.data[i] = (self->image.data[i] > 127) ? 1 : 0;
    self->image.mask[i] = (self->image.data[i] == 0) ? 0xff : 0;
  }

  /* Return NULL for no error */
  return NULL;
}
#endif

const char *font_init(font_t *self, const char *filename, int ptsize) {
  const char *errmsg = NULL;
  void *data = NULL;
  FILE *fp = NULL;
  memset(self, 0, sizeof(*self));

  /* Load font file */
  int size;
  data = filesystem_read(filename, &size);
  if (!data) {
    errmsg = "could not open font file";
    goto fail;
  }

  /* Init font */
#ifdef LOVE_TTF
  errmsg = initTrueTypeFont(self, data, ptsize);
#else
  errmsg = "TrueType Font support disabled";
#endif
  if (errmsg) {
    // TODO: Try loading the same font file as BMFont
    goto fail;
  }

  /* Free font data */
  filesystem_free(data);
  data = NULL;

  return NULL;

fail:
  if (fp)
    fclose(fp);
  filesystem_free(data);
  return errmsg;
}

static const char *initBitmapFont(font_t *self, const char *glyphs, int extraSpacing) {
  if (self->image.width <= 0 || self->image.height <= 0) {
    return "no image loaded";
  }

  self->height = self->image.height;
  self->glyphs[0] = (stbtt_bakedchar){.x0 = 0, .x1 = 0, .y0 = 0, .y1 = 0, .xoff = 0.0f, .yoff = 0.0f, .xadvance = 0.0f};

  // Per LOVE's documentation, the top left pixel is the color of space between the glyphs
  // https://love2d.org/wiki/ImageFontFormat
  pixel_t spacer = self->image.data[0];
  int glyphsCount = strlen(glyphs);
  int start = 0;
	int end = 0;
  for (int i = 0; i < glyphsCount; i++) {
    // Skip the vertical spacer lines
    start = end;
    while (start < self->image.width && self->image.data[start] == spacer)
      start++;

    // Measure the width of a glyph
    end = start;
    while (end < self->image.width && self->image.data[end] != spacer)
      end++;

    if (start >= end)
      break;
    
    char c = glyphs[i];
    int ord = c;
    if (ord > 127) {
      continue;
    }

    self->glyphs[ord] = (stbtt_bakedchar){
      .x0 = start,
      .x1 = end,
      .y0 = 0,
      .y1 = self->image.height,
      .xoff = 0,
      .yoff = 0,
      .xadvance = end - start + extraSpacing
    };
  }

  return NULL;
}

const char *font_initImage(font_t *self, const char *filename, const char *glyphs, int extraSpacing) {
  const char *errmsg = NULL;
  memset(self, 0, sizeof(*self));

  /* Load font image */
  /* Init font */
  errmsg = image_init(&self->image, filename);
  if (errmsg) {
    return errmsg;
  }

  errmsg = initBitmapFont(self, glyphs, extraSpacing);

  return errmsg;
}

const char *font_initEmbedded(font_t *self, int ptsize) {
#ifdef LOVE_TTF
#include "font_ttf.h"
  return initTrueTypeFont(self, font_ttf, ptsize);
#else
#include "font_png.h"
  const char *errmsg = NULL;
  memset(self, 0, sizeof(*self));
  errmsg = image_initData(&self->image, font_png, sizeof(font_png));
  if (errmsg) {
    return errmsg;
  }

  return initBitmapFont(self,
    " abcdefghijklmnopqrstuvwxyz" \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ0" \
    "123456789.,!?-+/():;%&`'*#=[]\"",
    0);
#endif
}

void font_deinit(font_t *self) { image_deinit(&self->image); }

extern int image_blendMode;
extern int image_flip;

void font_blit(font_t *self, pixel_t *buf, int bufw, int bufh, const char *str,
               int dx, int dy) {
  const char *p = str;
  int x = dx;
  int y = dy;

  int oldBlendMode = image_blendMode;
  int oldFlip = image_flip;
  if (self->forceMode)
    image_blendMode = IMAGE_COLOR;
  image_flip = 0;

  while (*p) {
    if (*p == '\n') {
      x = dx;
      y += self->height;
    } else {
      stbtt_bakedchar *g = &self->glyphs[(int)(*p & 127)];
      int w = g->x1 - g->x0;
      int h = g->y1 - g->y0;
      image_blit(&self->image, buf, bufw, bufh, x + g->xoff, y + g->yoff, g->x0,
                 g->y0, w, h);
      x += g->xadvance;
    }
    p++;
  }

  image_blendMode = oldBlendMode;
  image_flip = oldFlip;
}
