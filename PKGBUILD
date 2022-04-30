# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: xmuli <xmulitech@gmail.com>     # 包的维护者
pkgname=chinesschess                          # 包的名称（由小写字母 @ . _ + - 构成）
_pkgname=chinessChess                         # 自己添加的变量 （因 pkgname 要求全小写，而仓库源码中有大写）
_pkgname2=ChineseChess                        # 自己添加的变量 （最后项目生成的文件名）
pkgver=5.6.0                                  # 包的版本号 （不可有连字符 -）
pkgrel=1                                      # 包的发布号码
epoch=                                        # 用于强制升级软件包 （一般不允许使用）
pkgdesc="Network battle game written in Qt (available on LAN)"  # 软件包的详细描述
arch=('x86_64')                               # 包所能够生成并且使用的架构的序列
url="https://github.com/XMuli/chinessChess"   # 包的官网
license=('GPL3')                              # 采用的许可证
groups=()                                     # 软件包所在的包组
depends=()                                    # 软件包的生成和运行时，必须先行安装的软件列表
makedepends=()                                # 仅在软件生成时，需要的软件包列表
checkdepends=()                               # 运行测试组件时需要，而运行时不需要的包列表
optdepends=()                                 # 可选的软件包（可看作本软件的插件）
provides=()                                   # 说明当前包提供的功能 （若使用，则需加上替代版本号）
conflicts=()                                  # 与当前软件包发生冲突的包 与功能的列表
replaces=()                                   # 会因安装当前包而取代的过时的包的列表
backup=()                                     # 当包被升级或卸载时，应当备份的文件（的路径）序列
options=()                                    # 允许重载 makepkg 的部分 （在 /etc/makepkg.conf 中）
install=                                      # .install 脚本的名称 （值应和 pkgname 相同）
changelog=                                    # 软件包的更新日志的文件名
source=("$_pkgname-$pkgver::https://github.com/XMuli/$_pkgname/archive/v$pkgver.tar.gz")  # 源码的下载地址
noextract=()                                  # 在 source 中列出，但不应该在运行 makepkg 时被解包的文件列表
md5sums=('5abae73968ea0104e99b816bf0b720fe')  # 完整性校验值
validpgpkeys=()                               # PGP 指纹列表


prepare() {                                   # 准备
	cd $srcdir
    echo $srcdir
}

build() {                                     # 构建
	cd $_pkgname-$pkgver
	mkdir bin
    cd bin
    qmake ..
    make -j$(nproc) 
}

check() {                                     # 检查
	cd $_pkgname-$pkgver
}

package() {                                   # 包
	cd $_pkgname-$pkgver
	# make install
    cd bin/
    ./$_pkgname2
}
