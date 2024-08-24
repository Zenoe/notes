## Mindfulness meditation
emacs leverage treesitter to edit
filter out something like import xxx from goto defition list


## js

链接：https://www.zhihu.com/question/429436558/answer/1572099805
读 Node.js 和 Txiki 运行时的源码，参考它们的方式调 libuv 来搭 JS 的 event loop。
读 Skia 配套的 canvas2dcontext.js 源码，照着用 C++ 实现 Canvas 的 eclipse 方法。
读 QuickJS 配套的 quickjs-libc 源码，照着实现对 JS 原生 class 的封装。
读 Flutter Tool 的源码，把它调 Dart 编译服务的参数扒出来，编译出二进制 AST 文件自己用。
读 Three 的源码，学着它引入 WeakMap 解决纹理资源管理的问题。
读 Slate 富文本框架的源码，修它 IME 和选区的 bug（太多了修不完）。
读 Pica（基于 lanczos 的图片缩放库）的源码，解决它处理特殊尺寸图片报错的问题。
读 PBR 标准的 shader 源码，照着定制 3D 文字的渲染算法。
读 Photopea 的 shader 源码（需要 monkey-patch 一下），看它是怎么在 WebGL 和 canvas 之间无缝切换的
Internet OS: https://github.com/HeyPuter/puter

如果想高效学习技术，一定要尽可能找到最高层面，最易于理解的信息源。比如对于和 Chromium、V8 等谷歌系项目深度绑定的 [Ninja](https://aosabook.org/en/posa/ninja.html) 构建系统
我之前一直搞不懂它为什么要做成那样，直到偶然读到作者自述的设计理念以后，一下就豁然开朗了。这比上来就翻它的源码然后苦思冥想地倒推「这玩意到底想干嘛」要直接而方便得多。
