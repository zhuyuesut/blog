---

layout: post
title: "在macOS上使用brew home的纪录"
author: Zhu Yue

---

今天正准备看《Ｃ++ Ｐrimer》中文第五版，由于系统里面的*gcc*实际上*clang*，想到了在自己电脑上安装*gcc*

```
zhuyue@zhuyue:~|⇒  gcc --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/usr/include/c++/4.2.1
Apple LLVM version 7.3.0 (clang-703.0.31)
Target: x86_64-apple-darwin16.0.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

安装时遇到如下问题：

```
zhuyue@zhuyue:~|⇒  brew install gcc
Warning: You are using OS X 10.12.
We do not provide support for this pre-release version.
You may encounter build failures or other breakages.
Please create pull-requests instead of filing issues.
==> Installing dependencies for gcc: mpfr, libmpc, isl
==> Installing gcc dependency: mpfr
==> Downloading https://mirrors.ocf.berkeley.edu/debian/pool/main/m/mpfr4/mpfr4
Already downloaded: /Users/zhuyue/Library/Caches/Homebrew/mpfr-3.1.4.tar.xz
==> Downloading https://raw.githubusercontent.com/Homebrew/formula-patches/3014
Already downloaded: /Users/zhuyue/Library/Caches/Homebrew/mpfr--patch-9a03c3f304feaff747d1832f4a0f3653bbd24764df403305add0b76ca6cd6541.diff
==> Patching
==> Applying 3.1.4-patches.diff
patching file PATCHES
patching file VERSION
patching file src/mpfr-impl.h
patching file src/mpfr.h
patching file src/version.c
==> ./configure --prefix=/usr/local/Cellar/mpfr/3.1.4 --disable-silent-rules
Last 15 lines from /Users/zhuyue/Library/Logs/Homebrew/mpfr/01.configure:
checking whether make supports nested variables... yes
checking whether to enable maintainer-specific portions of Makefiles... yes
checking build system type... x86_64-apple-darwin16.0.0
checking host system type... x86_64-apple-darwin16.0.0
checking for grep that handles long lines and -e... /usr/bin/grep
checking for egrep... /usr/bin/grep -E
checking for a sed that does not truncate output... /usr/local/Library/Homebrew/shims/super/sed
checking for gcc... clang
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables...
checking whether we are cross compiling... configure: error: in `/private/tmp/mpfr-20160726-19392-gtr6e3/mpfr-3.1.4':
configure: error: cannot run C compiled programs.
If you meant to cross compile, use `--host'.
See `config.log' for more details

READ THIS: https://git.io/brew-troubleshooting
If reporting this issue please do so at (not Homebrew/brew):
https://github.com/Homebrew/homebrew-core/issues

...
```

初步诊断是由于我升级了*macOS*系统，也就是OS X 10.12

Google brew home on macOS，传送至这里 https://github.com/Homebrew/brew/issues/364，内容大概如下：

```
Support for macOS (OS X) 10.12.0 #364

[ yep ] Ran brew update and retried your prior step?
[ yep ] Ran brew doctor, fixed as many issues as possible and retried your prior step?
[ yep ] If you're seeing permission errors tried running sudo chown -R $(whoami) $(brew --prefix)?

Bug reports:

Add support for macOS 10.12.0 
When installing/updating/upgrading any taps, you get the following 
Warning: You are using OS X 10.12. We do not provide support for this pre-release version. You may encounter build failures or other breakages.
```

＊ ``brew update`` 命令每次使用必敲
＊ ``sudo chown -R $(whoami) $(brew --prefix)`` 重装升级系统必敲
＊ ``brew doctor`` 命令结果如下：

```
zhuyue@zhuyue:~|⇒  brew doctor
Please note that these warnings are just used to help the Homebrew maintainers
with debugging if you file an issue. If everything you use Homebrew for is
working fine: please don't worry and just ignore them. Thanks!

Warning: You are using OS X 10.12.
We do not provide support for this pre-release version.
You may encounter build failures or other breakages.
Please create pull-requests instead of filing issues.

Warning: Your Xcode (7.3.1) is outdated
Please update to Xcode 8.0.
Xcode can be updated from
https://developer.apple.com/xcode/downloads/
```

第一个warning暂时解决不了，macOS还没稳定，大家都在努力。

我访问了苹果[网站](https://developer.apple.com/xcode/downloads/ )发现Xcode 8.0指的是我已经安装的Xcode Beta.app，版本为（Version 8.0 beta 3 (8S174q)）

再回头一看``gcc --version``命令的输出，嗯，可能是*homebrew*没发现*Xcode 8.0*的存在，另附输出如下：

```
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/usr/include/c++/4.2.1
Apple LLVM version 7.3.0 (clang-703.0.31)
Target: x86_64-apple-darwin16.0.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

UI界面更改如下（中途需要输入密码）：

![use ui set xcode 7.3 to 8.0](/assets/img/use-ui-set-xcode-to-8.0.png)

(据说用``xcode-select``命令也能改，但我没有尝试)

之后测试如下：

```
zhuyue@zhuyue:~|⇒  gcc --version
Configured with: --prefix=/Applications/Xcode-beta.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode-beta.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include/c++/4.2.1
Apple LLVM version 8.0.0 (clang-800.0.33.1)
Target: x86_64-apple-darwin16.0.0
Thread model: posix
InstalledDir: /Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```
```
zhuyue@zhuyue:~|⇒  brew doctor
Please note that these warnings are just used to help the Homebrew maintainers
with debugging if you file an issue. If everything you use Homebrew for is
working fine: please don't worry and just ignore them. Thanks!

Warning: You are using OS X 10.12.
We do not provide support for this pre-release version.
You may encounter build failures or other breakages.
Please create pull-requests instead of filing issues.
```

``brew upgrade``与``brew install gcc``两个命令均能正常使用，功能正常（不知道编译比原来慢很多是不是我的错觉）

至此问题解决。

不过macOS确实够折腾一阵的，如图：

![old MOU.app can't be use in macOS](/assets/img/old-mou-can-not-use-on-macOS.png)

