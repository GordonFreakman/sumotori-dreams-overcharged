#include "containers.h"

#include <math.h>

// FUNCTION: SUMO 0x0040918e
// FUNCTION: EDITOR 0x004091b0
void Matrix3::Rotate(Vector3 &axis, SumoF32 cosine, SumoF32 sine) {
  Vector3 row0 = Row0();
  Vector3 row1 = Row1();
  Vector3 row2 = Row2();

  row0.Rotate(axis, cosine, sine);
  row1.Rotate(axis, cosine, sine);
  row2.Rotate(axis, cosine, sine);

  SetRow0(row0);
  SetRow1(row1);
  SetRow2(row2);
}

// FUNCTION: SUMO 0x0040925d
// FUNCTION: EDITOR 0x0040927f
void Matrix3::Rotate(Vector3 &rotation) {
  Vector3 axis = rotation;
  axis.Normalize();
  SumoF32 angle = (SumoF32)sqrt(rotation.LengthSquared());
  Rotate(axis, (SumoF32)cos(sqrt(rotation.LengthSquared())),
         (SumoF32)sin(angle));
}
