#include "game_runtime.h"

// FUNCTION: SUMO 0x004083df
// FUNCTION: EDITOR 0x00408401
Vector3 GameBox::VelocityAtPoint(Vector3& point)
{
  if (flagD0) {
    Vector3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    return zero;
  }

  return linearVelocity + (point - position).Cross(angularVelocity);
}

// FUNCTION: SUMO 0x00408481
// FUNCTION: EDITOR 0x004084a3
Vector3 GameBox::CalculateImpulseResponse(Vector3& impulsePoint,
                                          Vector3& impulse,
                                          Vector3& samplePoint)
{
  return impulse.Scale(inverseMass) +
         (impulsePoint - position)
           .Cross(impulse)
           .Cross(samplePoint - position)
           .Scale(inverseInertia);
}

// FUNCTION: SUMO 0x004084fe
// FUNCTION: EDITOR 0x00408520
Matrix3 GameBox::CalculateImpulseResponseMatrix(Vector3& impulsePoint,
                                                Vector3& samplePoint)
{
  Matrix3 matrix;
  Vector3 response;
  response.x = 1.0f;
  response.y = 0.0f;
  response.z = 0.0f;
  Vector3 impulse = response;
  response = CalculateImpulseResponse(impulsePoint, impulse, samplePoint);
  matrix.m00 = response.x;
  matrix.m01 = response.y;
  matrix.m02 = response.z;

  response.x = 0.0f;
  response.y = 1.0f;
  response.z = 0.0f;
  impulse = response;
  response = CalculateImpulseResponse(impulsePoint, impulse, samplePoint);
  matrix.m10 = response.x;
  matrix.m11 = response.y;
  matrix.m12 = response.z;

  response.x = 0.0f;
  response.y = 0.0f;
  response.z = 1.0f;
  impulse = response;
  response = CalculateImpulseResponse(impulsePoint, impulse, samplePoint);
  matrix.m20 = response.x;
  matrix.m21 = response.y;
  matrix.m22 = response.z;
  return matrix;
}

// FUNCTION: SUMO 0x004085f0
// FUNCTION: EDITOR 0x00408612
void GameBox::ApplyImpulseAtPoint(Vector3& point, Vector3& impulse)
{
  if (!flagD0) {
    Vector3 angularDelta;
    angularDelta = (point - position).Cross(impulse).Scale(inverseInertia);
    Vector3* angular = &angularVelocity;
    angular->x -= angularDelta.x;
    angular->y -= angularDelta.y;
    angular->z -= angularDelta.z;

    linearVelocity += impulse.Scale(inverseMass);
  }
}
