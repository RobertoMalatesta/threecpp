/*
 * Face3.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef THREE_CORE_FACE3_H_
#define THREE_CORE_FACE3_H_

#include <vector>

#include <three/math/Vector3.h>
#include <three/math/Color.h>

namespace three {

class Face3 {
public:
  Face3() = delete;
  Face3(int a, int b, int c);
  Face3(int a, int b, int c, const Vector3& normal);

  Face3(const Face3& f) = default;
  Face3(Face3&& f) = default;

  Face3& operator=(const Face3& f) = default;

  ~Face3();

  int a { -1 };
  int b { -1 };
  int c { -1 };
  Vector3 normal;

  Color color;

  std::vector<Vector3> vertexNormals;
  std::vector<Color> vertexColors;

  int materialIndex { 0 };
};

} /* namespace three */

#endif /* THREE_CORE_FACE3_H_ */
