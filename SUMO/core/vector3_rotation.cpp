#include "containers.h"

#include <math.h>

// FUNCTION: SUMO 0x00402e1d
// FUNCTION: EDITOR 0x00402e1d
void Vector3::Rotate(Vector3& axis, SumoF32 cosine, SumoF32 sine)
{
  SumoF32 projection = axis.Dot(*this) * (1.0f - cosine);
  *this = Scale(cosine) +
          axis.Scale(projection) +
          Cross(axis).Scale(sine);
}

// FUNCTION: SUMO 0x00402ea2
// FUNCTION: EDITOR 0x00402ea2
void Vector3::Rotate(Vector3& rotation)
{
  Vector3 axis = rotation;
  axis.Normalize();
  Rotate(axis,
         (SumoF32) cos(sqrt(rotation.LengthSquared())),
         (SumoF32) sin(sqrt(rotation.LengthSquared())));
}
