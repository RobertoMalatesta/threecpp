/*
 * Ojbect3D.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include <three/core/Object3D.h>

#include <stdexcept>
#include <algorithm>

namespace three {

const Vector3 Object3D::DefaultUp { 0, 1, 0 };
const bool Object3D::DefaultMatrixAutoUpdate { true };

unsigned long long Object3D::object3DId = 0;

Object3D::Object3D() :
    id_(object3DId++) {

  //TODO(zxi) UUID

  this->rotation.onChanged([this] {
    this->quaternion.setFromEular(this->rotation);
  });

  this->quaternion.onChanged([this]{
    //TODO(zxi) set rotation fron qu
  });
}

Object3D::~Object3D() {
}


Object3D& Object3D::add(Object3D* child) {
  if (child == this) {
    return *this;
  }

  if (!child) {
    throw std::invalid_argument("child is null.");
  }

  if (child->parent) {
    child->parent->remove(child);
  }

  child->parent = this;
  // TODO(zxi) dispatch event

  this->children.push_back(child);

  return *this;
}

void Object3D::traverse(std::function<void(Object3D* object)> callback) {
  callback(this);

  for (Object3D* child : children)
    child->traverse(callback);
}

void Object3D::traverseVisible(std::function<void(Object3D* object)> callback) {
  if (!this->visible)
    return;
  callback(this);

  for (Object3D* child : children)
    child->traverseVisible(callback);
}

Object3D& Object3D::remove(Object3D* child) {
  if (!child) {
    return *this;
  }

  auto it = std::find(this->children.begin(), this->children.end(), child);
  if (it != children.end()) {
    child->parent = nullptr;
    this->children.erase(it);
  }

  return *this;
}

///////////////////////////////////////////////////////////////////////////////
// update the matrix of the object
void Object3D::updateMatrix() {

  this->matrix.asCompose(this->position, this->quaternion, this->scale);
  this->matrixWorldNeedsUpdate = true;
}

void Object3D::updateMatrixWorld(bool force) {
  if (this->matrixAutoUpdate)
    this->updateMatrix();

  if (this->matrixWorldNeedsUpdate || force) {
    if (this->parent == nullptr) {
      this->matrixWorld = this->matrix;
    } else {
      this->matrixWorld = this->parent->matrixWorld * this->matrix;
    }

    this->matrixWorldNeedsUpdate = false;

    force = true;
  }

  // Update children
  for (auto child : this->children) {
    child->updateMatrixWorld(force);
  }
}

}/* namespace three */
