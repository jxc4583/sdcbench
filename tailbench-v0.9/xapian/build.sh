#/bin/bash

# Install Xapian core if not already present
if [[ ! -d xapian-core-1.4.4 ]]
then
    #tar -xf xapian-core-1.2.13.tar.gz
    cd xapian-core-1.4.4
    #mkdir install
    ./configure --prefix=$PWD/install
    make -j16
    make install
    cd -
fi

# Build search engine
make
