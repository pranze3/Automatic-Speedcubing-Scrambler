#include "CubeParser.h"

CubeParser::CubeParser() {
  moveCount = 0;
  currentMoveIndex = 0;
}

bool CubeParser::parse(String notation) {
  moveCount = 0;
  currentMoveIndex = 0;
  
  notation.trim();
  if (notation.length() == 0) {
    return false;
  }
  
  int start = 0;
  for (int i = 0; i < notation.length(); i++) {
    if (notation[i] == ' ' || i == notation.length() - 1) {
      int end = (i == notation.length() - 1) ? i + 1 : i;
      String move = notation.substring(start, end);
      move.trim();
      
      if (move.length() > 0 && moveCount < 100) {
        moveSequence[moveCount] = move;
        moveCount++;
      }
      
      start = i + 1;
    }
  }
  
  return moveCount > 0;
}

bool CubeParser::hasMoreMoves() {
  return currentMoveIndex < moveCount;
}

MoveCommand CubeParser::getNextMove() {
  if (currentMoveIndex >= moveCount) {
    MoveCommand invalid;
    invalid.valid = false;
    return invalid;
  }
  
  MoveCommand cmd = parseSingleMove(moveSequence[currentMoveIndex]);
  currentMoveIndex++;
  return cmd;
}

void CubeParser::reset() {
  currentMoveIndex = 0;
  moveCount = 0;
}

MoveCommand CubeParser::parseSingleMove(String move) {
  MoveCommand cmd;
  cmd.valid = false;
  
  if (move.length() == 0) {
    return cmd;
  }
  
  char faceChar = move[0];
  cmd.face = charToFace(faceChar);
  
  if (faceChar != 'R' && faceChar != 'L' && 
      faceChar != 'U' && faceChar != 'D' && faceChar != 'F' && faceChar != 'B') {
    return cmd;
  }
  
  cmd.type = parseMoveType(move);
  cmd.valid = true;
  
  return cmd;
}

Face CubeParser::charToFace(char c) {
  switch (c) {
    case 'R': return FACE_R;
    case 'L': return FACE_L;
    case 'U': return FACE_U;
    case 'D': return FACE_D;
    case 'F': return FACE_F;
    case 'B': return FACE_B;
    default: return FACE_R;
  }
}

MoveType CubeParser::parseMoveType(String move) {
  if (move.length() == 1) {
    return MOVE_CW;
  }
  
  if (move[1] == '\'' || move[1] == 'i') {
    return MOVE_CCW;
  }
  
  if (move[1] == '2') {
    return MOVE_DOUBLE;
  }
  
  return MOVE_CW;
}

