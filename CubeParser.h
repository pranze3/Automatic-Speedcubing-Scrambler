#ifndef CUBEPARSER_H
#define CUBEPARSER_H

#include <Arduino.h>

enum Face {
  FACE_R,  // right
  FACE_L,  // left
  FACE_U,  // up
  FACE_D,  // down
  FACE_F,  // front
  FACE_B   // back
};

enum MoveType {
  MOVE_CW,      // clockwise (R, U, F, etc)
  MOVE_CCW,     // counter-clockwise (R', U', F', etc)
  MOVE_DOUBLE   // double turn (R2, U2, F2, etc)
};

struct MoveCommand {
  Face face;
  MoveType type;
  bool valid;
};

class CubeParser {
public:
  CubeParser();
  bool parse(String notation);
  bool hasMoreMoves();
  MoveCommand getNextMove();
  void reset();
  
private:
  String moveSequence[100];
  int moveCount;
  int currentMoveIndex;
  
  MoveCommand parseSingleMove(String move);
  Face charToFace(char c);
  MoveType parseMoveType(String move);
};

#endif

