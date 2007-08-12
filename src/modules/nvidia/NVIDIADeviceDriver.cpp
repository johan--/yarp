// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2007 Giacomo Spigler
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 */

#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include "FBO_Filter.h"

#include "NVIDIADeviceDriver.h"

typedef FBO_Filter* GPUProgram;
//CGprofile GPUProfile=CG_PROFILE_ARBFP1;
CGprofile GPUProfile=CG_PROFILE_FP30;
//CGprofile GPUProfile=CG_PROFILE_FP40;


bool NVIDIAGPU::open(int w, int h, int bytespp, int elemtype) {
    this->w=w;
    this->h=h;

    if(bytespp==1) {
        oglformat = GL_LUMINANCE;
    } else if(bytespp==3) {
        oglformat = GL_RGB;
    } else if(bytespp==4) {
        oglformat = GL_RGBA;
    }

    if(elemtype==VOCAB_PIXEL_MONO || elemtype==VOCAB_PIXEL_RGB ||  elemtype==VOCAB_PIXEL_HSV || elemtype==VOCAB_PIXEL_BGR) {
      ogltype = GL_UNSIGNED_BYTE;
    } else if(elemtype==VOCAB_PIXEL_INT) {
      ogltype = GL_INT;
    } else if(elemtype==VOCAB_PIXEL_MONO_SIGNED || elemtype==VOCAB_PIXEL_RGB_SIGNED) {
      ogltype = GL_BYTE;
    } else if(elemtype==VOCAB_PIXEL_MONO_FLOAT || elemtype==VOCAB_PIXEL_RGB_FLOAT || elemtype==VOCAB_PIXEL_HSV_FLOAT) {
      ogltype = GL_FLOAT;
    }

    if(this->w>0 && this->h>0) {
      //Initialize the GLUT system to use OpenGL
      int argc=0;
      char **argv;
      glutInit(&argc, argv);

      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
      glutInitWindowSize(w, h);
      glutCreateWindow("");
      glutHideWindow();

      glewInit();

      //Build the needed textures (the working space for the GPU)
      glGenTextures(1, &(this->oTex));
      glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->oTex);
      glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, this->w, this->h, 0, oglformat, ogltype, NULL);
    }

    return w>0 && h>0;
}


bool NVIDIAGPU::resize(int width, int height) {
    this->w=width;
    this->h=height;

    if(this->w>0 && this->h>0) {
      glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, this->w, this->h, 0, oglformat, ogltype, NULL);
    }

    return w>0 && h>0;
}


int NVIDIAGPU::load(char *name) {
    return (int)new FBO_Filter(GPUProfile, name, this->oTex, this->w, this->h);
}


void NVIDIAGPU::setargument(int prg, char *name, float *vector, int len) {
  CGprogram prog = ((GPUProgram)prg)->getProgram();
  if(len==1){
    cgGLSetParameter1f(cgGetNamedParameter(prog, name), *vector);
  } else if(len==2) {
    cgGLSetParameter2fv(cgGetNamedParameter(prog, name), vector);
  } else if(len==3) {
    cgGLSetParameter3fv(cgGetNamedParameter(prog, name), vector);
  } else if(len==4) {
    cgGLSetParameter4fv(cgGetNamedParameter(prog, name), vector);
  }
}


//Actually in and out type's is the same!
void NVIDIAGPU::execute(int prg, unsigned char *in, unsigned char *out) {
    GPUProgram prog=(GPUProgram)prg;

    // Build the texture representing inputs
    glGenTextures(1, &(this->tex));
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_REPLACE);
    glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->tex);
    glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, this->w, this->h, 0, oglformat, ogltype, in);

    prog->apply(this->tex, true, oglformat, ogltype);

    glBindTexture(GL_TEXTURE_RECTANGLE_NV, this->oTex);

    glGetTexImage(GL_TEXTURE_RECTANGLE_NV, 0, oglformat, ogltype, out);
}


