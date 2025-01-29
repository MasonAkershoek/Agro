# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Mason Akershoek <masonakershoek@gmail.com>
pkgname='agro'
pkgver=0.0.1
pkgrel=1
epoch=
pkgdesc="File agregation for the command line"
arch=(x86_64)
url="https://github.com/MasonAkershoek/agro"
license=('GPL')
depends=('git')
makedepends=('cmake' 'gcc' 'make' 'glibc' 'glib2')
source=(agro::git+https://github.com/MasonAkershoek/agro.git)
md5sums=('SKIP')

build() {
	cd "$pkgname"
	cmake . 
	make
}


package() {
	cd "$pkgname"
	ls
	install -Dm755 build/agro "$pkgdir/usr/bin/agro"
}
