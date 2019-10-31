/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef PIXELSERVICE_H
#define PIXELSERVICE_H

#include <QString>
#include <QOpenGLExtraFunctions>
#include <OpenImageIO/imageio.h>

#include "decoder/frame.h"
#include "pixelformat.h"

/**
 * @brief A struct of information pertaining to each enum PixelFormat.
 *
 * Primarily this is a means of retrieving OpenGL texture information for different pixel formats/bit depths. Both
 * RAM and VRAM buffers will need a PixelFormat. To keep consistency between the OpenGL code and CPU code when using
 * a given PixelFormat, the PixelFormatInfo struct contains all necessary variables that you'll need to plug into
 * OpenGL.
 *
 * Use the static function PixelService::GetPixelFormatInfo to generate a PixelFormatInfo object.
 */
struct PixelFormatInfo {
  QString name;
  GLint internal_format;
  GLenum pixel_format;
  GLenum gl_pixel_type;
  int bytes_per_pixel;
  OIIO::TypeDesc oiio_desc;
};

class PixelService : public QObject {
public:

  PixelService();

  /**
   * @brief Return a PixelFormatInfo containing information for a certain format
   *
   * \see PixelFormatInfo
   */
  static PixelFormatInfo GetPixelFormatInfo(const olive::PixelFormat& format);

  /**
   * @brief Returns the minimum buffer size (in bytes) necessary for a given format, width, and height.
   *
   * @param format
   *
   * The format of the data the buffer should contain. Must be a member of the olive::PixelFormat enum.
   *
   * @param width
   *
   * The width (in pixels) of the buffer.
   *
   * @param height
   *
   * The height (in pixels) of the buffer.
   */
  static int GetBufferSize(const olive::PixelFormat &format, const int& width, const int& height);

  /**
   * @brief Returns the number of bytes per pixel for a certain format
   *
   * Different formats use different sizes of data for pixels. Use this function to determine how many bytes a pixel
   * requires for a certain format. The number of bytes will always be a multiple of 4 since all formats use RGBA and
   * are at least 1 bpc.
   */
  static int BytesPerPixel(const olive::PixelFormat& format);

  /**
   * @brief Returns the number of bytes per channel for a certain format
   */
  static int BytesPerChannel(const olive::PixelFormat& format);

  /**
   * @brief Convert a frame to a pixel format
   *
   * If the frame's pixel format == the destination format, this just returns `frame`.
   */
  static FramePtr ConvertPixelFormat(FramePtr frame, const olive::PixelFormat &dest_format);

  /**
   * @brief Convert an RGB image to an RGBA image
   */
  static void ConvertRGBtoRGBA(FramePtr frame);

};

#endif // PIXELSERVICE_H
