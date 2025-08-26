rm -rf *.o *.app Makefile
/opt/homebrew/opt/qt@5/bin/qmake .pro
make
./myapp.app/Contents/MacOS/myapp