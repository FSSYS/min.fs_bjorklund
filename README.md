# min.fs_bjorklund
high performance euclidean rhythm generator for Max 8.

With thanks to Zirfakend for the C++ implementation of the euclidean algorithm

https://github.com/Zirafkend/Bjorklund

and 11olsen for the testing patch euclidean_bjorklund_overview

https://11olsen.de/max-msp-externals/download/8-max-msp-examples/25-euclidean-bjorklund-algorithms

using the compare_speed page in 11olsen's patch, this compiled external completes 512 sequences in 1.3-4.7ms, 2-3x faster than the next fastest implementation, bjorklund_11olsen.maxpat, which completes in 9.7-13.9ms on my machine - your mileage may vary! It is recommended to test compiler settings for best results.

To compile yourself, follow installation instructions for the min-devkit here:

https://github.com/Cycling74/min-devkit

and build as described in the readme.
