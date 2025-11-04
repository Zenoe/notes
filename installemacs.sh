emacsV=29.3
echo "install emacs$emacsV"
# sudo apt-get install -y ncurses-dev gnutls-dev libxml2-dev automake autoconf
# wget https://git.savannah.gnu.org/cgit/emacs.git/snapshot/emacs-${emacsV}.tar.gz
# tar xzvf emacs-${emacsV}.tar.gz
cd emacs-${emacsV}
apt install -y autoconf build-essential texinfo zlib1g-dev
# ubuntu 18.04
apt install -y libgccjit-8-dev
# ubuntu 20.04
apt install -y libgccjit-9-dev
./autogen.sh
./configure --with-tree-sitter --with-json --with-native-compilation --without-makeinfo --with-xpm=no --with-jpeg=no --with-png=no --with-gif=no --with-tiff=no
make && make insatll
