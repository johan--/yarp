#!/bin/bash

BUILD_DIR=$PWD

source ./settings.sh || {
	echo "No settings.sh found, are we in the build directory?"
	exit 1
}

source $BUNDLE_FILENAME || {
	echo "Bundle settings not found"
	exit 1
}

source $SOURCE_DIR/src/process_options.sh $* || {
	echo "Cannot process options"
	exit 1
}

source ace_${compiler}_${variant}_${build}.sh || {
	echo "Cannot find corresponding ACE build"
	exit 1
}

source yarp_${compiler}_${variant}_${build}.sh || {
	echo "Cannot find corresponding YARP build"
	exit 1
}

source nsis_${compiler}_${variant}_${build}.sh || {
	echo "Cannot find corresponding NSIS build"
	exit 1
}

fname=yarp_core_package-$YARP_VERSION

fname2=$fname-$compiler-$variant-$build
zip_name="$fname2"

mkdir -p $fname2
cd $fname2 || exit 1
OUT_DIR=$PWD

rm -rf "$OUT_DIR/*_zip.sh"
function nsis_setup {
	prefix=$1
	echo -n > ${OUT_DIR}/${prefix}_add.nsi
	echo -n > ${OUT_DIR}/${prefix}_remove.nsi
	echo -n > ${OUT_DIR}/${prefix}_zip.sh
}

CYG_BASE=`cygpath -w /`
function nsis_add {
	prefix=$1
	src=$2
	dest=$3
	dir=$4 #optional
	#src=`cygpath -w $PWD/$src` -- too slow!
	#dest=`cygpath -w $3`       -- too slow!
	osrc="$src"
	odest="$dest"
	if [ "k$dir" = "k" ] ; then
		src="$PWD/$src"
		osrc="$src"
		src=${src//\//\\}
		src="$CYG_BASE$src"
	else
		src="$dir/$src"
		osrc="$src"
		src=${src//\//\\}
	fi
	dest=${dest//\//\\} # flip to windows convention
	#echo add "[$prefix]" "[$src]" "$dest"
	echo "File /oname=$dest $src" >> $OUT_DIR/${prefix}_add.nsi
	echo "Delete \"\$INSTDIR\\$dest\"" >> $OUT_DIR/${prefix}_remove.nsi
	zodest="zip/$prefix/$zip_name/$odest"
	echo "mkdir -p `dirname $zodest`" >> $OUT_DIR/${prefix}_zip.sh
	echo "cp '$osrc' $zodest" >> $OUT_DIR/${prefix}_zip.sh
}

YARP_DIR_UNIX=`cygpath -u $YARP_DIR`
# missing - need to package header files
nsis_setup yarp_libraries
nsis_setup yarp_dlls
nsis_setup yarp_programs
nsis_setup yarp_math_libraries
nsis_setup yarp_math_dlls
nsis_setup yarp_guis
nsis_setup yarp_ace_libraries
nsis_setup yarp_ace_dlls
nsis_setup yarp_vc_dlls

# Hmm, GSL is currently compiled statically with yarp_math
# nsis_setup yarp_gsl_libraries
# nsis_setup yarp_gsl_dlls

# Add YARP material
cd $YARP_DIR_UNIX || exit 1
YARP_LICENSE="$YARP_ROOT/LGPL.txt"
cd install/lib || exit 1
for f in `ls -1 *.lib | grep -v YARP_math`; do
	nsis_add yarp_libraries $f lib/$f
done
for f in `ls -1 *.lib | grep YARP_math`; do
	nsis_add yarp_math_libraries $f lib/$f
done
for f in `ls -1 *.dll | grep -v YARP_math`; do
	nsis_add yarp_dlls $f bin/$f
done
for f in `ls -1 *.dll | grep YARP_math`; do
	nsis_add yarp_math_dlls $f bin/$f
done
cd $YARP_DIR_UNIX/install/bin
for f in `ls -1 *.exe | grep -v yarpview`; do
	nsis_add yarp_programs $f bin/$f
done
for f in `ls -1 *.exe | grep yarpview`; do
	nsis_add yarp_guis $f yarpview/$f
done

# Add ACE material
cd $ACE_DIR || exit 1
cd lib || exit 1
if [ ! -e $ACE_LIBNAME.dll ]; then
	echo "Cannot find $ACE_LIBNAME.dll in $PWD"
	exit 1
fi
nsis_add yarp_ace_libraries $ACE_LIBNAME.lib lib/$ACE_LIBNAME.lib
nsis_add yarp_ace_dlls $ACE_LIBNAME.dll bin/$ACE_LIBNAME.dll

# Add VC material
if [ -e "$VC_REDIST_CRT" ] ; then
	cd "$VC_REDIST_CRT" || exit 1
	for f in `ls *.dll *.manifest`; do
		nsis_add yarp_vc_dlls $f bin/$f "$VC_REDIST_CRT"
		nsis_add yarp_vc_dlls $f yarpview/$f "$VC_REDIST_CRT"
	done
fi

cd $OUT_DIR

$NSIS_BIN -DYARP_VERSION=$YARP_VERSION -DBUILD_VERSION=${compiler}_${variant}_${build} -DYARP_LICENSE=$YARP_LICENSE -DNSIS_OUTPUT_PATH=`cygpath -w $PWD` `cygpath -m $SOURCE_DIR/src/nsis/yarp_core_package.nsi`

if [ "k$SKIP_ZIP" = "k" ] ; then
	# flush zips
	rm -rf "$OUT_DIR/zip"

	for f in `ls *_zip.sh`; do
		echo "Processing $f"
		bash ./$f || exit 1
	done
	for f in `cd zip; ls`; do
		cd $OUT_DIR/zip/$f || exit 1
		echo "  Zipping $f"
		zip -r ${zip_name}-$f $zip_name || exit 1
		mv *.zip $OUT_DIR || exit 1
	done
fi

cd $OUT_DIR

(
	echo "export YARP_CORE_PACKAGE_DIR='$PWD'"
) > $BUILD_DIR/yarp_core_package_${compiler}_${variant}_${build}.sh
