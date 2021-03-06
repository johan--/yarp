// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GOOCANVASMM_IMAGEMODEL_H
#define _GOOCANVASMM_IMAGEMODEL_H


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

#include <goocanvasmm/itemmodelsimple.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GooCanvasImageModel GooCanvasImageModel;
typedef struct _GooCanvasImageModelClass GooCanvasImageModelClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Goocanvas
{ class ImageModel_Class; } // namespace Goocanvas
namespace Goocanvas
{


class ImageModel : public Goocanvas::ItemModelSimple
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef ImageModel CppObjectType;
  typedef ImageModel_Class CppClassType;
  typedef GooCanvasImageModel BaseObjectType;
  typedef GooCanvasImageModelClass BaseClassType;

private:  friend class ImageModel_Class;
  static CppClassType imagemodel_class_;

private:
  // noncopyable
  ImageModel(const ImageModel&);
  ImageModel& operator=(const ImageModel&);

protected:
  explicit ImageModel(const Glib::ConstructParams& construct_params);
  explicit ImageModel(GooCanvasImageModel* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~ImageModel();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GooCanvasImageModel*       gobj()       { return reinterpret_cast<GooCanvasImageModel*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GooCanvasImageModel* gobj() const { return reinterpret_cast<GooCanvasImageModel*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GooCanvasImageModel* gobj_copy();

private:

protected:
  //TODO: goo_canvas_image_new() does more than g_object_new(), which is a goocanvas bug, 
  //so instances of this object will not work.
  //In the worst case, we can implement a custom ctor and reimplement the same code.
  ImageModel(double x, double y);
  ImageModel(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);
  

public:

  
  static Glib::RefPtr<ImageModel> create(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);

  
  static Glib::RefPtr<ImageModel> create(double x, double y);


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

  ImageModel();


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
   * @relates Goocanvas::ImageModel
   */
  Glib::RefPtr<Goocanvas::ImageModel> wrap(GooCanvasImageModel* object, bool take_copy = false);
}


#endif /* _GOOCANVASMM_IMAGEMODEL_H */

