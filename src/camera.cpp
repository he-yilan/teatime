#include "camera.h"

void Camera::configure(size_t screenW, size_t screenH) {
  this->screenW = screenW;
  this->screenH = screenH;
  nClip = 0.01;
  fClip = 10000;
  hFov = 50;
  vFov = 35;

  double ar1 = tan(radians(hFov) / 2) / tan(radians(vFov) / 2);
  ar = static_cast<double>(screenW) / screenH;
  if (ar1 < ar) {
    // hFov is too small
    hFov = 2 * degrees(atan(tan(radians(vFov) / 2) * ar));
  } else if (ar1 > ar) {
    // vFov is too small
    vFov = 2 * degrees(atan(tan(radians(hFov) / 2) / ar));
  }
  screenDist = ((double)screenH) / (2.0 * tan(radians(vFov) / 2));
}

void Camera::place(const Vector3D &targetPos, const double phi,
                   const double theta, const double r, const double minR,
                   const double maxR) {
  double r_ = std::min(std::max(r, minR), maxR);
  double phi_ = (sin(phi) == 0) ? (phi + FLT_EPSILON) : phi;
  this->targetPos = targetPos;
  this->phi = phi_;
  this->theta = theta;
  this->r = r_;
  this->minR = minR;
  this->maxR = maxR;
  compute_position();
}

void Camera::set_screen_size(const size_t screenW, const size_t screenH) {
  this->screenW = screenW;
  this->screenH = screenH;
  ar = 1.0 * screenW / screenH;
  hFov = 2 * degrees(atan(((double)screenW) / (2 * screenDist)));
  vFov = 2 * degrees(atan(((double)screenH) / (2 * screenDist)));
}

void Camera::move_by(const double dx, const double dy, const double d) {
  const double scaleFactor = d / screenDist;
  const Vector3D &displacement =
      c2w[0] * (dx * scaleFactor) + c2w[1] * (dy * scaleFactor);
  pos += displacement;
  targetPos += displacement;
}

void Camera::move_forward(const double dist) {
  double newR = std::min(std::max(r - dist, minR), maxR);
  pos = targetPos + ((pos - targetPos) * (newR / r));
  r = newR;
}

void Camera::rotate_by(const double dPhi, const double dTheta) {
  phi = clamp(phi + dPhi, 0.0, (double)PI);
  theta += dTheta;
  compute_position();
}

void Camera::compute_position() {
  double sinPhi = sin(phi);
  if (sinPhi == 0) {
    phi += FLT_EPSILON;
    sinPhi = sin(phi);
  }
  const Vector3D dirToCamera(r * sinPhi * sin(theta), r * cos(phi),
                             r * sinPhi * cos(theta));
  pos = targetPos + dirToCamera;
  Vector3D upVec(0, sinPhi > 0 ? 1 : -1, 0);
  Vector3D screenXDir = cross(upVec, dirToCamera);
  screenXDir.normalize();
  Vector3D screenYDir = cross(dirToCamera, screenXDir);
  screenYDir.normalize();

  c2w[0] = screenXDir;
  c2w[1] = screenYDir;
  c2w[2] = dirToCamera.unit(); // camera's view direction is the
                               // opposite of of dirToCamera, so
                               // directly using dirToCamera as
                               // column 2 of the matrix takes [0 0 -1]
                               // to the world space view direction
}

Matrix4f Camera::getProjectionMatrix() {
  Matrix4f perspective;
  perspective.setZero();

  double theta = vFov * PI / 360;
  double range = fClip - nClip;
  double invtan = 1. / tanf(theta);

  return {
          invtan / ar, 0, 0, 0,
          0, invtan, 0, 0,
          0, 0, -(nClip + fClip) / range, -2 * nClip * fClip / range,
          0, 0, -1, 0
  };

  return perspective;
}

Matrix4f Camera::getViewMatrix() {
  Matrix4f lookAt;
  Matrix3f R;

  lookAt.setZero();

  // Convert CGL vectors to Eigen vectors
  // TODO: Find a better way to do this!

  CGL::Vector3D c_udir = c2w[1];

  Vector3f eye(pos.x, pos.y, pos.z);
  Vector3f up(c_udir.x, c_udir.y, c_udir.z);
  Vector3f target(targetPos.x, targetPos.y, targetPos.z);

  R.col(2) = (eye - target).normalized();
  R.col(0) = up.cross(R.col(2)).normalized();
  R.col(1) = R.col(2).cross(R.col(0));

  lookAt.topLeftCorner<3, 3>() = R.transpose();
  lookAt.topRightCorner<3, 1>() = -R.transpose() * eye;
  lookAt(3, 3) = 1.0f;

  return lookAt;
}
