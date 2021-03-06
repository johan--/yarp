// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GOOCANVASMM_IMAGE_H
#define _GOOCANVASMM_IMAGE_H


#include <glibmm.h>

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


#include <gdkmm/pixbuf.h>

#include <goocanvasmm/itemsimple.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GooCanvasImage GooCanvasImage;
typedef struct _GooCanvasImageClass GooCanvasImageClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Goocanvas
{ class Image_Class; } // namespace Goocanvas
namespace Goocanvas
{


class Image : public Goocanvas::ItemSimple
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef Image CppObjectType;
  typedef Image_Class CppClassType;
  typedef GooCanvasImage BaseObjectType;
  typedef GooCanvasImageClass BaseClassType;

private:  friend class Image_Class;
  static CppClassType image_class_;

private:
  // noncopyable
  Image(const Image&);
  Image& operator=(const Image&);

protected:
  explicit Image(const Glib::ConstructParams& construct_params);
  explicit Image(GooCanvasImage* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~Image();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GooCanvasImage*       gobj()       { return reinterpret_cast<GooCanvasImage*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GooCanvasImage* gobj() const { return reinterpret_cast<GooCanvasImage*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GooCanvasImage* gobj_copy();

private:

protected:
  explicit Image(double x = 0.0, double y = 0.0);
  explicit Image(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x = 0.0, double y = 0.0);
  

public:

  
  static Glib::RefPtr<Image> create(double x =  0.0, double y =  0.0);

  
  static Glib::RefPtr<Image> create(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x =  0.0, double y =  0.0);


  //We put these in item.hg instead.
  //See the comment there.
  //_WRAP_PROPERTY("x", double)
  //_WRAP_PROPERTY("y", double)
  //_WRAP_PROPERTY("width", double)
  //_WRAP_PROPERTY("height", double)
  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The cairo pattern to paint.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy< Cairo::RefPtr<Cairo::Pattern> > property_pattern() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The cairo pattern to paint.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Cairo::RefPtr<Cairo::Pattern> > property_pattern() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** If the image is scaled to fit the width and height settings.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<bool> property_scale_to_fit() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** If the image is scaled to fit the width and height settings.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_scale_to_fit() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The GdkPixbuf to display.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_WriteOnly< Glib::RefPtr<Gdk::Pixbuf> > property_pixbuf() ;
#endif //#GLIBMM_PROPERTIES_ENABLED


protected:

  Image();


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};


}


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Goocanvas::Image
   */
  Glib::RefPtr<Goocanvas::Image> wrap(GooCanvasImage* object, bool take_copy = false);
}


#endif /* _GOOCANVASMM_IMAGE_H */

