// Generated by gtkmmproc -- DO NOT MODIFY!


#include <goocanvasmm/linedash.h>
#include <goocanvasmm/private/linedash_p.h>

/* Copyright (C) 1998-2006 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


namespace
{
} // anonymous namespace


namespace Glib
{

Goocanvas::LineDash wrap(GooCanvasLineDash* object, bool take_copy)
{
  return Goocanvas::LineDash(object, take_copy);
}

} // namespace Glib


namespace Goocanvas
{


// static
GType LineDash::get_type()
{
  return goo_canvas_line_dash_get_type();
}

LineDash::LineDash()
:
  gobject_ (0) // Allows creation of invalid wrapper, e.g. for output arguments to methods.
{}

LineDash::LineDash(const LineDash& other)
:
  gobject_ ((other.gobject_) ? goo_canvas_line_dash_ref(other.gobject_) : 0)
{}

LineDash::LineDash(GooCanvasLineDash* gobject, bool make_a_copy)
:
  // For BoxedType wrappers, make_a_copy is true by default.  The static
  // BoxedType wrappers must always take a copy, thus make_a_copy = true
  // ensures identical behaviour if the default argument is used.
  gobject_ ((make_a_copy && gobject) ? goo_canvas_line_dash_ref(gobject) : gobject)
{}

LineDash& LineDash::operator=(const LineDash& other)
{
  LineDash temp (other);
  swap(temp);
  return *this;
}

LineDash::~LineDash()
{
  if(gobject_)
    goo_canvas_line_dash_unref(gobject_);
}

void LineDash::swap(LineDash& other)
{
  GooCanvasLineDash *const temp = gobject_;
  gobject_ = other.gobject_;
  other.gobject_ = temp;
}

GooCanvasLineDash* LineDash::gobj_copy() const
{
  return goo_canvas_line_dash_ref(gobject_);
}


} // namespace Goocanvas


