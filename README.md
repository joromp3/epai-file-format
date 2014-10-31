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

At this stage, the specification and implementation are still in draft
stage and incomplete. They may change at any time, and the code here is
unstable and in early stages of development.

This repository will contain the reference implementation of the format,
including a general purpose library, and encoding/decoding utilities.
