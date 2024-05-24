<!-- Makefile -->
<!-- Copyright (c) 2024 Ishan Pranav -->
<!-- Licensed under the MIT license. -->

# Snake

The Snake Chess engine is based on the techniques described in the
[Bitboard chess engine in C](https://youtu.be/QUNP-UjujBM) video series and on
the [chess programming wiki](https://www.chessprogramming.org/).

## Components

- **Board representation:** [bitboards](https://www.chessprogramming.org/Bitboards)
per piece and color indexed from squares A8 to H1.
- **Move generation:** [magic bitboards](https://www.chessprogramming.org/Magic_Bitboards)
- **Search:** [negamax](https://www.chessprogramming.org/Negamax) with
[alpha-beta pruning](https://www.chessprogramming.org/Alpha-Beta)
- **Evaluation:** [material evaluation](https://www.chessprogramming.org/Material)
ane [piece-square tables](https://www.chessprogramming.org/Piece-Square_Tables)

To visualize and understand the magic constants involved in bitboard
manipulation, I have created a companion web application available
[here](https://ishanpranav.github.io/snake-chess/).

## License

This repository is licensed with the [MIT](LICENSE.txt) license.

## Thanks

I'd like to thank Kaylee Kim, Eric Ho, and Aren Balian for supporting me on my
journey (descent?) into the madness of bitboards. "Project Snake" began as our
high-school aspiration in Irvine, California. This software hopes to make that
vision a reality in the form of a working UCI-compatible chess engine.

## Attribution

This software uses third-party libraries or other resources that may be
distributed under licenses different than the software. Please see the
third-party notices included [here](THIRD-PARTY-NOTICES.md).
