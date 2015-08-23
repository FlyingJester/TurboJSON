TurboJSON
=========

Fast JSON parser with a sensible parse tree
-------------------------------------------

* Fast Parsing, up to 200 MB of naive JSON a second
* Sensible Parse Tree, Objects are std::maps, Arrays are std::vectors, etc
* Fast C api for more time-sensitive usage

Overview
--------

TurboJSON is a fast JSON parser with a sensible parse tree. It is designed to parse at least
as fast as RapidJSON or sajson. It exposes a more sensible parser tree than some parsers such 
as RapidJSON, by using STL types.

The somewhat higher speed compared to otherwise similar JSON parsers is accomplished with
careful performance testing and use of assembly for some critical operations.

FAQ
---

<strong>Q: How do I build TurboJSON? There is no makefile/Visual Studio file!</strong>

A: You need SCons and Python 2.7 (not 3). There is a Python 2.7 installer for Windows, and 
another for SCons. You can usually get SCons from your package manager on Linux, BSD, or Haiku,
and homebrew or fink on OS X.
To build, just type `scons`.

<strong>Q: What is the license?</strong>

A: TurboJSON is licensed under the BSD 3-clause license. A copy is included in the LICENSE file.

<strong>Q: There is no ASM for (insert CPU here).</strong>

A: That's not a question :) I accept patches for any platform, even if I don't own a machine to test
it on.
I am particularly interested in getting UltraSparc, ARMv6, and PowerPC modules added. I'm also fine
with only replacing some C modules on some platforms.

<strong>Q: I don't have yasm. Can I use another assembler?</strong>

A: Yes. Adding the 'assembler' argument can override the assembler used, although only a certain syntax
is supported on each platform.
For example, if you wanted to use nasm rather than yasm, you could build with `scons assembler=nasm`.

<strong>Q: Isn't that much assembly a bad idea? Isn't it not portable?</strong>

A: You caught me! Yes, each assembly file only works on a single CPU type :)
All the assembly modules are carefully profiled to be up to an order of magnitude faster
than the C modules they complement.
Additionally, all assembly modules have counterparts in portable C that perform the same
function for platforms that are not supported otherwise. None of the library exists without a portable
C implementation.
Assembly is only used when it provides around 5x or greater performance on a particular platform. As
an example, scanning whitespace is almost 4x faster on amd64 using ASM rather than C, and finding the
end of a string literal is almost 2x faster in ASM.
