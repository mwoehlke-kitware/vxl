// This is core/vgui/vgui_macro.cxx
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma implementation
#endif
//:
// \file
// \author fsm
// \brief  See vgui_macro.h for a description of this file.

#include <cstdlib>
#include <iostream>
#include "vgui_macro.h"

#include <vcl_compiler.h>

#include <vgui/vgui_gl.h>
#include <vgui/vgui_glu.h>

extern bool vgui_glerrors_are_bad;

void vgui_macro_error_reporter(char const *FILE, int LINE)
{
  static char const *last_file = VXL_NULLPTR;
  static int last_line = 0;
  static int numerrors = 0;

  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    if (last_file) {
      std::cerr << "Between " << last_file << ":" << last_line << '\n'
               << "    and " << FILE << ":" << LINE << " : \""
               << gluErrorString(err) << "\"\n";
    }
    else
      std::cerr << "In " << FILE << " before line " << LINE << " : "
               << gluErrorString(err) << '\n';

    if (++numerrors >= 20 && vgui_glerrors_are_bad) {
      std::cerr << "too many errors -- calling exit(1);\n";
      std::exit(1);
    }
  }

  // FIXME : this assumes that FILE points to static storage.
  last_file = FILE;
  last_line = LINE;
}
