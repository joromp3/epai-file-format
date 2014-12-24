# Extensible/Embedded Package for Animated Images

This is a file format which is somewhat inspired by PNG, but intended
for a different purpose/audience. It is a generalization that is
designed for use in games and easy to optimize on embedded platforms.

The major design goals are simplicity, extensibility, ease of
implementation, and performance.

The format allows for multiple images (optionally animated) to be
packaged in one file. Every image can use a different pixel format if
needed, and integer/float with varying precision can be used for
different channels in the same image. Every pixel can carry multiple
channels to accomodate for extra information such as alpha, depth
normals, diffuse/specularity, etc alongside the color information.

Currently, the specification and implementation are still in draft stage
and incomplete. They may change at any time, and the code here is
unstable and in early stages of development. The API constantly changes.
For now, all definitions in the library are made public through the main
header, to help with testing and development. As time passes and things
stabilize, a lot of them will become internal and a more streamlined
public interface will be designed.

The library currently only encodes to and decodes from memory buffers,
as it is easier to develop and test the code this way. This, however, is
not scalable to production scenarios where large files with large images
can be used. As the code matures, a more flexible encode/decode mode
using file I/O will be added.

This repository will contain the reference implementation of the format,
including a general purpose library, and encoding/decoding utilities.

The following subdirectories exist in this repository:
- doc/ - file format specification and other documentation.
- lib/ - libepai: general-purpose library.
- enc/ - epaienc: CLI encoding utility.
- dec/ - epaidec: CLI decoding utility.
- poke/ - epaipoke: CLI util for poking low-level aspects of EPAI files,
  to tweak, fix, and help with debugging.
- chk/ - epaichk: CLI utility to check EPAI files for corruption/errors.
- txt/ - epaitxt: CLI utility to produce plain text dumps of EPAI file
  data, and recreate EPAI files based on the text representation; useful
  for manually creating test cases.


This project uses GNU Autotools. To build from git, clone and run:

```
$ autoreconf --install
$ ./configure --prefix=/install/path/dir
$ make install
```

