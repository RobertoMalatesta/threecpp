/*
 * Vector3.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include "math/Vector3.h"

namespace three {

Vector3::Vector3() {

}

Vector3::Vector3(double x, double y, double z) {
  this->set(x, y, z);
}

Vector3::Vector3(const Vector3& v) {
  this->set(v.x, v.y, v.z);
}

inline Vector3& Vector3::set(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;

  return *this;
}

Vector3::~Vector3() {

}

} /* namespace three */