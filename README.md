# Mini chess

Mini chess is a simple chess engine for 5x6 game variation.

# Game rules

1. This variation is played on a board with 5 files and 6 ranks.
2. Starting position:
    - Ranks 2 and 5 are all pawns
    - The players agree on which 4 pieces from the set (1 queen, 2 rooks, 2 knights and 2 bishops) to play with
    - Each player arranges pieces as well as the king on their side (rank 1 for white and rank 6 for black)
3. Pawns have no 2-square push option, therefore no en-passant option either. Other pieces move the same way they do in
classical chess
4. Pawns can promote to only those pieces that were chosen to play with
5. If there is a king in the center, a rook in the corner and they both did not move, castling is allowed: the king moves 1
square towards the rook and the rook moves 2 squares towards the king. King must not be in check at the beginning and at the end
of the castling
6. The threefold repetition and the 50-move rule apply
