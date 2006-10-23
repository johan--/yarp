#!/bin/bash

# run as ./scripts/autocheck-linux.sh

. ./scripts/config.sh
if [ "k$WEB_USER" = "k" ] ; then
    WEB_USER=`cat CVS/Root | sed "s/^:[^:]*://" | sed "s/[^a-z].*//"`
fi
echo USER is "$WEB_USER"

CMAKEOPTS="-DCREATE_GUIS:BOOL=FALSE -DCREATE_DEVICE_LIBRARY:BOOL=TRUE"

while true; do

rm -f should_report.txt

(

cvs update -d > cvslog.txt
cat cvslog.txt | grep -v "cvs update" | egrep -v "^\? " | egrep -v "^M " | tee cvslog2.txt

if egrep "[a-zA-Z]" cvslog2.txt; then

echo Working in directory $SOURCE | tee should_report.txt

rm -f CMakeCache.txt
rm -f failure.txt
cmake $CMAKEOPTS $SOURCE || ( echo YARP_AUTOCHECK cmake configure failed | tee failure.txt )

make clean || echo "make clean failed"

if [ ! -e failure.txt ]; then
	make || ( echo YARP_AUTOCHECK make compile failed | tee failure.txt )
fi

echo "Regression tests not run" > testlog.txt
if [ ! -e failure.txt ]; then
    (
	make test || ( echo YARP_AUTOCHECK make regression failed | tee failure.txt )
    ) 2>&1 | tee testlog.txt
fi

cat cvslog.txt

if [ -e failure.txt ]; then
	echo YARP_AUTOCHECK at least one failure happened
else
    touch build-source.txt
    cat conf/build.txt | grep SOURCE | tee build-source-new.txt
    rm -rf debian-package
    cmp build-source-new.txt build-source.txt || (
        # update packages
	./scripts/make-source-package
	./scripts/update-web-packages
    )
    cp build-source-new.txt build-source.txt
    touch build-debian.txt
    cat conf/build.txt | grep DEBIAN | tee build-debian-new.txt
    cmp build-debian-new.txt build-debian.txt || (
        # update debian packages
	./scripts/make-debian
	./scripts/update-web-packages
    )
    cp build-debian-new.txt build-debian.txt
fi

else
	echo "Nothing new in CVS"
fi

./scripts/autocheck-doc

) | tee report.txt

if [ -e should_report.txt ]; then
	date > report-decor.txt
	cat testlog.txt >> report-decor.txt
	echo >> report-decor.txt
	echo >> report-decor.txt
	cat report.txt >> report-decor.txt
	#scp report-decor.txt eshuy@yarp0.sf.net:www/report-yarp2-linux.txt
	scp report-decor.txt $WEB_USER@$WEB_SERVER:$WEB_DIR/report-yarp2-linux.txt
fi

sleep 600

done
